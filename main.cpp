#include "capture.h"
#include "ball.h"
#include "tracker.h"

int main(int argc, char *argv[]){

    Capture capture = Capture();

    IplImage* image = capture.nextVideoFrame();
    Mat frame = image;

    Ball ball(image->height, image->width, 20, 20);
    Tracker tracker;

    cvNamedWindow("MainWindow", CV_WINDOW_AUTOSIZE);
    cvShowImage("MainWindow", image);

    cvNamedWindow("BIN", CV_WINDOW_AUTOSIZE);


    while(true){

        // Image is obtained from the camera
        image = capture.nextVideoFrame();
        frame = image;

        //
        tracker.setFrames(frame);
        tracker.binFrameProcessing();
        Mat bin = tracker.getBinFrame();
        Point posT = tracker.trackObject();
        imshow("BIN", bin);
        //

        if (image == 0)
            break;

        Point pos = ball.getPosition();

        // is the tennis ball tracked?
        circle(frame, posT, 5, Scalar(0,255,0), -1);

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
