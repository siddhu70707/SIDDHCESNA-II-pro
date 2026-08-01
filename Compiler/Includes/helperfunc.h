#pragma once
#include <cstdint>
#include <array>
#include <string>
#include <utility>
#include <unordered_map>

extern std::array<std::pair<uint16_t, std::string>, 4096> memory;
extern uint16_t IsOccupied; // memory is linear no operations in between

extern int calculateHelper(const string& s);
extern unordered_map<string, uint16_t> identifierlist;