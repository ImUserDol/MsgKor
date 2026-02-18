//
// Created by WhoIM on 2/12/26.
//

#include "stringMethods.h"

#include <string>

namespace stringMethods {

    std::size_t getLineSize(const std::string* const str, std::size_t pos) {
        std::size_t nextY = str -> find('\n', pos);

        if (nextY == std::string_view::npos) {
            return str -> length() - pos;
        }

        return nextY - pos;
    }


    std::size_t getMaxX(const std::string* const str) {
        std::size_t maxX = 0;
        std::size_t i = 0;

        std::size_t newX = str -> find('\n', i);
        while (newX != std::string_view::npos) {
            if (newX - i > maxX) {
                maxX = newX - i;
            }

            i = newX + 1;
            newX = str -> find('\n', i);
        }

        if (str -> length() - i > maxX) {
            maxX = str -> length() - i;
        }

        return maxX;
    }

    std::size_t getCountY(const std::string* const str) {
        std::size_t count = 0;
        std::size_t i = 0;
        while (str -> find('\n', i) != std::string_view::npos) {
            count++;
            i = str -> find('\n', i) + 1;
        }
        return count + 1;
    }
} // stringMethods