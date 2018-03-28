//----Author: Yuxiang LIU
//----Facility: Nanjing University
//----Email: lyx970124@gmail.com
//----Github: https://github.com/lyx0124

#include "circle.h"
#include <iostream>

Circle::Circle() : Shape(CIRCLE) {;}
Circle::~Circle() {;}

void Circle::paint(QPainter & painter) {
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

    xc = (start.x() + end.x()) / 2;
    yc = (start.y() + end.y()) / 2;
    r = sqrt(pow((start.x() - xc), 2) + pow((start.y() - yc), 2));
    float p = 5 / 4 - r;
    int x = 0, y = r;
    while (x <= y) {
        painter.drawPoint(x + xc, y + yc);
        painter.drawPoint(x + xc, -y + yc);
        painter.drawPoint(-x + xc, y + yc);
        painter.drawPoint(-x + xc, -y + yc);
        painter.drawPoint(y + xc, x + yc);
        painter.drawPoint(y + xc, -x + yc);
        painter.drawPoint(-y + xc, x + yc);
        painter.drawPoint(-y + xc, -x + yc);
        if (p > 0 || p == 0) {
            --y;  ++x;
            p = p + 2 * x + 1 - 2 * y;
        }
        else {
            y = y;  ++x;
            p = p + 2 * x + 1;
        }
    }

    QPen penRect(Qt::darkYellow);
    penRect.setWidth(1);
    penRect.setStyle(Qt::DashDotDotLine);
    painter.setPen(penRect);
    painter.drawRect(clipRect);
}

void Circle::fillArea(QPainter & painter) {
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

    float p = 5 / 4 - r;
    int x = 0, y = r;
    while (x <= y) {
        painter.drawLine(QPoint(x + xc, y + yc), QPoint(x + xc, -y + yc));
        painter.drawLine(QPoint(-x + xc, y + yc), QPoint(-x + xc, -y + yc));
        painter.drawLine(QPoint(y + xc, x + yc), QPoint(y + xc, -x + yc));
        painter.drawLine(QPoint(-y + xc, x + yc), QPoint(-y + xc, -x + yc));
        if (p > 0 || p == 0) {
            --y;  ++x;
            p = p + 2 * x + 1 - 2 * y;
        }
        else {
            y = y;  ++x;
            p = p + 2 * x + 1;
        }
    }
}

void Circle::updown(int arg) {
    QMatrix trans1(1, 0, 0, 1, 0, -1), trans2(1, 0, 0, 1, 0, 1);

    if(arg > lastUD) {
        applyMat(start, trans1);
        applyMat(end, trans1);
    }
    else {
        applyMat(start, trans2);
        applyMat(end, trans2);
    }
}

void Circle::leftright(int arg) {
    QMatrix trans1(1, 0, 0, 1, 1, 0), trans2(1, 0, 0, 1, -1, 0);

    if(arg > lastLR) {
        applyMat(start, trans1);
        applyMat(end, trans1);
    }
    else {
        applyMat(start, trans2);
        applyMat(end, trans2);
    }
}

void Circle::zoom(int arg) {
    QMatrix translate1(1, 0, 0, 1, -xc, -yc), translate2(1, 0, 0, 1, xc, yc);
    QMatrix zoom1(1.25, 0, 0, 1.25, 0, 0), zoom2(0.8, 0, 0, 0.8, 0, 0);

    applyMat(start, translate1);
    applyMat(end, translate1);

    if(arg > lastZ) {
        applyMat(start, zoom1);
        applyMat(end, zoom1);
    }
    else {
        applyMat(start, zoom2);
        applyMat(end, zoom2);
    }

    applyMat(start, translate2);
    applyMat(end, translate2);
}
