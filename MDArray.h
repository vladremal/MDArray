//
// Created by vladislav on 12.10.2024.
//

#ifndef MDARRAY_MDARRAY_H
#define MDARRAY_MDARRAY_H
#include <array>
#include <cstddef>
#include <iostream>
#include <utility>
#include <type_traits>

template<typename T, std::size_t... Dims>
class MDArray {
    static constexpr std::size_t totalSize = (... * Dims); //
    std::array<T, totalSize> data;

public:
    MDArray() = default;

    ~MDArray() = default;

    MDArray(const MDArray &) = default;

    MDArray(MDArray &&) = default;

    MDArray &operator=(const MDArray &) = default;

    MDArray &operator=(MDArray &&) = default;

    template<typename... Indices>
    T &operator()(Indices... indices) {
        static_assert((std::is_integral_v<Indices> && ...), "Все индексы должны быть целыми числами");
        static_assert(sizeof...(indices) == sizeof...(Dims),
                      "Количество индексов не совпадает с размерностью массива");
        std::size_t index = toIndex(indices...);
        return data[index];

    }

    template<typename... Indices>
    std::size_t toIndex(Indices... indices) const {
        std::array<std::size_t, sizeof...(indices)> idx = { static_cast<std::size_t>(indices)... };  // Массив индексов
        std::array<std::size_t, sizeof...(Dims)> dims = {Dims... };

        std::size_t index = 0;
        std::size_t multiplier = 1;
        for (std::ptrdiff_t i = idx.size() - 1; i >= 0; --i) {
            index += idx[i] * multiplier;
            multiplier *= dims[i];
        }
        return index;
    }

};
#endif //MDARRAY_MDARRAY_H
