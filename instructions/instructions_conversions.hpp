#include <iomanip>
#include <iostream>
#include <sstream>

template<typename T>
bool is_negative(const T number)
{
    return (number & (1 << (sizeof(T)*8 - 1)));
}

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

template<typename T>
std::string to_string_hex_signed_prefixed(const T number, const uint8_t digits) {
    const std::string sign = (is_negative(number)) ? "-" : "+";
    const T signedNumber = (is_negative(number)) ? -number : +number;
    return sign + "0x" + to_string_hex(signedNumber, digits);
}