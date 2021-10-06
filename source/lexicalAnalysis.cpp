#include "lexicalAnalysis.hpp"

/****************************************************************
 * main
 */
int main(int argc, char* argv[]) {
    std::string programPath("../demo/hello.c");
    program.open(programPath);

    std::string resultPath("../result/hello.txt");
    result.open(resultPath);

    lexicalAnalysis();

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
        case START:
            token = "";
            getChar();
            getNbc();
            if (isLetter(ch)) {
                state = ID;
            }
            else if (isDigit(ch)) {
                state = DIGITS;
            }
            break;

        case ID:
            cat();
            getChar();
            if (isLetter(ch)) {
                state = ID;
            }
            else if (isDigit(ch)) {
                state = DIGITS;
            }
            break;

        default:
            break;
        }
    }while (ch != EOF);
}

/****************************************************************
 * Unities
 */

/****************************************************************
 * Read char from program.
 */
int getChar() {
    program >> ch;
    return 0;
}

/****************************************************************
 * Make ch non-space char.
 */
int getNbc() {
    program >> ch;
    while (ch == ' ') {
        program >> ch;
    }
    return 0;
}

/****************************************************************
 * Cat token and ch.
 */
int cat() {
    token = token + ch;
    return 0;
}

/****************************************************************
 * Return 1 if ch is 'a'~'z', 'A'~'Z' or '_'.
 */
bool isLetter() {
    return (('a' <= ch) && (ch <= 'z')) || 
           (('A' <= ch) && (ch <= 'Z')) || 
           (ch == ' ');
}

/****************************************************************
 * Return 1 if ch is '0'~'9'.
 */
bool isDigit(char ch) {
    return ('0' <= ch) && (ch <= '9');
}

/****************************************************************
 * Return 1 if token is keyword.
 */
bool isReserve(const std::string &token) {
    return keyword.find(token) != keyword.end();
}

/****************************************************************
 * Return token as int.
 */
int SToI(const std::string &token) {
    return std::stoi(token);
}

/****************************************************************
 * Return token as float.
 */
float SToF(const std::string &token) {
    return std::stof(token);
}

/****************************************************************
 * Insert token to table.
 */
int tableInsert(std::vector<std::string> &table, const std::string &token) {
    table.push_back(token);
    return 0;
}

/****************************************************************
 * Handle error.
 */
int error() {
    return 0;
}

/****************************************************************
 * Handle return.
 */
int returnProcess() {
    return 0;
}