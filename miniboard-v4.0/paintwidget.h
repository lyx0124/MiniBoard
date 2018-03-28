//----Author: Yuxiang LIU
//----Facility: Nanjing University
//----Email: lyx970124@gmail.com
//----Github: https://github.com/lyx0124

#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H
#include <QGuiApplication>
#include <QtCore/QObject>
#include <Qt3DCore/qentity.h>
#include <Qt3DCore/qtransform.h>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DRender/qcamera.h>
#include <Qt3DCore/qentity.h>
#include <Qt3DRender/qcameralens.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QCommandLinkButton>
#include <QtGui/QScreen>
#include <Qt3DInput/QInputAspect>
#include <Qt3DExtras/qtorusmesh.h>
#include <Qt3DRender/qmesh.h>
#include <Qt3DRender/qtechnique.h>
#include <Qt3DRender/qmaterial.h>
#include <Qt3DRender/qeffect.h>
#include <Qt3DRender/qtexture.h>
#include <Qt3DRender/qrenderpass.h>
#include <Qt3DRender/qsceneloader.h>
#include <Qt3DRender/qpointlight.h>
#include <Qt3DCore/qtransform.h>
#include <Qt3DCore/qaspectengine.h>
#include <Qt3DRender/qrenderaspect.h>
#include <Qt3DExtras/qforwardrenderer.h>
#include <Qt3DExtras/qt3dwindow.h>
#include <Qt3DExtras/qfirstpersoncameracontroller.h>

#include <QtGui>
#include <QtCore>
#include <QDebug>
#include <QWidget>
#include <QPainter>
#include "line.h"
#include "rect.h"
#include "poly.h"
#include "circle.h"
#include "ellip.h"
#include "curve.h"

class PaintWidget : public QWidget {
    Q_OBJECT

public:
    PaintWidget(QWidget *parent = 0);

public slots:
    void newPainting();
    void openPainting();
    void savePainting();
    void setCurrentShape(Shape::shape_code s) { if(s != currShape) currShape = s; }
    void setCurrentColor(Shape::color_code c) { if(c != currColor) currColor = c; }
    void setCurrentThick(Shape::thick_code t) { if(t != currThick) currThick = t; }
    void deleteNode() { if(shape != nullptr)
        { if(shape->ctrlPoints.empty() == true) return; shape->ctrlPoints.pop_back(); shape->generateCurve(); } }
    void orderChange(int index) { if(shape != nullptr)
        { shape->orderK = index + 1; shape->generateCurve(); update(); } }
    void setCurrentK(int k) { if(k != currK) currK = k; }
    void fillStart() { if(shape != nullptr) shape->setFillFlag(); }
    void clipStart() { if(shape != nullptr) shape->setClipFlag(); }
    void clearCurrentScreen() { shapeList.clear(); update(); }
    void startUpdown(int arg) { if(shape != nullptr) { shape->updown(arg); shape->setLastUD(arg); } }
    void startLeftright(int arg) { if(shape != nullptr) { shape->leftright(arg); shape->setLastLR(arg); } }
    void startRotate(int arg) { if(shape != nullptr) { shape->rotate(arg); shape->setLastR(arg); } }
    void startZoom(int arg) { if(shape != nullptr) { shape->zoom(arg); shape->setLastZ(arg); } }
    void showThreeD();

signals:
    void clearTrans();  //clear transformation spinbox

protected:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);

protected:
    bool releaseFlag;

    Shape *shape;
    QList<Shape*> shapeList;
    Shape::shape_code currShape;
    Shape::color_code currColor;
    Shape::thick_code currThick;
    int currK;
};

#endif // PAINTWIDGET_H
