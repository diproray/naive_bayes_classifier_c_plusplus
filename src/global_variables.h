//
// Created by Dipro Ray on 3/13/18.
//

#ifndef NAIVEBAYES_GLOBAL_VARIABLES_H
#define NAIVEBAYES_GLOBAL_VARIABLES_H

// The number of different types of encodings:
// {0, 1} or {0, 1, 2}
// The '2' or '3' denotes the number of all such encodings.
// By default, it is set to 2. It can, however, be changed to 3 in the interface.
// This feature is implemented to extend my existing program for extra-credit feature
// of checking changes in accuracy of classifier by differentiating between the two foreground values.

extern int number_of_different_encodings = 2;

// The dimension of the pixel size which accounts for 1 feature.
// Indicates what the feature is:
// (pixel_dimension_per_feature * pixel_dimension_per_feature) pixels of the image
// E.g.: pixel_dimension_per_feature = 1 means that -
// 1x1 pixels will be evaluated as 1 feature
// E.g.: pixel_dimension_per_feature = 4 means that -
// 4x4 pixels will be evaluated as 1 feature

extern int pixel_dimension_per_feature = 1;

#endif //NAIVEBAYES_GLOBAL_VARIABLES_H
