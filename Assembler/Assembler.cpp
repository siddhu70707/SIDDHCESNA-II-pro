#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>
#include <fstream>
#include <bitset>
#include <iomanip>
#include <algorithm>

using namespace std;

// ANSI color codes
#define RESET   "\033[0m"
#define RED     "\033[31m"      // For errors
#define GREEN   "\033[32m"      // For success
#define YELLOW  "\033[33m"      // For warnings/Prompt
#define CYAN    "\033[36m"      // For headers
#define BOLD    "\033[1m"

// global variables
string filename;
string line;
bool assembled = false;
bool iamsure = false;
int program_counter; // for @ label assignation
int memory_counter;
vector<string> bincode; 
vector<string> hexcode;

// Constants 
unordered_map<string, int> ConstantsInProgram;
unordered_map<string, int> tag_id;

unordered_map<string, int> src = {
    {"R0", 0}, {"r0", 0},
    {"R1", 1}, {"r1", 1},
    {"R2", 2}, {"r2", 2},
    {"R3", 3}, {"r3", 3},
    {"RA", 4}, {"rA", 4}, {"Ra", 4},
    {"RB", 5}, {"rB", 5}, {"Rb", 5},
    {"CPU_OUT", 6},
    {"ALU_OUT", 4}
};

unordered_map<string, int> opcodes = {
    {"ADD",   0},
    {"SUB",   1},
    {"MUL",   2},
    {"DIV",   3},
    {"NOT",   4},
    {"AND",   5},
    {"OR",    6},
    {"XOR",   7},
    {"PASSA", 8},
    {"PASSB", 9},
    {"HALT",  15}
};

unordered_map<string, int> dest = {
    {"R0", 0},
    {"r0", 0},
    {"R1", 1}, {"r1", 1},
    {"R2", 2}, {"r2", 2},
    {"R3", 3}, {"r3", 3},
    {"RA", 4}, {"rA", 4}, {"Ra", 4},
    {"RB", 5}, {"rB", 5}, {"Rb", 5},
    {"OUT", 6}, {"CPU_OUT", 6}
};

unordered_map<string, int> flags = {
    {"JZ", 0},
    {"JGREATER", 1},
    {"JSMALLER", 2},
    {"JC", 3},
    {"JZERO", 0}
};


vector<string> ascii_characters = {
    "000", "001", "002", "003", "004", "005", "006", "007", "008", "009", "00a", "00b", "00c", "00d", "00e", "00f",
    "010", "011", "012", "013", "014", "015", "016", "017", "018", "019", "01a", "01b", "01c", "01d", "01e", "01f",
    "020", "021", "022", "023", "024", "025", "026", "027", "028", "029", "02a", "02b", "02c", "02d", "02e", "02f",
    "030", "031", "032", "033", "034", "035", "036", "037", "038", "039", "03a", "03b", "03c", "03d", "03e", "03f",
    "040", "041", "042", "043", "044", "045", "046", "047", "048", "049", "04a", "04b", "04c", "04d", "04e", "04f",
    "050", "051", "052", "053", "054", "055", "056", "057", "058", "059", "05a", "05b", "05c", "05d", "05e", "05f",
    "060", "061", "062", "063", "064", "065", "066", "067", "068", "069", "06a", "06b", "06c", "06d", "06e", "06f",
    "070", "071", "072", "073", "074", "075", "076", "077", "078", "079", "07a", "07b", "07c", "07d", "07e", "07f"
};


vector<string> ascii_name = {
    "NUL", "SOH", "STX", "ETX", "EOT", "ENQ", "ACK", "BEL", "BS",  "HT",  "LF",  "VT",  "FF",  "CR",  "SO",  "SI",
    "DLE", "DC1", "DC2", "DC3", "DC4", "NAK", "SYN", "ETB", "CAN", "EM",  "SUB", "ESC", "FS",  "GS",  "RS",  "US",
    "SPACE", "EXCLAMATION", "DOUBLE_QUOTE", "HASH", "DOLLAR", "PERCENT", "AMPERSAND", "SINGLE_QUOTE", 
    "OPEN_PAREN", "CLOSE_PAREN", "ASTERISK", "PLUS", "COMMA", "MINUS", "PERIOD", "SLASH",
    "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
    "COLON", "SEMICOLON", "LESS_THAN", "EQUAL", "GREATER_THAN", "QUESTION", "AT",
    "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",
    "OPEN_BRACKET", "BACKSLASH", "CLOSE_BRACKET", "CARET", "UNDERSCORE", "BACKTICK",
    "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z",
    "OPEN_BRACE", "PIPE", "CLOSE_BRACE", "TILDE", "DEL"
};

