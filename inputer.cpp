//
// Created by WhoIM on 2/12/26.
//

#include "inputer.h"

#include <cstring>
#include <istream>

enum QuotedType : unsigned char {
    unintialized,
    oneQuoted = '\'',
    doubleQuoted = '"'
};

std::size_t QuoteEndIndex(std::string_view str) {
    bool quoted = false;
    bool backslash = false;
    QuotedType quotedT = unintialized;

    for (std::size_t i = 0; i < str.length(); i++) {
        if (backslash) {
            backslash = false;
        } else if (str[i] == '\\') {
            backslash = true;
        } else if (str[i] == '\'' || str[i] == '"') {
            if (quoted) {
                if (quotedT == str[i]) {
                    return i;
                }
            } else {
                quotedT = static_cast<QuotedType>(str[i]);
                quoted = true;
            }
        }
    }

    return -1;
}

bool haveFirstQuotedSymbol(std::string_view str) {
    for (auto character : str) {
        if (!std::isspace(character)) {
            if (character == '"' || character == '\'')
                return true;

            return false;
        }
    }

    return false;
}


std::size_t getFirstQuote(std::string_view str) {
    bool backslash = false;

    for (std::size_t i = 0; i < str.length(); i++) {
        if (backslash) {
            backslash = false;
        } else if (str[i] == '\\') {
            backslash = true;
        } else if (str[i] == '\'' || str[i] == '"') {
            return i;
        }
    }
    return str.length();
}

std::size_t getFirstNotSpaceSymbol(std::string_view str) {
    std::size_t i = 0;
    for (; i < str.length() && std::isspace(str[i]); i++) {}

    return i;
}

void getLineWithQoutes(std::string& str, std::istream& stream) {
    std::getline(stream, str);
    if (haveFirstQuotedSymbol(str)) {
        while (QuoteEndIndex(str) == -1) {
            str += '\n';

            std::string tmpStr;
            std::getline(stream, tmpStr);

            str += tmpStr;
        }
        str.resize(QuoteEndIndex(str) + 1);

        std::size_t firstSymbol = getFirstNotSpaceSymbol(str);
        std::memcpy(str.data(), str.data() + firstSymbol, str.length() - firstSymbol);
        str.resize(str.length() - firstSymbol);
        std::memcpy(str.data(), str.data() + 1, str.length() - 1);
        str.resize(str.length() - 2);
    } else {
        str.resize(getFirstQuote(str));

        std::size_t firstSymbol = getFirstNotSpaceSymbol(str);
        std::memcpy(str.data(), str.data() + firstSymbol, str.length() - firstSymbol);
        str.resize(str.length() - firstSymbol);
    }
}