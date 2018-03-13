//
// Created by Dipro Ray on 3/11/18.
//

#ifndef NAIVEBAYES_TRAINING_DATA_H
#define NAIVEBAYES_TRAINING_DATA_H

#include "../image_data/image_data.cpp"

/**
 * . Class that encapsulates all the data used for training the model.
 * This includes the entire set of images encoded as 2D arrays contained in ImageData objects,
 * and the entire set of labels for the training images.
 *
 * @author diproray
 */
class ImagesAndLabelsDataset {

 private:

  // The vector that contains all the ImageData objects, which contain training images.
  std::vector<ImageData> vector_of_training_image_objects_;

  // The vector that contains the correct labels for the training images.
  // Each position in this vector contains the label of the image
  // at the corresponding position in vector_of_training_image_objects_.
  std::vector<int> vector_of_training_image_labels_;

  // The Laplace Smoothing factor for probability calculations.
  // This value can be tuned to modify the accuracy of the classifier.
  double laplace_smoothing_factor_;

 public:

  // The default constructor for ImagesAndLabelsDataset objects.
  ImagesAndLabelsDataset() = default;

  /**
   * . Another constructor for TrainingData objects.
   *  It takes file names as input - the files from which training images and labels are to be read.
   */
  explicit ImagesAndLabelsDataset(string filename_for_images,
                                  string filename_for_labels,
                                  double laplace_smoothing_factor);

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
   * . Function that returns the most common element in a feature of dimensions
   * pixel_dimension_per_feature * pixel_dimension_per_feature, with (row_index, column_index) as the upper
   * left corner postion of the feature.
   *
   * @param row_index the row index of the upper left corner of the feature
   * @param column_index the column index of the upper left corner of the feature
   * @param image_object the image object whose values are being considered
   * @return an int - the value of the most common element in the feature
   */
  int most_common_element_in_feature(int row_index, int column_index, const ImageData &image_object);

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

  /**
   * . Function that overloads the << operator to print out the contents of TrainingData:
   * the entire vector of images encoded as 2D arrays, and the vector of labels.
   * @param output_stream the stream to print to
   * @param training_data the TrainingData object that is to be printed
   * @return return the output_stream, the stream to be printed to
   */
  friend ostream &operator<<(ostream &output_stream, const ImagesAndLabelsDataset &training_data);

  /**
   * . Getter for vector of images
   * @return the vector of images (ImageData objects)
   */
  std::vector<ImageData> GetVectorOfImages();

  /**
   * . Getter for vector of labels/classes
   * @return the vector of labels
   */
  std::vector<int> GetVectorOfLabels();

};

#endif //NAIVEBAYES_TRAINING_DATA_H
