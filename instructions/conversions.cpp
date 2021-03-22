#include "conversions.h"

#include "constants.h"

byte get_least_significant_byte(const word wrd) {
    return static_cast<byte>(wrd & 0x00FF);
}

byte get_most_significant_byte(const word wrd) {
    return static_cast<byte>(wrd >> 8);
}

word little_endian_to_number(const byte lsb, const byte msb) {
    return ((msb << 8) | lsb);
}

word big_endian_to_number(const byte msb, const byte lsb) {
    return ((msb << 8) | lsb);
}

word extend_sign(const byte number) {
    return is_negative(number) ? (0xFF00 | number) : (0x0000 | number);
}

bytestring to_bytestring_little_endian(const word number) {
    return bytestring{get_least_significant_byte(number), get_most_significant_byte(number)};
}

bytestring opcode_to_bytestring(const Opcode opcode) {
    if (0x0000 <= opcode && opcode <= 0x00FF)
    {
        return bytestring{static_cast<byte>(opcode)};
    }
    else
    {
        // split into prefix and opcode
        return bytestring{get_most_significant_byte(opcode), get_least_significant_byte(opcode)};
    }
}

bytestring to_bytestring(const Opcode opcode, const bytestring &arguments) {
    bytestring bytestr = opcode_to_bytestring(opcode);
    append_to_bytestring(bytestr, arguments);
    return bytestr;
}