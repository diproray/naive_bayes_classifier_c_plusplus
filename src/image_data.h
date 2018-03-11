//
// Created by Dipro Ray on 3/11/18.
//

#ifndef NAIVEBAYES_IMAGE_DATA_H
#define NAIVEBAYES_IMAGE_DATA_H

#include <istream>
#include <ostream>
#include <string>
#include <vector>
#include <iostream>

using std::cin;
using std::cout;
using std::istream;
using std::ifstream;
using std::ostream;
using std::string;
using std::vector;

/**
 * . Class that encapsulates data pertaining to an image and relevant functions
 * that operate on them.
 *
 * @author diproray
 */
class ImageData {

 private:

  // The 2D array that stores the image.
  int image_as_2d_array_[28][28];

 public:
  // The default constructor.
  ImageData() = default;

/**
 * . Getter for image_as_2d_array_
 * @return  the image, as a 2D array, with each value as 0 or 1
 */
  int ** GetImageAs2dArray() const;

  // The dimension of an image width/length. For this program, it is ALWAYS 28.
  static const int kImageSize = 28;

/**
 * . Setter for image_as_2d_array_
 * @param image the image (a 2d array) to be set to
 */
  void SetImageAs2dArray(int image[28][28]);

/**
 * . Setter for image, using the data from a file
 * @param filename the file from which the data is to be taken.
 */
  void SetImageFromFile(const string & filename);

/**
 * . Function that overloads the input >> operator to read an entire image and store it into
 * a 2D array.
 * @param input_stream the stream to read from
 * @param image_data the ImageData object that is to be read
 * @return return the input_stream, the stream being read from
 */
  friend istream & operator >>(istream & input_stream, ImageData & image_data);

/**
 * . Function that overloads the << operator to print out the entire 2D array of an image.
 * @param output_stream the stream to print to
 * @param image_data the ImageData object that is to be printed
 * @return return the output_stream, the stream to be printed to
 */
  friend ostream & operator <<(ostream & output_stream, const ImageData & image_data);

};

#endif //NAIVEBAYES_IMAGE_DATA_H
