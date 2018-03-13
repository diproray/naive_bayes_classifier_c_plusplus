//
// Created by Dipro Ray on 3/11/18.
//


#include <iomanip>
#include <stdio.h>
#include <string.h>
#include "naive_bayes_classifying_model/naive_bayes_classifying_model.cpp"
#include "classifier_evaluator/classifier_evaluator.cpp"
#include "./classifier_improver/classifier_improver.cpp"

void interface();

int main() {

  // Call the interface function.
  interface();

}

void interface() {

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

    if (command == "read") {

      cout << '\n' << "Use default dataset? " << '\n';

      cin >> command;

      if (command == "yes") {

        model = NaiveBayesClassifyingModel("../data/trainingimages", "../data/traininglabels", 0.5);

      } else {

        cout << '\n' << "Enter file path name for images, then enter file name for labels." << '\n';

        string filename_for_images, filename_for_labels;
        cin >> filename_for_images >> filename_for_labels;

        cout << '\n' << "Now, enter the Laplace Smoothing Factor value: " << '\n';

        double value;
        cin >> value;

        model = NaiveBayesClassifyingModel(filename_for_images, filename_for_labels, value);
      }
    } else if (command == "save") {

      model.SaveModelFeatureProbabilityMatrixAndPriorsVectorToFiles("../data/probabilities", "../data/priors");

    } else if (command == "load") {

      model.LoadModelFeatureProbabilityMatrixAndPriorsVectorFromFiles("../data/probabilities", "../data/priors");

    } else if (command == "classify") {

      evaluator = ClassifierEvaluator(model);

      cout << evaluator;
    } else if (command == "improve") {

      cout << '\n' << "The best k value is" << improver.FindBestKValue() << ".\n";

    } else if (command == "exit") {

      exit_interface = true;
    } else {

      cout << '\n' << "I do not understand the command.";

    }

  } while (!exit_interface);

}

