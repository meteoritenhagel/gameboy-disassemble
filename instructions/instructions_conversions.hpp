#include <iomanip>
#include <iostream>
#include <sstream>

template<typename T>
bool is_negative(const T number) {
    return (number & (1 << (sizeof(T) * 8 - 1)));
}

template<typename T>
T twos_complement(const T number) {
    return ~number + 1;
}

template<typename T>
std::string to_string_hex(const T number, const byte digits) {
    std::stringstream buffer;
    buffer << std::setw(digits) << std::setfill('0') << std::fixed
           << std::hex << std::uppercase
           << +number; // '+' is necessary to avoid byte being displayed as character
    return buffer.str();
}

template<typename T>
std::string to_string_dec(const T number) {
    std::stringstream buffer;
    buffer << +number; // '+' is necessary to avoid byte being displayed as character
    return buffer.str();
}

template<typename T>
std::string to_string_hex_prefixed(const T number, const byte digits) {
    return "0x" + to_string_hex(number, digits);
}

template<typename T>
std::string to_string_hex_signed_prefixed(const T number, const byte digits) {
    const std::string sign = (is_negative(number)) ? "-" : "+";
    const T signedNumber = (is_negative(number)) ? twos_complement(number) : number;
    return sign + "0x" + to_string_hex(signedNumber, digits);
}