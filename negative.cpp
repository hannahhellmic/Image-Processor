#include "negative.h"

bool Negative::Correctness(File& user_args) {
    if (user_args.filter_attributes_.empty() ||
        user_args.filter_attributes_.find("-neg") == user_args.filter_attributes_.end()) {
        return true;
    } else {
        throw std::invalid_argument("Negative filter does not require any parameter");
    }
}

Image Negative::Apply(File& user_args, Image& original) {
    if (Correctness(user_args)) {
        Image result = original;
        for (auto& v : result.canvas_) {
            for (auto& p : v) {
                p.r = MAXIMUM - p.r;
                p.b = MAXIMUM - p.b;
                p.g = MAXIMUM - p.g;
            }
        }
        return result;
    }
    throw std::bad_exception();
}