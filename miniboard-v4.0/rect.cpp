//----Author: Yuxiang LIU
//----Facility: Nanjing University
//----Email: lyx970124@gmail.com
//----Github: https://github.com/lyx0124

#include "rect.h"

Rect::Rect() : Shape(RECT) {;}
Rect::~Rect() {;}

void Rect::paint(QPainter & painter) {
    QPen pen;
    switch(_color) {
    case BLACK:
        pen.setColor(Qt::black);
        break;
    case RED:
        pen.setColor(Qt::red);
        break;
    case GREEN:
        pen.setColor(Qt::green);
        break;
    case BLUE:
        pen.setColor(Qt::blue);
        break;
    }
    pen.setWidth(_thick);
    painter.setPen(pen);

    painter.drawLine(start, p1);
    painter.drawLine(start, p2);
    painter.drawLine(end, p1);
    painter.drawLine(end, p2);

    QPen penRect(Qt::darkYellow);
    penRect.setWidth(1);
    penRect.setStyle(Qt::DashDotDotLine);
    painter.setPen(penRect);
    painter.drawRect(clipRect);
}

void Rect::fillArea(QPainter &painter) {
    QPen pen;
    switch(_color) {
    case BLACK:
        pen.setColor(Qt::black);
        break;
    case RED:
        pen.setColor(Qt::red);
        break;
    case GREEN:
        pen.setColor(Qt::green);
        break;
    case BLUE:
        pen.setColor(Qt::blue);
        break;
    }
    painter.setPen(pen);


    if(start.x() < end.x() && start.y() < end.y())
        for(int i = start.x(); i < end.x(); ++i)
            for(int j = start.y(); j < end.y(); ++j)
                painter.drawPoint(i, j);
    if(start.x() > end.x() && start.y() < end.y())
        for(int i = end.x(); i < start.x(); ++i)
            for(int j = start.y(); j < end.y(); ++j)
                painter.drawPoint(i, j);
    if(start.x() < end.x() && start.y() > end.y())
        for(int i = start.x(); i < end.x(); ++i)
            for(int j = end.y(); j < start.y(); ++j)
                painter.drawPoint(i, j);
    if(start.x() > end.x() && start.y() > end.y())
        for(int i = end.x(); i < start.x(); ++i)
            for(int j = end.y(); j < start.y(); ++j)
                painter.drawPoint(i, j);
}

void Rect::updown(int arg) {
    QMatrix trans1(1, 0, 0, 1, 0, -1), trans2(1, 0, 0, 1, 0, 1);

    if(arg > lastUD) {
        applyMat(start, trans1);
        applyMat(end, trans1);
        applyMat(p1, trans1);
        applyMat(p2, trans1);
    }
    else {
        applyMat(start, trans2);
        applyMat(end, trans2);
        applyMat(p1, trans2);
        applyMat(p2, trans2);
    }
}

void Rect::leftright(int arg) {
    QMatrix trans1(1, 0, 0, 1, 1, 0), trans2(1, 0, 0, 1, -1, 0);

    if(arg > lastLR) {
        applyMat(start, trans1);
        applyMat(end, trans1);
        applyMat(p1, trans1);
        applyMat(p2, trans1);
    }
    else {
        applyMat(start, trans2);
        applyMat(end, trans2);
        applyMat(p1, trans2);
        applyMat(p2, trans2);
    }
}

void Rect::rotate(int arg) {
    QMatrix rotate1(cos(DEGREE), -sin(DEGREE), sin(DEGREE), cos(DEGREE), 0, 0);
    QMatrix rotate2(cos(-DEGREE), -sin(-DEGREE), sin(-DEGREE), cos(-DEGREE), 0, 0);

    if(arg > lastR) {
        applyMat(start, rotate1);
        applyMat(end, rotate1);
        applyMat(p1, rotate1);
        applyMat(p2, rotate1);
    }
    else {
        applyMat(start, rotate2);
        applyMat(end, rotate2);
        applyMat(p1, rotate2);
        applyMat(p2, rotate2);
    }
}

void Rect::zoom(int arg) {
    xc = (start.x() + end.x()) / 2;
    yc = (start.y() + end.y()) / 2;
    QMatrix translate1(1, 0, 0, 1, -xc, -yc), translate2(1, 0, 0, 1, xc, yc);
    QMatrix zoom1(1.25, 0, 0, 1.25, 0, 0), zoom2(0.8, 0, 0, 0.8, 0, 0);

    applyMat(start, translate1);
    applyMat(end, translate1);
    applyMat(p1, translate1);
    applyMat(p2, translate1);

    if(arg > lastZ) {
        applyMat(start, zoom1);
        applyMat(end, zoom1);
        applyMat(p1, zoom1);
        applyMat(p2, zoom1);
    }
    else {
        applyMat(start, zoom2);
        applyMat(end, zoom2);
        applyMat(p1, zoom2);
        applyMat(p2, zoom2);
    }

    applyMat(start, translate2);
    applyMat(end, translate2);
    applyMat(p1, translate2);
    applyMat(p2, translate2);
}
