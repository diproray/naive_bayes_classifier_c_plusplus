//
// Created by Dipro Ray on 3/12/18.
//

#include "naive_bayes_classifying_model.h"
#include "../utils/utils.h"

// This file contains implementations of the functions for
// NaiveBayesClassifier Model - the class that stores all the probabilities and priors data
// and carries out the classification.

/**
 * . Function that generates the features probabilities matrix for the model.
 * It uses a ImagesAndLabelsDataset object to do so.
 *
 * @param training_data the ImagesAndLabels dataset used
 */
void NaiveBayesClassifyingModel::GenerateFeatureProbabilityMatrixAndPriorsVector(ImagesAndLabelsDataset &training_data) {

  cout << "Generating the Feature Probability Matrix: " << std::endl;

  // Loop through the 4D array.
  // Assign each position value to zero.

  for (int row_index = 0; row_index < 28; row_index++) {
    for (int col_index = 0; col_index < 28; col_index++) {
      for (int class_value = 0; class_value < 10; class_value++) {
        for (int value_at_position = 0; value_at_position < ::number_of_different_encodings;
             value_at_position++) {
          feature_probability_matrix_[row_index][col_index][class_value][value_at_position] = 0;
        }
      }
    }
  }

  // Loop through all positions in the 4D array.
  // Assign respective values to respective positions.

  for (int row_index = 0; row_index < 28; row_index += ::pixel_dimension_per_feature) {
    for (int col_index = 0; col_index < 28; col_index += ::pixel_dimension_per_feature) {
      for (int class_value = 0; class_value < 10; class_value++) {
        for (int value_at_position = 0; value_at_position < ::number_of_different_encodings;
             value_at_position++) {

          feature_probability_matrix_[row_index][col_index][class_value][value_at_position] =
              training_data.CalculateFeatureProbabilityAtIndexForClass(row_index,
                                                                       col_index,
                                                                       class_value, value_at_position);

        }
      }
    }

    // The below line prints a neat status bar to indicate
    // how much more time is required to complete the process.

    PrintProgressBar(static_cast<unsigned long>(row_index), 28);
  }

  cout << '\n';

  // Place class label prior probabilities into the appropriate vector.

  for (auto prior : training_data.GenerateVectorOfPriorsForLabels()) {
    vector_of_priors_.push_back(prior);
  }

  // Print a status message.
  cout << "Feature Probability Matrix and Priors Vector generated for the NaiveBayesClassifyingModel." << '\n';

}

/**
 * . Function that writes the probabilities and priors data to files.
 *
 * @param filename_for_probability_matrix the file path to the file in which the probabilities are to be stored
 * @param filename_for_priors_vector the file path to the file in which the priors are to be stored
 */
void NaiveBayesClassifyingModel::SaveModelFeatureProbabilityMatrixAndPriorsVectorToFiles(string filename_for_probability_matrix,
                                                                                         string filename_for_priors_vector) {

  // Initialize an ofstream.

  std::ofstream fout;

  // Open the required file. Delete its contents.

  fout.open(filename_for_probability_matrix, std::ios::out | std::ios::trunc);

  // If an error occurs, print an error message and return.

  if (!fout) {

    cout << "Wrong file name - file does not exist or is in a different directory.";
    return;

  }

  // Write all the probability values into the file.

  for (int row_index = 0; row_index < 28; row_index++) {
    for (int col_index = 0; col_index < 28; col_index++) {
      for (int class_value = 0; class_value < 10; class_value++) {
        for (int value_at_position = 0; value_at_position < ::number_of_different_encodings;
             value_at_position++) {

          fout << feature_probability_matrix_[row_index][col_index][class_value][value_at_position] << std::endl;

        }
      }
    }
  }

  fout.close();

  // Do the same process for the priors.
  // Now, open another file - the file which will store priors.

  fout.open(filename_for_priors_vector, std::ios::out | std::ios::trunc);

  // If an error occurs, print an error message and return.

  if (!fout) {

    cout << "Wrong file name - file does not exist or is in a different directory.";
    return;

  }

  // Write all the prior values into the file.
  for (auto prior: vector_of_priors_) {
    fout << prior << std::endl;
  }

  // Close the ofstream.

  fout.close();

  // Print a status message.

  cout << "Saved Feature Probability Matrix to: " << filename_for_probability_matrix << '\n';
  cout << "Saved Priors Vector to: " << filename_for_priors_vector << '\n';
}

/**
 * .  Function that reads the probabilities and priors data to files.
 *
 * @param filename_for_probability_matrix the file path to the file in which the probabilities were stored previously
 * @param filename_for_priors_vector the file path to the file in which the priors were stored previously
 */
