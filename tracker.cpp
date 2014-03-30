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
    // H: 16 49 S: 38 196 V: 48 256
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

Point Tracker::trackObject(){

    int x, y;

    // Restrictions to avoid false objects
    const int minTrackingArea = 40; // The objects must be bigger than a 20x20 pixel block
    const int maxTrackingArea = binFrame_.cols * binFrame_.rows * 0.5; // and smaller than a half of the image
    const int maxTrackedObjects = 20; // A bigger number of objects means we have too much noise

    Mat temp;
    binFrame_.copyTo(temp);

    // Contours and their hierarchy are located and stored
    vector< vector<Point> > contours;
    vector<Vec4i> hierarchy;

    findContours(temp, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );

    // We use moments method to find our filtered object
    double prevArea = 0;
    bool objectFound = false;

    if (hierarchy.size() > 0) {

        int numObjects = hierarchy.size();

        if(numObjects < maxTrackedObjects){

            for (int i = 0; i >= 0; i = hierarchy[i][0]) {

                Moments moment = moments( (cv::Mat)contours[i] );
                double area = moment.m00;

                if( (area > minTrackingArea)  && (area < maxTrackingArea) && (area > prevArea)){

                    x = moment.m10 / area;
                    y = moment.m01 / area;

                    objectFound = true;
                    prevArea = area;

                } else {
                    objectFound = false;
                }

            }

            // If the object is found, return its position, if not, (-1,-1)
            if (objectFound ==true){
                return Point(x,y);
            } else {
                return Point (-1,-1);
            }

        } else {
            return Point(-1,-1);
        }
    }

    return Point(-1,-1);

}
