
Document Scanner APP
-----------------------------------------
This is a C++  a Document Scanner application using two submission files as follow:

Step 1: Submission.exe --> Grabcut for Background Removal code
from week 8 to the src image and the dst image as result.png. 

Step2: Submission2.exe to read the src result.png and apply the following steps:
1. Preprocessing and Contour Detection
2. Contour Approximation
3. Perspective Transformation
The dst image is the output.png.

Overview

This application use GrabCut face to remove the background of a input image document
and produce a tansformed and correctly warped image as the output. 

Requirements
C++ compiler supporting C++11 standard
OpenCV (4.0 or higher) 
CMake (for building)

Build the executable using CMake and insert the input image in the Release folder.
In order to build the executable please follow these steps:
1: Unzip the file
2: Create a build folder inside the unzipped folder
3: In the command line type: cmake -G "Visual Studio 16 2019" ..
You can choose your own VS version in my case it was:  cmake -G "Visual Studio 17 2022" .. '
4: Now, to run the executable: ..\build\Release\submission.exe

Credits
This application was developed by Your Mohammad Ghadban.

Cheers!