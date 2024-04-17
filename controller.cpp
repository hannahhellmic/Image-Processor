#include "controller.h"
#include "grey_scale.h"
#include "negative.h"
#include "edge_detection.h"
#include "sharpening.h"
#include "crop.h"

Image Controller(Image& image, File& info) {
    for (const auto& i : info.filters_) {
        if (i == "-gs") {
            GreyScale gs;
            image = gs.Apply(info, image);
        } else if (i == "-neg") {
            Negative neg;
            image = neg.Apply(info, image);
        } else if (i == "-edge") {
            Edge edge;
            image = edge.Apply(info, image);
        } else if (i == "-sharp") {
            Sharpening sharp;
            image = sharp.Apply(info, image);
        } else if (i == "-crop") {
            Crop crop;
            image = crop.Apply(info, image);
        }
    }
    return image;
}