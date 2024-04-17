#pragma once
#include "working_with_file.h"
#include "filters.h"
#include "grey_scale.h"

class Edge : public BaseFilter {
private:
    unsigned int threshold_;
    const int main_pix_ = 4;
    const int other_pix_ = -1;

public:
    bool Correctness(File& user_args) override;
    Image Apply(File& user_args, Image& original) override;
};