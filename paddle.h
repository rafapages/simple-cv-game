#ifndef PADDLE_H
#define PADDLE_H

#include "capture.h"

class Paddle {

public:

    Paddle(Point _initPosition, unsigned int _w, unsigned int _h, unsigned int _fw, unsigned int _fh);
    ~Paddle();
    Point getPosition();
    void setPosition(int _ypos);
    unsigned int getWidth();
    unsigned int getHeight();


private:

    Point position_;
    Point prevPosition_;
    unsigned int width_;
    unsigned int height_;
    unsigned int frameWidth_;
    unsigned int frameHeight_;

};

#endif // PADDLE_H
