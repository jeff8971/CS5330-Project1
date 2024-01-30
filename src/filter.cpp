/**
 * @file filter.cpp
 * @author Yuan Zhao zhao.yuan2@northeatern.edu
 * @brief filters, image manipulation functions
 * @version 0.1
 * @date 2024-01-21
*/

#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>
#include "filter.h"

// altgreyscale for Task 4
int greyscale(cv::Mat &src, cv::Mat &dst) {
    // Check if the source is empty
    if (src.empty()) {
        return -1;
    }
    // loop for each pixel of the src
    for (int y = 0; y < src.rows; y++){
      for (int x = 0; x < src.cols; x++){
            // by using the average RGB algorithm to get the alt grayscale
            cv::Vec3b pixel = src.at<cv::Vec3b>(y, x);
            uchar avg = (pixel[0] + pixel[1] + pixel[2]) / 3; // Average of RGB
            dst.at<cv::Vec3b>(y, x) = cv::Vec3b(avg, avg, avg);
      }
    }
    return 0;
}

// sepiaTone for Task 5

int sepiaTone(cv::Mat &src, cv::Mat &dst) {
    if (src.empty()) {
        return -1;
    }
    // clone the src to dst, to make sure the original src is not changed
    dst = src.clone();

    // Calculate the center of the image
    cv::Point center(src.cols / 2, src.rows / 2);
    double maxDistance = cv::norm(cv::Point(0, 0) - center);

    for (int y = 0; y < src.rows; y++) {
        for (int x = 0; x < src.cols; x++) {
            cv::Vec3b pixel = src.at<cv::Vec3b>(y, x);
            // using the new RGB to store the original RGB, to make sure the original RGB is not changed
            uchar newBlue   = std::min(255.0, pixel[2] * 0.272 + pixel[1] * 0.534 + pixel[0] * 0.131);
            uchar newGreen = std::min(255.0, pixel[2] * 0.349 + pixel[1] * 0.686 + pixel[0] * 0.168);
            uchar newRed  = std::min(255.0, pixel[2] * 0.393 + pixel[1] * 0.769 + pixel[0] * 0.189);
            
            dst.at<cv::Vec3b>(y, x) = cv::Vec3b(newBlue, newGreen, newRed);
            // Calculate the distance from the center
            double distance = cv::norm(cv::Point(x, y) - center);

            // Calculate the vignetting factor
            double vignette = std::max(0.0, 1 - distance / maxDistance);

            // Apply the vignetting factor to the new RGB values
            newBlue = std::min(255.0, newBlue * vignette);
            newGreen = std::min(255.0, newGreen * vignette);
            newRed = std::min(255.0, newRed * vignette);

            dst.at<cv::Vec3b>(y, x) = cv::Vec3b(static_cast<uchar>(newBlue), static_cast<uchar>(newGreen), static_cast<uchar>(newRed));
        }
    }
    return 0;
}

// 5 x 5 Gaussian blur function A
int blur5x5_1(cv::Mat &src, cv::Mat &dst) {
    if (src.empty()) {
        return -1;
    }
    // Clone the source to preserve the border
    dst = src.clone(); 

    int kernel[5][5] = {{1, 2, 4, 2, 1},
                        {2, 4, 8, 4, 2},
                        {4, 8, 16, 8, 4},
                        {2, 4, 8, 4, 2},
                        {1, 2, 4, 2, 1}};
    int kernelSum = 100; // Sum of the kernel values

    for (int y = 2; y < src.rows - 2; y++) {
        for (int x = 2; x < src.cols - 2; x++) {
            cv::Vec3i sum(0, 0, 0);
            for (int dy = -2; dy <= 2; dy++) {
                for (int dx = -2; dx <= 2; dx++) {
                    cv::Vec3b pixel = src.at<cv::Vec3b>(y + dy, x + dx);
                    for (int c = 0; c < 3; c++) {
                        sum[c] += pixel[c] * kernel[dy + 2][dx + 2];
                    }
                }
            }
            for (int c = 0; c < 3; c++) {
                dst.at<cv::Vec3b>(y, x)[c] = sum[c] / kernelSum;
            }
        }
    }

  return 0;
}


