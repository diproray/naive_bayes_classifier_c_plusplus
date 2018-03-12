//
// Created by Dipro Ray on 3/12/18.
//

#include "naive_bayes_classifying_model.h"

#include <utility>

/**
 * . Function that generates the features probabilities matrix for the model.
 * It uses a ImagesAndLabelsDataset object to do so.
 *
 * @param training_data the ImagesAndLabels dataset used
 */
void NaiveBayesClassifyingModel::GenerateFeatureProbabilityMatrixAndPriorsVector(ImagesAndLabelsDataset &training_data) {

  cout << "Generating the Feature Probability Matrix: " << std::endl;

  for (int row_index = 0; row_index < 28; row_index++) {
    for (int col_index = 0; col_index < 28; col_index++) {
      for (int class_value = 0; class_value < 10; class_value++) {
        for (int value_at_position = 0; value_at_position < 2; value_at_position++) {

          feature_probability_matrix_[row_index][col_index][class_value][value_at_position] =
              training_data.CalculateFeatureProbabilityAtIndexForClass(row_index,
                                                                       col_index,
                                                                       class_value,
                                                                       value_at_position);

        }
      }
    }

    print_progress_bar(row_index);
  }

  for (auto prior : training_data.GenerateVectorOfPriorsForLabels()) {
    vector_of_priors_.push_back(prior);
  }

  cout << "Feature Probability Matrix and Priors Vector generated for the NaiveBayesClassifyingModel." << '\n';

}

/**
 * . Helper function that prints a nice progress bar while the huge amount of data is loading.
 *
 * @param row_index parameter deciding part of progress bar to be shown
 */
void NaiveBayesClassifyingModel::print_progress_bar(int row_index) {

  auto number_of_hashes = (int) (((double) (row_index + 1) / 28) * 20);
  cout << "Status Bar: [|";

  for (int index = 0; index < number_of_hashes; index++) {
    cout << "#|";
  }

  for (int index = 0; index < (20 - number_of_hashes); index++) {
    cout << " |";
  }

  cout << "]" << std::endl;
}

/**
 * . Function that writes the probabilities and priors data to files.
 *
 * @param filename_for_probability_matrix the file path to the file in which the probabilities are to be stored
 * @param filename_for_priors_vector the file path to the file in which the priors are to be stored
 */
void NaiveBayesClassifyingModel::SaveModelFeatureProbabilityMatrixAndPriorsVectorToFiles(string filename_for_probability_matrix,
                                                                                         string filename_for_priors_vector) {

  std::ofstream fout;

  fout.open(filename_for_probability_matrix, std::ios::out | std::ios::trunc);

  if (!fout) {

    cout << "Wrong file name - file does not exist or is in a different directory.";
    return;

  }

  for (int row_index = 0; row_index < 28; row_index++) {
    for (int col_index = 0; col_index < 28; col_index++) {
      for (int class_value = 0; class_value < 10; class_value++) {
        for (int value_at_position = 0; value_at_position < 2; value_at_position++) {

          fout << feature_probability_matrix_[row_index][col_index][class_value][value_at_position] << std::endl;

        }
      }
    }
  }

  fout.close();

  fout.open(filename_for_priors_vector, std::ios::out | std::ios::trunc);

  if (!fout) {

    cout << "Wrong file name - file does not exist or is in a different directory.";
    return;

  }

  for (auto prior: vector_of_priors_) {
    fout << prior << std::endl;
  }

  fout.close();

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

  std::ifstream fin;

  fin.open(filename_for_probability_matrix);

  if (!fin) {

    cout << "Wrong file name - file does not exist or is in a different directory.";
    return;

  }

  for (int row_index = 0; row_index < 28; row_index++) {
    for (int col_index = 0; col_index < 28; col_index++) {
      for (int class_value = 0; class_value < 10; class_value++) {
        for (int value_at_position = 0; value_at_position < 2; value_at_position++) {

          double probability;
          fin >> probability;

          feature_probability_matrix_[row_index][col_index][class_value][value_at_position] = probability;

        }
      }
    }
  }

  fin.close();

  fin.open(filename_for_priors_vector);

  if (!fin) {

    cout << "Wrong file name - file does not exist or is in a different directory.";
    return;

  }

  double prior;
  while (fin >> prior) {
    vector_of_priors_.push_back(prior);
  }

  fin.close();

  cout << "Loaded Feature Probability Matrix from: " << filename_for_probability_matrix << '\n';
  cout << "Loaded Priors Vector from: " << filename_for_priors_vector << '\n';
  cout << "Your NaiveBayesClassifyingModel is now loaded" << '\n';
}

/**
 * . Function that classifies an image into one of the labels.
 *
 * @param image_to_be_classified the image to classifiy into a label
 * @return the classified label value
 */
int NaiveBayesClassifyingModel::Classifier(ImageData image_to_be_classified) {

  std::vector<double> posteriors;

  for (unsigned long class_val = 0; class_val < 10; class_val++) {

    double posterior = 0;

    posterior += log(vector_of_priors_.at(class_val));

    for (int row_index = 0; row_index < 28; row_index++) {
      for (int col_index = 0; col_index < 28; col_index++) {
        int value_at_position = image_to_be_classified.GetImageAs2dArray()[row_index][col_index];
        posterior += log(feature_probability_matrix_[row_index][col_index][class_val][value_at_position]);
      }
    }

    posteriors.push_back(posterior);
  }

  auto maximum_posterior = std::max_element(std::begin(posteriors), std::end(posteriors));
  int classified_class_val = (int) std::distance(std::begin(posteriors), maximum_posterior);

  return classified_class_val;

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
NaiveBayesClassifyingModel::NaiveBayesClassifyingModel(string filename_for_images, string filename_for_labels) {

  ImagesAndLabelsDataset
      training_data = ImagesAndLabelsDataset(std::move(filename_for_images), std::move(filename_for_labels));

  GenerateFeatureProbabilityMatrixAndPriorsVector(training_data);
  SaveModelFeatureProbabilityMatrixAndPriorsVectorToFiles();
}
