#pragma once
#include "working_with_file.h"
#include "filters.h"

class Sharpening : public BaseFilter {
private:
    const int other_pix_ = -1;
    const int main_pix_ = 5;

public:
    bool Correctness(File& user_args) override;
    Image Apply(File& user_args, Image& original) override;
};