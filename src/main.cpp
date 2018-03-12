//
// Created by Dipro Ray on 3/11/18.
//


#include <iomanip>
#include "naive_bayes_classifying_model/naive_bayes_classifying_model.cpp"
#include "classifier_evaluator.cpp"

int main() {

  NaiveBayesClassifyingModel model = NaiveBayesClassifyingModel("../data/probabilities", "../data/priors", "load");

  ClassifierEvaluator evaluator = ClassifierEvaluator(model);

  cout << evaluator;

}

