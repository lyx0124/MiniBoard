//----Author: Yuxiang LIU
//----Facility: Nanjing University
//----Email: lyx970124@gmail.com
//----Github: https://github.com/lyx0124

#include "paintwidget.h"

PaintWidget::PaintWidget(QWidget *parent) :
    QWidget(parent), currShape(Shape::LINE),
    currColor(Shape::BLACK), currThick(Shape::THIN),  currK(1), shape(NULL), releaseFlag(false) {
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

//----------------------------------------------------------------------------------------------------------------------------------
//public slots

void PaintWidget::newPainting() {
    clearCurrentScreen();
}

void PaintWidget::openPainting() {;}

void PaintWidget::savePainting() {
    QPixmap pixmap = QPixmap::grabWidget(this);
    pixmap.save("screenshot.png","PNG");
}

//----------------------------------------------------------------------------------------------------------------------------------
//protected

void PaintWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawRect(0, 0, size().width() - 1, size().height() - 1);

    foreach(Shape *shape, shapeList) {
        shape->paint(painter);
        if(shape->getFillFlag() == true)
            shape->fillArea(painter);
        update();
    }
}

void PaintWidget::mousePressEvent(QMouseEvent *event) {
    releaseFlag = false;

    if(currShape != Shape::POLY && currShape != Shape::CURVE) {
        if(event->button() == Qt::LeftButton) {
            if(shape != nullptr)
                if(shape->getClipFlag()) {
                    shape->setClipRect().setTopLeft(event->pos());
                    shape->setClipRect().setBottomRight(event->pos());
                }
            if(shape == nullptr || !shape->getClipFlag()) {
                switch(currShape) {
                case Shape::LINE:
                    shape = new Line;
                    shape->change_color(currColor);
                    shape->change_thick(currThick);
                    clearTrans();
                    break;
                case Shape::RECT:
                    shape = new Rect;
                    shape->change_color(currColor);
                    shape->change_thick(currThick);
                    clearTrans();
                    break;
                case Shape::CIRCLE:
                    shape = new Circle;
                    shape->change_color(currColor);
                    shape->change_thick(currThick);
                    clearTrans();
                    break;
                case Shape::ELLIP:
                    shape = new Ellip;
                    shape->change_color(currColor);
                    shape->change_thick(currThick);
                    clearTrans();
                    break;
                }
                shapeList<<shape;
                if(shape != nullptr && shape->getShape() != Shape::POLY) {
                    shape->setStart(event->pos());
                    shape->setEnd(event->pos());
                }
            }
        }
    }

    if(currShape == Shape::POLY) {
        if(event->button() == Qt::LeftButton) {
            shape = new Poly;
            shape->change_color(currColor);
            shape->change_thick(currThick);
            clearTrans();
            shapeList<<shape;
            if(shape != nullptr && shape->count == 0) {
                shape->setStart(event->pos());
                shape->setEnd(event->pos());
                shape->addVertex(event->pos());
                shape->addVertex(event->pos());
            }
        }
    }

    if(currShape == Shape::CURVE) {
        if(event->button() == Qt::LeftButton) {
            shape = new Curve;
            shape->change_color(currColor);
            shape->change_thick(currThick);
            shape->change_K(currK);
            clearTrans();
            shapeList<<shape;
            setCursor(QCursor(Qt::ClosedHandCursor));
            int i = shape->getCurrentNode(event->pos());
            if(i >= 0) {
                shape->currentNode = i;
                return;
            }
            shape->ctrlPoints.push_back(event->pos());
            shape->currentNode = shape->ctrlPoints.size()-1;
            shape->generateCurve();
            update();
        }
        if(event->button() == Qt::RightButton) {
            setCursor(QCursor(Qt::ClosedHandCursor));
            int i = shape->getCurrentNode(event->pos());
            if(i >= 0) {
                shape->currentNode = i;
                return;
            }
            shape->ctrlPoints.push_back(event->pos());
            shape->currentNode = shape->ctrlPoints.size()-1;
            shape->generateCurve();
            update();
        }
    }
}

