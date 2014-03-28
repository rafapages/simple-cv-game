#ifndef BALL_H
#define BALL_H

#include "capture.h"

class Ball{

public:

    Ball(unsigned int _h, unsigned int _w, unsigned int _r, unsigned int _s);

    Point getPosition();
    void updatePosition();
    unsigned int getRadious();

private:

    Point position_;
    Point prevPosition_;
    unsigned int radius_;
    unsigned int height_;
    unsigned int width_;
    unsigned int speed_;
    Point2f direction_;


};

#endif // BALL_H
