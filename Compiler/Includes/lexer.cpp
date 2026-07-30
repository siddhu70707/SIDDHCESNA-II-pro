#include "lexer.h"
#include <cctype>
#include <vector>
#include <string>
#include <unordered_map>

std::vector<Token> tokenizer(const std::string& source) {
    std::vector<Token> tokens;
    size_t pos = 0;
    int current_line = 1;

    static const std::unordered_map<std::string, TokenType> keyword_map = {
        {"int", TokenType::KEYWORD_INT},       {"def", TokenType::KEYWORD_DEF}, 
        {"bool", TokenType::KEYWORD_BOOL},     {"string", TokenType::KEYWORD_STRING}, 
        {"char", TokenType::KEYWORD_CHAR},     {"call", TokenType::KEYWORD_CALL}, 
        {"if", TokenType::KEYWORD_IF},         {"else", TokenType::KEYWORD_ELSE}, 
        {"for", TokenType::KEYWORD_FOR},       {"while", TokenType::KEYWORD_WHILE}, 
        {"print", TokenType::KEYWORD_PRINT}
    };

    while (pos < source.size()) {
        char current = source[pos];

        if (current == '\n') { 
            current_line++; pos++; continue; 
        }

        if (std::isspace(current)) {
            pos++; continue;
        }


        if (current == '/') {
            if (pos + 1 < source.size() && source[pos + 1] == '/') {
                while (pos < source.size() && source[pos] != '\n') { pos++; }
                continue; // for comments
            } else {
                tokens.push_back({TokenType::DIVIDE, "/", current_line});
                pos++;
                continue;
            }
        }

        if (current == '=') {
            if (pos + 1 < source.size() && source[pos + 1] == '=') {
                tokens.push_back({TokenType::EQUAL_TO, "==", current_line});
                pos += 2;
            } else {
                tokens.push_back({TokenType::ASSIGN, "=", current_line});
                pos++;
            }
            continue;
        }
            if (current == '&') {
                if (pos + 1 < source.size() && source[pos + 1] == '&') {
                    tokens.push_back({TokenType::AND, "&&", current_line});
                    pos += 2;
                } else {
                    tokens.push_back({TokenType::UNKNOWN, "&", current_line});
                    pos++;
                }
                continue;
            }
            
            if (current == '|') {
                if (pos + 1 < source.size() && source[pos + 1] == '|') {
                    tokens.push_back({TokenType::OR, "||", current_line});
                    pos += 2;
                } else {
                    tokens.push_back({TokenType::UNKNOWN, "|", current_line});
                    pos++;
                }
                continue;
            }



        if (current == '+') {
            tokens.push_back({TokenType::PLUS, "+", current_line});
            pos++;
            continue;
        }

        if (current == '-') { 
            tokens.push_back({TokenType::MINUS, "-", current_line});
            pos++; 
            continue; 
        }

        if (current == '*') { 
            tokens.push_back({TokenType::MULTIPLY, "*", current_line}); 
            pos++; 
            continue; 
        }

        if (current == '^') { 
            tokens.push_back({TokenType::XOR, "^", current_line}); 
            pos++; 
            continue; 
        }

        if (current == '>') { 
            tokens.push_back({TokenType::GREATER, ">", current_line}); 
            pos++; 
            continue; 
        }

        if (current == '<') { 
            tokens.push_back({TokenType::SMALLER, "<", current_line}); 
            pos++; 
            continue; 
        }

        if (current == ';') { 
            tokens.push_back({TokenType::SEMICOLON, ";", current_line}); 
            pos++; 
            continue;
        }

        if (current == '(') { 
            tokens.push_back({TokenType::OPEN_PAREN, "(", current_line}); 
            pos++; 
            continue; 
        }

        if (current == ')') { 
            tokens.push_back({TokenType::CLOSE_PAREN, ")", current_line}); 
            pos++; 
            continue; 
        }

        if (current == '{') { 
            tokens.push_back({TokenType::OPEN_BRACE, "{", current_line}); 
            pos++; 
            continue; 
        }

        if (current == '}') { 
            tokens.push_back({TokenType::CLOSE_BRACE, "}", current_line}); 
            pos++; 
            continue; 
        }

        if (current == '[') { 
            tokens.push_back({TokenType::OPEN_SQUARE, "[", current_line}); 
            pos++; 
            continue; 
        }

        if (current == ']') { 
            tokens.push_back({TokenType::CLOSE_SQUARE, "]", current_line}); 
            pos++; 
            continue; }


        if (current == '"') {
            std::string str_val = "";
            pos++; 
            while (pos < source.size() && source[pos] != '"') {
                if (source[pos] == '\n') current_line++;
                str_val += source[pos];
                pos++;
            }

            pos++; 
            tokens.push_back({TokenType::STRING_LITERAL, str_val, current_line});
            continue;
        }

        if (current == '\'') {
            std::string char_val = "";
            pos++;
            while (pos < source.size() && source[pos] != '\'') {
                char_val += source[pos++];
            }
            pos++;
            tokens.push_back({TokenType::CHAR_LITERAL, char_val, current_line});
            continue;
        }


        if (std::isdigit(current)) {
            std::string num = "";
            while (pos < source.size() && std::isdigit(source[pos])) { 
                num += source[pos]; 
                pos++;
            }
            tokens.push_back({TokenType::INT_LITERAL, num, current_line});
            continue;
        }


        if (std::isalpha(current) || current == '_') {
            std::string word = "";
            while (pos < source.size() && (std::isalnum(source[pos]) || source[pos] == '_')) {
                word += source[pos];
                pos++;
            }
            if (word == "int") {
                tokens.push_back({TokenType::KEYWORD_INT, word, current_line});
            }
            else if (word == "def" || word == "bool" || word == "string" || word == "char" || 
                    word == "call" || word == "if" || word == "else" || word == "for" || 
                    word == "while" || word == "print") {
                        
                // as clean as clean
                
                tokens.push_back({keyword_map.at(word), word, current_line});
            } 
            else {
                tokens.push_back({TokenType::IDENTIFIER, word, current_line});
            }
            continue;
            

        }

        // Unknown Character
        std::string unknown_str(1, current);
        tokens.push_back({TokenType::UNKNOWN, unknown_str, current_line});
        pos++;
    }
    return tokens;
}



