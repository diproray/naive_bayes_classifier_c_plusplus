//
// Created by Dipro Ray on 3/13/18.
//

#include "../src/classifier_evaluator/classifier_evaluator.cpp"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

// Test for ComputeAccuracyAndConfusionMatrix()

TEST_CASE("Test for ComputeAccuracyAndConfusionMatrix") {

  NaiveBayesClassifyingModel model;
  model.LoadModelFeatureProbabilityMatrixAndPriorsVectorFromFiles("../data/probabilities", "../data/priors");

  ClassifierEvaluator evaluator = ClassifierEvaluator(model);

  REQUIRE(evaluator.GetAccuracyPercentage() == 77.3);
}

// This function calls other functions, so they are indirectly tested.
// The output overloading function has been manually tested.