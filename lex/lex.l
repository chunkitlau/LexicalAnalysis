/* Declaration */
%{

#include <stdio.h>

#define ID          0 
#define INT         1   
#define FLOAT       2   
#define OP          3   
#define SINGLE      4   
#define NOTE        5   
#define KEYWORD     6  
#define STRING      7   
#define PREPROCESS  8

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
note            \/\/.\n|\/\*.\*\/
keyword         auto|break|case|char|const|continue|default|do|double|else|enum|extern|float|for|goto|if|int|long|register|return|short|signed|sizeof|static|struct|switch|typedef|unsigned|onion|void|volatile|while|inline|restrict
string          \".\"
preprocess      \#.

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
        case ID:            
        case INT:           
        case FLOAT:         
        case OP:            
        case SINGLE:        
        case NOTE:          
        case KEYWORD:       
        case STRING:        
        case PREPROCESS:    
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

    if(argc>=2){
        fclose(yyin);
        if (argc>=3) fclose(yyout);
    }
    return 0;
}
