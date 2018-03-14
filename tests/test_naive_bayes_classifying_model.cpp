//
// Created by Dipro Ray on 3/13/18.
//


#include "../src/naive_bayes_classifying_model/naive_bayes_classifying_model.cpp"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Test for GenerateFeatureProbabilityMatrixAndPriorsVector") {

  NaiveBayesClassifyingModel model = NaiveBayesClassifyingModel("../data/trainingimages", "../data/traininglabels", 0.1);

  REQUIRE( model.GetValueFromProbabilityMatrix(0, 0, 0, 0) == 0.999791);
  REQUIRE( model.GetValueFromPriorsVector(0) == 0.0958);

}

TEST_CASE("Test for LoadModelFeatureProbabilityMatrixAndPriorsVectorFromFiles") {

  NaiveBayesClassifyingModel model;

  model.LoadModelFeatureProbabilityMatrixAndPriorsVectorFromFiles("../data/probabilities", "../data/priors");
  REQUIRE( model.GetValueFromProbabilityMatrix(0, 0, 0, 0) == 0.999791);
  REQUIRE( model.GetValueFromPriorsVector(0) == 0.0958);

}

TEST_CASE("Test for Classifier") {

  ImageData image;
  image.SetImageFromFile("./data/test_single_image");
  NaiveBayesClassifyingModel model;
  model.LoadModelFeatureProbabilityMatrixAndPriorsVectorFromFiles("../data/probabilities", "../data/priors");
  int value = model.Classifier(image).first;

  REQUIRE(value == 5);
}
