//----Author: Yuxiang LIU
//----Facility: Nanjing University
//----Email: lyx970124@gmail.com
//----Github: https://github.com/lyx0124

#include "curve.h"

Curve::Curve() : Shape(CURVE, 0, false, false, 1), xmin(0), xmax(0), ymin(0), ymax(0) {;}
Curve::~Curve() {;}

qreal Curve::splineN(int k, int i, qreal u) {
    switch(k) {
    case 1:
        return splineN1(i, u);
    case 2:
        return splineN2(i, u);
    case 3:
        return splineN3(i, u);
    }
}

qreal Curve::splineN1(int i, qreal u) {
    qreal t = u - i;

    if(0 <= t && t < 1)
        return t;
    if(1 <= t && t < 2)
        return 2 - t;
    return 0;
}

qreal Curve::splineN2(int i, qreal u) {
    qreal t = u-i;

    if(0 <= t && t < 1)
        return 0.5*t*t;
    if(1 <= t && t < 2)
        return 3*t - t*t - 1.5;
    if(2 <= t && t < 3)
        return 0.5*pow(3 - t, 2);
    return 0;
}

qreal Curve::splineN3(int i, qreal u) {
    qreal t = u-i;
    qreal a = 1.0/6.0;

    if(0 <= t && t < 1)
        return a*t*t*t;
    if(1 <= t && t < 2)
        return a*(-3*pow(t - 1, 3) + 3*pow(t - 1, 2) + 3*(t - 1) + 1);
    if(2 <= t && t < 3)
        return a*(3*pow(t - 2, 3) - 6*pow(t - 2, 2) + 4);
    if(3 <= t && t < 4)
        return a*pow(4 - t, 3);
    return 0;
}

int Curve::getCurrentNode(QPointF t) {
    for(int i = 0; i < ctrlPoints.size(); ++i) {
        double dx = ctrlPoints[i].x() - t.x();
        double dy = ctrlPoints[i].y() - t.y();
        double length = sqrt(dx*dx + dy*dy);
        if(length < 10)
            return i;
    }
    return -1;
}

void Curve::generateCurve() {
    curvePoints.clear();
    for(double u = orderK; u < ctrlPoints.size(); u += 0.01) {
        QPointF tmp(0,0);
        for(int i = 0; i < ctrlPoints.size(); ++i) {
            QPointF t = ctrlPoints[i];
            t *= splineN(orderK, i, u);
            tmp += t;
        }
        curvePoints.push_back(tmp);
    }
    for(QVector<QPointF>::Iterator it = ctrlPoints.begin(); it != ctrlPoints.end(); ++it) {
        if(it->x() < xmin) xmin = it->x();
        if(it->x() > xmax) xmax = it->x();
        if(it->y() < ymin) ymin = it->y();
        if(it->y() > ymax) ymax = it->y();
    }
    xc = (xmin + xmax) / 2;
    yc = (ymin + ymax) / 2;
}
void Curve::paint(QPainter & painter) {
    // draw Contorl Points
    QPen ctrlPen1(Qt::darkMagenta);
    ctrlPen1.setWidth(7);
    painter.setPen(ctrlPen1);
    for(int i = 0; i < ctrlPoints.size(); ++i)
        painter.drawPoint(ctrlPoints[i]);
    // draw Control Lines;
    QPen ctrlPen2(Qt::darkYellow);
    ctrlPen2.setWidth(1);
    ctrlPen2.setStyle(Qt::DashDotDotLine);
    painter.setPen(ctrlPen2);
    for(int i = 0; i < ctrlPoints.size() - 1; ++i)
        painter.drawLine(ctrlPoints[i], ctrlPoints[i + 1]);
    // draw Spline Curve
    QPen curvePen;
    switch(_color) {
    case BLACK:
        curvePen.setColor(Qt::black);
        break;
    case RED:
        curvePen.setColor(Qt::red);
        break;
    case GREEN:
        curvePen.setColor(Qt::green);
        break;
    case BLUE:
        curvePen.setColor(Qt::blue);
        break;
    }
    curvePen.setWidth(_thick);
    painter.setPen(curvePen);
    for(int i = 0; i < curvePoints.size() - 1; ++i)
        painter.drawLine(curvePoints[i], curvePoints[i + 1]);
}

void Curve::updown(int arg) {
    QMatrix trans1(1, 0, 0, 1, 0, -1), trans2(1, 0, 0, 1, 0, 1);

    if(arg > lastUD) {
        for(QVector<QPointF>::Iterator it = ctrlPoints.begin(); it != ctrlPoints.end(); ++it)
            applyMat(*it, trans1);
        generateCurve();
    }
    else {
        for(QVector<QPointF>::Iterator it = ctrlPoints.begin(); it != ctrlPoints.end(); ++it)
            applyMat(*it, trans2);
        generateCurve();
    }
}

void Curve::leftright(int arg) {
    QMatrix trans1(1, 0, 0, 1, 1, 0), trans2(1, 0, 0, 1, -1, 0);

    if(arg > lastLR) {
        for(QVector<QPointF>::Iterator it = ctrlPoints.begin(); it != ctrlPoints.end(); ++it)
            applyMat(*it, trans1);
        generateCurve();
    }
    else {
        for(QVector<QPointF>::Iterator it = ctrlPoints.begin(); it != ctrlPoints.end(); ++it)
            applyMat(*it, trans2);
        generateCurve();
    }
}

void Curve::rotate(int arg) {
    QMatrix translate1(1, 0, 0, 1, -start.x(), -start.y()), translate2(1, 0, 0, 1, start.x(), start.y());
    QMatrix rotate1(cos(DEGREE), -sin(DEGREE), sin(DEGREE), cos(DEGREE), 0, 0);
    QMatrix rotate2(cos(-DEGREE), -sin(-DEGREE), sin(-DEGREE), cos(-DEGREE), 0, 0);

    for(QVector<QPointF>::Iterator it = ctrlPoints.begin(); it != ctrlPoints.end(); ++it)
        applyMat(*it, translate1);

    if(arg > lastR) {
        for(QVector<QPointF>::Iterator it = ctrlPoints.begin(); it != ctrlPoints.end(); ++it)
            applyMat(*it, rotate1);
    }
    else {
        for(QVector<QPointF>::Iterator it = ctrlPoints.begin(); it != ctrlPoints.end(); ++it)
            applyMat(*it, rotate2);
    }

    for(QVector<QPointF>::Iterator it = ctrlPoints.begin(); it != ctrlPoints.end(); ++it)
        applyMat(*it, translate2);

    generateCurve();
}

void Curve::zoom(int arg) {
    QMatrix translate1(1, 0, 0, 1, -xc, -yc), translate2(1, 0, 0, 1, xc, yc);
    QMatrix zoom1(1.25, 0, 0, 1.25, 0, 0), zoom2(0.8, 0, 0, 0.8, 0, 0);

    for(QVector<QPointF>::Iterator it = ctrlPoints.begin(); it != ctrlPoints.end(); ++it)
        applyMat(*it, translate1);

    if(arg > lastZ) {
        for(QVector<QPointF>::Iterator it = ctrlPoints.begin(); it != ctrlPoints.end(); ++it)
            applyMat(*it, zoom1);
    }
    else {
        for(QVector<QPointF>::Iterator it = ctrlPoints.begin(); it != ctrlPoints.end(); ++it)
            applyMat(*it, zoom2);
    }

    for(QVector<QPointF>::Iterator it = ctrlPoints.begin(); it != ctrlPoints.end(); ++it)
        applyMat(*it, translate2);

    generateCurve();
}
