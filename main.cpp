#include <unistd.h>

#include <iostream>
#include <stdio.h>

#include "ball.h"
#include "tracker.h"


int main(){

    VideoCapture cap;
    cap.open(0);

    Mat frame;

    namedWindow("Simple CV game", CV_WINDOW_AUTOSIZE);

    // Game welcoming screen
    while(true){

        // Image is obtained from the camera
        cap >> frame;

        if (frame.empty())
            break;

        putText(frame, "cvPONG!", Point(50, frame.rows * 0.5 + 30),FONT_HERSHEY_DUPLEX,4,Scalar(255,255,255),10);
        putText(frame, "PRESS ANY KEY TO PLAY", Point(150, frame.rows * 0.5 + 70),FONT_HERSHEY_DUPLEX,0.8,Scalar(255,255,255),1);


        // Image is shown in the window
        imshow("Simple CV game", frame);

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

    Mat leftHalfFrame(frame.rows, frame.cols * 0.5, CV_8UC3);
    Mat rightHalfFrame(frame.rows, frame.cols * 0.5, CV_8UC3);

    while ((score1 != 10) && (score2 != 10)){

        // Elements of the game are created
        Paddle leftPaddle(Point(20, (int)(frame.rows*0.5)), 5, 40, frame.cols, frame.rows);
        Paddle rightPaddle(Point(frame.cols - 20, (int)(frame.rows*0.5)), 5, 40, frame.cols, frame.rows);
        Ball ball(frame.rows, frame.cols, 8, 15, &leftPaddle, &rightPaddle);


        Tracker leftTracker, rightTracker;

        // The image is divided into two halves to track the ball in each
        Mat tmp;

        // Game loop
        while(true){

            // Image is obtained from the camera
            cap >> frame;

            if (frame.empty())
                break;


            // Half frames are set
            tmp = frame(Rect(0,0,leftHalfFrame.cols, leftHalfFrame.rows));
            tmp.copyTo(leftHalfFrame);

            tmp = frame(Rect(leftHalfFrame.cols, 0, rightHalfFrame.cols, rightHalfFrame.rows));
            tmp.copyTo(rightHalfFrame);

            // We draw the score in both sides
            std::stringstream s1, s2;
            s1 << score1;
            s2 << score2;

            putText(frame, s1.str(), Point(frame.cols* 0.25 - 10, 60), 1, 4, Scalar(255,255,255), 5);
            putText(frame, s2.str(), Point(frame.cols* 0.75 - 10, 60), 1, 4, Scalar(255,255,255), 5);

            // We draw the ball in the screen
            circle(frame, ball.getPosition(), ball.getRadious(), Scalar(0,0,255), -1);


            imshow("Simple CV game", frame);

            // Object is tracked in both half frames
            leftTracker.setFrames(leftHalfFrame);
            leftTracker.binFrameProcessing();
            rightTracker.setFrames(rightHalfFrame);
            rightTracker.binFrameProcessing();
            Point posL = leftTracker.trackObject();
            Point posR = rightTracker.trackObject();

            // A small circle is drawn in the center of the balls
            circle(frame, posL, 4, Scalar(0,255,0), -1);
            circle(frame, posR + Point(leftHalfFrame.cols, 0), 4, Scalar(0,255,0), -1);

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

            // Image is shown in the window
            imshow("Simple CV game", frame);

            ball.updatePosition();

            int winner = ball.checkWinner();
            if (winner == 1){
                score1++;
                break;
            } else if (winner == 2){
                score2++;
                break;
            }

            // To interrupt the game manually
            if( waitKey( 10 ) >= 0 ){
                stop = true;
                break;
            }

        }

        sleep(1);

        if (stop)
            break;

    }

    // The winner is displayed on the screen
    while(true){

        // If the player has stopped the game manually, no message is displayed
        if (stop)
            break;

        // Image is obtained from the camera
        cap >> frame;

        if (frame.empty())
            break;


        // Who is the winner?
        int winner = score1 > score2 ? 1 : 2;
        std::stringstream ss;
        ss << winner;
        putText(frame, "PLAYER " + ss.str() + " WINS!", Point(50, frame.rows * 0.5 + 30),FONT_HERSHEY_DUPLEX,2,Scalar(255,255,255),8);

        // Image is shown in the window
        imshow("Simple CV game", frame);

        // To stop the camera and close the window
        if( waitKey( 10 ) >= 0 ){
            break;
        }

    }

    destroyWindow( "Simple CV game" );

    return 0;

}
