//
// Created by Dipro Ray on 3/11/18.
//


#include <iomanip>
#include <stdio.h>
#include <string.h>
#include "naive_bayes_classifying_model/naive_bayes_classifying_model.cpp"
#include "classifier_evaluator/classifier_evaluator.cpp"
#include "./classifier_improver/classifier_improver.cpp"
#include "global_variables.h"

void interface();

int main() {

  // Call the interface function.
  interface();

}

void interface() {

  // All allowed commands.

  const string kTrainCommand = "train";
  const string kYesCommand = "yes";
  const string kSaveCommand = "save";
  const string kLoadCommand = "load";
  const string kClassifyCommand = "classify";
  const string kImproveCommand = "improve";
  const string kExitCommand = "exit";
  const string kResetEncodingsCommand = "reset-encodings";
  const string kResetPixelsFeatureCommand = "reset-pixelsfeature";

  // Set exit interface? to false

  bool exit_interface = false;

  // Declare the classifier, evaluator, and improver.

  NaiveBayesClassifyingModel model;
  ClassifierEvaluator evaluator;
  ClassifierImprover improver;

  do {

    // Allow the user to enter the command.

    cout << '\n' << "Enter command: " << '\n';

    string command;
    cin >> command;

    // Get the command in a string and find out which command it is.

    if (command == kTrainCommand) {

      // Ask user if he/she wants to use the default dataset.

      cout << '\n' << "Use default dataset? " << '\n';

      cin >> command;

      if (command == kYesCommand) {

        model = NaiveBayesClassifyingModel("../data/trainingimages", "../data/traininglabels", 0.1);

      } else {

        cout << '\n' << "Enter file path name for images, then enter file name for labels." << '\n';

        string filename_for_images, filename_for_labels;
        cin >> filename_for_images >> filename_for_labels;

        cout << '\n' << "Now, enter the Laplace Smoothing Factor value: " << '\n';

        double value;
        cin >> value;

        model = NaiveBayesClassifyingModel(filename_for_images, filename_for_labels, value);
      }
    } else if (command == kSaveCommand) {

      // Save the data of the model

      model.SaveModelFeatureProbabilityMatrixAndPriorsVectorToFiles("../data/probabilities", "../data/priors");

    } else if (command == kLoadCommand) {

      // Load the data for the model

      model.LoadModelFeatureProbabilityMatrixAndPriorsVectorFromFiles("../data/probabilities", "../data/priors");

    } else if (command == kClassifyCommand) {

      // Evaluate the model through a ClassifierEvaluator object.

      evaluator = ClassifierEvaluator(model);

      // Print out the results.
      // Note: << is overloaded here.

      cout << evaluator;
    } else if (command == kImproveCommand) {

      // Find the best k value.

      cout << '\n' << "The best k value is" << improver.FindBestKValue() << ".\n";

    } else if (command == kResetEncodingsCommand) {

      // Ask for the new value of number of different encodings.

      cout << '\n' << "How many encodings would you like for the image as a 2D array? 2 or 3?" << '\n';

      int encodings;
      cin >> encodings;

      // Accept the encoding value only if it is 2 or 3 or print an error message.

      if (encodings == 2 || encodings == 3) {
        ::number_of_different_encodings = encodings;
        cout << "The new number of different encodings is: " << ::number_of_different_encodings << ".\n";
      } else {
        cout << "Inavlid entry, please try again.";
      }

    } else if (command == kResetPixelsFeatureCommand) {

      // Ask for the new pixel feature size.

      cout << '\n' << "How many pixels would you like to be counted in a feature? Enter an even number < 14, or 1." << '\n';

      int pixel_dimensions;
      cin >> pixel_dimensions;

      // Accept it only if it meets the criteria: even no. <= 14, or 1.

      if ((pixel_dimensions < 14 && pixel_dimensions % 2 == 0) || (pixel_dimensions == 1)) {
        ::pixel_dimension_per_feature = pixel_dimensions;
        cout << "The new number of pixels in a feature is: " << ::pixel_dimension_per_feature << ".\n";
      } else {
        cout << "Inavlid entry, please try again.";
      }

    } else if (command == kExitCommand) {

      // Set exit interface? to true

      exit_interface = true;
    } else {

      cout << '\n' << "I do not understand the command.";

    }

  } while (!exit_interface);

}