void PaintWidget::mouseMoveEvent(QMouseEvent *event) {
    setMouseTracking(true);  //damn!!! nasty little thing!!!

    if(shape->getShape() != Shape::POLY && shape->getShape() != Shape::CURVE && !shape->getClipFlag()) {
        if(!releaseFlag) {
            shape->setEnd(event->pos());
            shape->generateCurve(); //use curve API to set rectangle p1, p2
            update();
        }
    }

    if(shape->getShape() == Shape::POLY && !shape->getClipFlag()) {
        if(releaseFlag) {
            shape->changeLastVertex(event->pos());
            update();
        }
    }

    if(shape->getShape() == Shape::CURVE && !shape->getClipFlag()) {
        if(event->buttons() & Qt::RightButton) {
            shape->ctrlPoints.removeAt(shape->currentNode);
            shape->ctrlPoints.insert(shape->currentNode,event->pos());
            shape->generateCurve();
            update();
            return;
        }
        if(shape->getCurrentNode(event->pos()) >= 0)
            setCursor(QCursor(Qt::SizeAllCursor));
        else
            setCursor(QCursor(Qt::ArrowCursor));
    }

    if(shape->getClipFlag() && !releaseFlag) {
        shape->setClipRect().setBottomRight(event->pos());
        update();
    }
}

void PaintWidget::mouseReleaseEvent(QMouseEvent *event) {
    releaseFlag = true;

    // a little note here for polygon:
    // left click to create a polygon(in mousePressEvent)
    // right click to add vertices to the polygon(as showed here)
    // middle click to add the last vertex(as showed here)
    if(shape->getShape() == Shape::POLY) {
        if(event->button() == Qt::RightButton)
            shape->addVertex(event->pos());
        if(event->button() == Qt::MiddleButton) {
            shape->changeLastVertex(event->pos());
            releaseFlag = false;
        }
    }

    if(shape->getShape() == Shape::CURVE) {
        setCursor(QCursor(Qt::ArrowCursor));
    }

    if(shape != nullptr)
        if(shape->getClipFlag()) {
            shape->clipShape();
            shape->setNegClipFlag();  //otherwise we cannot draw new shapes
            update();
        }
}

//----------------------------------------------------------------------------------------------------------------------------------
//public slots

void PaintWidget::showThreeD() {
    Qt3DExtras::Qt3DWindow *view = new Qt3DExtras::Qt3DWindow();
    view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x4d4d4f)));
    QWidget *container = QWidget::createWindowContainer(view);
    QSize screenSize = view->screen()->size();
    container->setMinimumSize(QSize(200, 100));
    container->setMaximumSize(screenSize);
    QWidget *widget = new QWidget;
    QHBoxLayout *hLayout = new QHBoxLayout(widget);
    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setAlignment(Qt::AlignTop);
    hLayout->addWidget(container, 1);
    hLayout->addLayout(vLayout);
    Qt3DInput::QInputAspect *input = new Qt3DInput::QInputAspect;
    view->registerAspect(input);
    // Root entity
    Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity();
    // Camera
    Qt3DRender::QCamera *cameraEntity = view->camera();
    cameraEntity->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    cameraEntity->setPosition(QVector3D(0, 0, 20.0f));
    cameraEntity->setUpVector(QVector3D(0, 1, 0));
    cameraEntity->setViewCenter(QVector3D(0, 0, 0));
    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(rootEntity);
    Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight(lightEntity);
    light->setColor("white");
    light->setIntensity(1);
    lightEntity->addComponent(light);
    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
    lightTransform->setTranslation(cameraEntity->position());
    lightEntity->addComponent(lightTransform);
    // For camera controls
    Qt3DExtras::QFirstPersonCameraController *camController = new Qt3DExtras::QFirstPersonCameraController(rootEntity);
    camController->setCamera(cameraEntity);
    Qt3DCore::QEntity *m_rootEntity = rootEntity;
    Qt3DCore::QEntity *m_cylinderEntity;
    // Cylinder shape data
    Qt3DExtras::QCylinderMesh *cylinder = new Qt3DExtras::QCylinderMesh();
    cylinder->setRadius(1);
    cylinder->setLength(3);
    cylinder->setRings(100);
    cylinder->setSlices(20);
    // CylinderMesh Transform
    Qt3DCore::QTransform *cylinderTransform = new Qt3DCore::QTransform();
    cylinderTransform->setScale(3.0f);
    cylinderTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1.0f, 0.0f, 0.0f), 30.0f));
    Qt3DExtras::QPhongMaterial *cylinderMaterial = new Qt3DExtras::QPhongMaterial();
    cylinderMaterial->setDiffuse(QColor(QRgb(0x928327)));
    // Cylinder
    m_cylinderEntity = new Qt3DCore::QEntity(m_rootEntity);
    m_cylinderEntity->addComponent(cylinder);
    m_cylinderEntity->addComponent(cylinderMaterial);
    m_cylinderEntity->addComponent(cylinderTransform);
    m_cylinderEntity->setEnabled(true);
    // Set root object of the scene
    view->setRootEntity(rootEntity);
    // Show window
    widget->show();
    widget->resize(QSize(800, 600));
}