int parseHex(string str) {
    if (str.empty()) return 0; 
    try {
        if (str.size() > 2 && (str.substr(0, 2) == "0x" || str.substr(0, 2) == "0X")) {
            return stoi(str, nullptr, 16);
        }
        if (isdigit(str[0]) || (str.size() > 1 && str[0] == '-')) {
            return stoi(str);
        }
    } catch (...) {
        return 0; 
    }
    return 0;
}

void initial_command(){
    cout << CYAN << "=============================================================" << RESET << endl;
    cout << CYAN << "|                                                           |" << RESET << endl;
    cout << CYAN << "|             " << BOLD << "SCESNA 16-bit Assembler v3.0" << RESET << CYAN << "                  |" << RESET << endl;
    cout << CYAN << "|            Command-Line Interface (C++17)                 |" << RESET << endl;
    cout << CYAN << "|                                                           |" << RESET << endl;
    cout << CYAN << "=============================================================" << RESET << endl;
    cout << endl;
    cout << YELLOW << "Available commands:" << RESET << endl;
    cout << "  assemble         - Assemble .scesna file" << endl;
    cout << "  view hex         - Display machine code in hexadecimal" << endl;
    cout << "  view bin         - Display machine code in binary" << endl;
    cout << "  view const       - Display symbol table" << endl; 
    cout << "  help             - Show this help message" << endl;
    cout << "  exit             - Exit the Assembler" << endl;
}

void type_00(string opcode, string src_str, string dest_str){
    if (opcodes.find(opcode) == opcodes.end()) return;
    
    int opc = opcodes[opcode];
    int s = src[src_str];
    int d = dest[dest_str];
    int instruction = (0 << 14) | ((opc & 0xF) << 10) | ((s & 0x7) << 7) | ((d & 0x7) << 4);
    
    bincode.push_back(bitset<16>(instruction).to_string());
    program_counter++;
}

void type_01(string reg, int addr){
    int reg_id = dest[reg];
    int instruction = (1 << 14) | (reg_id << 12) | (addr & 0xFFF);
    
    bincode.push_back(bitset<16>(instruction).to_string());
    program_counter++;
}

void type_10(string flag, int addr){
    int flg = flags[flag];
    int instruction = (2 << 14) | (flg << 12) | (addr & 0xFFF);
    
    bincode.push_back(bitset<16>(instruction).to_string());
    program_counter++;
}

void type_11(string reg, int addr){
    int reg_id = dest[reg];
    if (reg_id > 3) {
        cerr << RED << "> Error: Only R0-R3 can be used with LOAD/STORE." << RESET << endl;
        return;
    }
    int instruction = (3 << 14) | ((reg_id & 0x3) << 12) | (addr & 0xFFF);
    bincode.push_back(bitset<16>(instruction).to_string());
    program_counter++;
}

void binToHex(){
    hexcode.clear();
    for(string bin : bincode){
        unsigned int val = stoul(bin, nullptr, 2);
        stringstream ss;
        ss << uppercase << hex << setfill('0') << setw(4) << val;
        hexcode.push_back(ss.str());
    }
}

//clean commas and comments
string cleanLine(string line) {
    size_t commentPos = line.find("//");
    if (commentPos != string::npos) line = line.substr(0, commentPos);
    commentPos = line.find(";"); // Also clean up standard semicolon comments
    if (commentPos != string::npos) line = line.substr(0, commentPos);
    replace(line.begin(), line.end(), ',', ' ');
    return line;
}

void define_type(string line){
    line = cleanLine(line);
    stringstream ss(line);
    string cmd;
    ss >> cmd;

    if (cmd.empty() || cmd == "#define" || cmd == "#include" || cmd[0] == '@') return;

    if (cmd == "MOV") {
        string s_arg, d_arg;
        ss >> s_arg >> d_arg;

        if (s_arg == "R1" || s_arg == "r1" || d_arg == "RB" || d_arg == "rB") {
            type_00("PASSB", s_arg, d_arg); 
        } else {
            type_00("PASSA", s_arg, d_arg); 
        }
    }
    else if (cmd == "OUT") {
        string reg; ss >> reg;
        type_00("PASSA", reg, "CPU_OUT");
    }
    else if (opcodes.count(cmd)) {
        if (cmd == "HALT") {
            int inst = (0 << 14) | (opcodes["HALT"] << 10);
            bincode.push_back(bitset<16>(inst).to_string());
            program_counter++;
        } else {
            string target; ss >> target;
            type_00(cmd, "ALU_OUT", target);
        }
    }
    else if (cmd == "LOAD") {
        string r, addr_s; ss >> r >> addr_s;
        int addr = ConstantsInProgram.count(addr_s) ? ConstantsInProgram[addr_s] : parseHex(addr_s);
        type_11(r, addr);
    }
    else if (cmd == "STORE") {
        string r, addr_s; ss >> r >> addr_s;
        int addr = ConstantsInProgram.count(addr_s) ? ConstantsInProgram[addr_s] : parseHex(addr_s);
        type_01(r, addr);
    }
    else if (flags.count(cmd)) {
        string label; ss >> label;
        if (!label.empty() && label[0] == '@') label = label.substr(1);
        int addr = tag_id.count(label) ? tag_id[label] : parseHex(label);
        type_10(cmd, addr);
    }
}

