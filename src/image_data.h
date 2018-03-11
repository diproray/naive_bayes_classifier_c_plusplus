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


class ImageData {

 private:
  int image_as_2d_array_[28][28];

 public:
  ImageData() = default;

  int ** GetImageAs2dArray() const;

  void SetImageAs2dArray(int image[28][28]);

  void SetImageFromFile(const string & filename);

  friend istream & operator >>(istream & input_stream, ImageData & image_data);

  friend ostream & operator <<(ostream & output_stream, const ImageData & image_data);

};

#endif //NAIVEBAYES_IMAGE_DATA_H
