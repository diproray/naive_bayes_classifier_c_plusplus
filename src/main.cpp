//
// Created by Dipro Ray on 3/11/18.
//


#include "training_data.cpp"

int main() {
  /*
  ImageData image_object;
  image_object.SetImageFromFile("trainingimages");
  //cin >> image_object;
  cout << std::endl;
  cout << image_object;
  */


  TrainingData training_data_object;
  training_data_object.GenerateVectorOfLabelsFromFileData("../data/test_labels.txt");
  cout << '\n';
  training_data_object.GenerateVectorOfPriorsForLabels();
}

