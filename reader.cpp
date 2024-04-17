#include "working_with_file.h"

std::string HexAsciiConverter(char* const array_ptr, size_t start, size_t end) {
    std::string result;
    std::stringstream ss;
    for (size_t i = start; i < end; ++i) {
        ss << array_ptr[i];
    }
    ss >> std::hex >> result;
    return result;
}

size_t CharIntConverter(const char* object, size_t position) {
    size_t result = static_cast<uint8_t>(object[position + 1]);
    result <<= EIGHT;
    result += static_cast<size_t>(object[position]);
    return result;
}

Image ReadFile(const std::string& file_name) {
    std::ifstream file(file_name, std::ios::binary);
    Image user_image;
    file.read(user_image.header_, FIFTY_FOUR);
    if (!file) {
        throw std::invalid_argument("Impossible to read file");
    }
    if (HexAsciiConverter(user_image.header_, 0, TWO) != "BM") {
        throw std::invalid_argument("This file is not BMP");
    }

    user_image.width_ = CharIntConverter(user_image.header_, EIGHTEEN);
    user_image.height_ = CharIntConverter(user_image.header_, TWENTY_TWO);
    if (!user_image.width_ || !user_image.height_) {
        throw std::invalid_argument("Image size is incorrect");
    }
    user_image.data_offset_ = CharIntConverter(user_image.header_, TEN);
    if (user_image.data_offset_ != FIFTY_FOUR) {
        throw std::invalid_argument("Image must be 24-bit format");
    }
    user_image.bits_ppx_ = CharIntConverter(user_image.header_, TWENTY_EIGHT);
    if (user_image.bits_ppx_ != TWENTY_FOUR) {
        throw std::invalid_argument("Image must be 24-bit format");
    }
    user_image.bytes_ppx_ = user_image.bits_ppx_ / EIGHT;
    user_image.canvas_ = std::vector<std::vector<PIXEL>>(user_image.height_, std::vector<PIXEL>(user_image.width_));
    user_image.real_size_ = user_image.bytes_ppx_ * user_image.width_;
    user_image.padding_ = (FOUR - user_image.real_size_ % FOUR) % FOUR;
    size_t start = user_image.data_offset_;
    size_t end = start + user_image.real_size_;
    for (size_t i = 0; i < user_image.height_; ++i) {
        file.seekg(static_cast<std::streamoff>(start));
        for (size_t j = start; j < end;) {
            file.read(reinterpret_cast<char*>(&user_image.canvas_[i][(j - start) / 3].b), 1);
            file.read(reinterpret_cast<char*>(&user_image.canvas_[i][(j - start) / 3].g), 1);
            file.read(reinterpret_cast<char*>(&user_image.canvas_[i][(j - start) / 3].r), 1);
            j += 3;
        }
        start = end + user_image.padding_;
        end = start + user_image.real_size_;
    }
    return user_image;
}