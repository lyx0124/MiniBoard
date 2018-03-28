//----Author: Yuxiang LIU
//----Facility: Nanjing University
//----Email: lyx970124@gmail.com
//----Github: https://github.com/lyx0124

#ifndef LINE_H
#define LINE_H

#define LEFT 1
#define RIGHT 2
#define TOP 4
#define BOTTOM 8

#include "shape.h"

class Line : public Shape {
public:
    Line();
    ~Line();

    void paint(QPainter&);
    void fillArea(QPainter&) {;}
    void clipShape();
    void clip(int, int, int, int);
    int encode(int x, int y);

    void updown(int);
    void leftright(int);
    void rotate(int) {;}
    void zoom(int) {;}
};

#endif // LINE_H
