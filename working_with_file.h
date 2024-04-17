#pragma once
#include "utils.h"

#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <utility>
#include <stdexcept>

class File {
public:
    std::string program_name_;
    std::string file_in_;
    std::string file_out_;
    std::vector<std::string> filters_;
    std::map<std::string, std::vector<std::string>> filter_attributes_;
    std::set<std::string> correct_filters_names = {"-gs", "-neg", "-edge", "-sharp", "-crop"};
};

File Parsing(int argc, char* argv[]);

class PIXEL {
public:
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;
};

class Image {
public:
    char header_[FIFTY_FOUR];
    size_t width_ = 0;
    size_t height_ = 0;
    size_t bits_ppx_ = 0;
    size_t data_offset_{};
    size_t bytes_ppx_{};
    size_t real_size_{};
    size_t padding_{};
    std::vector<std::vector<PIXEL>> canvas_{};
};

std::string HexAsciiConverter(char* const array_ptr, size_t start, size_t end);

size_t CharIntConverter(const char* object, size_t position);

Image ReadFile(const std::string& file_name);

void WriteByte(std::ostream& out, uint8_t value);

void WriteInt(std::ostream& out, uint32_t value);

void WriteZeros(std::ostream& out, size_t count);

void SaveFile(const std::string& file_name, const Image& image);