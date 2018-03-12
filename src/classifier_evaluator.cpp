//
// Created by Dipro Ray on 3/12/18.
//

#include <iomanip>
#include <utility>
#include "classifier_evaluator.h"

static const int kNumberOfClassValues = 10;

void ClassifierEvaluator::ComputeAccuracyAndConfusionMatrix(NaiveBayesClassifyingModel model) {

  ImagesAndLabelsDataset test_data = ImagesAndLabelsDataset("../data/testimages", "../data/testlabels", 0.5);

  for (int i = 0; i < kNumberOfClassValues; i++) {
    for (int j = 0; j < i; j++) {
      confusion_matrix_[i][j] = 0;
    }
  }

  int count_of_correct_predictions = 0;

  unsigned long number_of_images = test_data.GetVectorOfImages().size();

  for (unsigned long index = 0; index < number_of_images; index++) {

    int estimated_class = model.Classifier(test_data.GetVectorOfImages().at(index));

    // cout << "Number: " << index << "| Classified as: " << estimated_class << "| Actually is: "
    //     << test_data.GetVectorOfLabels().at(index) << std::endl;
    if (estimated_class == test_data.GetVectorOfLabels().at(index)) {
      count_of_correct_predictions++;
    }

    confusion_matrix_[test_data.GetVectorOfLabels().at(index)][estimated_class]++;

    PrintProgressBar(index);
  }

  accuracy_percentage_ = ((double) count_of_correct_predictions / number_of_images) * 100;

  ConvertCountToPercentageInConfusionMatrix();

}

void ClassifierEvaluator::ConvertCountToPercentageInConfusionMatrix() {

  for (int row_index = 0; row_index < kNumberOfClassValues; row_index++) {

    int sum = 0;

    for (int col_index = 0; col_index < kNumberOfClassValues; col_index++) {
      sum += confusion_matrix_[row_index][col_index];
    }

    for (int col_index = 0; col_index < kNumberOfClassValues; col_index++) {
      confusion_matrix_[row_index][col_index] = (confusion_matrix_[row_index][col_index] / sum) * 100;
    }
  }
}

void ClassifierEvaluator::PrintProgressBar(unsigned long image_index) {

  int length_of_bar = 50;
  auto number_of_hashes = (int) (((double) (image_index + 1) / 1000) * length_of_bar);
  cout << "Status Bar: [|";

  for (int index = 0; index < number_of_hashes; index++) {
    cout << "#|";
  }

  for (int index = 0; index < (length_of_bar - number_of_hashes); index++) {
    cout << " |";
  }

  cout << "]" << std::endl;
}

ostream &operator<<(ostream &output_stream, const ClassifierEvaluator &classifier_evaluator) {

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

ClassifierEvaluator::ClassifierEvaluator(NaiveBayesClassifyingModel model) {

  ComputeAccuracyAndConfusionMatrix(std::move(model));
}