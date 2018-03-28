//----Author: Yuxiang LIU
//----Facility: Nanjing University
//----Email: lyx970124@gmail.com
//----Github: https://github.com/lyx0124

#ifndef SHAPE_H
#define SHAPE_H

#include <QtGui>
#include <QtCore>
#include "tools.h"

class Shape
{
public:
    enum shape_code {
        LINE,
        RECT,
        POLY,
        CIRCLE,
        ELLIP,
        CURVE
    };
    enum color_code {
        BLACK = Qt::black,
        RED = Qt::red,
        GREEN = Qt::green,
        BLUE = Qt::blue
    };
    enum thick_code {
        THIN = 2,
        MEDIUM = 4,
        HEAVY = 8
    };

    Shape() : count(0), fillFlag(false), clipFlag(false), lastUD(0), lastLR(0), lastR(0), lastZ(0), orderK(1) {;}
    Shape(shape_code s, int num = 0, bool fill = false, bool clip = false, int k = 1) : _shape(s), count(num),
        fillFlag(fill), clipFlag(clip), lastUD(0), lastLR(0), lastR(0), lastZ(0), orderK(k) {;}
    virtual ~Shape() {;}

    //generic APIs
    virtual QPointF getStart() const { return start; }
    virtual QPointF getEnd() const { return end; }
    virtual shape_code getShape() const { return _shape; }
    virtual color_code getColor() const { return _color; }
    virtual thick_code getThick() const { return _thick; }
    virtual bool getFillFlag() const { return fillFlag; }  //for filling area
    virtual bool getClipFlag() const { return clipFlag; }  //for clipping shape

    virtual void setStart(QPointF s) { start = s; }
    virtual void setEnd(QPointF e) { end = e; }
    virtual void setFillFlag() { fillFlag = true; }  //for filling area
    virtual void setClipFlag() { clipFlag = true; }  //for clipping shape
    virtual void setNegClipFlag() { clipFlag = false; }  //for clipping shape
    virtual QRect & setClipRect() { return clipRect; }  //for clipping shape
    virtual void change_color(color_code color) { _color = color; }
    virtual void change_thick(thick_code thick) { _thick = thick; }
    virtual void change_K(int k) { orderK = k; }  //for changing curve order
    virtual void setLastUD(int arg) { lastUD = arg; }  //these four are for transformation
    virtual void setLastLR(int arg) { lastLR = arg; }
    virtual void setLastR(int arg) { lastR = arg; }
    virtual void setLastZ(double arg) { lastZ = arg; }

    virtual void paint(QPainter&) = 0;
    virtual void fillArea(QPainter&) = 0;
    virtual void clipShape() = 0;  //shape clipping
    virtual void updown(int) = 0;  //these four are for transformation
    virtual void leftright(int) = 0;
    virtual void rotate(int) = 0;
    virtual void zoom(int) = 0;

    //for polygons only
    int count;
    QVector<QPointF> vertices;
    virtual void addVertex(QPointF p) { vertices.push_back(p); ++count; }
    virtual void changeLastVertex(QPointF p) { *(vertices.end() - 1) = p; }
    //for curves only
    int orderK;
    int currentNode;
    QVector<QPointF> ctrlPoints;
    QVector<QPointF> curvePoints;
    virtual int getCurrentNode(QPointF) {;}
    virtual void generateCurve() {;}

protected:
    bool fillFlag;
    bool clipFlag;
    QRect clipRect;  //for clipping

    QPointF start, end;
    shape_code _shape;
    color_code _color;
	thick_code _thick;
    int lastUD, lastLR, lastR, lastZ;
};

#endif // SHAPE_H
