//
// Created by Dipro Ray on 3/11/18.
//

#include "images_and_labels_dataset.h"
#include <utility>
#include <algorithm>
#include "../utils/utils.cpp"

// This file contains implementations of the functions of the
// ImagesAndLabelsDataset class ( Class that encapsulates all the data used for training the model.
// This includes the entire set of images encoded as 2D arrays contained in ImageData objects,
// and the entire set of labels for the training images)



/**
 * . Function that reads data from a file that contains labels data,
 * and puts them into the relevant vector (vector_of_training_image_labels_)
 * of the TrainingData object.
 * @param filename the file from which label data are to be read
 */
bool ImagesAndLabelsDataset::GenerateVectorOfLabelsFromFileData(string filename) {

  if (filename.empty()) {
    return false;
  }

  // Initialise an ifstream and open the desired file.

  std::ifstream file_reader;
  file_reader.open(filename);

  // If the file doesn't exist,
  // Then, an error message is printed and the system exits.

  if (!file_reader) {
    cout << "File is invalid.";
    return false;
  }

  // If the file exists,
  // Read in an integer, and push it into the vector_of_training_image_labels_.
  // Keep doing this till eof is reached.

  int value;

  while (file_reader >> value) {
    vector_of_training_image_labels_.push_back(value);
  }

  // Close the ifstream. [Deallocation of resources]
  file_reader.close();

  return true;
}

/**
 * . Function that reads data from a file that contains images,
 * and puts them into the relevant vector (vector_of_training_image_objects_)
 * of the TrainingData object.
 * @param filename the file from which images are to be read
 */
