//
// Created by Dipro Ray on 3/12/18.
//

#ifndef NAIVEBAYES_EVALUATOR_H
#define NAIVEBAYES_EVALUATOR_H

#include "naive_bayes_classifying_model/naive_bayes_classifying_model.h"
class ClassifierEvaluator {

 private:

  double accuracy_percentage_;
  double confusion_matrix_[10][10];

 public:

  ClassifierEvaluator() = default;

  explicit ClassifierEvaluator(NaiveBayesClassifyingModel model);

  void ComputeAccuracyAndConfusionMatrix(NaiveBayesClassifyingModel model);

  void PrintProgressBar(unsigned long index);

  void ConvertCountToPercentageInConfusionMatrix();

  friend ostream &operator<<(ostream &output_stream, const ClassifierEvaluator &classifier_evaluator);

};
#endif //NAIVEBAYES_EVALUATOR_H
