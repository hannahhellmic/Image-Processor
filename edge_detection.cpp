#include "edge_detection.h"

bool Edge::Correctness(File& user_args) {
    if (user_args.filter_attributes_.empty() ||
        (user_args.filter_attributes_.find("-edge") == user_args.filter_attributes_.end()) ||
        (user_args.filter_attributes_["-edge"].size() != 1)) {
        throw std::invalid_argument("Edge filter require one number parameter");
    } else {
        char* end_ptr = nullptr;
        threshold_ = std::lround(strtod(user_args.filter_attributes_["-edge"][0].c_str(), &end_ptr) * MAXIMUM);
        if (*end_ptr != '\0') {
            throw std::invalid_argument("Edge filter require one number parameter");
        } else {
            return true;
        }
    }
}

Image Edge::Apply(File& user_args, Image& original) {
    if (Correctness(user_args)) {
        GreyScale gs;
        user_args.filters_.push_back("-gs");
        original = gs.Apply(user_args, original);
        Image result = original;
        for (size_t i = 0; i < original.height_; ++i) {
            for (size_t j = 0; j < original.width_; ++j) {
                if (i == 0 && j == 0) {
                    result.canvas_[i][j].r =
                        std::clamp(main_pix_ * original.canvas_[i][j].r + other_pix_ * original.canvas_[i + 1][j].r +
                                       other_pix_ * original.canvas_[i][j + 1].r,
                                   MINIMUM, MAXIMUM);
                    if (result.canvas_[i][j].r > threshold_) {
                        result.canvas_[i][j].r = result.canvas_[i][j].g = result.canvas_[i][j].b = MAXIMUM;
                    } else {
                        result.canvas_[i][j].r = result.canvas_[i][j].g = result.canvas_[i][j].b = MINIMUM;
                    }
                } else if (i == 0 && j == original.width_ - 1) {
                    result.canvas_[i][j].r =
                        std::clamp(other_pix_ * original.canvas_[i][j - 1].r + main_pix_ * original.canvas_[i][j].r +
                                       other_pix_ * original.canvas_[i + 1][j].r,
                                   MINIMUM, MAXIMUM);
                    if (result.canvas_[i][j].r > threshold_) {
                        result.canvas_[i][j].r = result.canvas_[i][j].g = result.canvas_[i][j].b = MAXIMUM;
                    } else {
                        result.canvas_[i][j].r = result.canvas_[i][j].g = result.canvas_[i][j].b = MINIMUM;
                    }
                } else if (i == original.height_ - 1 && j == 0) {
                    result.canvas_[i][j].r =
                        std::clamp(other_pix_ * original.canvas_[i - 1][j].r + main_pix_ * original.canvas_[i][j].r +
                                       other_pix_ * original.canvas_[i][j + 1].r,
                                   MINIMUM, MAXIMUM);
                    if (result.canvas_[i][j].r > threshold_) {
                        result.canvas_[i][j].r = result.canvas_[i][j].g = result.canvas_[i][j].b = MAXIMUM;
                    } else {
                        result.canvas_[i][j].r = result.canvas_[i][j].g = result.canvas_[i][j].b = MINIMUM;
                    }
                } else if (i == original.height_ - 1 && j == original.width_ - 1) {
                    result.canvas_[i][j].r =
                        std::clamp(other_pix_ * original.canvas_[i][j - 1].r +
                                       other_pix_ * original.canvas_[i - 1][j].r + main_pix_ * original.canvas_[i][j].r,
                                   MINIMUM, MAXIMUM);
                    if (result.canvas_[i][j].r > threshold_) {
                        result.canvas_[i][j].r = result.canvas_[i][j].g = result.canvas_[i][j].b = MAXIMUM;
                    } else {
                        result.canvas_[i][j].r = result.canvas_[i][j].g = result.canvas_[i][j].b = MINIMUM;
                    }
                } else if (i == 0) {
                    result.canvas_[i][j].r = std::clamp(
                        other_pix_ * original.canvas_[i][j - 1].r + main_pix_ * original.canvas_[i][j].r +
                            other_pix_ * original.canvas_[i + 1][j].r + other_pix_ * original.canvas_[i][j + 1].r,
                        MINIMUM, MAXIMUM);
                    if (result.canvas_[i][j].r > threshold_) {
                        result.canvas_[i][j].r = result.canvas_[i][j].g = result.canvas_[i][j].b = MAXIMUM;
                    } else {
                        result.canvas_[i][j].r = result.canvas_[i][j].g = result.canvas_[i][j].b = MINIMUM;
                    }
                } else if (i == original.height_ - 1) {
                    result.canvas_[i][j].r = std::clamp(
                        other_pix_ * original.canvas_[i][j - 1].r + other_pix_ * original.canvas_[i - 1][j].r +
                            main_pix_ * original.canvas_[i][j].r + other_pix_ * original.canvas_[i][j + 1].r,
                        MINIMUM, MAXIMUM);
                    if (result.canvas_[i][j].r > threshold_) {
                        result.canvas_[i][j].r = result.canvas_[i][j].g = result.canvas_[i][j].b = MAXIMUM;
                    } else {
                        result.canvas_[i][j].r = result.canvas_[i][j].g = result.canvas_[i][j].b = MINIMUM;
                    }
                } else if (j == 0) {
                    result.canvas_[i][j].r = std::clamp(
                        other_pix_ * original.canvas_[i - 1][j].r + main_pix_ * original.canvas_[i][j].r +
                            other_pix_ * original.canvas_[i + 1][j].r + other_pix_ * original.canvas_[i][j + 1].r,
                        MINIMUM, MAXIMUM);
                    if (result.canvas_[i][j].r > threshold_) {
                        result.canvas_[i][j].r = result.canvas_[i][j].g = result.canvas_[i][j].b = MAXIMUM;
                    } else {
                        result.canvas_[i][j].r = result.canvas_[i][j].g = result.canvas_[i][j].b = MINIMUM;
                    }
                } else if (j == original.width_ - 1) {
                    result.canvas_[i][j].r = std::clamp(
                        other_pix_ * original.canvas_[i][j - 1].r + other_pix_ * original.canvas_[i - 1][j].r +
                            main_pix_ * original.canvas_[i][j].r + other_pix_ * original.canvas_[i + 1][j].r,
                        MINIMUM, MAXIMUM);
                    if (result.canvas_[i][j].r > threshold_) {
                        result.canvas_[i][j].r = result.canvas_[i][j].g = result.canvas_[i][j].b = MAXIMUM;
                    } else {
                        result.canvas_[i][j].r = result.canvas_[i][j].g = result.canvas_[i][j].b = MINIMUM;
                    }
                } else {
                    result.canvas_[i][j].r = std::clamp(
                        other_pix_ * original.canvas_[i][j - 1].r + other_pix_ * original.canvas_[i - 1][j].r +
                            main_pix_ * original.canvas_[i][j].r + other_pix_ * original.canvas_[i + 1][j].r +
                            other_pix_ * original.canvas_[i][j + 1].r,
                        MINIMUM, MAXIMUM);
                    if (result.canvas_[i][j].r > threshold_) {
                        result.canvas_[i][j].r = result.canvas_[i][j].g = result.canvas_[i][j].b = MAXIMUM;
                    } else {
                        result.canvas_[i][j].r = result.canvas_[i][j].g = result.canvas_[i][j].b = MINIMUM;
                    }
                }
            }
        }
        user_args.filters_.pop_back();
        return result;
    }
    throw std::bad_exception();
}