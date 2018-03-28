//----Author: Yuxiang LIU
//----Facility: Nanjing University
//----Email: lyx970124@gmail.com
//----Github: https://github.com/lyx0124

#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"

class Circle : public Shape {
private:
    float xc, yc;
    float r;
public:
    Circle();
    ~Circle();

    void paint(QPainter&);
    void fillArea(QPainter&);
    void clipShape() {;}

    void updown(int);
    void leftright(int);
    void rotate(int) {;}
    void zoom(int);
};

#endif // CIRCLE_H
