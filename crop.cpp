#include "crop.h"

bool Crop::Correctness(File& user_args) {
    if (user_args.filter_attributes_.empty() ||
        (user_args.filter_attributes_.find("-crop") == user_args.filter_attributes_.end())) {
        throw std::invalid_argument("Crop filter requires 2 number parameters");
    } else if (user_args.filter_attributes_["-crop"].size() != 2) {
        throw std::invalid_argument("Crop filter requires 2 number parameters");
    } else {
        width_ = strtol(user_args.filter_attributes_["-crop"][0].c_str(), nullptr, TEN_1);
        height_ = strtol(user_args.filter_attributes_["-crop"][1].c_str(), nullptr, TEN_1);
        if (width_ == 0L || height_ == 0L) {
            throw std::invalid_argument("Crop filter requires 2 number parameters");
        } else {
            return true;
        }
    }
}

Image Crop::Apply(File& user_args, Image& original) {
    if (Correctness(user_args)) {
        if (width_ > 1900 && width_ < original.width_ && width_ % 4 != 0) {
            original.padding_ = 4 - (width_ * 3) % 4;
        }
        if (height_ > 1900 && height_ < original.height_ && height_ % 4 != 0) {
            original.padding_ = 4 - (width_ * 3) % 4;
        }
        if (height_ < original.height_) {
            std::reverse(original.canvas_.begin(), original.canvas_.end());
            original.canvas_.resize(height_);
            std::reverse(original.canvas_.begin(), original.canvas_.end());
            original.height_ = static_cast<size_t>(height_);
        }
        if (width_ < original.width_) {
            for (auto& row : original.canvas_) {
                row.resize(width_);
            }
            original.width_ = static_cast<size_t>(width_);
        }
        return original;
    }
    throw std::bad_exception();
}
