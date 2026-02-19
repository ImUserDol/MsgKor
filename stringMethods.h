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

    std::size_t getMaxX(const std::string* str);

    std::size_t getCountY(const std::string* str);

    std::size_t getLineSize(const std::string* str, std::size_t pos);

    bool startwith(std::string_view str, std::string_view prefix);
} // stringMethods5

#endif //MSGKOR_STRINGMETHODS_H