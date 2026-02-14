#include <cstring>
#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>

#include "inputer.h"
#include "stringMethods.h"
#include "korobochka.h"


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
    auto* strPtr = new std::string;
    *strPtr = "Hello world!";

    auto* strPtr2 = new std::string;
    *strPtr2 = "Hello world!\n:)";

    auto* strPtrKorobka2 = new std::string;
    *strPtrKorobka2 = "Hello world!\n:)";

    auto* strPtrKorobka22 = new std::string;
    *strPtrKorobka22 = "Hello world!\n:)";

    auto* strPtrKorobka3 = new std::string;
    *strPtrKorobka3 = "Hello world!\n\n\n\n\n:)"; // 16


    auto* korobka3 = new Korobochka::Korobka{1,1};
    Korobochka::ElementData elementKor3{Korobochka::Tstr, strPtrKorobka3};
    korobka3 -> data.push_back(std::move(elementKor3));

    auto* korobka2 = new Korobochka::Korobka{3,1};

    Korobochka::ElementData elementKor2{Korobochka::Tstr, strPtrKorobka2};
    Korobochka::ElementData elementKor22{Korobochka::Tstr, strPtrKorobka22};
    Korobochka::ElementData elementKor23{Korobochka::Tkorobka, korobka3};

    korobka2 -> data.push_back(std::move(elementKor2));
    korobka2 -> data.push_back(std::move(elementKor22));
    korobka2 -> data.push_back(std::move(elementKor23));

    Korobochka::ElementData element{Korobochka::Tstr, strPtr};
    Korobochka::ElementData element2{Korobochka::Tstr, strPtr2};
    Korobochka::ElementData element3{Korobochka::Tkorobka, korobka2};

    Korobochka::Korobka korobka{3, 1};

    korobka.data.push_back(std::move(element));
    korobka.data.push_back(std::move(element2));
    korobka.data.push_back(std::move(element3));

    korobka.calcAlignYPerLine();
    korobka.calcAlignXPerX();
        // korobka.data.emplace_back(Korobochka::Tstr, strPtr);
    std::cout << "Y align:" << std::endl;
    for (auto i : korobka.yAlignPerY) {
        std::cout << i << std::endl;
    }

    for (auto y : static_cast<Korobochka::Korobka*>(korobka.data[2].data)->yAlignPerY) {
        std::cout << y << std::endl;
    }

    std::cout << "x align:" << std::endl;
    for (auto x: korobka.xAlignPerX) {
        std::cout << x << std::endl;
    }

    return 0;
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