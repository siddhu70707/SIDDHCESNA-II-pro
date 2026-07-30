#include <vector>
#include <string>
#include <iostream>
#include <cstdint>
#include "lexer.h"
#include "scan.h"
#include "helperfunc.h"
using namespace std;

void MemoryAllocation(const vector<Token> &tokens) {
    size_t i = 0;
    
    while (i < tokens.size()) {
        if (tokens[i].type == TokenType::KEYWORD_INT) {
            int line_num = tokens[i].line;
            string Identifier;
            
            // 1. Advance past 'int'
            i++; 
            
            // 2. Expect IDENTIFIER
            if(i < tokens.size() && tokens[i].type == TokenType::IDENTIFIER )
            if (i < tokens.size() && tokens[i].type == TokenType::IDENTIFIER && tokens[i].line == line_num) {
                Identifier = tokens[i].value;
                i++;
            } else {
                cerr << RED << "Expected 'IDENTIFIER' at " << (i < tokens.size() ? tokens[i].line : line_num) << endl;
                // Skimming recovery: advance until next line or end
                while (i < tokens.size() && tokens[i].line == line_num) i++;
                continue; 
            }
            
            // 3. Expect ASSIGN (=)
            if (i < tokens.size() && tokens[i].type == TokenType::ASSIGN && tokens[i].line == line_num) {
                i++;
            } else {
                cerr << RED << "Expected '=' at " << (i < tokens.size() ? tokens[i].line : line_num) << endl;
                while (i < tokens.size() && tokens[i].line == line_num) i++;
                continue;
            }

            // 4. Handle Right-Hand Side (Expression or Literal)
            if (i < tokens.size() && tokens[i].line == line_num) {
                
                // Case A: Mathematical expression starts with '(' or has trailing operators
                bool is_expression = (tokens[i].type == TokenType::OPEN_PAREN);
                if (!is_expression && i + 1 < tokens.size() && tokens[i+1].line == line_num) {
                    TokenType next_t = tokens[i+1].type;
                    if (next_t == TokenType::OPEN_PAREN || next_t == TokenType::DIVIDE || 
                        next_t == TokenType::MULTIPLY || next_t == TokenType::MINUS || 
                        next_t == TokenType::PLUS) {
                        is_expression = true;
                    }
                }

                if (is_expression) {
                    string s;
                    // Safely collect the rest of the expression on this line
                    while (i < tokens.size() && tokens[i].line == line_num) {
                        s.append(tokens[i].value);
                        i++;
                    }
                    int res = calculateHelper(s);
                    
                    // TODO: Write evaluated 'res' expression to your memory vector
                }
                // Case B: Single Integer Literal
                else if (tokens[i].type == TokenType::INT_LITERAL) {
                    uint16_t value = stoi(tokens[i].value);
                    if (IsOccupied < memory.size()) {
                        memory[IsOccupied].first = value;
                        IsOccupied++;
                    }
                    i++; // Consume literal
                } 
                else {
                    cerr << RED << "Expected an 'Int literal' or expression at " << tokens[i].line << endl;
                    while (i < tokens.size() && tokens[i].line == line_num) i++;
                }
            }
        } 
        else if (tokens[i].type == TokenType::KEYWORD_CHAR) {
            // Handle char later
            i++;
        } 
        else {
            // Advance if token doesn't match initialization patterns
            i++;
        }
    }
}
