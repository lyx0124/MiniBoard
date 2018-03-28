//----Author: Yuxiang LIU
//----Facility: Nanjing University
//----Email: lyx970124@gmail.com
//----Github: https://github.com/lyx0124

#ifndef CURVE_H
#define CURVE_H

#include "shape.h"

class Curve : public Shape {
private:
    qreal xc, yc;
    qreal xmin, ymin, xmax, ymax;
public:
    Curve();
    ~Curve();

    qreal splineN(int, int, qreal);
    qreal splineN1(int, qreal);
    qreal splineN2(int, qreal);
    qreal splineN3(int, qreal);

    void generateCurve();
    int getCurrentNode(QPointF);

    void paint(QPainter&);
    void fillArea(QPainter&) {;}
    void clipShape() {;}

    void updown(int);
    void leftright(int);
    void rotate(int);
    void zoom(int);
};

#endif // CURVE_H