void NaiveBayesClassifyingModel::LoadModelFeatureProbabilityMatrixAndPriorsVectorFromFiles(string filename_for_probability_matrix,
                                                                                           string filename_for_priors_vector) {

  // Initialize an ifstream.

  std::ifstream fin;

  // Open the desired file.

  fin.open(filename_for_probability_matrix);

  // If an error occurs, print an error message and return.
  if (!fin) {

    cout << "Wrong file name - file does not exist or is in a different directory.";
    return;

  }

  // Read values from the file into the probabilities matrix.

  for (int row_index = 0; row_index < 28; row_index++) {
    for (int col_index = 0; col_index < 28; col_index++) {
      for (int class_value = 0; class_value < 10; class_value++) {
        for (int value_at_position = 0; value_at_position < ::number_of_different_encodings;
             value_at_position++) {

          double probability;
          fin >> probability;

          feature_probability_matrix_[row_index][col_index][class_value][value_at_position] = probability;

        }
      }
    }
  }

  // Close the ifstream.

  fin.close();

  // Open the desired file.

  fin.open(filename_for_priors_vector);

  // If an error occurs, print an error message and return.

  if (!fin) {

    cout << "Wrong file name - file does not exist or is in a different directory.";
    return;

  }

  // Read values from the file into the priors vector.

  double prior;

  while (fin >> prior) {
    vector_of_priors_.push_back(prior);
  }

  // Close the ifstream.

  fin.close();

  // Print a status message.

  cout << "Loaded Feature Probability Matrix from: " << filename_for_probability_matrix << '\n';
  cout << "Loaded Priors Vector from: " << filename_for_priors_vector << '\n';
  cout << "Your NaiveBayesClassifyingModel is now loaded" << '\n';
}

/**
 * . Function that classifies an image into one of the labels.
 *
 * @param image_to_be_classified the image to classify into a label
 * @return the classified label value and its posterior probability
 */
std::pair<int, double> NaiveBayesClassifyingModel::Classifier(ImageData image_to_be_classified) {

  // Declare the vector that will store all the posterior probabilities.
  std::vector<double> posteriors;

  // For all possible class values,
  // Calculate the posterior probability using the formula provided in the documentation.

  for (unsigned long class_val = 0; class_val < 10; class_val++) {

    double posterior = 0;

    // Add log(class = c) to the posterior probability.
    posterior += log(vector_of_priors_.at(class_val));

    for (int row_index = 0; row_index < 28; row_index += ::pixel_dimension_per_feature) {
      for (int col_index = 0; col_index < 28; col_index += ::pixel_dimension_per_feature) {

        // Add P(F(i, j) = f | class = c) to the posterior probability.

        int value_at_position = image_to_be_classified.GetImageAs2dArray()[row_index][col_index];
        posterior += log(feature_probability_matrix_[row_index][col_index][class_val][value_at_position]);

      }
    }

    // Add this posterior probability into the vector.
    posteriors.push_back(posterior);
  }

  // Find the maximum posterior probability, and get its index.
  // The index is the class value the image is classified to by the classifier model.

  auto maximum_posterior = std::max_element(std::begin(posteriors), std::end(posteriors));
  int classified_class_val = (int) std::distance(std::begin(posteriors), maximum_posterior);

  // Make a pair out of classified class and its posterior probability.

  std::pair<int, double> classified_class_val_and_posterior (classified_class_val, posteriors[classified_class_val]);

  // Return the pair.

  return classified_class_val_and_posterior;

}

/**
 * . Constructor for a NaiveBayesClassifyingModel object, in which probabilities and priors
 * are found from previously stored model data, extracted out of files.
 *
 * @param filename_for_stored_probabilities the file path to the file in which the probabilities were stored previously
 * @param filename_for_stored_priors_vector the file path to the file in which the priors were stored previously
 * @param method set to "load". This argument isn't actually used. Placed to differentiate the constructors.
 */
NaiveBayesClassifyingModel::NaiveBayesClassifyingModel(string filename_for_stored_probabilities,
                                                       string filename_for_stored_priors_vector,
                                                       string method) {

  // Load data from previously created files.

  LoadModelFeatureProbabilityMatrixAndPriorsVectorFromFiles(std::move(filename_for_stored_probabilities),
                                                            std::move(filename_for_stored_priors_vector));

}

/**
 * . Constructor for a NaiveBayesClassifyingModel object, in which probabilities and priors
 * are found from training data, extracted out of files.
 *
 * @param filename_for_images the file path to the file in which the training images are stored
 * @param filename_for_labels the file path to the file in which the training images'labels are stored.
 */
NaiveBayesClassifyingModel::NaiveBayesClassifyingModel(string filename_for_images,
                                                       string filename_for_labels,
                                                       double laplace_smoothing_factor) {

  // Generate a dataset of images and labels to train the classifier.
  ImagesAndLabelsDataset
      training_data =
      ImagesAndLabelsDataset(std::move(filename_for_images), std::move(filename_for_labels), laplace_smoothing_factor);

  // Generate probability matrix and priors vector.
  GenerateFeatureProbabilityMatrixAndPriorsVector(training_data);
}
