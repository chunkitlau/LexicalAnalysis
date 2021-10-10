#include "lexicalAnalysis.hpp"

/****************************************************************
 * main
 */
int main(int argc, char* argv[]) {
    std::string programName("hello");

    int c = 0; 
    while(EOF != (c = getopt(argc,argv,"p:"))){
        switch(c){
            case 'p':
                programName = optarg;
                break;
            case '?':
                printf("-p <file>.c to specify demo program file\n");
                break;
            default:
                break;
        }
    }

    // Plan a: Don't work.
    std::string programPath("./demo/" + programName + ".c");
    program.open(programPath.c_str());

    // Plan b: Work.
    freopen(programPath.c_str(), "r", stdin);

    std::string resultPath("./result/" + programName + ".txt");
    result.open(resultPath.c_str());

    lexicalAnalysis();
    
    result << "****************************************************************" << std::endl
           << "Lexical analysis compleated. Source program has " << line << " lines." << std::endl
           << "Token type count:" << std::endl
           << typeCount2str()
           << "Total " << character << " characters." << std::endl
           << "****************************************************************" << std::endl
           << "Error info:" << std::endl
           << error << std::endl;

    std::cout << "****************************************************************" << std::endl
           << "Lexical analysis compleated. Source program has " << line << " lines." << std::endl
           << "Token type count:" << std::endl
           << typeCount2str()
           << "Total " << character << " characters." << std::endl
           << "****************************************************************" << std::endl
           << "Error info:" << std::endl
           << error << std::endl
           << "****************************************************************" << std::endl
           << "Find detail infomation at ./result/" + programName + ".txt" << std::endl;

    program.close();
    result.close();
}

/****************************************************************
 * lexicalAnalysis
 */
