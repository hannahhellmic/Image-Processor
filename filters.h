#pragma once
#include "working_with_file.h"

#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <stdexcept>

class BaseFilter {
    virtual bool Correctness(File& user_args) = 0;
    virtual Image Apply(File& user_args, Image& original) = 0;
};

const int MAXIMUM = 255;
const int MINIMUM = 0;
const int TEN_1 = 10;