void assembler(string fname) {
    ifstream file(fname);
    if (!file.is_open()) { cerr << RED << "File Error!" << RESET << endl; return; }

    program_counter = 0;
    tag_id.clear();
    ConstantsInProgram.clear();
    bincode.clear();

    string temp;
    // Pass 1: Capture Labels AND Constants
    while (getline(file, temp)) {
        temp = cleanLine(temp);
        stringstream ss(temp);
        string word; ss >> word;
        if (word.empty()) continue;

        if(word == "#include"){
            string name;
            ss >> name;
            // Handle optional quotes around filename
            if (!name.empty() && (name.front() == '"' || name.front() == '<')) {
                name = name.substr(1, name.length() - 2);
            }
            if(name == "ASCII"){
                for(size_t i = 0; i < ascii_characters.size(); i++){
                    ConstantsInProgram[ascii_name[i]] = parseHex("0x" + ascii_characters[i]);
                }
            }
            continue;
        }

        if (word == "#define") {
            string name, val;
            ss >> name >> val;
            ConstantsInProgram[name] = parseHex(val);
        } 
        else if (word[0] == '@') {
            tag_id[word.substr(1)] = program_counter;
        } 
        else {
            program_counter++;
        }
    }
    
    // Pass 2: Generate Code
    file.clear(); file.seekg(0);
    program_counter = 0; 
    while (getline(file, temp)) {
        define_type(temp);
    }
    file.close();
    assembled = true; iamsure = false;
    cout << GREEN << "> Assembly complete! Lines: " << bincode.size() << RESET << endl;
}

int main() {
    initial_command();
    string full_command;

    while (true) {
        cout << YELLOW << "> " << RESET;
        if (!getline(cin >> ws, full_command)) break;

        if (full_command == "exit") {
            break;
        } 
        else if (full_command == "help") {
            initial_command();
        } 
        else if (full_command == "view hex") {
            if (assembled) {
                if (!iamsure) {
                    binToHex();
                    iamsure = true;
                }
                for (const string& s : hexcode) {
                    cout << GREEN << s << RESET << endl;
                }
            } else {
                cout << RED << "> You must assemble a file first" << RESET << endl;
            }
        } 
        else if (full_command == "view bin") {
            if (assembled) {
                for (const string& s : bincode) {
                    cout << GREEN << s << RESET << endl;
                }
            } else {
                cout << RED << "> You must assemble a file first" << RESET << endl;
            }
        } 
        else if (full_command == "view const") {
            if (assembled) {
                cout << CYAN << "Labels:" << RESET << endl;
                for (auto const& [key, val] : tag_id) {
                    cout << GREEN << key << RESET << ": " << val << endl;
                }
                cout << CYAN << "Constants:" << RESET << endl;
                for (auto const& [key, val] : ConstantsInProgram) {
                    cout << GREEN << key << RESET << ": " << val << endl;
                }
            } else {
                cout << RED << "> You must assemble a file first" << RESET << endl;
            }
        } 
        else if (full_command == "assemble") {
            cout << YELLOW << "> enter the filename: " << RESET << endl;
            cout << YELLOW << "> " << RESET;
            getline(cin >> ws, filename);
            assembler(filename);
        } 
        else if (full_command == "fun") {
            cout << RED << BOLD << endl;
            cout << "   ** ** " << endl;
            cout << " **** **** " << endl;
            cout << " ********* " << endl;
            cout << "  ******* " << endl;
            cout << "   ***** " << endl;
            cout << "    *** " << endl;
            cout << "     * " << endl;
            cout << RESET << endl;
            cout << CYAN << "> SCESNA sends its regards! <" << RESET << endl;
        }
        else {
            cout << RED << "> Unknown command: " << full_command << RESET << endl;
        }
    }
    return 0;
}