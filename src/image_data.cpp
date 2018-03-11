//
// Created by Dipro Ray on 3/11/18.
//

#include <fstream>
#include "image_data.h"

void ImageData::SetImageAs2dArray(int image[28][28]) {

  for (int row_index = 0; row_index < 28; row_index++) {
    for (int column_index = 0; column_index < 28; column_index++) {

      image_as_2d_array_[row_index][column_index] = image[row_index][column_index];

    }
  }

}

int ** ImageData::GetImageAs2dArray() const {

  auto ** image = new int * [28];

  for (int row_index = 0; row_index < 28; row_index++) {

    image[row_index] = new int[28];

    for (int column_index = 0; column_index < 28; column_index++) {
      image[row_index][column_index] = image_as_2d_array_[row_index][column_index];
    }
  }

  return image;
}

ostream & operator <<(ostream & output_stream, const ImageData & image_data) {

  for (int row_index = 0; row_index < 28; row_index++) {

    for (int column_index = 0; column_index < 28; column_index++) {
      output_stream << image_data.image_as_2d_array_[row_index][column_index];
    }

    output_stream << std::endl;
  }

  return output_stream;
}

istream & operator >>(istream & input_stream, ImageData & image_data) {

  int image[28][28];

  string line;

  for (int line_number = 0; line_number < 28; line_number++) {

    std::getline(input_stream, line);


    for (int column_index = 0; column_index < 28; column_index++) {

      int value_to_be_set_to = 0;

      if (line.at(column_index) == '+' || line.at(column_index) == '#') {
        value_to_be_set_to = 1;
      }

      image[line_number][column_index] = value_to_be_set_to;
    }
  }

  image_data.SetImageAs2dArray(image);

  return input_stream;
}

void ImageData::SetImageFromFile(const string &filename){

  ImageData image = ImageData();

  ifstream file (filename);

  string line;

  if (file.is_open()) {
    while (getline(file, line)) {
      cin >> image;
    }
  }

  SetImageAs2dArray(image.image_as_2d_array_);

}