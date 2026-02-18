//
// Created by WhoIM on 2/12/26.
//

#include "korobochka.h"

#include <cstring>
#include <iostream>
#include <ostream>
#include <string>
#include "stringMethods.h"


namespace Korobochka {
    ElementData::~ElementData() {
        switch (type) {
            case Tkorobka: {
                static_cast<Korobka*>(data) -> ~Korobka();
                break;
            }
            case Tstr: {
                if (data) {
                    auto* str = static_cast<std::string*>(data);
                    delete str;

                    data = nullptr;
                }
            }
             default: {}
        }
    }




    ElementData::ElementData(ElementData&& other) noexcept {
        type = other.type;
        data = other.data;

        other.data = nullptr;
        other.type = uninitialized;
    };

    ElementData &ElementData::operator=(const ElementData &other) {
        if (this != &other) {
            type = other.type;
            data = other.data;
        }
        return *this;
    }

    constexpr ElementData::ElementData(const ElementData& element_data) {
        type = element_data.type;
        data = element_data.data;
    }

    void Korobka::printKorobka() {
        std::string resultString;

        while (yPrint != -1) {
            std::vector<stackSaveX> stackPrints;
            std::size_t result = 0;
            stackPrints.emplace_back(0, *this);

            while (!stackPrints.empty()) {
                auto& korobkaNow = stackPrints.back();
                std::size_t totalAlign = 1;

                for (auto i : korobkaNow.korobka.xAlignPerX) {
                    totalAlign += i+3;
                }

                if (!korobkaNow.korobka.StartLinePrinted || korobkaNow.korobka.yPrint == -1 || korobkaNow.korobka.yAlignPerY[korobkaNow.korobka.yPrint] == 0) {
                    korobkaNow.korobka.StartLinePrinted = true;


                    result = totalAlign;

                    std::string tmpStr;
                    tmpStr.resize(totalAlign);

                    char characterPrint = '-';
                    if (korobkaNow.korobka.yPrint == -1) {
                        characterPrint = ' ';
                    } else {
                        if (korobkaNow.korobka.yAlignPerY[korobkaNow.korobka.yPrint] == 0) {
                            std::fill_n(korobkaNow.korobka.nextXPrint.begin(), korobkaNow.korobka.nextXPrint.size(), 0);
                            korobkaNow.korobka.yPrint = korobkaNow.korobka.yAlignPerY.size()-1 == korobkaNow.korobka.yPrint ? -1 : korobkaNow.korobka.yPrint + 1;
                        }
                    }
                    std::fill_n(tmpStr.begin(), tmpStr.size(), characterPrint);
                    resultString += tmpStr;

                    stackPrints.pop_back();
                    continue;
                }

                if (korobkaNow.xParse != 0) {
                    std::size_t alignX = korobkaNow.korobka.xAlignPerX[korobkaNow.xParse-1] - result;

                    for (std::size_t i = 0; i < alignX; i++) {
                        resultString += ' ';
                    }

                    resultString += ' ';
                }

                resultString += '|';

                bool korobkaFinded = false;


                for (;korobkaNow.xParse < korobkaNow.korobka.countX; korobkaNow.xParse++) {
                    auto& element = korobkaNow.korobka.data[korobkaNow.korobka.yPrint * korobkaNow.korobka.countX + korobkaNow.xParse];

                    resultString += ' ';
                    if (element.type == Tstr) {
                        std::size_t pos = korobkaNow.korobka.nextXPrint[korobkaNow.xParse];
                        std::size_t lineSize = stringMethods::getLineSize(static_cast<std::string*>(element.data), pos);
                        korobkaNow.korobka.nextXPrint[korobkaNow.xParse] = pos + lineSize + (pos+lineSize == static_cast<std::string*>(element.data)->length() ? 0 : 1);

                        resultString.append(static_cast<std::string*>(element.data)->data() + pos, lineSize);

                        std::size_t alignCount = korobkaNow.korobka.xAlignPerX[korobkaNow.xParse] - lineSize;
                        for (std::size_t i = 0; i < alignCount; i++) {
                            resultString += ' ';
                        }

                        resultString += " |";
                    } else {
                        korobkaNow.xParse++;
                        stackPrints.emplace_back(0, *static_cast<Korobka*>(element.data));
                        korobkaFinded = true;
                        break;
                    }
                }

                if (korobkaFinded) {
                    continue;
                }

                result = totalAlign;

                korobkaNow.korobka.yAlignPerY[korobkaNow.korobka.yPrint]--;
                stackPrints.pop_back();
            }
            resultString += '\n';
        }

        std::cout << resultString << std::endl;
    }

