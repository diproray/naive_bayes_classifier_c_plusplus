cmake_minimum_required(VERSION 3.5)
project(naivebayes)

set(CMAKE_CXX_STANDARD 14)

add_executable(naivebayes ./src/main.cpp)
add_executable(unit-tests tests/test_image_data.cpp)
add_executable(unit-tests-images_and_labels_dataset tests/test_images_and_labels_dataset.cpp)

#add_executable(unit-tests)
