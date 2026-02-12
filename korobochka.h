//
// Created by WhoIM on 2/12/26.
//

#ifndef MSGKOR_KOROBOCHKA_H
#define MSGKOR_KOROBOCHKA_H
#include <cstddef>

namespace korobochka {

    enum TypeElem {
        uninitialized = 0,
        korobka,
        str
    };

    struct ElementData {

    };

    struct korobka {
        std::size_t CountY;
        std::size_t CountX;
        
    };
} // korobochka

#endif //MSGKOR_KOROBOCHKA_H