std::string token_type_to_string(TokenType type) {
    switch (type) {
        case TokenType::KEYWORD_INT:     return "KEYWORD_INT";
        case TokenType::KEYWORD_DEF:     return "KEYWORD_DEF";
        case TokenType::KEYWORD_BOOL:    return "KEYWORD_BOOL";
        case TokenType::KEYWORD_STRING:  return "KEYWORD_STRING";
        case TokenType::KEYWORD_CHAR:    return "KEYWORD_CHAR";
        case TokenType::KEYWORD_CALL:    return "KEYWORD_CALL";
        case TokenType::KEYWORD_IF:      return "KEYWORD_IF";
        case TokenType::KEYWORD_ELSE:    return "KEYWORD_ELSE";
        case TokenType::KEYWORD_FOR:     return "KEYWORD_FOR";
        case TokenType::KEYWORD_WHILE:    return "KEYWORD_WHILE";
        case TokenType::KEYWORD_PRINT:    return "KEYWORD_PRINT";
        case TokenType::IDENTIFIER:      return "IDENTIFIER";
        case TokenType::INT_LITERAL:     return "INT_LITERAL";
        case TokenType::STRING_LITERAL:  return "STRING_LITERAL";
        case TokenType::CHAR_LITERAL:    return "CHAR_LITERAL";
        case TokenType::ASSIGN:          return "ASSIGN";
        case TokenType::EQUAL_TO:        return "EQUAL_TO";
        case TokenType::PLUS:            return "PLUS";
        case TokenType::GREATER:         return "GREATER";
        case TokenType::SMALLER:        return "SMALLER";
        case TokenType::MINUS:           return "MINUS";
        case TokenType::DIVIDE:          return "DIVIDE";
        case TokenType::MULTIPLY:        return "MULTIPLY";
        case TokenType::AND:             return "AND";
        case TokenType::OR:              return "OR";
        case TokenType::XOR:             return "XOR";
        case TokenType::SEMICOLON:       return "SEMICOLON";
        case TokenType::OPEN_PAREN:      return "OPEN_PAREN";
        case TokenType::CLOSE_PAREN:     return "CLOSE_PAREN";
        case TokenType::OPEN_BRACE:      return "OPEN_BRACE";
        case TokenType::CLOSE_BRACE:     return "CLOSE_BRACE";
        case TokenType::OPEN_SQUARE:     return "OPEN_SQUARE";
        case TokenType::CLOSE_SQUARE:    return "CLOSE_SQUARE";
        case TokenType::UNKNOWN:         return "UNKNOWN";
    }
    return "UNKNOWN";
}
