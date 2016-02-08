#ifndef CAPTURE_H
#define CAPTURE_H

#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;


class Capture {


public:
    Capture();
    ~Capture();
    IplImage* nextVideoFrame();

private:
    CvCapture* capt_;

};

#endif // CAPTURE_H
