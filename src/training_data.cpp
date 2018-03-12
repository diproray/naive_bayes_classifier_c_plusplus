//
// Created by Dipro Ray on 3/11/18.
//

#include "training_data.h"

#include <utility>

/**
 * . Function that reads data from a file that contains labels data,
 * and puts them into the relevant vector (vector_of_training_image_labels_)
 * of the TrainingData object.
 * @param filename the file from which label data are to be read
 */
void TrainingData::GenerateVectorOfLabelsFromFileData(string filename) {

  std::ifstream file_reader;
  file_reader.open(filename);

  if (!file_reader) {
    cout << "File is invalid.";
    exit;
  }

  int value;

  while (file_reader >> value) {
    vector_of_training_image_labels_.push_back(value);
    cout << value << '\n';
  }

  file_reader.close();
}

/**
 * . Function that reads data from a file that contains images,
 * and puts them into the relevant vector (vector_of_training_image_objects_)
 * of the TrainingData object.
 * @param filename the file from which images are to be read
 */
void TrainingData::GenerateVectorOfImagesFromFileData(string filename) {

  std::ifstream file_reader;
  file_reader.open(filename);

  if (!file_reader) {
    cout << "File is invalid.";
    exit;
  }

  for (auto i = 1; i != file_reader.eof(); i += 28) {

    ImageData image_object;
    file_reader >> image_object;
    vector_of_training_image_objects_.push_back(image_object);

  }

  file_reader.close();
}

/**
 * . Function that calculates the probability of a feature for the classifier, i.e.
 * it computes the probability of finding value_at_position at position (row_index, column_index)
 * in an image whose label/class is class_value.
 * Probability is calculated using the formula:
 * P(Fi,j =f|class=c)= (k + # of times F(i,j) =f when class=c) / (2k + Total number of training examples where class = c)
 *
 * @param row_index the row index of the desired position
 * @param column_index the column index of the desired position
 * @param class_value the label/class of desired images
 * @param value_at_position the desired value at the desired position
 * @return a double value, which is the probability of finding value_at_position at position (row_index, column_index)
 *         in an image whose label/class is class_value.
 */
double TrainingData::CalculateFeatureProbabilityAtIndexForClass(int row_index,
                                                                int column_index,
                                                                int class_value,
                                                                int desired_value_at_position) {

  int count_of_occurrences_of_class_value = 0;
  int count_of_desired_value_at_desired_position = 0;

  for (unsigned long index = 0; index < vector_of_training_image_labels_.size(); index++) {

    if (vector_of_training_image_labels_.at(index) == class_value) {
      count_of_occurrences_of_class_value++;

      const ImageData &image_object = vector_of_training_image_objects_.at(index);
      if (image_object.GetImageAs2dArray()[row_index][column_index] == desired_value_at_position) {
        count_of_desired_value_at_desired_position++;
      }

    }
  }

  double desiredFeatureProbability =
      (kLaplaceSmoothingFactor_ + count_of_desired_value_at_desired_position)
          / (2 * kLaplaceSmoothingFactor_ + count_of_occurrences_of_class_value);

  return desiredFeatureProbability;
}

/**
 * . Function that calculates the probability of finding a particular value among the training labels,
 * i.e. the probability of finding class_value among values in vector_of_training_image_labels_.
 *
 * @param class_value the desired value of the label/class
 * @return a double value, which is the probability of finding class_value among values in vector_of_training_image_labels_.
 */
double TrainingData::CalculateProbabilityOfClassInLabels(int class_value) {

  int count_of_occurrences_of_class_value = 0;

  for (auto label: vector_of_training_image_labels_) {

    if (label == class_value) {
      count_of_occurrences_of_class_value++;
    }

  }

  double
      desiredPriorProbability = (double) count_of_occurrences_of_class_value / vector_of_training_image_labels_.size();
  return desiredPriorProbability;
}

/**
 * . Function that returns a vector of probabilities for label/class values 0 through 9.
 *
 * @return a vector of doubles, which is a vector of probabilities for label/class values 0 through 9.
 */
std::vector<double> TrainingData::GenerateVectorOfPriorsForLabels() {

  std::vector<double> vector_of_priors;

  for (int class_value = 0; class_value < 10; class_value++) {

    double probability_of_class_value = CalculateProbabilityOfClassInLabels(class_value);
    vector_of_priors.push_back(probability_of_class_value);

  }

  return vector_of_priors;
}

/**
 * . Another constructor for TrainingData objects.
 *  It takes file names as input - the files from which training images and labels are to be read.
 */
explicit TrainingData::TrainingData(string filename_for_images, string filename_for_labels) {

  GenerateVectorOfImagesFromFileData(std::move(filename_for_images));
  GenerateVectorOfLabelsFromFileData(std::move(filename_for_labels));

}