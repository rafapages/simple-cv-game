#include "ball.h"


Ball::Ball(unsigned int _h, unsigned int _w, unsigned int _r, unsigned int _s, Paddle* _lp, Paddle* _rp){

    height_ = _h;
    width_  = _w;
    radius_ = _r;
    speed_  = _s;
    lPaddle_ = _lp;
    rPaddle_ = _rp;
    winner_ = 0; // no winner yet

    position_ = Point((int)(width_*0.5), (int)(height_*0.5));
    prevPosition_ = Point (0, 0); // this one could be just anything...

    const float xdir = (float) (rand()) / ((float)(RAND_MAX/2)) - 1;
    const float ydir = (float) (rand()) / ((float)(RAND_MAX/2)) - 1;
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
    // If the ball hits either top or bottom borders, it bounces off.

    if ( ((newPos.y + radius_) >= height_) || ((newPos.y -  (int) radius_) <= 0) ){

        direction_.y = -direction_.y;
        disp.x = (int)(direction_.x * speed_);
        disp.y = (int)(direction_.y * speed_);
        newPos = position_ + disp;

    }

    // If the ball hits the paddle
    const int yLmax = lPaddle_->getPosition().y + lPaddle_->getHeight() * 0.5;
    const int yLmin = lPaddle_->getPosition().y - lPaddle_->getHeight() * 0.5;
    const int xLpos = lPaddle_->getPosition().x - lPaddle_->getWidth() * 0.5;
    const int yRmax = rPaddle_->getPosition().y + rPaddle_->getHeight() * 0.5;
    const int yRmin = rPaddle_->getPosition().y - rPaddle_->getHeight() * 0.5;
    const int xRpos = rPaddle_->getPosition().x + rPaddle_->getWidth() * 0.5;

    if ( ((newPos.y - radius_ < yLmax) && ( newPos.y + radius_ > yLmin) && ( (newPos.x - radius_) <= xLpos)) ||
         ((newPos.y - radius_ < yRmax) && ( newPos.y + radius_ > yRmin) && ( (newPos.x + radius_) >= xRpos)) ){

        direction_.x = -direction_.x;
        disp.x = (int)(direction_.x * speed_);
        disp.y = (int)(direction_.y * speed_);
        newPos = position_ + disp;

    }
    // If the ball this one of the lateral walls, the we have a winner
    else if ((newPos.x + radius_) >= width_){
        winner_ = 1;
        return;

    } else if ((newPos.x - (int) radius_) <= 0){
        winner_ = 2;
        return;

    }

    prevPosition_ = position_;
    position_ = newPos;

}

unsigned int Ball::getRadious(){
    return radius_;
}

int Ball::checkWinner(){
    return winner_;
}
