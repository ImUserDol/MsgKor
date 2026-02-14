//
// Created by WhoIM on 2/12/26.
//

#include "stringMethods.h"

#include <string>

namespace stringMethods {
    std::size_t getMaxX(std::string_view str) {
        std::size_t maxX = 0;
        std::size_t i = 0;

        std::size_t newX = str.find('\n', i);
        while (newX != std::string_view::npos) {
            if (newX - i > maxX) {
                maxX = newX - i;
            }

            i = newX + 1;
            newX = str.find('\n', i);
        }

        if (str.length() - i > maxX) {
            maxX = str.length() - i;
        }

        return maxX;
    }

    std::size_t getMaxX(std::string* str) {
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

    std::size_t getCountY(std::string_view str) {
        std::size_t count = 0;
        std::size_t i = 0;
        while (str.find('\n', i) != std::string_view::npos) {
            count++;
            i = str.find('\n', i) + 1;
        }
        return count + 1;
    }

    std::size_t getCountY(std::string* str) {
        std::size_t count = 0;
        std::size_t i = 0;
        while (str -> find('\n', i) != std::string_view::npos) {
            count++;
            i = str -> find('\n', i) + 1;
        }
        return count + 1;
    }


    LineData getLineByY(std::string_view str, std::size_t y) {
        LineData retData{};
        std::string_view line = str;
        std::size_t newY = line.find('\n');
        while (y > 0 && newY != std::string_view::npos) {
            line = line.data() + newY + 1;
            newY = line.find('\n');
            y--;
        }

        if (y > 0) {
            retData.LineLength = 0;
            retData.LinePtr = nullptr;
        } else {
            retData.LinePtr = line.data();
            if (newY != std::string_view::npos) {
                retData.LineLength = newY;
            } else {
                retData.LineLength = line.length();
            }
        }

        return retData;



    }
} // stringMethods