int lexicalAnalysis() {
    state = START;
    do {
        switch (state) {
        // Inital state
        case START:
            token = "";
            getChar();
            getNbc();
            if (isLetter()) {
                state = RID;
            }
            else if (isDigit()) {
                state = NUM1;
            }
            else {
                switch (ch) {
                case '+': state = PLUS; break;
                case '-': state = MINUS; break;
                case '*': state = STAR; break;
                case '/': state = SLASH; break;
                case '%': state = MOD; break;
                case '=': state = EQUAL; break;
                case '!': state = BANG; break;
                case '<': state = GREATER; break;
                case '>': state = SMALLER; break;
                case '&': state = AND; break;
                case '|': state = OR; break;
                case '^': state = CARET; break;
                case '"': state = RSTRING; break;
                case '#': state = RPREPROCESS; break;
                case '~': state = START; returnToken(OP); break;
                case '?': state = START; returnToken(OP); break;
                case ':': state = START; returnToken(OP); break;
                case '(': state = START; returnToken(SINGLE); break;
                case ')': state = START; returnToken(SINGLE); break;
                case '[': state = START; returnToken(SINGLE); break;
                case ']': state = START; returnToken(SINGLE); break;
                case '{': state = START; returnToken(SINGLE); break;
                case '}': state = START; returnToken(SINGLE); break;
                case '.': state = START; returnToken(SINGLE); break;
                case ',': state = START; returnToken(SINGLE); break;
                case ';': state = START; returnToken(SINGLE); break;
                case '\n': state = START; break;
                case EOF: break;
                default: 
                    // Handle returnError
                    returnError();
                    state = START;
                    break;
                }
            }
            break;

        // ID state
        case RID:
            cat();
            getChar();
            if (isLetter() || isDigit()) {
                state = RID;
            }
            else {
                retract();
                state = START;
                isKey = isReserve();
                if (isKey) {
                    returnToken(KEYWORD);
                }
                else {
                    tableInsert();
                    returnToken(ID);
                }
            }
            break;

        // Int state
        case NUM1:
            cat();
            getChar();
            if (isDigit()) {
                state = NUM1;
            }
            else if (isLetter() && (ch != '_') && (ch != 'E')) {
                retract();
                state = START;
                returnError();
            }
            else {
                switch (ch) {
                case '.': state = NUM2; break;
                case 'E': state = NUM4; break;
                default: 
                    retract();
                    state = START;
                    returnToken(INT);
                    break;
                }
            }
            break;

        // Float point state
        case NUM2:
            cat();
            getChar();
            if (isDigit()) {
                state = NUM3;
            }
            else {
                returnError();
                state = START;
            }
            break;

        // Float state
        case NUM3:
            cat();
            getChar();
            if (isDigit()) {
                state = NUM3;
            }
            else if (isLetter() && (ch != '_') && (ch != 'E')) {
                retract();
                state = START;
                returnError();
            }
            else {
                switch (ch) {
                case 'E': state = NUM4; break;
                default: 
                    retract();
                    state = START;
                    returnToken(FLOAT);
                    break;
                }
            }
            break;

        // Float exponent state
        case NUM4:
            cat();
            getChar();
            if (isDigit()) {
                state = REMAINDER;
            }
            else {
                switch (ch) {
                case '+': 
                case '-': state = DIGITS; break;
                default: 
                    retract();
                    returnError();
                    state = START;
                    break;
                }
            }
            break;

        // Float digits state
        case DIGITS:
            cat();
            getChar();
            if (isDigit()) {
                state = REMAINDER;
            }
            else {
                retract();
                returnError();
                state = START;
            }
            break;

        // Float remainder state
        case REMAINDER:
            cat();
            getChar();
            if (isDigit()) {
                state = REMAINDER;
            }
            else {
                retract();
                state = START;
                returnToken(FLOAT);
            }
            break;
        
        // Plus state
        case PLUS:
            cat();
            getChar();
            switch (ch) {
            case '+': state = START; returnToken(OP); break;
            case '=': state = START; returnToken(OP); break;
            default:
                retract();
                state = START;
                returnToken(OP);
                break;
            }
            break;

        // Minus state
        case MINUS:
            cat();
            getChar();
            switch (ch) {
            case '-': state = START; returnToken(OP); break;
            case '=': state = START; returnToken(OP); break;
            default:
                retract();
                state = START;
                returnToken(OP);
                break;
            }
            break;

        // Star state
        case STAR:
            cat();
            getChar();
            switch (ch) {
            case '=': state = START; returnToken(OP); break;
            default:
                retract();
                state = START;
                returnToken(OP);
                break;
            }
            break;

        // Slash state
        case SLASH:
            cat();
            getChar();
            switch (ch) {
            case '=': state = START; returnToken(OP); break;
            case '/': state = SLASH1; break;
            case '*': state = STAR1; break;
            default:
                retract();
                state = START;
                returnToken(OP);
                break;
            }
            break;

        // Slash slash state
        case SLASH1:
            cat();
            getChar();
            switch (ch) {
            case '\n': state = START; ch = token.back(); token.pop_back(); returnToken(NOTE); break;
            default:
                state = SLASH1;
                break;
            }
            break;

        // Slash star state
        case STAR1:
            cat();
            getChar();
            switch (ch) {
            case '*': state = STAR2; break;
            default:
                state = STAR1;
                break;
            }
            break;

        // Slash star ... star state
        case STAR2:
            cat();
            getChar();
            switch (ch) {
            case '/': state = START; returnToken(NOTE); break;
            default:
                state = STAR1;
                break;
            }
            break;

        // Mod state
        case MOD:
            cat();
            getChar();
            switch (ch) {
            case '=': state = START; returnToken(OP); break;
            default:
                retract();
                state = START;
                returnToken(OP);
                break;
            }
            break;

        // Equal state
        case EQUAL:
            cat();
            getChar();
            switch (ch) {
            case '=': state = START; returnToken(OP); break;
            default:
                retract();
                state = START;
                returnToken(OP);
                break;
            }
            break;

        // Bang state
        case BANG:
            cat();
            getChar();
            switch (ch) {
            case '=': state = START; returnToken(OP); break;
            default:
                retract();
                state = START;
                returnToken(OP);
                break;
            }
            break;

        // Greater state
        case GREATER:
            cat();
            getChar();
            switch (ch) {
            case '=': state = START; returnToken(OP); break;
            case '>': state = RSHIFT; break;
            default:
                retract();
                state = START;
                returnToken(OP);
                break;
            }
            break;

        // Rshift state
        case RSHIFT:
            cat();
            getChar();
            switch (ch) {
            case '=': state = START; returnToken(OP); break;
            default:
                retract();
                state = START;
                returnToken(OP);
                break;
            }
            break;

        // Smaller state
        case SMALLER:
            cat();
            getChar();
            switch (ch) {
            case '=': state = START; returnToken(OP); break;
            case '<': state = LSHIFT; break;
            default:
                retract();
                state = START;
                returnToken(OP);
                break;
            }
            break;

        // Lshift state
        case LSHIFT:
            cat();
            getChar();
            switch (ch) {
            case '=': state = START; returnToken(OP); break;
            default:
                retract();
                state = START;
                returnToken(OP);
                break;
            }
            break;

        // And state
        case AND:
            cat();
            getChar();
            switch (ch) {
            case '&': state = START; returnToken(OP); break;
            case '=': state = START; returnToken(OP); break;
            default:
                retract();
                state = START;
                returnToken(OP);
                break;
            }
            break;

        case OR:
            cat();
            getChar();
            switch (ch) {
            case '|': state = START; returnToken(OP); break;
            case '=': state = START; returnToken(OP); break;
            default:
                retract();
                state = START;
                returnToken(OP);
                break;
            }
            break;

        case CARET:
            cat();
            getChar();
            switch (ch) {
            case '=': state = START; returnToken(OP); break;
            default:
                retract();
                state = START;
                returnToken(OP);
                break;
            }
            break;

        case RSTRING:
            cat();
            getChar();
            switch (ch) {
            case '"': state = START; returnToken(STRING); break;
            case '\n': state = START; returnError(); break;
            default:
                state = RSTRING;
                break;
            }
            break;

        case RPREPROCESS:
            cat();
            getChar();
            switch (ch) {
            case '\n': state = START; ch = token.back(); token.pop_back(); returnToken(PREPROCESS); break;
            default:
                state = RPREPROCESS;
                break;
            }
            break;

        default:
            returnError();
            state = START;
            break;
        }
    }while (ch != EOF);
    return 0;
}

