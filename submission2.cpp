#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // reading the image
    Mat image = imread("result.png");

    // converting the image to grayscale
    Mat gray;
    cvtColor(image, gray, COLOR_BGR2GRAY);

    Mat gaussianImage;
    GaussianBlur(gray, gaussianImage, Size(15, 15),0);

    // applying canny edges:
    Mat edges;
    Canny(gray, edges, 100, 200); // Applying Canny edge detection

    // finding the contours;
    vector<vector<Point>> contours;
    findContours(edges, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // approximate contours
    vector<vector<Point>> approxContours(contours.size());
    for (size_t i = 0; i < contours.size(); ++i) {
        approxPolyDP(contours[i], approxContours[i], 10, true);
        // Calculate the area of each contour
        double area = contourArea(contours[i]);
        cout << "area: " << area << endl;

        // getting the size of the original image 
        int originalWidth = image.cols;
        int originalHeight = image.rows;

        // new width for transformed image 
        int customWidth = 500;

        // calculating the new height based on the original image aspect ratio
        int newHeight = (originalHeight * customWidth) / originalWidth;

        // define source and destination points
        vector<Point2f> srcPoints, dstPoints;

        // define the destination points with swapped order
        dstPoints.push_back(Point2f(customWidth - 1, 0));        // Top-right point
        dstPoints.push_back(Point2f(0, 0));                     // Top-left point
        dstPoints.push_back(Point2f(0, newHeight - 1));         // Bottom-left point
        dstPoints.push_back(Point2f(customWidth - 1, newHeight - 1)); // Bottom-right point



        // get the perspective transform of the approximate contour
        if (approxContours[i].size() == 4) {
            // convert contour points to float
            for (int j = 0; j < 4; j++) {
                srcPoints.push_back(Point2f(approxContours[i][j].x, approxContours[i][j].y));
            }

            // get perspective transform matrix
            Mat perspectiveMatrix = getPerspectiveTransform(srcPoints, dstPoints);

            // apply perspective transformation to the image
            Mat warpedImage;
            warpPerspective(image, warpedImage, perspectiveMatrix, Size(customWidth, newHeight));

            // display the warped image
            imshow("Image", image);
            imshow("Gaussian", gaussianImage);
            imshow("Canny", edges);
            imshow("Warped Image", warpedImage);

            // save wrapped image as output image
            imwrite("output.png", warpedImage);
        }
    }

    waitKey(0);
    destroyAllWindows();

    return 0;
}
