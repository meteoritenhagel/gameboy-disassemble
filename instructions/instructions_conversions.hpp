#include <iomanip>
#include <iostream>
#include <sstream>

template<typename T>
std::string to_string_hex(const T number, const uint8_t digits) {
    std::stringstream buffer;
    buffer << std::setw(digits) << std::setfill('0') << std::fixed
           << std::hex << std::uppercase
           << +number; // '+' is necessary to avoid uint8_t being displayed as character
    return buffer.str();
}

template<typename T>
std::string to_string_hex_prefixed(const T number, const uint8_t digits) {
    return "0x" + to_string_hex(number, digits);
}