/****************************************************************
 * Unities
 */

/****************************************************************
 * Read char from program.
 */
int getChar() {
    if (!isRetract) {
        // Plan a: Don't work.
        // program >> ch;

        // Plan b: Work.
        ch = getchar();
        ++character;
    }
    else {
        isRetract = 0;
        ch = chRetract;
    }
    if (ch != '\n') {
        ++column;
    }
    else {
        ++line;
        column = 1;
    }
    return 0;
}

/****************************************************************
 * Make ch non-space char.
 */
int getNbc() {
    //getChar();
    while (ch == ' ') {
        getChar();
    }
    return 0;
}

/****************************************************************
 * Cat token and ch.
 */
int cat() {
    token.push_back(ch);
    return 0;
}

/****************************************************************
 * Return 1 if ch is 'a'~'z', 'A'~'Z' or '_'.
 */
bool isLetter() {
    return (('a' <= ch) && (ch <= 'z')) || 
           (('A' <= ch) && (ch <= 'Z')) || 
           (ch == '_');
}

/****************************************************************
 * Return 1 if ch is '0'~'9'.
 */
bool isDigit() {
    return ('0' <= ch) && (ch <= '9');
}

/****************************************************************
 * retract
 */
int retract() {
    if (column > 1) {
        --column;
    }
    else {
        return 1;
    }
    isRetract = 1;
    chRetract = ch;
    ch = token.back();
    token.pop_back();
    return 0;
}

/****************************************************************
 * Return 1 if token is keyword.
 */
bool isReserve() {
    return keyword.find(token + ch) != keyword.end();
}

/****************************************************************
 * Return token as int.
 */
int SToI() {
    return std::stoi(token);
}

/****************************************************************
 * Return token as float.
 */
float SToF() {
    return std::stof(token);
}

/****************************************************************
 * Insert token to table.
 */
int tableInsert() {
    table.push_back(token);
    return 0;
}

/****************************************************************
 * Handle error.
 */
int returnError() {
    error += "ERROR at Ln " + std::to_string(line) + ", Col " + std::to_string(column) + "\n";
    return 0;
}

/****************************************************************
 * Handle return.
 * Token = Token + ch
 */
int returnToken(int type) {
    ++typeCount[type];
    result << "Find token <" << type2str(type) << ", " << token << ch << "> " << 
        "at Ln " << line << ", Col " << column << std::endl;
    return 0;
}

/****************************************************************
 * typeCount2str.
 */
std::string typeCount2str() {
    std::string result;
    for (std::map<int, int>::iterator it = typeCount.begin(); it != typeCount.end(); ++it) {
        result += type2str(it->first) + ": " + std::to_string(it->second) + "\n";
    }
    return result;
}