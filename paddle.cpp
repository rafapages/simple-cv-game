#include "paddle.h"

Paddle::Paddle(Point _initPosition, unsigned int _w, unsigned int _h, unsigned int _fw, unsigned int _fh){

    position_ = _initPosition;
    width_ = _w;
    height_ = _h;
    frameWidth_ = _fw;
    frameHeight_ = _fh;

}

Paddle::~Paddle(){

}

unsigned int Paddle::getWidth(){
    return width_;
}

unsigned int Paddle::getHeight(){
    return height_;
}

Point Paddle::getPosition(){
    return position_;
}

void Paddle::setPosition(int _ypos){

    // The paddle shouldn't go above or below de screen
    if ( ((_ypos + (int)(height_*0.5)) >= frameHeight_) || ((_ypos - (int)(height_*0.5) <= 0)) ){
        return;
    }
    position_.y = _ypos;
}
