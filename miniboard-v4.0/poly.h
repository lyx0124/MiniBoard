//----Author: Yuxiang LIU
//----Facility: Nanjing University
//----Email: lyx970124@gmail.com
//----Github: https://github.com/lyx0124

#ifndef POLYGON_H
#define POLYGON_H

#include "shape.h"

typedef struct XET
{
    float x;
    float dx, MaxY;
    XET* next;
}AET, NET;

class Poly : public Shape {
private:
    qreal xc, yc;
    qreal xmin, ymin, xmax, ymax;
public:
    Poly();
    ~Poly();

    void paint(QPainter&);
    void fillArea(QPainter&);
    void clipShape() {;}

    void updown(int);
    void leftright(int);
    void rotate(int);
    void zoom(int);
};

#endif // POLYGON_H