// 5 x 5 Gaussian blur function B
int blur5x5_2(cv::Mat &src, cv::Mat &dst) {
    if (src.empty()) {
        return -1;
    }

    cv::Mat temp = src.clone();
    dst = src.clone();

    // Define the 1D kernel
    int kernel[5] = {1, 2, 4, 2, 1};
    int kernelSum = 10;  // Sum of kernel values

    // Horizontal pass
    for (int y = 2; y < src.rows - 2; y++) {
        for (int x = 2; x < src.cols - 2; x++) {
            cv::Vec3i sum(0, 0, 0);
            for (int dx = -2; dx <= 2; dx++) {
                cv::Vec3b pixel = src.at<cv::Vec3b>(y, x + dx);
                for (int c = 0; c < 3; c++) {
                    sum[c] += pixel[c] * kernel[dx + 2];
                }
            }
            for (int c = 0; c < 3; c++) {
                temp.at<cv::Vec3b>(y, x)[c] = sum[c] / kernelSum;
            }
        }
    }

    // Vertical pass
    for (int y = 2; y < src.rows - 2; y++) {
        for (int x = 2; x < src.cols - 2; x++) {
            cv::Vec3i sum(0, 0, 0);
            for (int dy = -2; dy <= 2; dy++) {
                cv::Vec3b pixel = temp.at<cv::Vec3b>(y + dy, x);
                for (int c = 0; c < 3; c++) {
                    sum[c] += pixel[c] * kernel[dy + 2];
                }
            }
            for (int c = 0; c < 3; c++) {
                dst.at<cv::Vec3b>(y, x)[c] = sum[c] / kernelSum;
            }
        }
    }

    return 0;
}

// Task 7: Sobel_X 3 x 3 function
int sobelX3x3( cv::Mat &src, cv::Mat &dst ){
    if (src.empty()) {
        return -1;
    }

    dst.create(src.size(), CV_16SC3);

    // Horizontal kernel [-1, 0, 1]
    for (int y = 1; y < src.rows - 1; y++) {
        for (int x = 1; x < src.cols - 1; x++) {
            cv::Vec3s sum(0, 0, 0);
            for (int dx = -1; dx <= 1; dx++) {
                cv::Vec3b pixel = src.at<cv::Vec3b>(y, x + dx);
                for (int c = 0; c < 3; c++) {
                    sum[c] += pixel[c] * dx;
                }
            }
            dst.at<cv::Vec3s>(y, x) = sum;
        }
    }
    return 0;

}

// Task 7: Sobel_Y 3 x 3 function
int sobelY3x3( cv::Mat &src, cv::Mat &dst ){
    if (src.empty()) {
        return -1;
    }

    dst.create(src.size(), CV_16SC3);

    // Vertical kernel [-1, 0, 1] transposed
    for (int y = 1; y < src.rows - 1; y++) {
        for (int x = 1; x < src.cols - 1; x++) {
            cv::Vec3s sum(0, 0, 0);
            for (int dy = -1; dy <= 1; dy++) {
                cv::Vec3b pixel = src.at<cv::Vec3b>(y + dy, x);
                for (int c = 0; c < 3; c++) {
                    sum[c] += pixel[c] * dy;
                }
            }
            dst.at<cv::Vec3s>(y, x) = sum;
        }
    }
    return 0;

}

// Task 8: generates a gradient magnitude image from the X and Y Sobel images
int magnitude(cv::Mat &sx, cv::Mat &sy, cv::Mat &dst) {
    if (sx.empty() || sy.empty() || sx.size() != sy.size() || sx.type() != sy.type()) {
        return -1;
    }

    dst.create(sx.size(), CV_8UC3);

    for (int y = 0; y < sx.rows; y++) {
        for (int x = 0; x < sx.cols; x++) {
            cv::Vec3b magnitudeColor;
            for (int c = 0; c < 3; c++) {
                float gradX = sx.at<cv::Vec3s>(y, x)[c];
                float gradY = sy.at<cv::Vec3s>(y, x)[c];
                magnitudeColor[c] = cv::saturate_cast<uchar>(std::sqrt(gradX * gradX + gradY * gradY));
            }
            dst.at<cv::Vec3b>(y, x) = magnitudeColor;
        }
    }
    return 0;
}

// Task 9: blurs and quantizes the image
int blurQuantize(cv::Mat &src, cv::Mat &dst, int levels) {
    if (src.empty() || levels <= 0) {
        return -1;
    }

    // Step 1: Blur the image
    // Use a simple blur like a box filter for simplicity
    cv::Mat blurred;
    cv::blur(src, blurred, cv::Size(5, 5));

    // Step 2: Quantize the image
    dst = blurred.clone();
    int bucketSize = 255 / levels;

    for (int y = 0; y < dst.rows; y++) {
        for (int x = 0; x < dst.cols; x++) {
            cv::Vec3b &pixel = dst.at<cv::Vec3b>(y, x);
            for (int c = 0; c < 3; c++) {
                int bucket = pixel[c] / bucketSize;
                pixel[c] = static_cast<uchar>(bucket * bucketSize);
            }
        }
    }

    return 0;
}

