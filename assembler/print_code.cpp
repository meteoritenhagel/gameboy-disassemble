#include "print_code.h"

#include <iomanip>

std::string separated_line(const std::string &left, const std::string &right)
{
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

/*********************/

//void Printer::print(const std::string &message) const {
//    _ostr << message;
//}
