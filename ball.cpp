#include "ball.h"


Ball::Ball(unsigned int _h, unsigned int _w, unsigned int _r, unsigned int _s){

    height_ = _h;
    width_  = _w;
    radius_ = _r;
    speed_  = _s;

    position_ = Point((int)(height_*0.5), (int)(width_*0.5));
    prevPosition_ = Point (-1, -1); // this one could be just anything...

    const float xdir = (float) (rand()) / ((float)(RAND_MAX/2));
    const float ydir = (float) (rand()) / ((float)(RAND_MAX/2));
    const float norm = sqrt(xdir*xdir + ydir*ydir);

    direction_ = Point2f(xdir/norm, ydir/norm);
}

Point Ball::getPosition(){
    return position_;
}


void Ball::updatePosition(){

    Point disp((int)(direction_.x * speed_), (int)(direction_.y * speed_));
    Point newPos = position_ + disp;


    // In case it reaches one of the borders
    if ( ((newPos.x + radius_) >= height_) || ((newPos.x -  (int) radius_) <= 0) ){

        direction_.x = -direction_.x;
        disp.x = (int)(direction_.x * speed_);
        disp.y = (int)(direction_.y * speed_);
        newPos = position_ + disp;

    } else if (((newPos.y + radius_) >= width_) || ((newPos.y - (int) radius_) <= 0)){

        direction_.y = -direction_.y;
        disp.x = (int)(direction_.x * speed_);
        disp.y = (int)(direction_.y * speed_);
        newPos = position_ + disp;

    }


    prevPosition_ = position_;
    position_ = newPos;

}

unsigned int Ball::getRadious(){
    return radius_;
}
