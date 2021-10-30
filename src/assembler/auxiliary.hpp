#include "pretty_format.h"

template<typename T>
std::string to_string(const std::vector<T> &vector) {
    std::string str{};

    if (vector.size() == 1) {
        str += to_string(vector[0]);
    } else if (vector.size() > 1) {
        for (size_t i = 0; i < vector.size() - 1; ++i) {
            str += to_string(vector[i]) + ", ";
        }

        str += "or " + to_string(vector[vector.size() - 1]);
    }

    return str;
}

template<typename ExceptionType>
void throw_exception_and_highlight(const std::string &code, const size_t lineNumber, const size_t columnNumber,
                                   const std::string &errorMessage, const size_t highlightWidth) {
    std::string extendedString = errorMessage + " at " + get_position_string(lineNumber, columnNumber) + '\n';
    if (!code.empty()) {
        extendedString += to_string_line_and_highlight(code, lineNumber, columnNumber, highlightWidth);
    }
    throw ExceptionType(extendedString);
}

template<typename ExceptionType>
void throw_exception_and_highlight_with_reference(const std::string &code, const size_t lineNumber,
                                                  const size_t columnNumber, const size_t referenceLineNumber,
                                                  const size_t referenceColumnNumber, const std::string &errorMessage,
                                                  const size_t highlightWidth, const size_t referenceHighlightWidth) {
    std::string extendedString = errorMessage + " at " + get_position_string(lineNumber, columnNumber) + '\n';
    if (!code.empty()) {
        extendedString += to_string_line_and_highlight(code, lineNumber, columnNumber, highlightWidth);
        extendedString += "The expression is referring to\n";
        extendedString += to_string_line_and_highlight(code, referenceLineNumber, referenceColumnNumber, referenceHighlightWidth);
    }
    throw ExceptionType(extendedString);
}