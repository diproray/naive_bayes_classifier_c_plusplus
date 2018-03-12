//
// Created by Dipro Ray on 3/12/18.
//

#include "utils.h"

#include <iostream>

using std::cout;

/**
 * . Helper function that prints a nice progress bar while the huge amount of data is loading.
 *
 * @param row_index parameter deciding part of progress bar to be shown
 */
void PrintProgressBar(unsigned long image_index, int size) {

  int length_of_bar = 40;

  // Compute the number of squares to be printed.

  auto number_of_squares = (int) (((double) (image_index + 1) / size) * length_of_bar);

  cout << "\rStatus Bar: [";

  for (int index = 0; index < number_of_squares; index++) {
    cout << "\u25A0";
  }

  for (int index = 0; index < (length_of_bar - number_of_squares); index++) {
    cout << " ";
  }

  cout << "]" << std::flush;
}
