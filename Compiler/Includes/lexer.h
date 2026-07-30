#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

enum class TokenType {
    
    // KEYWORDS
    KEYWORD_INT,
    KEYWORD_DEF,
    KEYWORD_BOOL,
    KEYWORD_STRING, 
    KEYWORD_CHAR,
    KEYWORD_CALL,
    KEYWORD_IF,
    KEYWORD_ELSE,
    KEYWORD_FOR,
    KEYWORD_WHILE, 
    KEYWORD_PRINT,

    // Identifiers & Literals
    IDENTIFIER,
    INT_LITERAL,
    STRING_LITERAL,
    CHAR_LITERAL,

    // Operators
    ASSIGN,       // =
    EQUAL_TO,     // ==
    PLUS,         // +
    GREATER,      // >
    SMALLER,      // <
    MINUS,        // -
    DIVIDE,       // /
    MULTIPLY,     // *
    AND,          // &&
    OR,           // ||
    XOR,          // ^


    // Punctuation & Brackets
    SEMICOLON,          // ;
    OPEN_PAREN,         // (
    CLOSE_PAREN,        // )
    OPEN_BRACE,         // {
    CLOSE_BRACE,        // }
    OPEN_SQUARE,        // [
    CLOSE_SQUARE,       // ]
    

    UNKNOWN
};

struct Token {
    TokenType type;
    std::string value;
    int line;
};

std::vector<Token> tokenizer(const std::string& source);

std::string token_type_to_string(TokenType type);

#endif