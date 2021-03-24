#include <iomanip>
#include <iostream>
#include <sstream>

template<typename T>
bool is_negative(const T number) {
    return (number & (1 << (sizeof(T) * 8 - 1)));
}

template<typename T>
bool is_unsigned_8_bit(const T num) {
    return (0 <= num && num <= 255);
}

template<typename T>
bool is_signed_8_bit(const T num) {
    return (-128 <= num && num <= 127);
}

template<typename T>
bool is_8_bit(const T num) {
    return is_signed_8_bit(num) || is_unsigned_8_bit(num);
}

template<typename T>
bool is_unsigned_16_bit(const T num) {
    return (0 <= num && num <= 65535);
}

template<typename T>
bool is_signed_16_bit(const T num) {
    return (-32768 <= num && num <= 32767);
}

template<typename T>
bool is_16_bit(const T num) {
    return is_signed_16_bit(num) || is_unsigned_16_bit(num);
}

template<typename T>
bool is_index(const T num) {
    return (0 <= num) && (num <= 7);
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