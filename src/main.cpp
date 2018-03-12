//
// Created by Dipro Ray on 3/11/18.
//


#include <iomanip>
#include "naive_bayes_classifying_model/naive_bayes_classifying_model.cpp"
#include "classifier_evaluator/classifier_evaluator.cpp"
#include "extra_credit_code/classifier_improver/classifier_improver.cpp"

int main() {

  // NaiveBayesClassifyingModel model = NaiveBayesClassifyingModel("../data/probabilities", "../data/priors", "load");

  NaiveBayesClassifyingModel model = NaiveBayesClassifyingModel("../data/trainingimages", "../data/traininglabels", 0.5);

  ClassifierEvaluator evaluator = ClassifierEvaluator(model);

  cout << evaluator;
  /*
  ClassifierImprover improver;

  cout << improver.FindBestKValue();
   */

}

