#include <cstring>
#include <iostream>
#include <vector>
#include <string>



void printFirstAndLastLine(std::size_t len) {
    std::string startEndLine;
    startEndLine.resize(len);
    startEndLine[0] = '|';
    std::fill_n(startEndLine.begin() + 1, len - 2, '-');
    startEndLine[startEndLine.length()-1] = '|';
    std::cout << startEndLine << std::endl;
}


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

void getLineWithQoutes(std::string& str) {
    std::getline(std::cin, str);
    if (haveFirstQuotedSymbol(str)) {
        while (QuoteEndIndex(str) == -1) {
            str += '\n';

            std::string tmpStr;
            std::getline(std::cin, tmpStr);

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


// std::size_t getMaxX(std::string_view str) {
//     std::size_t maxX = 0;
//     std::size_t i = 0;
//
//     std::size_t newX = std::find(str.begin() + i);
//     while ()
// }

int main() {
    std::size_t countMessages = 0;
    std::cin >> countMessages;

    std::vector<std::string> strs(countMessages);

    std::cin.ignore();


    std::size_t totalLen = 2 + (countMessages * 3) - 1;
    std::vector<std::size_t> maxXLens(countMessages);

    for (std::size_t i = 0; i < countMessages; i++) {
        getLineWithQoutes(strs[i]);

        totalLen += strs[i].length();
    }

    printFirstAndLastLine(totalLen);
    std::cout << "|";

    for (auto& str : strs) {
        std::cout << ' ' << str << " |";
    }
    std::cout << std::endl;
    printFirstAndLastLine(totalLen);
    return 0;
}