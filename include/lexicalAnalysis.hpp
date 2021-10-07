#ifndef LEXICALANALYSIS_HPP
#define LEXICALANALYSIS_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>

/****************************************************************
 * Const
 */

/****************************************************************
 * State
 */
#define START         0
#define RID           2
#define LETTER        3
#define DIGIT         4
#define DIGITS        5
#define REMAINDER     6
#define NUM1          7
#define NUM2          8
#define NUM3          9
#define NUM4         10
#define SMALLEREQUAL 12
#define GREATEREQUAL 13
#define STAR1        16
#define STAR2        17
#define SLASH1       18

#define PLUS         19
#define MINUS        20
#define STAR         21
#define SLASH        22
#define MOD          23
#define EQUAL        24
#define BANG         25
#define GREATER      26
#define RSHIFT       27
#define SMALLER      28
#define LSHIFT       29
#define AND          30
#define OR           31
#define CARET        32

/****************************************************************
 * Token type
 */
#define ID           31
#define NUM          32
#define INT          33
#define FLOAT        34
#define OP           35
#define SINGLE       36
#define NOTE         37
#define KEYWORD      38

static std::string type2str(int type) {
    switch (type) {
    case ID: return "ID";
    case NUM: return "NUM";
    case INT: return "INT";
    case FLOAT: return "FLOAT";
    case OP: return "OP";
    case SINGLE: return "SINGLE";
    case NOTE: return "NOTE";
    case KEYWORD: return "KEYWORD";
    default: return "UNDEFINE";
    }
}

static std::map<int, int> typeCount = {
    {ID, 0},
    {NUM, 0},
    {INT, 0},
    {FLOAT, 0},
    {OP, 0},
    {SINGLE, 0},
    {NOTE, 0},
    {KEYWORD, 0}
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