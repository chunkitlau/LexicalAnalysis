/* Declaration */
%{

#include <stdio.h>

#define ID          1 
#define INT         2   
#define FLOAT       3   
#define OP          4   
#define SINGLE      5   
#define NOTE        6   
#define KEYWORD     7  
#define STRING      8   
#define PREPROCESS  9

int count[20];

%}

/* Formal definition */
delim           [ \t\n]
ws              {delim}+
letter          [A-Za-z]
digit           [0-9]
id              {letter}({letter}|{digit})*
int             {digit}+
float           {digit}+\.({digit}+)?(E[+\-]?{digit}+)?
arithmeticOp    \+|\-|\*|\\|\%|\+\+|\-\-
relationalOp    \=\=|\!\=|\>|\<|\>\=|\<\=
logicalOp       \&\&|\|\||\!
bitOp           \&|\||\^|\~|\<\<|\>\>
assignmentOp    \=|\+\=|\-\=|\*\=|\/\=|\%\=|\<\<\=|\>\>\=|\&\=|\^\=|\|\=
op              {arithmeticOp}|{relationalOp}|{logicalOp}|{bitOp}|{assignmentOp}|\?|\:
single          \(|\)|\[|\]|\{|\}|\.|\,|\;
note            \/\/.*\n|\/\*.*\*\/
keyword         auto|break|case|char|const|continue|default|do|double|else|enum|extern|float|for|goto|if|int|long|register|return|short|signed|sizeof|static|struct|switch|typedef|unsigned|onion|void|volatile|while|inline|restrict
string          \".*\"
preprocess      \#.*

%% /* Translation rules */

{ws}            { } /* No action, no return, skip all blank charactors*/
{keyword}       { return(KEYWORD); }
{id}            { return(ID); }
{int}           { return(INT); }
{float}         { return(FLOAT); }
{op}            { return(OP); }
{single}        { return(SINGLE); }
{note}          { return(NOTE); }
{string}        { return(STRING); }
{preprocess}    { return(PREPROCESS); }

%%

/* Auxiliary process */
void writeout(int c){
    switch(c){
        case ID:            ++count[ID];         fprintf(yyout, "(ID, \"%s\")\n", yytext);break;
        case INT:           ++count[INT];        fprintf(yyout, "(INT, \"%s\")\n", yytext);break;
        case FLOAT:         ++count[FLOAT];      fprintf(yyout, "(FLOAT, \"%s\")\n", yytext);break;
        case OP:            ++count[OP];         fprintf(yyout, "(OP, \"%s\")\n", yytext);break;
        case SINGLE:        ++count[SINGLE];     fprintf(yyout, "(SINGLE, \"%s\")\n", yytext);break;
        case NOTE:          ++count[NOTE];       fprintf(yyout, "(NOTE, \"%s\")\n", yytext);break;
        case KEYWORD:       ++count[KEYWORD];    fprintf(yyout, "(KEYWORD, \"%s\")\n", yytext);break;
        case STRING:        ++count[STRING];     fprintf(yyout, "(STRING, \"%s\")\n", yytext);break;
        case PREPROCESS:    ++count[PREPROCESS]; fprintf(yyout, "(PREPROCESS, \"%s\")\n", yytext);break;
        default:break;
    }
    return;
}

int main (int argc, char ** argv){
    int c;
    if (argc>=2){
        if ((yyin = fopen(argv[1], "r")) == NULL){
            printf("Can't open file %s\n", argv[1]);
            return 1;
        }
        if (argc>=3){
            yyout=fopen(argv[2], "w");
        }
    }

    /* yyin和yyout是lex中定义的输入输出文件指针，它们指明了
     * lex生成的词法分析器从哪里获得输入和输出到哪里。
     * 默认：stdin，stdout。
     */
    while ((c = yylex()) != 0) {
        writeout(c);
    }
    
    fprintf(yyout, "****************************************************************\n");
    fprintf(yyout, "Token type count\n");
    fprintf(yyout, "ID: %d\n", count[ID]);
    fprintf(yyout, "INT: %d\n", count[INT]);
    fprintf(yyout, "FLOAT: %d\n", count[FLOAT]);
    fprintf(yyout, "OP: %d\n", count[OP]);
    fprintf(yyout, "SINGLE: %d\n", count[SINGLE]);
    fprintf(yyout, "NOTE: %d\n", count[NOTE]);
    fprintf(yyout, "KEYWORD: %d\n", count[KEYWORD]);
    fprintf(yyout, "STRING: %d\n", count[STRING]);
    fprintf(yyout, "PREPROCESS: %d\n", count[PREPROCESS]);
    
    if(argc>=2){
        fclose(yyin);
        if (argc>=3) fclose(yyout);
    }
    return 0;
}
