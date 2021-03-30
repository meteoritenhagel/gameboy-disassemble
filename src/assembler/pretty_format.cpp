#include "pretty_format.h"

#include <iomanip>

std::string to_pretty_string(const Token& token) noexcept {
    std::ostringstream outputStream;
    outputStream << std::setw(13) << std::left << to_string(token.get_token_type()) << " ";
    outputStream << std::setw(4) << std::right << token.get_line() << ":" << std::setw(4) << std::left << token.get_column() << " ";
    outputStream << std::setw(10) << std::left << token.get_string();
    if (token.has_numeric_value())
    {
        outputStream << " " << token.get_numeric();
    }
    return outputStream.str();
}

std::string get_position_string(const size_t lineNumber, const size_t columnNumber) noexcept {
    return std::to_string(lineNumber) + ":" + std::to_string(columnNumber);
}

std::string separated_line(const std::string &left, const std::string &right) {
    std::ostringstream ostr;
    ostr << std::setw(6) << left << " |    " << right << '\n';
    return ostr.str();
}

std::string to_string_with_line_numbers(const std::string &code) {
    std::ostringstream ostr;
    std::istringstream iss(code);
    std::string line;

    size_t lineNumber = 1;

    while (std::getline(iss, line))
    {
        ostr << separated_line(std::to_string(lineNumber), line) << '\n';
        ++lineNumber;
    }

    return ostr.str();
}

std::string to_string_single_line(const std::string &code, const size_t lineNumber) {
    std::istringstream iss(code);
    std::string line;

    for (size_t i = 0; i < lineNumber; ++i)
    {
        std::getline(iss, line);
    }

    return separated_line(std::to_string(lineNumber), line);
}

std::string to_string_line_and_highlight(const std::string &code, const size_t lineNumber, const size_t columnNumber, const size_t highlightWidth) {
    std::ostringstream ostr;

    const std::string highlighter{ "^" + std::string(std::max(highlightWidth-1, 0UL), '~')};

    const size_t repetitions = std::max(columnNumber, 1UL) - 1;
    const std::string returnString = to_string_single_line(code, lineNumber)
                                   + separated_line(" ", std::string(repetitions, ' ') + highlighter);

    return returnString;
}