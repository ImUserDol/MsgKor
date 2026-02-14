//
// Created by WhoIM on 2/12/26.
//

#ifndef MSGKOR_KOROBOCHKA_H
#define MSGKOR_KOROBOCHKA_H
#include <vector>

namespace Korobochka {

    enum TypeElem {
        uninitialized = 0,
        Tkorobka,
        Tstr
    };

    // TODO дореализовывать inPrint структуру
    struct ElementData {
        TypeElem type{uninitialized};
        void* data{};

        ~ElementData();
        ElementData(ElementData&& other) noexcept;
        ElementData(TypeElem type, void* data): type(type), data(data) {};
    };

    class Korobka;

    struct stackKorobok {
        std::size_t xParse = 0;
        std::size_t yParse = 0;

        Korobka& korobka;

        stackKorobok(std::size_t parseX, std::size_t parseY, Korobka& korobka) : xParse(parseX), yParse(parseY), korobka(korobka) {};
    };

    struct calcYStack : stackKorobok {
        std::size_t maxY = 0;
        std::size_t yInXNow = 0;

        calcYStack(std::size_t maxY, std::size_t yInXNow, std::size_t parseX, std::size_t parseY, Korobka& korobka): maxY(maxY), yInXNow(yInXNow), stackKorobok(parseX, parseY, korobka) {};
    };

    struct calcXAlignStack : stackKorobok {
        std::size_t maxXTotal = 0;

        calcXAlignStack(std::size_t maxXInY, std::size_t parseX, std::size_t parseY, Korobka& korobka): maxXTotal(maxXInY), stackKorobok(parseX, parseY, korobka) {};
    };


    class Korobka {
        public:
        std::size_t countX;
        std::size_t countY;

        std::vector<std::size_t> yAlignPerY;

        std::vector<std::size_t> xAlignPerX;

        std::vector<ElementData> data;


        void calcAlignXPerX();
        void calcAlignYPerLine();

        Korobka(std::size_t xCount, std::size_t yCount): countX(xCount), countY(yCount) {
            yAlignPerY.resize(countY, 0);
            xAlignPerX.resize(countX, 0);
        };
    };
} // korobochka

#endif //MSGKOR_KOROBOCHKA_H