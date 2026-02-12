#include <cstring>
#include <iostream>
#include <vector>
#include <string>

#include "inputer.h"
#include "stringMethods.h"

void printFirstAndLastLine(std::size_t len) {
    std::string startEndLine;
    startEndLine.resize(len);
    startEndLine[0] = '|';
    std::fill_n(startEndLine.begin() + 1, len - 2, '-');
    startEndLine[startEndLine.length()-1] = '|';
    std::cout << startEndLine << std::endl;
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
        getLineWithQoutes(strs[i], std::cin);
        maxXLens[i] = stringMethods::getMaxX(strs[i]);

        totalLen += stringMethods::getMaxX(strs[i]);

        maxY = maxY > stringMethods::getCountY(strs[i]) ? maxY : stringMethods::getCountY(strs[i]);
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