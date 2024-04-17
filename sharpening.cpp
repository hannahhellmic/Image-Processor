#include "sharpening.h"

bool Sharpening::Correctness(File& user_args) {
    if (user_args.filter_attributes_.empty() ||
        user_args.filter_attributes_.find("-sharp") == user_args.filter_attributes_.end()) {
        return true;
    } else {
        throw std::invalid_argument("Sharpening filter dose not require any parameter");
    }
}

Image Sharpening::Apply(File& user_args, Image& original) {
    if (Correctness(user_args)) {
        Image result = original;
        for (size_t i = 0; i < original.height_; ++i) {
            for (size_t j = 0; j < original.width_; ++j) {
                if (i == 0 && j == 0) {
                    result.canvas_[i][j].r =
                        std::clamp(main_pix_ * original.canvas_[i][j].r + other_pix_ * original.canvas_[i + 1][j].r +
                                       other_pix_ * original.canvas_[i][j + 1].r,
                                   MINIMUM, MAXIMUM);
                    result.canvas_[i][j].g =
                        std::clamp(main_pix_ * original.canvas_[i][j].g + other_pix_ * original.canvas_[i + 1][j].g +
                                       other_pix_ * original.canvas_[i][j + 1].g,
                                   MINIMUM, MAXIMUM);
                    result.canvas_[i][j].b =
                        std::clamp(main_pix_ * original.canvas_[i][j].b + other_pix_ * original.canvas_[i + 1][j].b +
                                       other_pix_ * original.canvas_[i][j + 1].b,
                                   MINIMUM, MAXIMUM);
                } else if (i == 0 && j == original.width_ - 1) {
                    result.canvas_[i][j].r =
                        std::clamp(other_pix_ * original.canvas_[i][j - 1].r + main_pix_ * original.canvas_[i][j].r +
                                       other_pix_ * original.canvas_[i + 1][j].r,
                                   MINIMUM, MAXIMUM);
                    result.canvas_[i][j].g =
                        std::clamp(other_pix_ * original.canvas_[i][j - 1].g + main_pix_ * original.canvas_[i][j].g +
                                       other_pix_ * original.canvas_[i + 1][j].g,
                                   MINIMUM, MAXIMUM);
                    result.canvas_[i][j].b =
                        std::clamp(other_pix_ * original.canvas_[i][j - 1].b + main_pix_ * original.canvas_[i][j].b +
                                       other_pix_ * original.canvas_[i + 1][j].b,
                                   MINIMUM, MAXIMUM);
                } else if (i == original.height_ - 1 && j == 0) {
                    result.canvas_[i][j].r =
                        std::clamp(other_pix_ * original.canvas_[i - 1][j].r + main_pix_ * original.canvas_[i][j].r +
                                       other_pix_ * original.canvas_[i][j + 1].r,
                                   MINIMUM, MAXIMUM);
                    result.canvas_[i][j].g =
                        std::clamp(other_pix_ * original.canvas_[i - 1][j].g + main_pix_ * original.canvas_[i][j].g +
                                       other_pix_ * original.canvas_[i][j + 1].g,
                                   MINIMUM, MAXIMUM);
                    result.canvas_[i][j].b =
                        std::clamp(other_pix_ * original.canvas_[i - 1][j].b + main_pix_ * original.canvas_[i][j].b +
                                       other_pix_ * original.canvas_[i][j + 1].b,
                                   MINIMUM, MAXIMUM);
                } else if (i == original.height_ - 1 && j == original.width_ - 1) {
                    result.canvas_[i][j].r =
                        std::clamp(other_pix_ * original.canvas_[i][j - 1].r +
                                       other_pix_ * original.canvas_[i - 1][j].r + main_pix_ * original.canvas_[i][j].r,
                                   MINIMUM, MAXIMUM);
                    result.canvas_[i][j].g =
                        std::clamp(other_pix_ * original.canvas_[i][j - 1].g +
                                       other_pix_ * original.canvas_[i - 1][j].g + main_pix_ * original.canvas_[i][j].g,
                                   MINIMUM, MAXIMUM);
                    result.canvas_[i][j].b =
                        std::clamp(other_pix_ * original.canvas_[i][j - 1].b +
                                       other_pix_ * original.canvas_[i - 1][j].b + main_pix_ * original.canvas_[i][j].b,
                                   MINIMUM, MAXIMUM);
                } else if (i == 0) {
                    result.canvas_[i][j].r = std::clamp(
                        other_pix_ * original.canvas_[i][j - 1].r + main_pix_ * original.canvas_[i][j].r +
                            other_pix_ * original.canvas_[i + 1][j].r + other_pix_ * original.canvas_[i][j + 1].r,
                        MINIMUM, MAXIMUM);
                    result.canvas_[i][j].g = std::clamp(
                        other_pix_ * original.canvas_[i][j - 1].g + main_pix_ * original.canvas_[i][j].g +
                            other_pix_ * original.canvas_[i + 1][j].g + other_pix_ * original.canvas_[i][j + 1].g,
                        MINIMUM, MAXIMUM);
                    result.canvas_[i][j].b = std::clamp(
                        other_pix_ * original.canvas_[i][j - 1].b + main_pix_ * original.canvas_[i][j].b +
                            other_pix_ * original.canvas_[i + 1][j].b + other_pix_ * original.canvas_[i][j + 1].b,
                        MINIMUM, MAXIMUM);
                } else if (i == original.height_ - 1) {
                    result.canvas_[i][j].r = std::clamp(
                        other_pix_ * original.canvas_[i][j - 1].r + other_pix_ * original.canvas_[i - 1][j].r +
                            main_pix_ * original.canvas_[i][j].r + other_pix_ * original.canvas_[i][j + 1].r,
                        MINIMUM, MAXIMUM);
                    result.canvas_[i][j].g = std::clamp(
                        other_pix_ * original.canvas_[i][j - 1].g + other_pix_ * original.canvas_[i - 1][j].g +
                            main_pix_ * original.canvas_[i][j].g + other_pix_ * original.canvas_[i][j + 1].g,
                        MINIMUM, MAXIMUM);
                    result.canvas_[i][j].b = std::clamp(
                        other_pix_ * original.canvas_[i][j - 1].b + other_pix_ * original.canvas_[i - 1][j].b +
                            main_pix_ * original.canvas_[i][j].b + other_pix_ * original.canvas_[i][j + 1].b,
                        MINIMUM, MAXIMUM);
                } else if (j == 0) {
                    result.canvas_[i][j].r = std::clamp(
                        other_pix_ * original.canvas_[i - 1][j].r + main_pix_ * original.canvas_[i][j].r +
                            other_pix_ * original.canvas_[i + 1][j].r + other_pix_ * original.canvas_[i][j + 1].r,
                        MINIMUM, MAXIMUM);
                    result.canvas_[i][j].g = std::clamp(
                        other_pix_ * original.canvas_[i - 1][j].g + main_pix_ * original.canvas_[i][j].g +
                            other_pix_ * original.canvas_[i + 1][j].g + other_pix_ * original.canvas_[i][j + 1].g,
                        MINIMUM, MAXIMUM);
                    result.canvas_[i][j].b = std::clamp(
                        other_pix_ * original.canvas_[i - 1][j].b + main_pix_ * original.canvas_[i][j].b +
                            other_pix_ * original.canvas_[i + 1][j].b + other_pix_ * original.canvas_[i][j + 1].b,
                        MINIMUM, MAXIMUM);
                } else if (j == original.width_ - 1) {
                    result.canvas_[i][j].r = std::clamp(
                        other_pix_ * original.canvas_[i][j - 1].r + other_pix_ * original.canvas_[i - 1][j].r +
                            main_pix_ * original.canvas_[i][j].r + other_pix_ * original.canvas_[i + 1][j].r,
                        MINIMUM, MAXIMUM);
                    result.canvas_[i][j].g = std::clamp(
                        other_pix_ * original.canvas_[i][j - 1].g + other_pix_ * original.canvas_[i - 1][j].g +
                            main_pix_ * original.canvas_[i][j].g + other_pix_ * original.canvas_[i + 1][j].g,
                        MINIMUM, MAXIMUM);
                    result.canvas_[i][j].b = std::clamp(
                        other_pix_ * original.canvas_[i][j - 1].b + other_pix_ * original.canvas_[i - 1][j].b +
                            main_pix_ * original.canvas_[i][j].b + other_pix_ * original.canvas_[i + 1][j].b,
                        MINIMUM, MAXIMUM);
                } else {
                    result.canvas_[i][j].r = std::clamp(
                        other_pix_ * original.canvas_[i][j - 1].r + other_pix_ * original.canvas_[i - 1][j].r +
                            main_pix_ * original.canvas_[i][j].r + other_pix_ * original.canvas_[i + 1][j].r +
                            other_pix_ * original.canvas_[i][j + 1].r,
                        MINIMUM, MAXIMUM);
                    result.canvas_[i][j].g = std::clamp(
                        other_pix_ * original.canvas_[i][j - 1].g + other_pix_ * original.canvas_[i - 1][j].g +
                            main_pix_ * original.canvas_[i][j].g + other_pix_ * original.canvas_[i + 1][j].g +
                            other_pix_ * original.canvas_[i][j + 1].g,
                        MINIMUM, MAXIMUM);
                    result.canvas_[i][j].b = std::clamp(
                        other_pix_ * original.canvas_[i][j - 1].b + other_pix_ * original.canvas_[i - 1][j].b +
                            main_pix_ * original.canvas_[i][j].b + other_pix_ * original.canvas_[i + 1][j].b +
                            other_pix_ * original.canvas_[i][j + 1].b,
                        MINIMUM, MAXIMUM);
                }
            }
        }
        return result;
    }
    throw std::bad_exception();
}