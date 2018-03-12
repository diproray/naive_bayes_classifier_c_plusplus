//
// Created by Dipro Ray on 3/11/18.
//


#include "naive_bayes_classifying_model/naive_bayes_classifying_model.cpp"

int main() {

  NaiveBayesClassifyingModel model = NaiveBayesClassifyingModel("../data/probabilities", "../data/priors", "load");

  ImagesAndLabelsDataset test_data = ImagesAndLabelsDataset("../data/testimages", "../data/testlabels");


  int count = 0;

  for (unsigned long i = 0; i < test_data.GetVectorOfImages().size(); i++) {

    int estimated_class = model.Classifier(test_data.GetVectorOfImages().at(i));

    cout << "Number: " << i << "| Classified as: " << estimated_class << "| Actually is: " << test_data.GetVectorOfLabels().at(i) << std::endl;
    if (estimated_class == test_data.GetVectorOfLabels().at(i)) {
      count ++;
    }
  }

  cout << '\n' << "Percentage of Accuracy: " << (double) count / 10 << "%";

}

