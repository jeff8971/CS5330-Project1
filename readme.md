# Project1_YZ: CS5330 Project 1 - Video-special effects

[Project Repository](https://github.com/jeff8971/Project1_YZ)

## Overview
This project is part of the CS5330 Computer Vision course. It focuses on implementing various image processing techniques and face detection using OpenCV in C++. The project includes tasks such as displaying images, detecting faces in images and videos, and applying different filters to process images.

## System Environment
- **IDE**: Visual Studio Code
- **Compiler**: C++ Compiler (C++11 standard)
- **System Configuration**: macOS Sonoma
- **Dependencies**: OpenCV library

## Project Structure
- `src/`: Contains the source files for the project.
  - `faceDetect.cpp`: Face detection functionality.
  - `filter.cpp`: Various image filters.
  - `imgDisplay.cpp`: Displaying images.
  - `showFaces.cpp`: Show detected faces.
  - `timeBlur.cpp`: Time-based blurring.
  - `vidDisplay.cpp`: Video display functionality.
- `include/`: Header files for the project.
  - `faceDetect.h`: Header for face detection.
  - `filter.h`: Header for image filters.
- `data/`: Sample images and data used by the project.
- `CMakeLists.txt`: CMake configuration file.
- `build/`: Contains build-related files. This is where the project is built and compiled.
- `bin/`: Contains the executable files generated after building the project.



## Features
- **Image Display**: Read and display images using OpenCV.
- **Face Detection**: Detect faces in images and videos.
- **Image Filters**: Apply various filters like grayscale, sepia tone, Gaussian blur, Sobel filters, and more.
- **Image Transformations**: Implement transformations like emboss effect and color quantization.

## Getting Started
### Prerequisites
- OpenCV library
- C++ compiler (C++11 standard)

### Installation
1. Clone the repository:
```git clone https://github.com/jeff8971/Project1_YZ.git```
2. Navigate to the project directory: ```cd Project1_YZ```

3. Build the project (example using CMake):
    ```bash
    cd build
    cmake ..
    make
    ```
4. Compiling Different Applications

    The project is set up to allow for the compilation of different applications based on your requirements. This is managed through the `CMakeLists.txt` file. Here's how you can modify it:

    In the `CMakeLists.txt`, you will find lines that specify which source files should be compiled into executables. For example:

    ```
    # Add both vidDisplay.cpp and filters.cpp to the executable
    #add_executable(Project1_YZ ./src/vidDisplay.cpp ./src/filter.cpp)

    # Add timeBlur.cpp and filters.cpp to the executable
    #add_executable(time_YZ ./src/timeBlur.cpp ./src/filter.cpp)

    # Add faceDetect.cpp and showFaces.cpp to the executable
    #add_executable(faceDetect_YZ ./src/faceDetect.cpp ./src/showFaces.cpp)

    # Current configuration: Compiles vidDisplay.cpp, filter.cpp, and faceDetect.cpp into a single executable
    add_executable(Project1_YZ ./src/vidDisplay.cpp ./src/filter.cpp ./src/faceDetect.cpp)
    ```
5. Enable or Disable Executables:

    To compile a specific application, uncomment the corresponding add_executable line by removing the # at the beginning of the line.
    To disable an application, comment out the line by adding a # at the beginning.
6. Linking Libraries:

   Ensure that the necessary libraries (like OpenCV) are linked to your executables:
   ```
    target_link_libraries(Project1_YZ ${OpenCV_LIBS})
    #target_link_libraries(time_YZ ${OpenCV_LIBS})
    #target_link_libraries(faceDetect_YZ ${OpenCV_LIBS})
    ```
### Running the Application

- Run the executable generated after building the project.```./bin/Project1_YZ```
- command ```q``` quit the program
- command ```g``` standard grayscale mode
- command ```h``` alternative grayscale mode
- command ```p``` sepiaTone mode
- command ```b``` alternative blur mode
- command ```x``` Sobel X mode
- command ```y``` Sobel Y mode
- command ```m``` generates a gradient magnitude image from the X and Y Sobel images
- command ```l``` blurs and quantizes a color image
- command ```f``` detect faces in an image
- command ```n``` make the image a negative of itself
- command ```e``` embossing effect
- command ```c``` make the face colorful, while the rest of the image is greyscale
- command ```u``` brightness +10
- command ```d``` brightness -10
- command ```i``` contrast +10
- command ```o``` contrast -10
- command ```u``` brightness +10
- command ```a``` make the video cartoon mode
- command ```w``` horizontal warp mode
- command ```v``` vertical warp mode
- command ```r``` on/off for the recording video (.avi)

### Data and results

- images processed by filters: `data/`
- links of video: [Google Link](https://drive.google.com/file/d/10MeBpye9ZssSkro5LRphwuVtTyzsyjTe/view?usp=drive_link) ,  [Youtube](https://www.youtube.com/watch?v=cKiark0QWcA&ab_channel=JeffZhao)

## License
This project is licensed under the [MIT License](LICENSE).

## Note on Late Submission

Due to an unexpected health condition caused by a virus, my ability to work on the project was deeply affected. This situation unavoidably led to a delay in the project's progress and submission. I appreciate your understanding and consideration of these circumstances.

Thank you for your support.
