#include "capture.h"
#include "ball.h"
#include "tracker.h"
//#include "paddle.h"

int main(int argc, char *argv[]){

    Capture capture = Capture();

    IplImage* image = capture.nextVideoFrame();
    Mat frame = image;

    cvNamedWindow("MainWindow", CV_WINDOW_AUTOSIZE);
    cvShowImage("MainWindow", image);

    // Game welcoming screen
    while(true){

        // Image is obtained from the camera
        image = capture.nextVideoFrame();
        frame = image;

        if (image == 0)
            break;

        putText(frame, "cvPONG!", Point(50, image->height * 0.5 + 30),FONT_HERSHEY_DUPLEX,4,Scalar(255,255,255),10);
        putText(frame, "PRESS ANY KEY TO PLAY", Point(150, image->height * 0.5 + 70),FONT_HERSHEY_DUPLEX,0.8,Scalar(255,255,255),1);


        // Image is shown in the window
        cvShowImage("MainWindow", image);

        // To stop the camera and close the window
        if( waitKey( 10 ) >= 0 ){
            break;
        }

    }

    bool stop = false;

    // The game starts
    int score1, score2;
    score1 = score2 = 0;
    // It will finish when one of the two players wins 10 times
    while ((score1 != 10) && (score2 != 10)){

        Paddle leftPaddle(Point(20, (int)(image->height*0.5)), 10, 40, image->width, image->height);
        Paddle rightPaddle(Point(image->width - 20, (int)(image->height*0.5)), 10, 40, image->width, image->height);
        Ball ball(image->height, image->width, 10, 20, &leftPaddle, &rightPaddle);

        Tracker leftTracker, rightTracker;

        // The image is divided into two halves to track the ball in each
        IplImage* leftHalfImage  = cvCreateImage(cvSize(image->width/2, image->height), image->depth, image->nChannels);
        IplImage* rightHalfImage = cvCreateImage(cvSize(image->width/2, image->height), image->depth, image->nChannels);
        CvMat tmp;
        Mat leftHalfFrame, rightHalfFrame;

        // Game loop
        while(true){

            // Image is obtained from the camera
            image = capture.nextVideoFrame();
            frame = image;

            if (image == 0)
                break;

            // We draw the score in both sides
            stringstream s1, s2;
            s1 << score1;
            s2 << score2;

            putText(frame, s1.str(), Point(image->width* 0.25 - 10, 60), 1, 4, Scalar(255,255,0), 5);
            putText(frame, s2.str(), Point(image->width* 0.75 - 10, 60), 1, 4, Scalar(255,255,0), 5);

            // We draw the ball in the screen
            circle(frame, ball.getPosition(), ball.getRadious(), Scalar(0,0,255), -1);

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

            // A small circle is drawn in the center of the balls
            circle(frame, posL, 5, Scalar(0,255,0), -1);
            circle(frame, posR + Point(leftHalfImage->width, 0), 5, Scalar(0,255,0), -1);

            // Left paddle is drawn in the screen
            leftPaddle.setPosition(posL.y);
            const Point c1 = leftPaddle.getPosition() - Point(leftPaddle.getWidth()*0.5, leftPaddle.getHeight());
            const Point c2 = leftPaddle.getPosition() + Point(leftPaddle.getWidth()*0.5, leftPaddle.getHeight());
            rectangle(frame, c1, c2, Scalar(255,0,0), -1);

            // Right paddle is drawn in the screen
            rightPaddle.setPosition(posR.y);
            const Point c3 = rightPaddle.getPosition() - Point(rightPaddle.getWidth()*0.5, rightPaddle.getHeight());
            const Point c4 = rightPaddle.getPosition() + Point(rightPaddle.getWidth()*0.5, rightPaddle.getHeight());
            rectangle(frame, c3, c4, Scalar(255,0,0), -1);


            ball.updatePosition();
            int winner = ball.checkWinner();
            if (winner == 1){
                score1++;
                break;
            } else if (winner == 2){
                score2++;
                break;
            }

            // Image is shown in the window
            cvShowImage("MainWindow", image);

            // To interrupt the game manually
            if( waitKey( 10 ) >= 0 ){
                stop = true;
                break;
            }

        }

        if (stop)
            break;

    }

    // The winner is displayed on the screen
    while(true){

        // If the player has stopped the game manually, no message is displayed
        if (stop)
            break;

        // Image is obtained from the camera
        image = capture.nextVideoFrame();
        frame = image;

        if (image == 0)
            break;

        // Who is the winner?
        int winner = score1 > score2 ? 1 : 2;
        stringstream ss;
        ss << winner;
        putText(frame, "PLAYER " + ss.str() + " WINS!", Point(50, image->height * 0.5 + 30),FONT_HERSHEY_DUPLEX,2,Scalar(255,255,255),8);

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
