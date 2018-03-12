//
// Created by Dipro Ray on 3/11/18.
//


#include "training_data.cpp"

int main() {

  TrainingData training_data_object = TrainingData("../data/trainingimages", "../data/traininglabels");
  cout << training_data_object;

  /*
  training_data_object.GenerateVectorOfImagesFromFileData("../data/trainingimages");

  training_data_object.GenerateVectorOfLabelsFromFileData("../data/traininglabels");
  cout << '\n';
  training_data_object.GenerateVectorOfPriorsForLabels();
   */

}

