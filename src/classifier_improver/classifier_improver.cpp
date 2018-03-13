//
// Created by Dipro Ray on 3/12/18.
//

#include "classifier_improver.h"
#include "../classifier_evaluator/classifier_evaluator.h"

/**
 * . Function that finds the optimum k-value (Laplace Smoothing Factor)
 * for best accuracy by classifier.
 *
 * @return the best k value
 */
double ClassifierImprover::FindBestKValue() {

  // Declare doubles to store maximum accuracy and best k value

  double max_accuracy = 0;
  double best_k_value = 0;

  // For all possible k-values between 0.1 and 10, by increments of 0.1, do the following:
  double k = 0;
  for (k = 0.1; k <= 10.0; k = k + 0.1) {

    // Evaluate the model created with k as the Laplace Smoothing Factor.
    ClassifierEvaluator evaluator =
        ClassifierEvaluator(NaiveBayesClassifyingModel("../data/trainingimages", "../data/traininglabels", k));

    // Get the accuracy percentage for this classifier.
    double current_accuracy_percentage = evaluator.GetAccuracyPercentage();

    // If it is greater than the current max accuracy,
    // Store the k value.
    if (current_accuracy_percentage > max_accuracy) {
      max_accuracy = current_accuracy_percentage;
      best_k_value = k;
    }
  }

  // Return the best k value, which gives maximum accuracy percentage.

  return best_k_value;
}