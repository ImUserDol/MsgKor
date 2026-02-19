#include <iostream>
#include <vector>
#include <string>

#include "inputer.h"
#include "korobochka.h"
#include "stringMethods.h"


struct korobkaNode {
    Korobochka::Korobka& korobka;
    korobkaNode* prev = nullptr;
};


enum enteredType : unsigned char {
    uninitialized = 0,
    error,
    Tstr,
    Tkorobka
};



bool allSpace(std::string_view str) {
    std::size_t i = 0;
    for (; i < str.length() && std::isspace(str[i]); i++) {}

    return str.length() == i;
}

enteredType getEnteredType(std::string str) {
    for (auto& c : str) {
        c = std::tolower(c);
    }

    if (stringMethods::startwith(str, "str") && allSpace(str.data() + 3))
        return Tstr;
    if (stringMethods::startwith(str, "korobka") && allSpace(str.data() + 7))
        return Tkorobka;

    return error;
}

int main() {
    Korobochka::Korobka startKorobka;

    while (true) {
        std::cout << "Please enter a valid x and y for you korobka" << std::endl;
        std::cin >> startKorobka.countX >> startKorobka.countY;

        if (startKorobka.countX != 0 && startKorobka.countY != 0)
            break;
    }

    startKorobka.data.reserve(startKorobka.countX * startKorobka.countY);

    startKorobka.xAlignPerX.resize(startKorobka.countX, 0);
    startKorobka.yAlignPerY.resize(startKorobka.countY, 0);
    startKorobka.nextXPrint.resize(startKorobka.countX, 0);

    auto* korobkaLinkedList = new korobkaNode{startKorobka};
    bool newLinkedList = false;

    do {
        while (korobkaLinkedList->korobka.data.size() < korobkaLinkedList->korobka.countX * korobkaLinkedList->korobka.countY) {
            std::cout << "Please enter a type" << std::endl;
            std::string tmpStr;

            enteredType enteredType;
            do {
                getLineWithQoutes(tmpStr, std::cin);
                enteredType = getEnteredType(tmpStr);
            } while (enteredType == error);

            if (enteredType == Tstr) {
                auto* str = new std::string;
                std::cout << "Please enter a string" << std::endl;

                getLineWithQoutes(*str, std::cin);

                korobkaLinkedList->korobka.data.emplace_back(static_cast<Korobochka::TypeElem>(Tstr), str);
            } else {
                auto* nextKorobka = new Korobochka::Korobka();
                auto* tmpKorobkaLinkedList = new korobkaNode{*nextKorobka};

                tmpKorobkaLinkedList->prev = korobkaLinkedList;


                while (true) {
                    std::cout << "Please enter a valid x and y for you korobka" << std::endl;
                    std::cin >> nextKorobka->countX >> nextKorobka->countY;

                    if (nextKorobka->countX != 0 && nextKorobka->countY != 0)
                        break;
                }

                nextKorobka->data.reserve(nextKorobka->countX * nextKorobka->countY);
                nextKorobka->yAlignPerY.resize(nextKorobka->countY, 0);
                nextKorobka->xAlignPerX.resize(nextKorobka->countX, 0);
                nextKorobka->nextXPrint.resize(startKorobka.countX, 0);

                korobkaLinkedList->korobka.data.emplace_back(static_cast<Korobochka::TypeElem>(Tkorobka), nextKorobka);
                korobkaLinkedList = tmpKorobkaLinkedList;
                newLinkedList = true;
            }
        }

        if (newLinkedList) {
            newLinkedList = false;
            continue;
        }

        korobkaNode* prev = korobkaLinkedList->prev;
        delete korobkaLinkedList;

        korobkaLinkedList = prev;

    } while (korobkaLinkedList != nullptr);

    startKorobka.calcAlignYPerLine();
    startKorobka.calcAlignXPerX();

    startKorobka.printKorobka();
    return 0;
}