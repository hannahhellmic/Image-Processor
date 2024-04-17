#pragma once
#include "working_with_file.h"
#include "filters.h"

class GreyScale : public BaseFilter {
private:
    const double blue_ = 0.114;
    const double green_ = 0.587;
    const double red_ = 0.299;

public:
    bool Correctness(File& user_args) override;
    Image Apply(File& user_args, Image& original) override;
};