#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>

/****************************************************************
 * Const
 */

#define START         0
#define ID            1
#define RID           2
#define LETTER        3
#define DIGIT         4
#define DIGITS        5
#define REMAINDER     6
#define NUM           7
#define NUM1          8
#define NUM2          9
#define NUM3         10
#define NUM4         11
#define OP           12
#define PLUS         13
#define MINUS        14
#define EQUAL        15
#define AND          16
#define OR           17
#define SMALLER      18
#define GREATER      19
#define SMALLEREQUAL 20
#define GREATEREQUAL 21
#define SINGLE       22
#define NOTE         23
#define STAR         24
#define STAR1        25
#define STAR2        26
#define SLASH        27
#define SLASH1       28


/****************************************************************
 * Attributes
 */
static char ch;
static int state, isKey;
static std::string token;

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
static bool isReserve(const std::string &token);
static int SToI(const std::string &token);
static float SToF(const std::string &token);
static int tableInsert(std::vector<std::string> &table, const std::string &token);
static int error();
static int returnProcess();
