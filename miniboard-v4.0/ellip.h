//----Author: Yuxiang LIU
//----Facility: Nanjing University
//----Email: lyx970124@gmail.com
//----Github: https://github.com/lyx0124

#ifndef ELLIP_H
#define ELLIP_H

#include "shape.h"

class Ellip : public Shape {
private:
    qreal xc, yc;
    qreal rx, ry;
    QVector<QPointF> border;
    bool rotateFlag;
public:
    Ellip();
    ~Ellip();

    void paint(QPainter&);
    void fillArea(QPainter&);
    void clipShape() {;}

    void updown(int);
    void leftright(int);
    void rotate(int);
    void zoom(int);
};

#endif // ELLIP_H
