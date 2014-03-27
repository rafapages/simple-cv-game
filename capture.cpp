#include "capture.h"


Capture::Capture(){

    capt = cvCaptureFromCAM( CV_CAP_ANY );
    if (!capt){
        cout << "No camera detected" << endl;
    }
}

Capture::~Capture(){
    // Terminate video capture and free capture resources
    cvReleaseCapture( &capt );
}

IplImage* Capture::nextVideoFrame(){

    Mat frame, frameCopy;

    IplImage* image = cvQueryFrame( capt );
    frame = image;

    if( frame.empty() )
        image = 0;

    if( image->origin == IPL_ORIGIN_TL )
        frame.copyTo( frameCopy );

    else
        flip( frame, frameCopy, 0 );

    return image;

}
