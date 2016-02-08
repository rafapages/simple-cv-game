#ifndef TRACKER_H
#define TRACKER_H

#include "capture.h"

class Tracker{

public:

    Tracker();
    ~Tracker();
    Mat getHsvFrame();
    Mat getBinFrame();
    void setFrames(Mat _cameraFrame);
    void binFrameProcessing();
    Point trackObject();


private:

    Mat bgrFrame_;
    Mat hsvFrame_;
    Mat binFrame_;

};


#endif // TRACKER_H