bool ImagesAndLabelsDataset::GenerateVectorOfImagesFromFileData(string filename) {

  if (filename.empty()) {
    return false;
  }

  // Initialise an ifstream and open the desired file.

  std::ifstream file_reader;
  file_reader.open(filename);

  // If the file doesn't exist,
  // Then, an error message is printed and the system exits.

  if (!file_reader) {
    cout << "File is invalid.";
    return false;
  }

  // From the file,
  // Read in an ImageData object.
  // (This will call the overloaded >> operator of ImageData.)
  // Push it into the vector: vector_of_training_image_objects_
  // Keep doing this till the eof is reached.

  while (!file_reader.eof()) {

    ImageData image_object;
    string line;
    file_reader >> image_object;
    vector_of_training_image_objects_.push_back(image_object);

  }

  // Close the ifstream.
  file_reader.close();

  // Pop the last element (ImageData object) in the vector.
  // The last element is always a blank image and so, it needs to be removed.
  // (This is because, I'm not sure why, but, after adding all images to the vector from the file,
  // a blank image gets added. So, I just remove that last object.)

  vector_of_training_image_objects_.pop_back();
  return true;
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
double ImagesAndLabelsDataset::CalculateFeatureProbabilityAtIndexForClass(int row_index,
                                                                          int column_index,
                                                                          int class_value,
                                                                          int desired_value_at_position) {

  // Initialize int variables to store the counts of class_value and desired value at position.

  int count_of_occurrences_of_class_value = 0;
  int count_of_desired_value_at_desired_position = 0;

  // Loop through all the labels in the vector containing all labels,
  // If the label is the desired value, go further and count the occurrences of the desired value at
  // the desired position.

  for (unsigned long index = 0; index < vector_of_training_image_labels_.size(); index++) {

    // If the desired class value is the label,
    // increment its count by 1.

    if (vector_of_training_image_labels_.at(index) == class_value) {
      count_of_occurrences_of_class_value++;

      // If the desired value is present at the desired position,
      // increment the count by 1.

      const ImageData &image_object = vector_of_training_image_objects_.at(index);
      if (most_common_element_in_feature(row_index, column_index, image_object) == desired_value_at_position) {
        count_of_desired_value_at_desired_position++;
      }

    }
  }

  // Probability calculation using the formula given in the documentation.

  double desiredFeatureProbability =
      (laplace_smoothing_factor_ + count_of_desired_value_at_desired_position)
          / (2 * laplace_smoothing_factor_ + count_of_occurrences_of_class_value);

  return desiredFeatureProbability;
}

/**
 * . Function that returns the most common element in a feature of dimensions
 * pixel_dimension_per_feature * pixel_dimension_per_feature, with (row_index, column_index) as the upper
 * left corner postion of the feature.
 *
 * @param row_index the row index of the upper left corner of the feature
 * @param column_index the column index of the upper left corner of the feature
 * @param image_object the image object whose values are being considered
 * @return an int - the value of the most common element in the feature
 */
int ImagesAndLabelsDataset::most_common_element_in_feature(int row_index,
                                                           int column_index,
                                                           const ImageData &image_object) {

  // Initialize a vector that will store all the values in the feature.
  std::vector<int> values;

  // For all positions within the feature, push the value at that position into the vector of values.

  for (int row_number = row_index; row_number < row_index + ::pixel_dimension_per_feature; row_number++) {
    for (int col_number = column_index; col_number < column_index + ::pixel_dimension_per_feature; col_number++) {
      values.push_back(image_object.GetImageAs2dArray()[row_number][col_number]);
    }
  }

  // Find the value that occurs most in the vector.

  int max_occurrences = 0;
  int most_occurring_value = values[0];

  for (int index = 0; index < values.size(); index++) {
    int occurrences = (int) std::count(values.begin(), values.end(), values[index]);

    if (occurrences > max_occurrences) {
      max_occurrences = occurrences;
      most_occurring_value = values[index];
    }
  }

  // Return the most frequently occurring element in the vector

  return most_occurring_value;
}

/**
 * . Function that calculates the probability of finding a particular value among the training labels,
 * i.e. the probability of finding class_value among values in vector_of_training_image_labels_.
 *
 * @param class_value the desired value of the label/class
 * @return a double value, which is the probability of finding class_value among values in vector_of_training_image_labels_.
 */
double ImagesAndLabelsDataset::CalculateProbabilityOfClassInLabels(int class_value) {

  // Initialize an int variables that stores the number of occurrences
  // of class_value as the label's value.

  int count_of_occurrences_of_class_value = 0;

  // Loop through all labels in the vector.
  // If the label value matches class_value,
  // increment the count value by 1.

  for (auto label: vector_of_training_image_labels_) {

    if (label == class_value) {
      count_of_occurrences_of_class_value++;
    }

  }

  // Calculate the probability using formula provided in the documentation.
  // Then, return it.

  double desiredPriorProbability =
      (double) count_of_occurrences_of_class_value / vector_of_training_image_labels_.size();

  return desiredPriorProbability;
}

/**
 * . Function that returns a vector of probabilities for label/class values 0 through 9.
 *
 * @return a vector of doubles, which is a vector of probabilities for label/class values 0 through 9.
 */
std::vector<double> ImagesAndLabelsDataset::GenerateVectorOfPriorsForLabels() {

  // Initialize a vector of doubles,
  // that will store the probabilities of encountering label/class values 0 through 9
  // in vector_of_training_image_labels_.

  std::vector<double> vector_of_priors;

  // Loop through all possible class values 0 - 9 (provided in the documentation).
  // Calculate the probability of the occurrence of each.

  for (int class_value = 0; class_value < 10; class_value++) {

    double probability_of_class_value = CalculateProbabilityOfClassInLabels(class_value);
    vector_of_priors.push_back(probability_of_class_value);

  }

  // Return the vector containing the probabilities.

  return vector_of_priors;
}

/**
 * . Another constructor for TrainingData objects.
 *  It takes file names as input - the files from which training images and labels are to be read.
 *
 *  Uses other class functions. It is just a fast way to combine everything into one and execute.
 */
ImagesAndLabelsDataset::ImagesAndLabelsDataset(string filename_for_images,
                                               string filename_for_labels,
                                               double laplace_smoothing_factor) {

  // Generate vectors of training images and training image labels
  // for the ImagesAndLabelsDataset object.

  // Usage of std::move here.
  // For reference, see http://en.cppreference.com/w/cpp/utility/move
  // std::move "converts" lvalues / rvalues into xvalues - telling the compiler
  // that it is OK to move it around instead of creating copies.

  GenerateVectorOfImagesFromFileData(std::move(filename_for_images));
  GenerateVectorOfLabelsFromFileData(std::move(filename_for_labels));
  laplace_smoothing_factor_ = laplace_smoothing_factor;

}

/**
 * . Function that overloads the << operator to print out the contents of TrainingData:
 * the entire vector of images encoded as 2D arrays, and the vector of labels.
 * @param output_stream the stream to print to
 * @param training_data the TrainingData object that is to be printed
 * @return return the output_stream, the stream to be printed to
 */
ostream &operator<<(ostream &output_stream, const ImagesAndLabelsDataset &training_data) {

  // Print all the training images.

  cout << "Training Images: " << '\n';

  for (unsigned long i = 0; i < training_data.vector_of_training_image_objects_.size(); i++) {
    cout << "Image " << i << ": " << std::endl << training_data.vector_of_training_image_objects_.at(i) << '\n';
  }

  // Print all the labels for the training images.

  cout << '\n' << "Labels for the Training Images: " << std::endl;

  for (unsigned long i = 0; i < training_data.vector_of_training_image_labels_.size(); i++) {
    cout << "Label for Image " << i << ": " << training_data.vector_of_training_image_labels_.at(i) << '\n';
  }

  // Return the ostream.

  return output_stream;
}

/**
 * . Getter for vector of images
 * @return the vector of images (ImageData objects)
 */
std::vector<ImageData> ImagesAndLabelsDataset::GetVectorOfImages() {

  return vector_of_training_image_objects_;
}

/**
 * . Getter for vector of labels/classes
 * @return the vector of labels
 */
std::vector<int> ImagesAndLabelsDataset::GetVectorOfLabels() {

  return vector_of_training_image_labels_;
}
