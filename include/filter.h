/**
 * @file filter.h
 * @author Yuan Zhao zhao.yuan2@northeatern.edu
 * @brief header file for all the filter functions
 * @version 0.1
 * @date 2024-01-25
*/

#ifndef FILTER_H
#define FILTER_H

#include <opencv2/opencv.hpp>

// Task 4: alt greyscale function
int greyscale(cv::Mat &src, cv::Mat &dst);

// Task 5: sepia tone function
int sepiaTone(cv::Mat &src, cv::Mat &dst);

// Task 6: 5 x 5 Gaussian blur function A
int blur5x5_1(cv::Mat &src, cv::Mat &dst);

// Task 6: 5 x 5 Gaussian blur function B
int blur5x5_2(cv::Mat &src, cv::Mat &dst);

// Task 7: Sobel_X 3 x 3 function
int sobelX3x3( cv::Mat &src, cv::Mat &dst );

// Task 7: Sobel_Y 3 x 3 function
int sobelY3x3( cv::Mat &src, cv::Mat &dst );

// Task 8: magnitude for Sobel_X & Sobel_Y
int magnitude(cv::Mat &sx, cv::Mat &sy, cv::Mat &dst);

// Task 9: blurs and quantizes the image
int blurQuantize( cv::Mat &src, cv::Mat &dst, int levels );

// Task 11: other filter 1 - Single-Step Pixel-Wise Modification
// negative filter
int negativeFilter(cv::Mat &src, cv::Mat &dst);

// Task 11: other filter 2 - emboss effect
int embossEffect(cv::Mat &src, cv::Mat &dst);

// Task 11: other filter 3 - face detect 
// colorful faces, grayscale background
int colorfulFaces(cv::Mat &src, std::vector<cv::Rect> &faces, cv::Mat &dst);

// Extension Part 2: cartoon filter
int cartoon(cv::Mat &src, cv::Mat &dst, int levels, int magThreshold);

// Extension Part 3: warp effect
void warpImage(cv::Mat &src, cv::Mat &dst, bool horizontalWarp);

#endif // FILTER_H
