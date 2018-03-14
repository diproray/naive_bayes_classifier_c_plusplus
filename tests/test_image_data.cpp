//
// Created by Dipro Ray on 3/13/18.
//

#include "../src/image_data/image_data.cpp"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

// Test for SetImageAs2dArray()

TEST_CASE("Test for SetImageAs2dArray") {

  int image[28][28];

  for (int row_index = 0; row_index < 28; row_index++) {
    for (int col_index = 0; col_index < 28; col_index++) {
      image[row_index][col_index] = 0;
    }
  }

  ImageData image_object{};
  image_object.SetImageAs2dArray(image);

  ImageData image_object_loaded_from_file{};
  image_object_loaded_from_file.SetImageFromFile("./data/test_single_image.txt");

  REQUIRE((image_object == image_object_loaded_from_file) == TRUE);
}

// The other functions cannot be tested because they are operator overloading functions.
// They have been manually tested.
// Also, some of them are used when testing functions of other class, so they are indirectly tested.



