//
// Created by Dipro Ray on 3/12/18.
//

#ifndef NAIVEBAYES_MODEL_H
#define NAIVEBAYES_MODEL_H

#include "../images_and_labels_dataset/images_and_labels_dataset.cpp"
#include<cmath>

class NaiveBayesClassifyingModel {

 private:

  double feature_probability_matrix_[28][28][10][2];
  std::vector<double> vector_of_priors_;

 public:

  NaiveBayesClassifyingModel() = default;

  explicit NaiveBayesClassifyingModel(string filename_for_images, string filename_for_labels);

  explicit NaiveBayesClassifyingModel(string filename_for_stored_probabilities,
                 string filename_for_stored_priors_vector,
                 string method);

  void GenerateFeatureProbabilityMatrixAndPriorsVector(ImagesAndLabelsDataset &training_data);

  void SaveModelFeatureProbabilityMatrixAndPriorsVectorToFiles(string filename_for_probability_matrix = "../data/probabilities",
                                                               string filename_for_priors_vector = "../data/priors");

  void LoadModelFeatureProbabilityMatrixAndPriorsVectorFromFiles(string filename_for_probability_matrix = "../data/probabilities",
                                                                 string filename_for_priors_vector = "../data/priors");

  int Classifier(ImageData image_to_be_classified);

  void print_progress_bar(int row_index);
};

#endif //NAIVEBAYES_MODEL_H
