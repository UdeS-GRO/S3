#include "plot.h"

// Functions

Plot::Plot(){
}

void Plot::setColor(int r, int g, int b){
    QColor color;
    color.setAlpha(255);
    color.setRed(r);
    color.setGreen(g);
    color.setBlue(b);
    pen.setColor(color);
}

void Plot::setDataLen(int dataLen){
    dataBufferLen = dataLen;
}

void Plot::addData(double newData){

    if (data.length()>dataBufferLen){
        data.pop_front();
    }
    data.append(newData);
}

void Plot::draw(QGraphicsScene* scene){

    QPainterPath curve;
    curve.moveTo(0,-gain*data[0]);
    for (int i = 0; i < data.length(); ++i){
        curve.lineTo(i,-gain*data[i]);
    }
    scene->addPath(curve,pen);
}

void Plot::setGain(double gain_){
    gain = gain_;
}
