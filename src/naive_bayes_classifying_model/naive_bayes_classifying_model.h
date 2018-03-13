//
// Created by Dipro Ray on 3/12/18.
//

#ifndef NAIVEBAYES_MODEL_H
#define NAIVEBAYES_MODEL_H

#include "../images_and_labels_dataset/images_and_labels_dataset.cpp"
#include<cmath>

/**
 * . Class that stores all the probabilities and priors data
 * and carries out the classification. This is the Classifier for the entire program.
 *
 * @author diproray
 */
class NaiveBayesClassifyingModel {

 private:

  // The 4 - dimensional matrix storing the probabilities of all possible features.
  double feature_probability_matrix_[28][28][10][3];

  // The vector containing the probabilities of all possible class/label values.
  std::vector<double> vector_of_priors_;

 public:

  // The default constructor.
  NaiveBayesClassifyingModel() = default;

  // NaiveBayesClassifyingModel objects can be made in 2 ways:
  // 1. Using training data from files, building a model.
  // 2. Load the model data saved in files previously.
  //
  // For this, we have 2 non-default (explicit) constructors.

  /**
   * . Constructor for a NaiveBayesClassifyingModel object, in which probabilities and priors
   * are found from training data, extracted out of files.
   *
   * @param filename_for_images the file path to the file in which the training images are stored
   * @param filename_for_labels the file path to the file in which the training images'labels are stored.
   * @param laplace_smoothing_factor the Laplace smoothing factor
   */
  explicit NaiveBayesClassifyingModel(string filename_for_images,
                                      string filename_for_labels,
                                      double laplace_smoothing_factor);

  /**
   * . Constructor for a NaiveBayesClassifyingModel object, in which probabilities and priors
   * are found from previously stored model data, extracted out of files.
   *
   * @param filename_for_stored_probabilities the file path to the file in which the probabilities were stored previously
   * @param filename_for_stored_priors_vector the file path to the file in which the priors were stored previously
   * @param method set to "load". This argument isn't actually used. Placed to differentiate the constructors.
   */
  explicit NaiveBayesClassifyingModel(string filename_for_stored_probabilities,
                                      string filename_for_stored_priors_vector,
                                      string method);

  /**
   * . Function that generates the features probabilities matrix for the model.
   * It uses a ImagesAndLabelsDataset object to do so.
   *
   * @param training_data the ImagesAndLabels dataset used
   */
  void GenerateFeatureProbabilityMatrixAndPriorsVector(ImagesAndLabelsDataset &training_data);

  /**
   * . Function that writes the probabilities and priors data to files.
   *
   * @param filename_for_probability_matrix the file path to the file in which the probabilities are to be stored
   * @param filename_for_priors_vector the file path to the file in which the priors are to be stored
   */
  void SaveModelFeatureProbabilityMatrixAndPriorsVectorToFiles(string filename_for_probability_matrix = "../data/probabilities",
                                                               string filename_for_priors_vector = "../data/priors");

  /**
   * .  Function that reads the probabilities and priors data to files.
   *
   * @param filename_for_probability_matrix the file path to the file in which the probabilities were stored previously
   * @param filename_for_priors_vector the file path to the file in which the priors were stored previously
   */
  void LoadModelFeatureProbabilityMatrixAndPriorsVectorFromFiles(string filename_for_probability_matrix = "../data/probabilities",
                                                                 string filename_for_priors_vector = "../data/priors");

  /**
   * . Function that classifies an image into one of the labels.
   *
   * @param image_to_be_classified the image to classifiy into a label
   * @return the classified label value, and its posterior probability
   */
  std::pair<int, double> Classifier(ImageData image_to_be_classified);

};

#endif //NAIVEBAYES_MODEL_H
