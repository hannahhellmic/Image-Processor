#pragma once
#include "working_with_file.h"
#include "filters.h"

class Negative : public BaseFilter {
public:
    bool Correctness(File& user_args) override;
    Image Apply(File& user_args, Image& original) override;
};