#include "capture.h"
#include "ball.h"
#include "tracker.h"

int main(int argc, char *argv[]){

    Capture capture = Capture();

    IplImage* image = capture.nextVideoFrame();
    Mat frame = image;

    Ball ball(image->height, image->width, 20, 20);
    Tracker leftTracker, rightTracker;

    cvNamedWindow("MainWindow", CV_WINDOW_AUTOSIZE);
    cvShowImage("MainWindow", image);

    // The image is divided into two halves to track the ball in each
    IplImage* leftHalfImage  = cvCreateImage(cvSize(image->width/2, image->height), image->depth, image->nChannels);
    IplImage* rightHalfImage = cvCreateImage(cvSize(image->width/2, image->height), image->depth, image->nChannels);
    CvMat tmp;
    Mat leftHalfFrame, rightHalfFrame;

    while(true){

        // Image is obtained from the camera
        image = capture.nextVideoFrame();
        frame = image;

        // Half frames are set
        cvGetSubRect(image, &tmp, cvRect(0,0, leftHalfImage->width, leftHalfImage->height));
        cvCopy(&tmp, leftHalfImage);
        leftHalfFrame = leftHalfImage;

        cvGetSubRect(image, &tmp, cvRect(leftHalfImage->width, 0, rightHalfImage->width, rightHalfImage->height));
        cvCopy(&tmp, rightHalfImage);
        rightHalfFrame = rightHalfImage;

        // Object is tracked in both half frames
        leftTracker.setFrames(leftHalfFrame);
        leftTracker.binFrameProcessing();
        rightTracker.setFrames(rightHalfFrame);
        rightTracker.binFrameProcessing();
        Point posL = leftTracker.trackObject();
        Point posR = rightTracker.trackObject();

        if (image == 0)
            break;

        Point pos = ball.getPosition();

        // A small circle is drawn in the center of the balls
        circle(frame, posL, 5, Scalar(0,255,0), -1);
        circle(frame, posR + Point(leftHalfImage->width, 0), 5, Scalar(0,255,0), -1);

        // We draw a ball in the screen
        circle(frame, Point(pos.y, pos.x), ball.getRadious(), Scalar(0,0,255), -1);
        ball.updatePosition();

        // Image is shown in the window
        cvShowImage("MainWindow", image);

        // To stop the camera and close the window
        if( waitKey( 10 ) >= 0 ){
            break;
        }

    }

    cvDestroyWindow( "result" );

    return 0;

}
