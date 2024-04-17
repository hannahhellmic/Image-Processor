#pragma once
#include "working_with_file.h"
#include "filters.h"

class Crop : public BaseFilter {
private:
    uint64_t width_;
    uint64_t height_;

public:
    bool Correctness(File& user_args) override;
    Image Apply(File& user_args, Image& original) override;
};