    void Korobka::calcAlignXPerX() {
        for (std::size_t x = 0; x < countX; x++) {
            for (std::size_t y = 0; y < countY; y++) {

                auto& firstTableElement = data[y*countX + x];

                if (firstTableElement.type == Tstr) {
                    xAlignPerX[x] = std::max(stringMethods::getMaxX(static_cast<std::string*>(firstTableElement.data)), xAlignPerX[x]);
                } else {
                    std::vector<stackKorobok> StackKorobok;
                    StackKorobok.emplace_back(0, 0, *static_cast<Korobka*>(firstTableElement.data));

                    std::size_t lastMaxX = 0;

                    while (!StackKorobok.empty()) {
                        auto& element = StackKorobok.back();

                        if (element.yParse != 0) {
                            element.korobka.xAlignPerX[element.xParse] = std::max(lastMaxX, element.korobka.xAlignPerX[element.xParse]);
                        }

                        bool findedKorobka = false;

                        for (; element.xParse < element.korobka.countX; element.xParse++) {
                            for (; element.yParse < element.korobka.countY; element.yParse++) {
                                auto& elementInKorobka = element.korobka.data[element.yParse * element.korobka.countX + element.xParse];
                                if (elementInKorobka.type == Tstr) {
                                    std::size_t countX = stringMethods::getMaxX(static_cast<std::string*>(elementInKorobka.data));
                                    element.korobka.xAlignPerX[element.xParse] = std::max(countX, element.korobka.xAlignPerX[element.xParse]);
                                } else {
                                    element.yParse++;
                                    StackKorobok.emplace_back(0,0, *static_cast<Korobka*>(elementInKorobka.data));
                                    findedKorobka = true;
                                    break;
                                }
                            }

                            if (findedKorobka)
                                break;

                            element.yParse = 0;
                        }

                        if (findedKorobka)
                            continue;

                        lastMaxX = 1;

                        for (auto alignX: element.korobka.xAlignPerX) {
                            lastMaxX += alignX+3;
                        }

                        StackKorobok.pop_back();
                    }

                    xAlignPerX[x] = std::max(lastMaxX, xAlignPerX[x]);
                }
            }
        }
    }

    void Korobka::calcAlignYPerLine() {
        for (std::size_t y = 0; y < countY; y++) {

            std::size_t maxY = 0;

            for (std::size_t x = 0; x < countX; x++) {

                if (data[y*countX + x].type == Tstr) {
                    std::size_t countY = stringMethods::getCountY(static_cast<std::string*>(data[y*countX + x].data));
                    maxY = countY > maxY ? countY : maxY;
                } else {
                    std::size_t lastMaxY = 0;

                    std::vector<stackKorobok> StackKorobok;
                    StackKorobok.emplace_back(0, 0, *static_cast<Korobka*>(data[y*countX + x].data));
                    while (!StackKorobok.empty()) {
                        auto& element = StackKorobok.back();

                        if (element.yParse != 0) {
                            element.korobka.yAlignPerY[element.yParse - 1] = std::max(element.korobka.yAlignPerY[element.yParse - 1], lastMaxY);
                        }

                        bool findedKorobka = false;

                        for (; element.xParse < element.korobka.countX; element.xParse++) {
                            for (; element.yParse < element.korobka.countY; element.yParse++) {

                                auto& elementInKorobka = element.korobka.data[element.yParse * element.korobka.countX + element.xParse];
                                if (elementInKorobka.type == Tstr) {
                                    std::size_t countY = stringMethods::getCountY(static_cast<std::string*>(elementInKorobka.data));
                                    element.korobka.yAlignPerY[element.yParse] = std::max(element.korobka.yAlignPerY[element.yParse], countY);

                                } else {
                                    element.yParse++;
                                    StackKorobok.emplace_back(0,0, *static_cast<Korobka*>(elementInKorobka.data));
                                    findedKorobka = true;
                                    break;
                                }
                            }

                            if (findedKorobka)
                                break;

                            element.yParse = 0;
                        }

                        if (findedKorobka)
                            continue;

                        lastMaxY = 0;
                        for (auto i: element.korobka.yAlignPerY) {
                            lastMaxY += i+2;
                        }

                        StackKorobok.pop_back();
                    }
                    maxY = lastMaxY > maxY ? lastMaxY : maxY;

                }
            }

            yAlignPerY[y] = maxY;
        }
    }
} // korobochka