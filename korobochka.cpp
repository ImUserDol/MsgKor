//
// Created by WhoIM on 2/12/26.
//

#include "korobochka.h"

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
                    // std::cout << "Deleting str: " << *str << std::endl;
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


    void Korobka::calcAlignXPerX() {
        for (std::size_t x = 0; x < countX; x++) {
            for (std::size_t y = 0; y < countY; y++) {

                auto& firstTableElement = data[y*countX + x];

                if (firstTableElement.type == Tstr) {
                    xAlignPerX[x] = std::max(stringMethods::getMaxX(static_cast<std::string*>(firstTableElement.data)), xAlignPerX[x]);
                } else {
                    std::vector<calcXAlignStack> StackKorobok;
                    StackKorobok.emplace_back(0, 0, 0, *static_cast<Korobka*>(firstTableElement.data));

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
                                    StackKorobok.emplace_back(0,0,0, *static_cast<Korobka*>(elementInKorobka.data));
                                    findedKorobka = true;
                                    element.yParse++;
                                    break;
                                }
                            }

                            if (findedKorobka)
                                break;

                            element.yParse = 0;
                        }

                        if (findedKorobka)
                            continue;

                        lastMaxX = 2;

                        for (auto alignX: element.korobka.xAlignPerX) {
                            lastMaxX += alignX+2;
                        }
                        element.maxXTotal = lastMaxX;
                        StackKorobok.pop_back();
                    }

                    xAlignPerX[x] = std::max(lastMaxX, xAlignPerX[x]);

                    // StackKorobok.emplace_back();
                }
            }
        }
    }

    void Korobka::calcAlignYPerLine() {
        for (std::size_t y = 0; y < countY; y++) {

            std::size_t maxY = 0;

            for (std::size_t x = 0; x < countX; x++) {
                // std::cout << "index:" << y*countX + x << std::endl;
                // std::cout << "Size: " << data.size() << std::endl;

                if (data[y*countX + x].type == Tstr) {
                    std::size_t countY = stringMethods::getCountY(static_cast<std::string*>(data[y*countX + x].data));
                    maxY = countY > maxY ? countY : maxY;
                } else {

                    std::size_t lastMaxY = 0;

                    std::vector<calcYStack> StackKorobok;
                    StackKorobok.emplace_back(0, 0, 0, 0, *static_cast<Korobka*>(data[y*countX + x].data));

                    while (!StackKorobok.empty()) {
                        auto& element = StackKorobok.back();

                        if (element.yParse != 0) {
                            element.korobka.yAlignPerY[element.yParse - 1] = std::max(element.korobka.yAlignPerY[element.yParse - 1], lastMaxY);
                            element.yInXNow += lastMaxY;
                        }

                        bool findedKorobka = false;

                        for (; element.xParse < element.korobka.countX; element.xParse++) {
                            for (; element.yParse < element.korobka.countY; element.yParse++) {

                                // std::cout << " y:" << yElem << " xParse:" << element.xParse << " countY:" << element.korobka.countY << " countX:" << element.korobka.countX << std::endl;
                                auto& elementInKorobka = element.korobka.data[element.yParse * element.korobka.countX + element.xParse];
                                if (elementInKorobka.type == Tstr) {
                                    std::size_t countY = stringMethods::getCountY(static_cast<std::string*>(elementInKorobka.data));
                                    element.korobka.yAlignPerY[element.yParse] = std::max(element.korobka.yAlignPerY[element.yParse], countY);

                                    element.yInXNow += countY;
                                    // std::cout << "after" << std::endl;
                                } else {
                                    element.yParse++;
                                    StackKorobok.emplace_back(0,0,0,0, *static_cast<Korobka*>(elementInKorobka.data));
                                    findedKorobka = true;
                                    break;
                                    //Брякнуться из этого ебанутого цикла
                                }
                            }

                            if (findedKorobka)
                                break;

                            element.maxY = element.yInXNow > element.maxY ? element.yInXNow : element.maxY;
                            element.yInXNow = 0;
                            element.yParse = 0;
                            //Тут тоже
                        }

                        if (findedKorobka)
                            continue;

                        lastMaxY = element.maxY + 2;
                        StackKorobok.pop_back();
                        //Обработать выход тут
                    }

                    maxY = lastMaxY > maxY ? lastMaxY : maxY;

                }
            }

            yAlignPerY[y] = maxY;
        }
    }
} // korobochka