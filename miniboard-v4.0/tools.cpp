//----Author: Yuxiang LIU
//----Facility: Nanjing University
//----Email: lyx970124@gmail.com
//----Github: https://github.com/lyx0124

#include "tools.h"
#include <iostream>

void applyMat(QPoint & p, QMatrix & m) {
    int x, y;
    x = p.x()*m.m11() + p.y()*m.m21() + m.dx();
    y = p.y()*m.m22() + p.x()*m.m12() + m.dy();
    p.setX(x);
    p.setY(y);
}

void applyMat(QPointF & p, QMatrix & m) {
    int x, y;
    x = (int)(p.x()*m.m11() + p.y()*m.m21() + m.dx() + 0.5);
    y = (int)(p.y()*m.m22() + p.x()*m.m12() + m.dy() + 0.5);
    p.setX(x);
    p.setY(y);
}
