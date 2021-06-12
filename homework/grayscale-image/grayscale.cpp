#include "grayscale.hpp"

CompressedBitmap compressGrayscale(const Bitmap& bitmap) {
    CompressedBitmap compressed{};

    uint8_t currCount{1};
    for (Bitmap::size_type i{0}; i < height; ++i) {
        for (Bitmap::size_type j{1}; j < width + 1; ++j) {
            while (bitmap[i][j] == bitmap[i][j - 1] && j < width) {
                ++currCount;
                ++j;
            }
            compressed.emplace_back(bitmap[i][j - 1], currCount);
            currCount = 1;
        }
    }

    return compressed;
}

Bitmap decompressGrayscale(const CompressedBitmap& compressed) {
    Bitmap bitmap{};

    std::vector<uint8_t> temp;
    temp.reserve(width * height);
    for (const auto& el : compressed) {
        for (int i = 0; i < std::get<1>(el); ++i) {
            temp.push_back(std::get<0>(el));
        }
    }

    auto it = temp.begin();
    for (int r = 0; r < height; ++r) {
        std::copy(it, it + width - 1, bitmap[r].begin());
        it += width;
    }

    return bitmap;
}

uint8_t getGrayScale(uint8_t code) {
    static constexpr int scale{255};
    static constexpr std::array<uint8_t, 10> grayScaleChars{' ', '.', ':', '-', '=', '+', '*', '#', '%', '@'};

    std::array<uint8_t, 10>::size_type index{index = code * grayScaleChars.size() / (scale + 1)};

    return grayScaleChars[index];
}

void printMap(const Bitmap& bitmap) {
    for (const auto& row : bitmap) {
        for (const auto chCode : row) {
            std::cout << getGrayScale(chCode);
        }
        std::cout << '\n';
    }
}