// Task 11: other filter 1 - Single-Step Pixel-Wise Modification
// negative filter
int negativeFilter(cv::Mat &src, cv::Mat &dst) {
    if (src.empty()) {
        return -1;
    }

    dst = src.clone();
    for (int y = 0; y < dst.rows; y++) {
        for (int x = 0; x < dst.cols; x++) {
            for (int c = 0; c < dst.channels(); c++) {
                dst.at<cv::Vec3b>(y, x)[c] = 255 - dst.at<cv::Vec3b>(y, x)[c];
            }
        }
    }
    return 0;
}

// Task 11: other filter 2 - area effect (emboss effect)
int embossEffect(cv::Mat &src, cv::Mat &dst) {
    if (src.empty()) {
        return -1;
    }

    cv::Mat sobelXOutput, sobelYOutput;
    sobelX3x3(src, sobelXOutput); // Assuming sobelX3x3 is implemented
    sobelY3x3(src, sobelYOutput); // Assuming sobelY3x3 is implemented

    dst.create(src.size(), src.type());

    for (int y = 0; y < src.rows; y++) {
        for (int x = 0; x < src.cols; x++) {
            cv::Vec3s gradX = sobelXOutput.at<cv::Vec3s>(y, x);
            cv::Vec3s gradY = sobelYOutput.at<cv::Vec3s>(y, x);
            for (int c = 0; c < 3; c++) {
                float emboss = gradX[c] * 0.7071 + gradY[c] * 0.7071;
                dst.at<cv::Vec3b>(y, x)[c] = cv::saturate_cast<uchar>(emboss + 128);
            }
        }
    }

    return 0;
}

// Task 11: other filter 3 - face detect (colorful faces, grayscale background)
int colorfulFaces(cv::Mat &src, std::vector<cv::Rect> &faces, cv::Mat &dst) {
    if (src.empty()) {
        return -1;
    }

    cv::cvtColor(src, dst, cv::COLOR_BGR2GRAY);
    cv::cvtColor(dst, dst, cv::COLOR_GRAY2BGR);

    for (const auto &face : faces) {
        src(face).copyTo(dst(face));
    }
    return 0;
}


// Extension Part 1: 
// cartoonized the live video
int cartoon(cv::Mat &src, cv::Mat &dst, int levels, int magThreshold) {
  // generate the gradient magnitude
  cv::Mat sobelx;
  sobelX3x3(src, sobelx);
  cv::Mat sobely;
  sobelY3x3(src, sobely);
  cv::Mat mag;
  magnitude(sobelx, sobely, mag);

  // generate the blurred and quantized image
  cv::Mat quantize;
  blurQuantize(src, quantize, levels);

  dst = cv::Mat::zeros(src.size(), CV_8UC3);

  // apply the threshold
  for (int i = 0; i < src.rows; i++)
  {
    cv::Vec3b *dptr = dst.ptr<cv::Vec3b>(i);
    cv::Vec3b *mptr = mag.ptr<cv::Vec3b>(i);
    cv::Vec3b *qptr = quantize.ptr<cv::Vec3b>(i);

    for (int j = 0; j < src.cols; j++)
    {
      for (int c = 0; c < 3; c++)
      {
        // only copy the quantized image if the magnitude is lower than the threshold
        if (mptr[j][c] <= magThreshold)
        {
          dptr[j][c] = qptr[j][c];
        }
      }
    }
  }

  return (0);
}


void warpImage(cv::Mat &src, cv::Mat &dst, bool horizontalWarp) {
    dst = cv::Mat::zeros(src.size(), src.type());

    double frequency = 100; // Frequency of the sine wave
    double amplitude = 200; // Amplitude of the sine wave

    for (int y = 0; y < src.rows; y++) {
        for (int x = 0; x < src.cols; x++) {
            int newX = x, newY = y;

            if (horizontalWarp) {
                newY = y + static_cast<int>(amplitude * sin(2 * M_PI * x / frequency));
            } else {
                newX = x + static_cast<int>(amplitude * sin(2 * M_PI * y / frequency));
            }

            if (newX >= 0 && newX < src.cols && newY >= 0 && newY < src.rows) {
                dst.at<cv::Vec3b>(y, x) = src.at<cv::Vec3b>(newY, newX);
            }
        }
    }
}