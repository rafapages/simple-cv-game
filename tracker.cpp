#include "tracker.h"

Tracker::Tracker(){

}

Tracker::~Tracker(){

}


Mat Tracker::getBinFrame(){
    return binFrame_;
}

Mat Tracker::getHsvFrame(){
    return hsvFrame_;
}

void Tracker::setFrames(Mat _cameraFrame){

    bgrFrame_ = _cameraFrame;

    // Turning the camera BGR frame into a HSV image
    cvtColor(bgrFrame_,hsvFrame_,COLOR_BGR2HSV);

    // HSV values to filter yellow (for a tennis ball) are determined
    int hmin, hmax, smin, smax, vmin, vmax;
    hmin = 15;
    hmax = 50;
    smin = 35;
    smax = 200;
    vmin = 50;
    vmax = 256;

    // Binary image with the thresholded values is defined
    inRange(hsvFrame_,Scalar(hmin,smin,vmin),Scalar(hmax,smax,vmax),binFrame_);

}

void Tracker::binFrameProcessing(){

    Mat eroder  = getStructuringElement(MORPH_RECT, Size(5,5));
    Mat dilater = getStructuringElement(MORPH_RECT, Size(7,7));

    erode(binFrame_, binFrame_, eroder);
    erode(binFrame_, binFrame_, eroder);

    dilate(binFrame_,binFrame_,dilater);
    dilate(binFrame_,binFrame_,dilater);


}
