//
// Created by Dipro Ray on 3/12/18.
//

#ifndef NAIVEBAYES_CLASSIFIER_IMPROVER_H
#define NAIVEBAYES_CLASSIFIER_IMPROVER_H

/**
 * . Class that has functions which try to improve the accuracy of classifiers.
 *
 * @author diproray
 */
class ClassifierImprover {

 public:

/**
 * . Function that finds the optimum k-value (Laplace Smoothing Factor)
 * for best accuracy by classifier.
 *
 * @return the best k value
 */
  double FindBestKValue();
};
#endif //NAIVEBAYES_CLASSIFIER_IMPROVER_H
