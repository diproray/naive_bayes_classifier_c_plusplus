//
// Created by Dipro Ray on 3/12/18.
//

#include <iomanip>
#include <utility>
#include "classifier_evaluator.h"
#include "../utils/utils.h"

// The number of class values.
// For the given dataset, it is 10.


static const int kNumberOfClassValues = 10;

/**
 * . Function that computes the accuracy and confusion matrix for a given model.
 *
 * @param model the model which is to be evaluated
 */
void ClassifierEvaluator::ComputeAccuracyAndConfusionMatrix(NaiveBayesClassifyingModel model) {

  // Obtain the test dataset of images and labels.
  ImagesAndLabelsDataset test_data = ImagesAndLabelsDataset("../data/testimages", "../data/testlabels", 0.5);

  // Initialize all values in the confusion matrix to zero.

  for (int row_index = 0; row_index < kNumberOfClassValues; row_index++) {
    for (int col_index = 0; col_index < row_index; col_index++) {
      confusion_matrix_[row_index][col_index] = 0;
    }
  }

  // Initialize the int that keeps track of the number of times the classifier
  // classified correctly.

  int count_of_correct_predictions = 0;

  // Get the total number of images.

  unsigned long number_of_images = test_data.GetVectorOfImages().size();

  // Do the following for all possible class values.
  for (unsigned long index = 0; index < number_of_images; index++) {

    // Get the class value predicted by the classifier for the image.

    int estimated_class = model.Classifier(test_data.GetVectorOfImages().at(index));


    // Check if it matches the actual label/class value.
    // Add to the count of correct predictions, if yes.

    if (estimated_class == test_data.GetVectorOfLabels().at(index)) {
      count_of_correct_predictions++;
    }

    // Increment the respective position in the confusion matrix by one.

    confusion_matrix_[test_data.GetVectorOfLabels().at(index)][estimated_class]++;

    // Print the progress bar to track status.

    PrintProgressBar(index, number_of_images);
  }

  // Compute the accuracy percentage.
  accuracy_percentage_ = ((double) count_of_correct_predictions / number_of_images) * 100;

  // At this point, the confusion matrix contains the number of events at each position.
  // This will now be converted into precentages in the below function.

  ConvertCountToPercentageInConfusionMatrix();

}

/**
 * . Function that converts a confusion matrix of number of occurrences of events
 * into a percentage.
 */
void ClassifierEvaluator::ConvertCountToPercentageInConfusionMatrix() {

  // Since the count has to be converted to percentage,
  // In each row, find the total number of images of that class label.
  // Then, divide all the values in that row by the total no. and multiply by 100.
  // This gives us the percentage values.

  for (int row_index = 0; row_index < kNumberOfClassValues; row_index++) {

    int sum = 0;

    // Compute the total number of images of that class label.

    for (int col_index = 0; col_index < kNumberOfClassValues; col_index++) {
      sum += confusion_matrix_[row_index][col_index];
    }

    // Divide all the values in that row by the total no. and multiply by 100.
    // This gives us the percentages.

    for (int col_index = 0; col_index < kNumberOfClassValues; col_index++) {
      confusion_matrix_[row_index][col_index] = (confusion_matrix_[row_index][col_index] / sum) * 100;
    }
  }
}

/**
 * . Function that overloads the << operator. Used mainly for debugging purposes.
 *
 * @param output_stream the stream to put the data into
 * @param classifier_evaluator the object whose data is to be printed
 * @return the output stream
 */
ostream &operator<<(ostream &output_stream, const ClassifierEvaluator &classifier_evaluator) {

  // Print all the relevant details.

  cout << '\n' << "Percentage of Accuracy: " << classifier_evaluator.accuracy_percentage_ << "%";

  cout << '\n' << "Confusion Matrix: " << '\n';

  for (int row_index = 0; row_index < 10; row_index++) {
    for (int col_index = 0; col_index < 10; col_index++) {

      std::cout << std::fixed;
      std::cout << std::setprecision(2);
      cout << classifier_evaluator.confusion_matrix_[row_index][col_index] << "%" << '\t';
    }

    cout << '\n';
  }

  return output_stream;
}

/**
 * . Constructor for ClassifierEvaluator object.
 *
 * @param model the classifier model to be evaluated
 */
ClassifierEvaluator::ClassifierEvaluator(NaiveBayesClassifyingModel model) {

  // Compute accuracy % and the confusion matrix for the model.

  ComputeAccuracyAndConfusionMatrix(std::move(model));
}

/**
 * . Getter for the object's accuracy percentage.
 * @return the accuracy percentage
 */
double ClassifierEvaluator::GetAccuracyPercentage() {

  // Return the accuracy percentage.

  return accuracy_percentage_;
}