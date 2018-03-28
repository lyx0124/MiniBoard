//----Author: Yuxiang LIU
//----Facility: Nanjing University
//----Email: lyx970124@gmail.com
//----Github: https://github.com/lyx0124

#include "ellip.h"

Ellip::Ellip() : Shape(ELLIP), rotateFlag(false) {;}
Ellip::~Ellip() {;}

void Ellip::paint(QPainter & painter) {
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

    if(rotateFlag == false) {
        border.clear();
        xc = (start.x() + end.x()) / 2;
        yc = (start.y() + end.y()) / 2;
        rx = abs(start.x() - end.x()) / 2;
        ry = abs(start.y() - end.y()) / 2;
        qreal x = 0, y = ry;
        qreal dx = 2 * rx*rx*y, dy = 2 * ry*ry*x;
        qreal p1 = ry*ry - rx*rx*ry + rx*rx / 4;    //region 1
        while ((dy / dx) < 1 || (dy / dx) == 1) {
            border.push_back(QPointF(x + xc, y + yc));
            border.push_back(QPointF(x + xc, -y + yc));
            border.push_back(QPointF(-x + xc, y + yc));
            border.push_back(QPointF(-x + xc, -y + yc));
            if (p1 > 0) {
                --y;  ++x;
                p1 = p1 + 2 * ry*ry*x - 2 * rx*rx*y + ry*ry;
                dx = 2 * rx*rx*y;  dy = 2 * ry*ry*x;
            }
            else {
                y = y;  ++x;
                p1 = p1 + 2 * ry*ry*x + ry*ry;
                dx = 2 * rx*rx*y;  dy = 2 * ry*ry*x;
            }
        }
        qreal p2 = ry*ry*(x + 0.5)*(x + 0.5) + rx*rx*(y - 1)*(y - 1) - rx*rx*ry*ry;    //region2
        while (y > 0) {
            border.push_back(QPointF(x + xc, y + yc));
            border.push_back(QPointF(x + xc, -y + yc));
            border.push_back(QPointF(-x + xc, y + yc));
            border.push_back(QPointF(-x + xc, -y + yc));
            if (p2 < 0) {
                ++x;  --y;
                p2 = p2 + 2 * ry*ry*x - 2 * rx*rx*y + rx*rx;
            }
            else {
                x = x;  --y;
                p2 = p2 - 2 * rx*rx*y + rx*rx;
            }
        }
        for(QVector<QPointF>::Iterator it = border.begin(); it != border.end(); ++it)
            painter.drawPoint(*it);
    }
    else
        for(QVector<QPointF>::Iterator it = border.begin(); it != border.end(); ++it)
            painter.drawPoint(*it);

    QPen penRect(Qt::darkYellow);
    penRect.setWidth(1);
    penRect.setStyle(Qt::DashDotDotLine);
    painter.setPen(penRect);
    painter.drawRect(clipRect);
}

void Ellip::fillArea(QPainter & painter) {
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

    qreal x = 0, y = ry;
    qreal dx = 2 * rx*rx*y, dy = 2 * ry*ry*x;
    qreal p1 = ry*ry - rx*rx*ry + rx*rx / 4;
    while ((dy / dx) < 1 || (dy / dx) == 1) {
        painter.drawLine(QPointF(x + xc, y + yc), QPointF(x + xc, -y + yc));
        painter.drawLine(QPointF(-x + xc, y + yc), QPointF(-x + xc, -y + yc));
        if (p1 > 0) {
            --y;  ++x;
            p1 = p1 + 2 * ry*ry*x - 2 * rx*rx*y + ry*ry;
            dx = 2 * rx*rx*y;  dy = 2 * ry*ry*x;
        }
        else {
            y = y;  ++x;
            p1 = p1 + 2 * ry*ry*x + ry*ry;
            dx = 2 * rx*rx*y;  dy = 2 * ry*ry*x;
        }
    }
    qreal p2 = ry*ry*(x + 0.5)*(x + 0.5) + rx*rx*(y - 1)*(y - 1) - rx*rx*ry*ry;
    while (y > 0) {
        painter.drawLine(QPointF(x + xc, y + yc), QPointF(x + xc, -y + yc));
        painter.drawLine(QPointF(-x + xc, y + yc), QPointF(-x + xc, -y + yc));
        if (p2 < 0) {
            ++x;  --y;
            p2 = p2 + 2 * ry*ry*x - 2 * rx*rx*y + rx*rx;
        }
        else {
            x = x;  --y;
            p2 = p2 - 2 * rx*rx*y + rx*rx;
        }
    }
}

void Ellip::updown(int arg) {
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

void Ellip::leftright(int arg) {
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

void Ellip::rotate(int arg) {
    rotateFlag = true;

    QMatrix rotate1(cos(DEGREE), -sin(DEGREE), sin(DEGREE), cos(DEGREE), 0, 0);
    QMatrix rotate2(cos(-DEGREE), -sin(-DEGREE), sin(-DEGREE), cos(-DEGREE), 0, 0);

    for(QVector<QPointF>::Iterator it = border.begin(); it != border.end(); ++it) {
        if(arg > lastR)
            applyMat(*it, rotate1);
        else
            applyMat(*it, rotate2);
    }
}

void Ellip::zoom(int arg) {
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
