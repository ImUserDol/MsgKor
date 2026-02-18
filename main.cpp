#include <iostream>
#include <vector>
#include <string>

#include "korobochka.h"


int main() {
    auto* strPtr = new std::string;
    *strPtr = "Hello world!Hellllllllllllooooooooo!F";

    auto* strPtr2 = new std::string;
    *strPtr2 = "Hello world!\n:)";

    auto* strPtr3 = new std::string;
    *strPtr3 = "Hello world!\n:)";

    auto* strPtrKorobka2 = new std::string;
    *strPtrKorobka2 = "Hello world!\n:)";

    auto* strPtrKorobka22 = new std::string;
    *strPtrKorobka22 = "Hello world!\n:)";

    auto* strPtrKorobka3 = new std::string;
    *strPtrKorobka3 = "Hello world!\n\n\n\n\n:)";


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
    Korobochka::ElementData element4{Korobochka::Tstr, strPtr3};

    Korobochka::Korobka korobka{2, 2};

    korobka.data.push_back(std::move(element));
    korobka.data.push_back(std::move(element2));
    korobka.data.push_back(std::move(element3));
    korobka.data.push_back(std::move(element4));


    korobka.calcAlignYPerLine();
    korobka.calcAlignXPerX();

    korobka.printKorobka();

    return 0;
}