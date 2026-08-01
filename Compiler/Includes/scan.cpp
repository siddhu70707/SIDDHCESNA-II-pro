#include <vector>
#include <string>
#include <iostream>
#include <cstdint>
#include "lexer.h"
#include "scan.h"
#include "helperfunc.h"
using namespace std;


// TODO: add a map for variables of memory in order to avoid duplicates
void MemoryAllocation(const vector<Token> &tokens) {
    size_t i = 0;
    
    while (i < tokens.size()) {

        // For memory allocation of INT

        if (tokens[i].type == TokenType::KEYWORD_INT) {
            int line_num = tokens[i].line;
            string Identifier;
            i++; 
            
            // Expect IDENTIFIER
            if (i < tokens.size() && tokens[i].type == TokenType::IDENTIFIER && tokens[i].line == line_num) {
                Identifier = tokens[i].value;
                i++;
            } else {
                cerr << RED << "Expected 'IDENTIFIER' at " << (i < tokens.size() ? tokens[i].line : line_num) << endl;
                while (i < tokens.size() && tokens[i].line == line_num) i++;
                continue; 
            }
            
            //  Expect ASSIGN
            if (i < tokens.size() && tokens[i].type == TokenType::ASSIGN && tokens[i].line == line_num) {
                i++;
            } else {
                cerr << RED << "Expected '=' at " << (i < tokens.size() ? tokens[i].line : line_num) << endl;
                while (i < tokens.size() && tokens[i].line == line_num) i++;
                continue;
            }

            // Expect Int Literal or Expression
            if (i < tokens.size() && tokens[i].line == line_num) {
                
                // Case A: Mathematical expression starts with '(' or has trailing operators
                bool is_expression = (tokens[i].type == TokenType::OPEN_PAREN);
                if (!is_expression && i + 1 < tokens.size() && tokens[i+1].line == line_num) {
                    TokenType next_t = tokens[i+1].type;
                    if (next_t == TokenType::OPEN_PAREN || next_t == TokenType::DIVIDE || 
                        next_t == TokenType::MULTIPLY || next_t == TokenType::MINUS || 
                        next_t == TokenType::PLUS) {
                        is_expression = true;
                        identifierlist
                    }
                }

                if (is_expression) {
                    string s;
                    while (i < tokens.size() && tokens[i].line == line_num) {
                        s.append(tokens[i].value);
                        i++;
                    }
                    uint16_t res = calculateHelper(s);

                    memory[IsOccupied].first = res;
                    memory[IsOccupied].second = Identifier;
                    
                }

                // Case B: Single Integer Literal
                else if (tokens[i].type == TokenType::INT_LITERAL) {
                    uint16_t value = stoi(tokens[i].value);
                    if (IsOccupied < memory.size()) {
                        memory[IsOccupied].first = value;
                        memory[IsOccupied].second = Identifier;
                        IsOccupied++;
                    }
                    i++;
                } 
                else {
                    cerr << RED << "Expected an 'Int literal' or expression at " << tokens[i].line << endl;
                    while (i < tokens.size() && tokens[i].line == line_num) i++;
                }
            }
        } 

        // For memory allocation of char
        else if (tokens[i].type == TokenType::KEYWORD_CHAR) {
            int line_num = tokens[i].line;
            string identifier;
            // expect identifier

            if (i < tokens.size() && tokens[i].type == TokenType::IDENTIFIER && tokens[i].line == line_num) {
                identifier = tokens[i].value;
                i++;
            } 

            else {
                cerr << RED << "Expected 'IDENTIFIER' at " << (i < tokens.size() ? tokens[i].line : line_num) << endl;
                while (i < tokens.size() && tokens[i].line == line_num) i++;
                continue; 
            }
            i++;

            // expect assigantion
            if (i < tokens.size() && tokens[i].type == TokenType::ASSIGN && tokens[i].line == line_num) {
                i++;
            }

            else {
                cerr << RED << "Expected '=' at " << (i < tokens.size() ? tokens[i].line : line_num) << endl;
                while (i < tokens.size() && tokens[i].line == line_num) i++;
                continue;
            }
            
            // expect char literal

            if(tokens[i].type == TokenType::CHAR_LITERAL){
                uint16_t value = stoi(tokens[i].value);
                if (IsOccupied < memory.size()) {
                    memory[IsOccupied].first = value;
                    memory[IsOccupied].second = identifier;
                    IsOccupied++;
                }
                else{
                    cerr << RED << "Capacity Reached" << endl;
                }
                i++;
            }

        } 

        // For memory allocation of bool

        else if (tokens[i].type == TokenType::KEYWORD_BOOL) {

            int line_num = tokens[i].line;
            string identifier;
            i++;

            // expect a identifier

            if(tokens[i].type == TokenType::IDENTIFIER){
                identifier = tokens[i].value;
            }

            else{
                cerr << RED << "Expected '=' at " << (i < tokens.size() ? tokens[i].line : line_num) << endl;
            }

            // expect a assignation

            if (i < tokens.size() && tokens[i].type == TokenType::ASSIGN && tokens[i].line == line_num) {
                i++;
            }

            else {
                cerr << RED << "Expected '=' at " << (i < tokens.size() ? tokens[i].line : line_num) << endl;
                while (i < tokens.size() && tokens[i].line == line_num) i++;
                continue;
            }
            
            // expect bool_literal

            if(tokens[i].type == TokenType::IDENTIFIER){
                uint16_t booolean;
                if(tokens[i].value == "true"){
                    booolean = 1;
                    if (IsOccupied < memory.size()) {
                        memory[IsOccupied].first = booolean;
                        memory[IsOccupied].second = identifier;
                        IsOccupied++;
                    }
                    else{
                        cerr << RED << "Capacity Reached" << endl;
                    }
                    i++;
                }

                
                else if(tokens[i].value == "false"){
                    booolean = 0;
                    if (IsOccupied < memory.size()) {
                        memory[IsOccupied].first = booolean;
                        memory[IsOccupied].second = identifier;
                        IsOccupied++;
                    }
                    else{
                        cerr << RED << "Capacity Reached" << endl;
                    }
                    i++;
                }

                else{
                    cerr << RED << "Expected a bool at " << (i < tokens.size() ? tokens[i].line : line_num) << endl;
                }
            }
        }
    }
}
