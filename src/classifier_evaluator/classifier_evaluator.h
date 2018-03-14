//
// Created by Dipro Ray on 3/12/18.
//

#ifndef NAIVEBAYES_EVALUATOR_H
#define NAIVEBAYES_EVALUATOR_H

#include "../naive_bayes_classifying_model/naive_bayes_classifier.h"

/**
 * . Class that evaluates the accuracy of a classifier.
 *
 * @author diproray
 */
class ClassifierEvaluator {

 private:

  // The accuracy percentage of the classifier.

  double accuracy_percentage_;

  // The confusion matrix of the classifier.

  double confusion_matrix_[10][10];

  // Map from class value to a pair of (index of maximum posterior, maximum posterior)
  std::map<int, std::pair<unsigned int, double>> class_val_to_max_posterior_index_;

  // Map from class value to a pair of (index of minimum posterior, minimum posterior)
  std::map<int, std::pair<unsigned int, double>> class_val_to_min_posterior_index_;

 public:

  // The default constructor.
  ClassifierEvaluator() = default;

  /**
   * . Constructor for ClassifierEvaluator object.
   *
   * @param model the classifier model to be evaluated
   */
  explicit ClassifierEvaluator(NaiveBayesClassifier model);

  /**
   * . Function that computes the accuracy and confusion matrix for a given model.
   *
   * @param model the model which is to be evaluated
   */
  void ComputeAccuracyAndConfusionMatrix(NaiveBayesClassifier model);

  /**
   * . Function that initializes all values in the maps and confusion matrix to zero.
   *
   */
  void InitializeAllToZero();

  /**
   * . Function that updates the map for each pair of estimated class and posterior read.
   *
   * @param pair the pair containing the estimated class and the posterior probability
   * @param estimated_class the estimated class
   */
  void UpdateMaps(std::pair<int, double> &pair, int index);

  /**
   * . Function that converts a confusion matrix of number of occurrences of events
   * into a percentage.
   */
  void ConvertCountToPercentageInConfusionMatrix();

  /**
   * . Getter for the object's accuracy percentage.
   * @return the accuracy percentage
   */
  double GetAccuracyPercentage();

  /**
   * . Function that overloads the << operator. Used mainly for debugging purposes.
   *
   * @param output_stream the stream to put the data into
   * @param classifier_evaluator the object whose data is to be printed
   * @return the output stream
   */
  friend ostream &operator<<(ostream &output_stream, const ClassifierEvaluator &classifier_evaluator);

};
#endif //NAIVEBAYES_EVALUATOR_H
