/**
 * @file imgDisplay.cpp
 * @author Yuan Zhao zhao.yuan2@northeatern.edu
 * @brief task 1: Read an image from a file and display it
 * @version 0.1
 * @date 2024-01-21
*/

#include <iostream>
#include <opencv2/opencv.hpp>

int main(){
  // image path for input
  std::string imagePath = "/Users/jeff/Desktop/task1.jpeg";

  // Read the image file
  cv::Mat image = cv::imread(imagePath, cv::IMREAD_COLOR);

  // Check for failure
  if (image.empty()) {
      std::cout << "Could not open or find the image" << std::endl;
      std::cin.get(); // Wait for any key press
      return -1;
  }

  // Create a window
  std::string windowName = "Image Display";
  cv::namedWindow(windowName);

  // Show the image inside the created window
  cv::imshow(windowName, image);

  // Wait for any keystroke in the window
  char key = cv::waitKey(0);

  while (key != 'q') {
      // Add functionality for other keypresses here
      // Example: if (key == 's') { /* Save image, etc. */ }

      // Wait for another keystroke
      key = cv::waitKey(0);
  }

  // Destroy the created window
  cv::destroyWindow(windowName);

  return 0;
}
