#include <string>
#include <cctype>
#include <stack>
#include <array>
#include <cstdint>
#include <utility>
#include "helperfunc.h"
using namespace std;




std::array<std::pair<uint16_t, std::string>, 4096> memory = {{
    {0, "\0"}, {1, "\x01"}, {2, "\x02"}, {3, "\x03"}, {4, "\x04"}, {5, "\x05"}, {6, "\x06"}, {7, "\a"},
    {8, "\b"}, {9, "\t"}, {10, "\n"}, {11, "\v"}, {12, "\f"}, {13, "\r"}, {14, "\x0E"}, {15, "\x0F"},
    {16, "\x10"}, {17, "\x11"}, {18, "\x12"}, {19, "\x13"}, {20, "\x14"}, {21, "\x15"}, {22, "\x16"}, {23, "\x17"},
    {24, "\x18"}, {25, "\x19"}, {26, "\x12"}, {27, "\x1B"}, {28, "\x1C"}, {29, "\x1D"}, {30, "\x1E"}, {31, "\x1F"},
    {32, " "}, {33, "!"}, {34, "\""}, {35, "#"}, {36, "$"}, {37, "%"}, {38, "&"}, {39, "'"},
    {40, "("}, {41, ")"}, {42, "*"}, {43, "+"}, {44, ","}, {45, "-"}, {46, "."}, {47, "/"},
    {48, "0"}, {49, "1"}, {50, "2"}, {51, "3"}, {52, "4"}, {53, "5"}, {54, "6"}, {55, "7"},
    {56, "8"}, {57, "9"}, {58, ":"}, {59, ";"}, {60, "<"}, {61, "="}, {62, ">"}, {63, "?"},
    {64, "@"}, {65, "A"}, {66, "B"}, {67, "C"}, {68, "D"}, {69, "E"}, {70, "F"}, {71, "G"},
    {72, "H"}, {73, "I"}, {74, "J"}, {75, "K"}, {76, "L"}, {77, "M"}, {78, "N"}, {79, "O"},
    {80, "P"}, {81, "Q"}, {82, "R"}, {83, "S"}, {84, "T"}, {85, "U"}, {86, "V"}, {87, "W"},
    {88, "X"}, {89, "Y"}, {90, "Z"}, {91, "["}, {92, "\\"}, {93, "]"}, {94, "^"}, {95, "_"},
    {96, "`"}, {97, "a"}, {98, "b"}, {99, "c"}, {100, "d"}, {101, "e"}, {102, "f"}, {103, "g"},
    {104, "h"}, {105, "i"}, {106, "j"}, {107, "k"}, {108, "l"}, {109, "m"}, {110, "n"}, {111, "o"},
    {112, "p"}, {113, "q"}, {114, "r"}, {115, "s"}, {116, "t"}, {117, "u"}, {118, "v"}, {119, "w"},
    {120, "x"}, {121, "y"}, {122, "z"}, {123, "{"}, {124, "|"}, {125, "}"}, {126, "~"}, {127, "\x7F"}
}};

uint16_t IsOccupied = 127;

