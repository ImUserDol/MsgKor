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

std::size_t getMaxX(std::string_view str) {
     std::size_t maxX = 0;
     std::size_t i = 0;

     std::size_t newX = str.find('\n', i);
     while (newX != std::string_view::npos) {
         if (newX - i > maxX) {
             maxX = newX - i;
         }

         i = newX + 1;
         newX = str.find('\n', i);
     }

    if (str.length() - i > maxX) {
        maxX = str.length() - i;
    }

    return maxX;
}


std::size_t getCountY(std::string_view str) {
    std::size_t count = 0;
    std::size_t i = 0;
    while (str.find('\n', i) != std::string_view::npos) {
        count++;
        i = str.find('\n', i) + 1;
    }
    return count + 1;
}


std::size_t printY(std::string_view str, std::size_t& indexPrint) {
    std::string printStr;
    std::size_t len = 0;

    std::size_t lastIndexPrint = indexPrint;

    if (str.find('\n', indexPrint) == std::string_view::npos) {
        len = str.length() - indexPrint;
        indexPrint = str.length();
    } else {
        std::size_t nextY = str.find('\n', indexPrint);
        len = nextY - indexPrint;

        indexPrint = nextY + 1;
    }

    printStr.resize(len);
    std::memcpy(printStr.data(), str.data() + lastIndexPrint, len);

    std::cout << printStr;

    return len;
}


void printLine(const std::string_view str, std::size_t& indexPrint, std::size_t globalXLen) {
    std::size_t lenPrinted = printY(str, indexPrint);
    std::string outStr;

    std::size_t CountSpacePrinted = globalXLen - lenPrinted;
    outStr.resize(CountSpacePrinted);

    std::fill_n(outStr.data(), CountSpacePrinted, ' ');
    std::cout << outStr;
}

int main() {

    std::size_t countMessages = 0;
    std::cin >> countMessages;

    std::vector<std::string> strs(countMessages);

    std::cin.ignore();


    std::size_t totalLen = 2 + (countMessages * 3) - 1;

    std::vector<std::size_t> maxXLens(countMessages);
    std::vector<std::size_t> IndexPrintAfter(countMessages, 0);

    std::size_t maxY = 0;

    for (std::size_t i = 0; i < countMessages; i++) {
        getLineWithQoutes(strs[i]);
        maxXLens[i] = getMaxX(strs[i]);

        totalLen += getMaxX(strs[i]);

        maxY = maxY > getCountY(strs[i]) ? maxY : getCountY(strs[i]);
    }

    printFirstAndLastLine(totalLen);

    for (std::size_t y = 0; y < maxY; y++) {
        std::cout << '|';

        for (std::size_t i = 0; i < strs.size(); i++) {
            std::cout << ' ';
            printLine(strs[i], IndexPrintAfter[i], maxXLens[i]);
            std::cout << " |";
        }

        std::cout << std::endl;
    }

    printFirstAndLastLine(totalLen);

    return 0;
}