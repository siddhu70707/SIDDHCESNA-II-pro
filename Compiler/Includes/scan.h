#ifndef SCAN_H
#define SCAN_H
#include <vector>
#include "lexer.h"

// colors
#define RESET   "\033[0m"
#define RED     "\033[31m"      
#define GREEN   "\033[32m"     
#define YELLOW  "\033[33m"      
#define CYAN    "\033[36m"      
#define BOLD    "\033[1m"


extern void MemoryAllocation(const std::vector<Token> &tokens);

#endif