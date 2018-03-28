//----Author: Yuxiang LIU
//----Facility: Nanjing University
//----Email: lyx970124@gmail.com
//----Github: https://github.com/lyx0124

#ifndef RECT_H
#define RECT_H

#include "shape.h"

class Rect : public Shape
{
private:
    QPointF p1, p2;
    qreal xc, yc;
public:
    Rect();
    ~Rect();

    //use curve API to set rectangle p1, p2
    void generateCurve() { p1.rx() = start.x(); p2.ry() = start.y(); p1.ry() = end.y(); p2.rx() = end.x(); }

    void paint(QPainter&);
    void fillArea(QPainter&);
    void clipShape() {;}

    void updown(int);
    void leftright(int);
    void rotate(int);
    void zoom(int);
};

#endif // RECT_H
