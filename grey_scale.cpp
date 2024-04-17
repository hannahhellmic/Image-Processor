#include "grey_scale.h"

bool GreyScale::Correctness(File& user_args) {
    if (user_args.filter_attributes_.empty() ||
        user_args.filter_attributes_.find("-gs") == user_args.filter_attributes_.end()) {
        return true;
    } else {
        throw std::invalid_argument("Greyscale filter does not require any parameter");
    }
}

Image GreyScale::Apply(File& user_args, Image& original) {
    if (Correctness(user_args)) {
        Image result = original;
        for (auto& v : result.canvas_) {
            for (auto& p : v) {
                uint8_t grey = static_cast<uint8_t>(red_ * p.r + green_ * p.g + blue_ * p.b);
                p.b = grey;
                p.g = grey;
                p.r = grey;
            }
        }
        return result;
    }
    throw std::bad_exception();
}