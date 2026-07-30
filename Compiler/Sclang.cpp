#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

// colors
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"     
#define BOLD    "\033[1m"

// helper files
#include "Includes/ui.h"
#include "Includes/lexer.h"
#include "Includes/scan.h"

using namespace std;

// Global Variables
string filename;
string file_contents; 

int main(){

    InitialCommand();
    // g++ Sclang.cpp Includes/ui.cpp Includes/lexer.cpp Includes/scan.cpp Includes/helperfunc.cpp -o main && ./main
    while(true){
        string command;
        cout << YELLOW << "$ " << RESET; 

        if(!getline(cin >> ws, command)){
            break;
        }

        if(command == "compile"){
            cout << YELLOW << "$ " << RESET;
            cout << "Enter filename: ";
            
            if(!getline(cin >> ws, filename)){
                break;
            }
            size_t len = filename.size();
            if(len < 3 || filename[len - 1] != 'c' || filename[len - 2] != 's' || filename[len - 3] != '.'){
                cout << RED << "[Error] File must have a .sc extension: " << filename << RESET << "\n\n";
                continue;
            }

            ifstream source_file(filename);

            if (!source_file.is_open()) {
                cout << RED << "[Error] Could not open file: " << filename << RESET << "\n\n";
                continue;
            }

            stringstream buffer;
            buffer << source_file.rdbuf();
            file_contents = buffer.str();
            source_file.close();

            cout << GREEN << "[Success] Loaded " << filename << " (" << file_contents.size() << " bytes)" << RESET << "\n\n";
            
            vector<Token> tokens = tokenizer(file_contents);
            
            for(const auto &t : tokens){
                cout << t.line << " | " << token_type_to_string(t.type) << " | " << t.value << " | " << endl;
            }

            continue;
        }

        if(command == "exit"){
            break;
        }
    }
    return 0;
}