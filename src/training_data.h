//
// Created by Dipro Ray on 3/11/18.
//

#ifndef NAIVEBAYES_TRAINING_DATA_H
#define NAIVEBAYES_TRAINING_DATA_H

#include "image_data.cpp"

/**
 * . Class that encapsulates all the data used for training the model.
 * This includes the entire set of images encoded as 2D arrays contained in ImageData objects,
 * and the entire set of labels for the training images.
 *
 * @author diproray
 */
class TrainingData {

 private:

  // The vector that contains all the ImageData objects, which contain training images.
  std::vector<ImageData> vector_of_training_image_objects_;

  // The vector that contains the correct labels for the training images.
  // Each position in this vector contains the label of the image
  // at the corresponding position in vector_of_training_image_objects_.
  std::vector<int> vector_of_training_image_labels_;

 public:

  // The default constructor for TrainingData objects.
  TrainingData() = default;

  // The Laplace Smoothing factor for probability calculations.
  // This value can be tuned to modify the accuracy of the classifier.
  const double kLaplaceSmoothingFactor_ = 0.5;

  /**
   * . Another constructor for TrainingData objects.
   *  It takes file names as input - the files from which training images and labels are to be read.
   */
  explicit TrainingData(string filename_for_images, string filename_for_labels);

  /**
   * . Function that reads data from a file that contains labels data,
   * and puts them into the relevant vector (vector_of_training_image_labels_)
   * of the TrainingData object.
   * @param filename the file from which label data are to be read
   */
  void GenerateVectorOfLabelsFromFileData(string filename);

  /**
    * . Function that reads data from a file that contains images,
    * and puts them into the relevant vector (vector_of_training_image_objects_)
    * of the TrainingData object.
    * @param filename the file from which images are to be read
    */
  void GenerateVectorOfImagesFromFileData(string filename);

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
  double CalculateFeatureProbabilityAtIndexForClass(int row_index,
                                                    int column_index,
                                                    int class_value,
                                                    int value_at_position);

  /**
   * . Function that calculates the probability of finding a particular value among the training labels,
   * i.e. the probability of finding class_value among values in vector_of_training_image_labels_.
   *
   * @param class_value the desired value of the label/class
   * @return a double value, which is the probability of finding class_value among values in vector_of_training_image_labels_.
   */
  double CalculateProbabilityOfClassInLabels(int class_value);

  /**
   * . Function that returns a vector of probabilities for label/class values 0 through 9.
   *
   * @return a vector of doubles, which is a vector of probabilities for label/class values 0 through 9.
   */
  std::vector<double> GenerateVectorOfPriorsForLabels();

};
#endif //NAIVEBAYES_TRAINING_DATA_H