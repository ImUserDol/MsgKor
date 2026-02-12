//
// Created by WhoIM on 2/12/26.
//

#ifndef MSGKOR_STRINGMETHODS_H
#define MSGKOR_STRINGMETHODS_H

#include <string_view>

namespace stringMethods {
    struct LineData {
        const char *LinePtr;
        std::size_t LineLength;
    };

    std::size_t getMaxX(std::string_view str);

    std::size_t getCountY(std::string_view str);

    LineData getLineByY(std::string_view str, std::size_t y);
} // stringMethods5

#endif //MSGKOR_STRINGMETHODS_H