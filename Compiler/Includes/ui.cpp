#include <iostream>
#include "ui.h"

void InitialCommand() {
    std::cout << CYAN << "==========================================================\n";
    std::cout << CYAN << "   _____  _____ _               _   _   _____   \n";
    std::cout << CYAN << "  / ____|/ ____| |     /\\      | \\ | | / ____|  \n";
    std::cout << CYAN << " | (___ | |    | |    /  \\     |  \\| || |  __   \n";
    std::cout << CYAN << "  \\___ \\| |    | |   / /\\ \\    | . ` || | |_ |  \n";
    std::cout << CYAN << "  ____) | |____| |__/ ____ \\   | |\\  || |__| |  \n";
    std::cout << CYAN << " |_____/ \\_____|_____/     \\   \\_\\  |_| \\_| \\_____|  \n";
    std::cout << CYAN << "==========================================================\n";
    std::cout << BOLD << GREEN << "              Sclang Custom Compiler v1.0\n\n";
    std::cout << RESET << "   Target Architecture: " << GREEN  << "SCESNA 16-Bit CPU\n";
    std::cout << RESET << "   Memory Capacity:     " << GREEN << "4096 Words\n";
    std::cout << CYAN << "==========================================================\n\n";
}
