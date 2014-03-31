#include "capture.h"


Capture::Capture(){

    capt_ = cvCaptureFromCAM( CV_CAP_ANY );
    if (!capt_){
        cout << "No camera detected" << endl;
    }
}

Capture::~Capture(){
    // Terminate video capture and free capture resources
    cvReleaseCapture( &capt_ );
}

IplImage* Capture::nextVideoFrame(){

    Mat frame;

    IplImage* image = cvQueryFrame( capt_ );
    frame = image;

    if( frame.empty() )
        image = 0;

    // Image is flipped horizontally so it works as a mirror
    cvFlip(image, image,1);

    return image;

}
