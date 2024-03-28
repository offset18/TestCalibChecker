// TestCalibChecker.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int main()
{
    std::cout << "Hello World!\n";
}
bool FlowPut::calibrateProjector()
{
    // create fullscreen window on second screen
    namedWindow("projector", CV_WINDOW_NORMAL);
    moveWindow("projector", -1920, 0);
    setWindowProperty("projector", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);

    // construct chessboard pattern image & store inner corner positions
    Size patternSize(6, 5);
    int width = 1920;
    int height = 1080;
    int marginX = 0.1f * width;
    int marginY = 0.1f * height;
    int widthPerCell = (width - 2 * marginX) / (patternSize.width + 1);
    int heightPerCell = (height - 2 * marginY) / (patternSize.height + 1);
    Mat chessBoardPattern(height, width, CV_8UC1, Scalar(255));

    vector<Point2f> cornersInProjector2D;
    for (int r = 0; r < patternSize.height + 1; ++r) {
        for (int c = 0; c < patternSize.width + 1; ++c) {
            int x = marginX + c * widthPerCell;
            int y = marginY + r * heightPerCell;
            unsigned char color = 255 * ((c + r * (patternSize.width + 1)) % 2);

            Rect roi(x, y, widthPerCell, heightPerCell);
            chessBoardPattern(roi).setTo(Scalar::all(color));

            if (r > 0 && c > 0)
                cornersInProjector2D.push_back(Point2f(x, y));
        }
    }

    imshow("projector", chessBoardPattern);
    waitKey(1);