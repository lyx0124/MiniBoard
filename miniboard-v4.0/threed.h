//----Author: Yuxiang LIU
//----Facility: Nanjing University
//----Email: lyx970124@gmail.com
//----Github: https://github.com/lyx0124

#ifndef CUBE_H
#define CUBE_H

#include "shape.h"

class ThreeD : public Shape {
public:
    ThreeD();
    ~ThreeD();

    void paint(QPainter&);
    void fillArea(QPainter&) {;}
    void clipShape() {;}

    void updown(int) {;}
    void leftright(int) {;}
    void rotate(int) {;}
    void zoom(int) {;}
};

#endif // CUBE_H
