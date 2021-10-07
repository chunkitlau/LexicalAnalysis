#ifndef LEXICALANALYSIS_HPP
#define LEXICALANALYSIS_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <unistd.h>

/****************************************************************
 * Const
 */

/****************************************************************
 * State
 */
#define START         0
#define RID           1
#define LETTER        2
#define DIGIT         3
#define DIGITS        4
#define REMAINDER     5
#define NUM1          6
#define NUM2          7
#define NUM3          8
#define NUM4          9
#define SMALLEREQUAL 10
#define GREATEREQUAL 11
#define STAR1        12
#define STAR2        13
#define SLASH1       14

#define PLUS         15
#define MINUS        16
#define STAR         17
#define SLASH        18
#define MOD          19
#define EQUAL        20
#define BANG         21
#define GREATER      22
#define RSHIFT       23
#define SMALLER      24
#define LSHIFT       25
#define AND          26
#define OR           27
#define CARET        28
#define RSTRING      29
#define RPREPROCESS  30

/****************************************************************
 * Token type
 */
#define ID           31
#define INT          32
#define FLOAT        33
#define OP           34
#define SINGLE       35
#define NOTE         36
#define KEYWORD      37
#define STRING       38
#define PREPROCESS   39

static std::string type2str(int type) {
    switch (type) {
    case ID: return "ID";
    case INT: return "INT";
    case FLOAT: return "FLOAT";
    case OP: return "OP";
    case SINGLE: return "SINGLE";
    case NOTE: return "NOTE";
    case KEYWORD: return "KEYWORD";
    case STRING: return "STRING";
    case PREPROCESS: return "PREPROCESS";
    default: return "UNDEFINE";
    }
}

static std::map<int, int> typeCount = {
    {ID, 0},
    {INT, 0},
    {FLOAT, 0},
    {OP, 0},
    {SINGLE, 0},
    {NOTE, 0},
    {KEYWORD, 0},
    {STRING, 0},
    {PREPROCESS, 0}
};

/****************************************************************
 * Attributes
 */
static char ch, chRetract;
static int state, isKey, isRetract, line = 1, column = 1, character;
static std::string token, error;

static std::ifstream program;
static std::ofstream result;
static std::vector<std::string> table;
static std::map<std::string, bool> keyword = {
    {"auto", 1},
    {"break", 1},
    {"case", 1},
    {"char", 1},
    {"const", 1},
    {"continue", 1},
    {"default", 1},
    {"do", 1},
    {"double", 1},
    {"else", 1},
    {"enum", 1},
    {"extern", 1},
    {"float", 1},
    {"for", 1},
    {"goto", 1},
    {"if", 1},
    {"int", 1},
    {"long", 1},
    {"register", 1},
    {"return", 1},
    {"short", 1},
    {"signed", 1},
    {"sizeof", 1},
    {"static", 1},
    {"struct", 1},
    {"switch", 1},
    {"typedef", 1},
    {"unsigned", 1},
    {"onion", 1},
    {"void", 1},
    {"volatile", 1},
    {"while", 1},
    {"inline", 1},
    {"restrict", 1}
};

/****************************************************************
 * Methods
 */
static int getChar();
static int getNbc();
static int cat();
static bool isLetter();
static bool isDigit();
static int retract();
static bool isReserve();
static int SToI();
static float SToF();
static int tableInsert();
static int returnError();
static int returnToken(int type);
static std::string typeCount2str();
static int lexicalAnalysis();

#endif // LEXICALANALYSIS_HPP