// MY CODE was trash.
int calculation(string equation){

    stack<pair<int, char>> mainStack; 
    char global_op = '+'; 

    for(int i = 0; i < equation.size(); i++){
        char curr = equation[i];

        if (curr == ' ') {
            continue;
        }

        // for INT_LITERALS
        
        if(isdigit(curr)){
            int num = 0;
            while(i < equation.size() && isdigit(equation[i])){
                // handles more than one digit
                num = (num * 10) + (equation[i] - '0'); 
                i++;
            }
            i--; // very important to decrement otherwise it will skip a value
            

            if (global_op == '*') {
                int prev_num = mainStack.top().first;
                char prev_op = mainStack.top().second;
                mainStack.pop(); //this logic was hard i used help for this 
                mainStack.push({prev_num * num, prev_op});
            } 
            else if (global_op == '/') {
                int prev_num = mainStack.top().first;
                char prev_op = mainStack.top().second;
                mainStack.pop();
                if (num != 0) {
                    mainStack.push({prev_num / num, prev_op});
                } else {
                    mainStack.push({0, prev_op}); // Handle division by zero (edgecase)
                }
            } 
            else {
                mainStack.push({num, global_op});
            }
        }

        if (curr == '+' || curr == '-' || curr == '*' || curr == '/') {
            global_op = curr;
        }

        // for INT_LITERALS containing parenthesis
        if(curr == '('){
            stack<pair<int, char>> numberAndoperation;
            int idx = i + 1;
            char curr_op = '+'; // default value just to prevent garbage

            while(idx < equation.size() && equation[idx] != ')'){
                if(equation[idx] == ' ') {
                    idx++;
                    continue;
                }

                if(equation[idx] == '+' || equation[idx] == '-' || equation[idx] == '*' || equation[idx] == '/'){
                    curr_op = equation[idx];
                    idx++;
                    continue;
                }
                if(isdigit(equation[idx])){
                    int num = 0;
                    while(idx < equation.size() && isdigit(equation[idx])){
                        num = (num * 10) + (equation[idx] - '0'); 
                        idx++;
                    }
                    
                    if (curr_op == '*') {
                        int prev_num = numberAndoperation.top().first;
                        char prev_op = numberAndoperation.top().second;
                        numberAndoperation.pop();
                        numberAndoperation.push({prev_num * num, prev_op});
                    } 
                    else if (curr_op == '/') {
                        int prev_num = numberAndoperation.top().first;
                        char prev_op = numberAndoperation.top().second;
                        numberAndoperation.pop();
                        if (num != 0) {
                            numberAndoperation.push({prev_num / num, prev_op});
                        } else {
                            numberAndoperation.push({0, prev_op});
                        }
                    } 
                    else {
                        numberAndoperation.push({num, curr_op});
                    }
                    continue; 
                }
                
                idx++; 
            }
            i = idx; 

            int bracket_total = 0;
            while(!numberAndoperation.empty()){

                pair<int, char> topElement = numberAndoperation.top();

                numberAndoperation.pop();
                // this is also a edge case where multiplication comes before additin like this (5 * 4 + 8)
                if(topElement.second == '+') {
                    bracket_total += topElement.first;
                } else if(topElement.second == '-') {
                    bracket_total -= topElement.first;
                }
            }
            if (global_op == '*') {
                int prev_num = mainStack.top().first;
                char prev_op = mainStack.top().second;
                mainStack.pop();
                mainStack.push({prev_num * bracket_total, prev_op});
            } 
            else if (global_op == '/') {
                int prev_num = mainStack.top().first;
                char prev_op = mainStack.top().second;
                mainStack.pop();
                if (bracket_total != 0) {
                    mainStack.push({prev_num / bracket_total, prev_op});

                } 
                else {
        
                    mainStack.push({0, prev_op});
                }
            } 
            else {
                mainStack.push({bracket_total, global_op});
            }
        }
    }
    int total_result = 0;
    while(!mainStack.empty()){
        pair<int, char> topElement = mainStack.top();
        mainStack.pop();
        if(topElement.second == '+') {
            total_result += topElement.first;
        } else if(topElement.second == '-') {
            total_result -= topElement.first;
        }
    }

    return total_result;
}

int calculateHelper(const string& s) {
    stack<int> st;
    int num = 0;
    int i = 0;
    char curr_op = '+';

    while (i < s.size()) {
        char ch = s[i];

        if (isdigit(ch)) {
            num = num * 10 + (ch - '0');
        }

        if (ch == '(') {
            i++; 
            num = calculateHelper(s);
        }

        if ((!isdigit(ch) && ch != ' ') || i == s.size() - 1) {
            if (curr_op == '+') {
                st.push(num);
            } else if (curr_op == '-') {
                st.push(-num);
            } else if (curr_op == '*') {
                int top = st.top();
                st.pop();
                st.push(top * num);
            } else if (curr_op == '/') {
                int top = st.top();
                st.pop();
                st.push(top / num);
            }

            curr_op = ch;
            num = 0;
        }

        if (ch == ')') {
            break;
        }

        i++;
    }
    int result = 0;
    while (!st.empty()) {
        result += st.top();
        st.pop();
    }

    return result;
}