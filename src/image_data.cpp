//
// Created by Dipro Ray on 3/11/18.
//

#include <fstream>
#include "image_data.h"

/**
 * . Setter for image_as_2d_array_
 * @param image the image (a 2d array) to be set to
 */
void ImageData::SetImageAs2dArray(int image[kImageSize][kImageSize]) {

  // Using a nested for loop, copy each value of image into the respective
  // position at image_as_2d_array_.
  // (This is the only way to copy arrays in C++, it doesn't allow making a deep copy easily.)

  for (int row_index = 0; row_index < kImageSize; row_index++) {
    for (int column_index = 0; column_index < kImageSize; column_index++) {

      image_as_2d_array_[row_index][column_index] = image[row_index][column_index];

    }
  }

}

/**
 * . Getter for image_as_2d_array_
 * @return  the image, as a 2D array, with each value as 0 or 1
 */
int ** ImageData::GetImageAs2dArray() const {

  // Initialize a new array of pointers.
  auto ** image = new int * [kImageSize];

  // Point respective pointers in image to the appropriate positions in image_as_2d_array_.
  for (int row_index = 0; row_index < kImageSize; row_index++) {

    // The below line allows the particular pointer to point to an array (i.e. 1 row of the 2d array).
    image[row_index] = new int[kImageSize];

    for (int column_index = 0; column_index < kImageSize; column_index++) {
      image[row_index][column_index] = image_as_2d_array_[row_index][column_index];
    }
  }

  return image;
}

/**
 * . Function that overloads the << operator to print out the entire 2D array of an image.
 * @param output_stream the stream to print to
 * @param image_data the ImageData object that is to be printed
 * @return return the output_stream, the stream to be printed to
 */
ostream & operator <<(ostream & output_stream, const ImageData & image_data) {

  // In a nested for loop,
  // Print each value in the 2D array.

  for (int row_index = 0; row_index < image_data.kImageSize; row_index++) {

    for (int column_index = 0; column_index < image_data.kImageSize; column_index++) {
      output_stream << image_data.image_as_2d_array_[row_index][column_index];
    }

    output_stream << std::endl;
  }

  return output_stream;
}

/**
 * . Function that overloads the input >> operator to read an entire image and store it into
 * a 2D array.
 * @param input_stream the stream to read from
 * @param image_data the ImageData object that is to be read
 * @return return the input_stream, the stream being read from
 */
istream & operator >>(istream & input_stream, ImageData & image_data) {

  int image[28][28];

  string line;

  // For kImageSize number of times,
  // read in each line, through a loop.

  for (int line_number = 0; line_number < image_data.kImageSize; line_number++) {

    std::getline(input_stream, line);

    // For each line,
    // Iterate through the entire line, placing value 0 into the respective position in the array if
    // the character is ' ', or 1 if the character is '#' or '+'.

    for (unsigned long column_index = 0; column_index < image_data.kImageSize; column_index++) {

      int value_to_be_set_to = 0;

      if (line.at(column_index) == '+' || line.at(column_index) == '#') {
        value_to_be_set_to = 1;
      }

      image[line_number][column_index] = value_to_be_set_to;
    }
  }

  // Set this 2D array as the image for the ImageData object.
  image_data.SetImageAs2dArray(image);

  return input_stream;
}

/**
 * . Setter for image, using the data from a file
 * @param filename the file from which the data is to be taken.
 */
void ImageData::SetImageFromFile(const string &filename){

  ImageData image = ImageData();

  // Open file using ifstream, and read data from there.
  ifstream file (filename);

  string line;

  // The below line invokes the overloaded input operator.
  file >> image;

  // Set the object's image to the 2D array of the object the file data was read into.
  SetImageAs2dArray(image.image_as_2d_array_);

}