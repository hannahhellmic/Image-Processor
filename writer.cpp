#include "working_with_file.h"

void WriteByte(std::ostream& out, uint8_t value) {
    out.write(reinterpret_cast<char*>(&value), 1);
}

void WriteInt(std::ostream& out, uint32_t value) {
    for (size_t i = 0; i < BYTES_PER_INT; ++i) {
        WriteByte(out, (value >> (i * BITS_PER_BYTE)) & BYTE_MASK);
    }
}

void WriteZeros(std::ostream& out, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        WriteByte(out, 0);
    }
}

void SaveFile(const std::string& file_name, const Image& image) {
    std::ofstream out(file_name, std::ios::binary);
    WriteByte(out, BMP_SIGNATURE_BYTE_1);
    WriteByte(out, BMP_SIGNATURE_BYTE_2);
    auto file_size = HEADER_SIZE + image.height_ * (image.width_ * 3 + image.padding_);
    WriteInt(out, file_size);
    WriteZeros(out, 4);
    WriteInt(out, HEADER_SIZE);
    WriteInt(out, INFO_HEADER_SIZE);
    WriteInt(out, image.width_);
    WriteInt(out, image.height_);
    WriteByte(out, PLANES);
    WriteZeros(out, PLANES);
    WriteByte(out, BITS_PPX);
    WriteZeros(out, PLANES);
    WriteZeros(out, BITS_PPX);
    for (size_t i = 0; i < image.height_; ++i) {
        for (size_t j = 0; j < image.width_; ++j) {
            WriteByte(out, image.canvas_[i][j].b);
            WriteByte(out, image.canvas_[i][j].g);
            WriteByte(out, image.canvas_[i][j].r);
        }
        WriteZeros(out, image.padding_);
    }
}