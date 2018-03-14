//
// Created by Dipro Ray on 3/13/18.
//


#include "../src/images_and_labels_dataset/images_and_labels_dataset.cpp"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Test for GenerateVectorOfImagesFromFileData") {

  ImagesAndLabelsDataset dataset;
  bool task_successful = dataset.GenerateVectorOfImagesFromFileData("../src/data/trainingimages");

  REQUIRE(task_successful == TRUE);
}

TEST_CASE("Test for GenerateVectorOfImagesFromFileData", "[exception]") {

  ImagesAndLabelsDataset dataset;
  bool task_successful = dataset.GenerateVectorOfImagesFromFileData("../trainingimages");

  REQUIRE(task_successful == FALSE);
}

TEST_CASE("Test for GenerateVectorOfLabelsFromFileData") {

  ImagesAndLabelsDataset dataset;
  bool task_successful = dataset.GenerateVectorOfLabelsFromFileData("../src/data/traininglabels");

  REQUIRE(task_successful == TRUE);
}

TEST_CASE("Test for GenerateVectorOfLabelsFromFileData", "[exception]") {

  ImagesAndLabelsDataset dataset;
  bool task_successful = dataset.GenerateVectorOfImagesFromFileData("../traininglabels");

  REQUIRE(task_successful == FALSE);
}

TEST_CASE("Test for CalculateFeatureProbabilityAtIndexForClass", ) {

  ImagesAndLabelsDataset dataset;
  dataset.GenerateVectorOfImagesFromFileData("../data/traininglabels");

  double probability = dataset.CalculateFeatureProbabilityAtIndexForClass(0,0,0,0);
  REQUIRE( probability == 0.9997);
}

TEST_CASE("Test for CalculateProbabilityOfClassInLabels", ) {

  ImagesAndLabelsDataset dataset;
  dataset.GenerateVectorOfLabelsFromFileData("../data/traininglabels");

  double probability = dataset.CalculateProbabilityOfClassInLabels(0);
  REQUIRE( probability == 0.0958);
}

TEST_CASE("Test for GenerateVectorOfPriorsForLabels", ) {

  ImagesAndLabelsDataset dataset;
  dataset.GenerateVectorOfLabelsFromFileData("../data/traininglabels");
  std::vector<double> priors = dataset.GenerateVectorOfPriorsForLabels();

  double first_prior = priors.at(0);
  REQUIRE( first_prior == 0.0958);
}

TEST_CASE("Test for GetVectorOfImages", ) {

  ImagesAndLabelsDataset dataset;
  dataset.GenerateVectorOfImagesFromFileData("../data/trainingimages");
  std::vector<ImageData> images = dataset.GetVectorOfImages();

  ImageData image;
  image.SetImageFromFile("./data/test_single_image");

  REQUIRE( images.at(0) == image);
}

TEST_CASE("Test for GetVectorOfLabels", ) {

  ImagesAndLabelsDataset dataset;
  dataset.GenerateVectorOfLabelsFromFileData("../data/traininglabels");
  std::vector<int> labels = dataset.GetVectorOfLabels();

  REQUIRE(labels.at(0) == 5);
}



