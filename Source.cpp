#define _CRT_SECURE_NO_WARNINGS // To disable deprecation warnings for strcpy

#include <stdio.h>       // I'm using this for input and output functions like printf
#include <ctype.h>       // This library helps me check if a character is a letter or digit
#include <string.h>      // I included this for string manipulation like strcpy

#define LETTER 0          // I use this to represent letters
#define DIGIT 1           // This one represents digits
#define UNKNOWN 99        // For characters I don't recognize like operators or parentheses
#define EOF_TOKEN -1      // This means the end of the input

// Token codes to help identify each type of input
#define INT_LIT 10        // This is the code for integer numbers
#define IDENT 11          // This represents identifiers like variable names
#define ASSIGN_OP 20      // the assignment operator (=)
#define ADD_OP 21         // the addition operator (+)
#define SUB_OP 22         // the subtraction operator (-)
#define MULT_OP 23        // the multiplication operator (*)
#define DIV_OP 24         // the division operator (/)
#define LEFT_PAREN 25     // the left parenthesis '('
#define RIGHT_PAREN 26    // the right parenthesis ')'

// Declaring variables for analysis
int charClass;              // This stores the type of the current character
char lexeme[100];           // This array will store the current lexeme
char nextChar;              // This is the next character we’re going to check
int lexLen;                 // This tracks the length of the current lexeme
int token;                  // This will hold the final token code
int nextToken;              // This holds the next token we're going to return
int inputIndex = 0;         // Renamed index to inputIndex to avoid conflict

// expression to analyze
char input[] = "(sum + 62 / total)";

// Function declarations to keep everything organized
void addChar();             // help build the lexeme
void getChar();             // This grabs the next character
void getNonBlank();         // This skips white spaces
int lex();                  // This is the main function that does lexical analysis
int lookup(char ch);       // This checks unknown characters and classifies them

// This function adds nextChar to the lexeme array
void addChar() {
    if (lexLen <= 98) {
        lexeme[lexLen++] = nextChar;   // I store the character in lexeme and increase the length
        lexeme[lexLen] = '\0';         // I add null character to mark end of the string
    }
    else {
        printf("Error: lexeme is too long\n");   // Just in case the lexeme gets too long
    }
}

// This function reads the next character and decides its class
void getChar() {
    if (input[inputIndex] != '\0') {
        nextChar = input[inputIndex++];     // I take the next character from input
        if (isalpha(nextChar))
            charClass = LETTER;        // It's a letter
        else if (isdigit(nextChar))
            charClass = DIGIT;         // It's a digit
        else
            charClass = UNKNOWN;       // Something else like +, -, etc.
    }
    else {
        charClass = EOF_TOKEN;         // We've reached the end of input
    }
}

// This function just skips over any spaces
void getNonBlank() {
    while (isspace(nextChar))
        getChar();                     // Keep going until I hit a non-space character
}

// This one helps identify operators and parentheses
int lookup(char ch) {
    switch (ch) {
    case '(':
        addChar();
        nextToken = LEFT_PAREN;
        break;
    case ')':
        addChar();
        nextToken = RIGHT_PAREN;
        break;
    case '+':
        addChar();
        nextToken = ADD_OP;
        break;
    case '-':
        addChar();
        nextToken = SUB_OP;
        break;
    case '*':
        addChar();
        nextToken = MULT_OP;
        break;
    case '/':
        addChar();
        nextToken = DIV_OP;
        break;
    default:
        addChar();
        nextToken = EOF_TOKEN;   // If it's nothing I recognize
        break;
    }
    return nextToken;
}

// This is the core function that does the lexical analysis
int lex() {
    lexLen = 0;             // I reset the lexeme length
    getNonBlank();          // First I skip any spaces

    switch (charClass) {
    case LETTER:        // If the character is a letter
        addChar();
        getChar();
        while (charClass == LETTER || charClass == DIGIT) {
            addChar();
            getChar();
        }
        nextToken = IDENT;   // It's an identifier
        break;
    case DIGIT:         // If the character is a digit
        addChar();
        getChar();
        while (charClass == DIGIT) {
            addChar();
            getChar();
        }
        nextToken = INT_LIT; // It's an integer literal
        break;
    case UNKNOWN:       // If it’s an unknown character
        lookup(nextChar);  // I check what kind of operator or symbol it is
        getChar();
        break;
    case EOF_TOKEN:     // End of input
        nextToken = EOF_TOKEN;
        strcpy(lexeme, "EOF");  // Using strcpy instead of strcpy_s
        break;
    }

    // I print the result of the current lexeme
    printf("Next token is: %d, Next lexeme is %s\n", nextToken, lexeme);
    return nextToken;
}

// This is where I start the program
int main() {
    getChar();   // I get the first character
    do {
        lex();   // I keep calling lex() until end of input
    } while (nextToken != EOF_TOKEN);
    return 0;    // Program ends here
}
