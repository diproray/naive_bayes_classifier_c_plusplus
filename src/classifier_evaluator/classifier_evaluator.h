//
// Created by Dipro Ray on 3/12/18.
//

#ifndef NAIVEBAYES_EVALUATOR_H
#define NAIVEBAYES_EVALUATOR_H

#include "../naive_bayes_classifying_model/naive_bayes_classifying_model.h"

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

 public:

  // The default constructor.
  ClassifierEvaluator() = default;

  /**
   * . Constructor for ClassifierEvaluator object.
   *
   * @param model the classifier model to be evaluated
   */
  explicit ClassifierEvaluator(NaiveBayesClassifyingModel model);

  /**
   * . Function that computes the accuracy and confusion matrix for a given model.
   *
   * @param model the model which is to be evaluated
   */
  void ComputeAccuracyAndConfusionMatrix(NaiveBayesClassifyingModel model);

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
