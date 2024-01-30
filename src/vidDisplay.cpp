/**
 * @file vidDisplay.cpp
 * @author Yuan Zhao zhao.yuan2@northeatern.edu
 * @brief main function for video display
 * @version 0.1
 * @date 2024-01-21
*/

#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include "filter.h"
#include "faceDetect.h"


int main(int argc, char *argv[]) {
    cv::VideoCapture *capdev;

    // open the video device
    capdev = new cv::VideoCapture(0);
    if( !capdev->isOpened() ) {
        printf("Unable to open video device\n");
        return(-1);
    }

    cv::Size refS( (int) capdev->get(cv::CAP_PROP_FRAME_WIDTH ),
                   (int) capdev->get(cv::CAP_PROP_FRAME_HEIGHT));
    printf("Expected size: %d %d\n", refS.width, refS.height);

    cv::namedWindow("Video", 1);

    // Create the variables for the processed frames
    cv::Mat frame, processedFrame, grayFrame;
    cv::Mat sobelXOutput, sobelYOutput, magnitudeOutput;
    cv::Mat quantizedOutput;

    cv::Mat grey;
    std::vector<cv::Rect> faces;
    cv:: Rect last(0, 0, 0, 0);

    cv::VideoWriter videoWriter;

    
    // modes flags
    bool grayMode = false, altGrayMode = false, sepiaMode = false, blurMode = false; 
    bool sobelXMode = false, sobelYMode = false, magnitudeMode = false;
    bool quantizeMode = false;
    bool faceDetectionMode = false;
    bool negativeMode = false, embossMode = false, colorfulFacesMode = false;
    // extension parts flags
    bool cartoonMode = false;
    bool horizontalWarpMode = false;
    bool verticalWarpMode = false;


    bool isRecording = false;

    float brightness = 0.0f; // Range can be -100 to 100
    float contrast = 1.0f;   // Range can be 0.5 to 3.0

    // main loop
    for(;;) {
        *capdev >> frame;
        if( frame.empty() ) {
            printf("frame is empty\n");
            break;
        }

        // Check for a keystroke
        char key = cv::waitKey(10);

        if( key == 'q') {
            break;
        }
        if( key == 'g') {
            grayMode = !grayMode; // Toggle standard grayscale mode
            altGrayMode = false;  // Turn off alternative grayscale mode
        }
        if( key == 'h') {
            altGrayMode = !altGrayMode; // Toggle alternative grayscale mode
            grayMode = false;           // Turn off standard grayscale mode
        }
        if (key == 'p'){
            sepiaMode = !sepiaMode; // Toggle sepiaTone mode
            grayMode = false;       // Turn off standard grayscale mode 
            altGrayMode = false;    // Turn off alternative grayscale mode
        }
        if (key == 'b'){
            blurMode = !blurMode; // Toggle blur mode
            grayMode = false;     // Turn off standard grayscale mode 
            altGrayMode = false;  // Turn off alternative grayscale mode
            sepiaMode = false;    // Turn off sepiaTone mode
        }
        if (key == 'x') {
            sobelXMode = !sobelXMode; // Toggle Sobel X mode
            sobelYMode = false;       // Turn off Sobel Y mode
        }
        if (key == 'y') {
            sobelYMode = !sobelYMode; // Toggle Sobel Y mode
            sobelXMode = false;       // Turn off Sobel X mode
        }
        if (key == 'm') {
            magnitudeMode = !magnitudeMode; // Toggle magnitude mode
        }
        if (key == 'l') {
            quantizeMode = !quantizeMode; // Toggle quantize mode
        }
        if (key == 'f') {
            faceDetectionMode = !faceDetectionMode;
        }
        if (key == 'n') {
            negativeMode = !negativeMode;
        }
        if (key == 'e') {
            embossMode = !embossMode;
        }
        if (key == 'c') {
            colorfulFacesMode = !colorfulFacesMode;
            if (colorfulFacesMode) {
            // Convert frame to grey and detect faces
            cv::Mat greyFrame;
            cv::cvtColor(frame, greyFrame, cv::COLOR_BGR2GRAY);
            detectFaces(greyFrame, faces);
            }
        } 
        if (key == 'u') {
            brightness += 10.0f;
        }
        if (key == 'd') {
            brightness -= 10.0f;
        }
        if (key == 'i') {
            contrast += 0.1f;
        }
        if (key == 'o') {
            contrast -= 0.1f;
        }
        if (key == 'a') {
            cartoonMode = !cartoonMode;
        }
        if (key == 'w') {
            horizontalWarpMode = !horizontalWarpMode;
            if (horizontalWarpMode) verticalWarpMode = false; // Disable vertical warp when horizontal warp is enabled
        }
        if (key == 'v') {
            verticalWarpMode = !verticalWarpMode;
            if (verticalWarpMode) horizontalWarpMode = false; // Disable horizontal warp when vertical warp is enabled
        }
        if (key == 'r') {
            if (!isRecording) {
                // Start recording
                std::string filename = "recorded_video.avi";  // Name of the output video file
                int codec = cv::VideoWriter::fourcc('M', 'J', 'P', 'G'); // Define the codec
                double frameRate = 20.0; // Set frame rate
                videoWriter.open(filename, codec, frameRate, cv::Size(refS.width, refS.height));

                if (!videoWriter.isOpened()) {
                    std::cerr << "Could not open the video file for write\n";
                    return -1;
                }
            } else {
                // Stop recording
                videoWriter.release();
            }
            isRecording = !isRecording;
        }


        // Apply brightness and contrast adjustment
        frame.convertTo(frame, -1, contrast, brightness);
        frame += cv::Scalar(brightness, brightness, brightness);
        frame *= contrast;
        cv::normalize(frame, frame, 0, 255, cv::NORM_MINMAX);
        frame.convertTo(frame, CV_8UC3);

        // Process the frame based on the filter's mode
        if(grayMode) {
            cv::cvtColor(frame, processedFrame, cv::COLOR_BGR2GRAY);
        } else if(altGrayMode) {
            greyscale(frame, processedFrame); // Apply custom grayscale
        } else if(sepiaMode) {
            sepiaTone(frame, processedFrame); // Apply sepiaTone
        } else if (blurMode){
            blur5x5_2(frame, processedFrame); // Apply blur gaussian 5x5_2
        } else if (sobelXMode) {
            sobelX3x3(frame, sobelXOutput);
            cv::convertScaleAbs(sobelXOutput, processedFrame);
        } else if (sobelYMode) {
            sobelY3x3(frame, sobelYOutput);
            cv::convertScaleAbs(sobelYOutput, processedFrame);
        } else if (magnitudeMode) {
            sobelX3x3(frame, sobelXOutput);
            sobelY3x3(frame, sobelYOutput);
            magnitude(sobelXOutput, sobelYOutput, magnitudeOutput);
            cv::convertScaleAbs(magnitudeOutput, processedFrame);
        } else if (quantizeMode) {
            int levels = 10; // Default number of levels
            blurQuantize(frame, quantizedOutput, levels);
            processedFrame = quantizedOutput;
        } else if (faceDetectionMode) {
            cv::Mat resizedFrame;
            float scale = 0.5; // Reduce the frame size to 50% to avoid lag
            cv::resize(frame, resizedFrame, cv::Size(), scale, scale);

            cv::cvtColor(resizedFrame, grey, cv::COLOR_BGR2GRAY);
            detectFaces(grey, faces);

            // Scale the face rectangles and draw them on the original frame
            for (cv::Rect &face : faces) {
                face.x /= scale;
                face.y /= scale;
                face.width /= scale;
                face.height /= scale;
                cv::rectangle(frame, face, cv::Scalar(0, 255, 0), 2);
            }

            processedFrame = frame;
        } else if (negativeMode){
            negativeFilter(frame, processedFrame); // Apply negative filter
        } else if (colorfulFacesMode){
            colorfulFaces(frame, faces, processedFrame); // Apply colorful faces
        } else if(embossMode){
            embossEffect(frame, processedFrame); // Apply emboss effect
        } else if (cartoonMode) {
            int levels = 15; // Adjust as needed
            int magThreshold = 20; // Adjust as needed
            cartoon(frame, processedFrame, levels, magThreshold);
        } else if (horizontalWarpMode) {
            warpImage(frame, processedFrame, true); // Apply horizontal warp
        } else if (verticalWarpMode) {
            warpImage(frame, processedFrame, false); // Apply vertical warp
        } else {
            processedFrame = frame.clone();
        }
        if (isRecording) {
            videoWriter.write(processedFrame);
        }

        cv::imshow("Video", processedFrame);

        // Save the processed frame if 's' is pressed
        if(key == 's') {
            static int imageCount = 0;
            std::string filename = "capture_" + std::to_string(imageCount++);
            if(grayMode) {
                filename += "_gray.jpg";
            } 
            else if(altGrayMode){
                filename += "_altgray.jpg";
            } 
            else if(sepiaMode){
                filename += "_sepia.jpg";
            }
            else if(blurMode){
                filename += "_blur.jpg";
            }
            else if(sobelXMode){
                filename += "_sobelX.jpg";
            }
            else if(sobelYMode){
                filename += "_sobelY.jpg";
            }
            else if (magnitudeMode){
                filename += "_magnitude.jpg";
            } 
            else if (quantizeMode){
                filename += "_quantize.jpg";
            } 
            else if (faceDetectionMode) {
                filename += "_face.jpg";
            } 
            else if (embossMode) {
                filename += "_emboss.jpg";
            }
            else if (negativeMode) {
                filename += "_negative.jpg";
            }
            else if (colorfulFacesMode) {
                filename += "_colorfulFaces.jpg";
            }
            else {
                filename += ".jpg";
        }

        if(cv::imwrite(filename, processedFrame)) {
                std::cout << "Saved " << filename << std::endl;
            } else {
                std::cout << "Failed to save image" << std::endl;
            }
        }
    }

    videoWriter.release();
    delete capdev;
    return(0);
}
