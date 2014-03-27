#include "capture.h"

int main(int argc, char *argv[]){

    Capture capture = Capture();

    cvNamedWindow("MainWindow", CV_WINDOW_AUTOSIZE);

    while(true){

        // Image is obtained from the camera
        IplImage* image = capture.nextVideoFrame();
        Mat frame = image;

        if (image == 0)
            break;

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
