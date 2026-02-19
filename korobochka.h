//
// Created by WhoIM on 2/12/26.
//

#ifndef MSGKOR_KOROBOCHKA_H
#define MSGKOR_KOROBOCHKA_H
#include <vector>

#include "korobochka.h"

namespace Korobochka {

    enum TypeElem {
        uninitialized = 0,
        Tkorobka,
        Tstr
    };

    struct ElementData {
        TypeElem type{uninitialized};
        void* data{nullptr};


        ~ElementData();
        ElementData(ElementData&& other) noexcept;
        ElementData(TypeElem type, void* data): type(type), data(data) {};
        constexpr ElementData(const ElementData&);
        ElementData& operator=(const ElementData& other);
        constexpr ElementData() = default;

    };

    class Korobka;

    struct stackKorobok {
        std::size_t xParse = 0;
        std::size_t yParse = 0;

        Korobka& korobka;

        stackKorobok(std::size_t parseX, std::size_t parseY, Korobka& korobka) : xParse(parseX), yParse(parseY), korobka(korobka) {};
    };

    struct stackSaveX {
        std::size_t xParse = 0;
        Korobka& korobka;

        stackSaveX(std::size_t parseX, Korobka& korobka): xParse(parseX), korobka(korobka) {};
    };


    class Korobka {
        public:

        bool StartLinePrinted = false;
        std::size_t yPrint = 0;

        std::size_t countX;
        std::size_t countY;

        std::vector<std::size_t> yAlignPerY;
        std::vector<std::size_t> xAlignPerX;

        std::vector<std::size_t> nextXPrint;

        std::vector<ElementData> data;


        void calcAlignXPerX();
        void calcAlignYPerLine();
        void printKorobka();

        Korobka(std::size_t xCount, std::size_t yCount): countX(xCount), countY(yCount) {
            yAlignPerY.resize(countY, 0);

            xAlignPerX.resize(countX, 0);
            nextXPrint.resize(countX, 0);
        };

        Korobka(): Korobka(0,0) {};
    };

} // korobochka

#endif //MSGKOR_KOROBOCHKA_H
