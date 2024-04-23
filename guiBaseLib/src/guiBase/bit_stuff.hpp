#pragma once

#include <concepts>
#include <string>

namespace guiBase {
    template<typename T>
    concept NumericInt = std::integral<T> && !std::same_as<T, bool>;

    template<NumericInt T>
    void intToBin(std::string& str, T t) {
        str = "0b";
        // multiply byte-size * 8 to get bit size
        int typeSize = sizeof(t) * 8 - 1;
        for (int i = typeSize; i >= 0; i--) {
            str += (((t >> i) & 1) == 1 ? "1" : "0");
        }
    }
}// namespace guiBase
