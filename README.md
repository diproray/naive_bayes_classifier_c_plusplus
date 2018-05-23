# Naive Bayes Classifier 

# File Storage
1. All classes are placed into directories of the class name within `./src/`. All classes have associated `.cpp` and `.h` files.
2. Universal utility/helper functions are placed in `./src/utils`. 
3. `src/global_variables.h` contains global variables implemented for the purpose of extra-credit features.
4. The program to be run is in `src/main.cpp`.

# Design
1. The "smallest" unit of data is `ImageData`. It represents a single image. This class contains an image, encoded as a 2D array of 1s (foreground) and 0s (background).
2. The next bigger unit of data is `ImagesAndLabelsDataset`. It represents a dataset of images and labels. This class contains `vectors` of `ImageData` objects, and of the image labels.
3. Another unit of data is `NaiveBayesClassifier`. It represents a single Naive Bayes Classifier. This class contains `array` of probabilities and `vector` of priors.
4. The next class is `ClassifierEvaluator`. It contains an `array` representing the confusion matrix of a classifier, and a `double` representing accuracy percentage of a classifier.
5. The next class is `ClassifierImprover`. It contains functions that try to improve the accuracy of a model.

# Features
1. K Cross - Form Validation: Predicting the Value of K that Gives Highest Accuracy for the Classifier - implemented in `./src/classifier_improver/` - can be run through `main`.
2. Ternary Value Detection: Detect Changes in Accuracy due to Differentiating between `+` and `#` - implemented throughout files in the program - can be run through `main`.
3. Larger Pixel Size Features: Support for this involves code implemented throughout files in the program - can be run through `main`.

