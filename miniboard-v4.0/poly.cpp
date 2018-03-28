//----Author: Yuxiang LIU
//----Facility: Nanjing University
//----Email: lyx970124@gmail.com
//----Github: https://github.com/lyx0124

#include "poly.h"

Poly::Poly() : Shape(POLY, 0), xc(0), yc(0), xmin(0), ymin(0), xmax(0), ymax(0) {;}
Poly::~Poly() {;}

void Poly::paint(QPainter & painter) {
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

    xmax = 0;  ymax = 0;
    xmin = 800;  ymin = 600;
    for(QVector<QPointF>::Iterator it = vertices.begin(); it != vertices.end() - 1; ++it) {
        painter.drawLine(*it, *(it + 1));

        if(it->x() < xmin) xmin = it->x();
        if(it->x() > xmax) xmax = it->x();
        if(it->y() < ymin) ymin = it->y();
        if(it->y() > ymax) ymax = it->y();
    }
    painter.drawLine(*(vertices.end() - 1), getStart());
    if((vertices.end() - 1)->x() < xmin) xmin = (vertices.end() - 1)->x();
    if((vertices.end() - 1)->x() > xmax) xmax = (vertices.end() - 1)->x();
    if((vertices.end() - 1)->y() < ymin) ymin = (vertices.end() - 1)->y();
    if((vertices.end() - 1)->y() > ymax) ymax = (vertices.end() - 1)->y();

    xc = (xmin + xmax) / 2;
    yc = (ymin + ymax) / 2;
}

void Poly::fillArea(QPainter & painter) {
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



    AET *pAET = new AET;
    pAET->next = NULL;

    NET *pNET[1024];
    for (int i = 0; i <= ymax; i++)
    {
        pNET[i] = new NET;
        pNET[i]->next = NULL;
    }
    for (int i = 0; i <= ymax; i++)
    {
        for (int j = 0; j<count; j++)
            if (vertices[j].y() == i)
            {
                if (vertices[(j - 1 + count) % count].y()>vertices[j].y())
                {
                    NET *p = new NET;
                    p->x = vertices[j].x();
                    p->MaxY = vertices[(j - 1 + count) % count].y();
                    p->dx = (vertices[(j - 1 + count) % count].x() - vertices[j].x()) /
                            (vertices[(j - 1 + count) % count].y() - vertices[j].y());
                    p->next = pNET[i]->next;
                    pNET[i]->next = p;
                }
                if (vertices[(j + 1 + count) % count].y()>vertices[j].y())
                {
                    NET *p = new NET;
                    p->x = vertices[j].x();
                    p->MaxY = vertices[(j + 1 + count) % count].y();
                    p->dx = (vertices[(j + 1 + count) % count].x() - vertices[j].x()) /
                            (vertices[(j + 1 + count) % count].y() - vertices[j].y());
                    p->next = pNET[i]->next;
                    pNET[i]->next = p;
                }
            }
    }

    for (int i = 0; i <= ymax; i++)
    {
        NET *p = pAET->next;
        while (p)
        {
            p->x = p->x + p->dx;
            p = p->next;
        }
        AET *tq = pAET;
        p = pAET->next;
        tq->next = NULL;
        while (p)
        {
            while (tq->next && p->x >= tq->next->x)
                tq = tq->next;
                NET *s = p->next;
                p->next = tq->next;
                tq->next = p;
                p = s;
                tq = pAET;
        }
        AET *q = pAET;
        p = q->next;
        while (p)
        {
            if (p->MaxY == i)
            {
                q->next = p->next;
                delete p;
                p = q->next;
            }
            else
            {
                q = q->next;
                p = q->next;
            }
        }
        p = pNET[i]->next;
        q = pAET;
        while (p)
        {
            while (q->next && p->x >= q->next->x)
                q = q->next;
            NET *s = p->next;
            p->next = q->next;
            q->next = p;
            p = s;
            q = pAET;
        }
        p = pAET->next;
        while (p && p->next)
        {
            for (float j = p->x; j <= p->next->x; j++)
                painter.drawPoint(static_cast<int>(j), i);
            p = p->next->next;
        }
    }
}

void Poly::updown(int arg) {
    QMatrix trans1(1, 0, 0, 1, 0, -1), trans2(1, 0, 0, 1, 0, 1);

    if(arg > lastUD) {
        for(QVector<QPointF>::Iterator it = vertices.begin(); it != vertices.end(); ++it)
            applyMat(*it, trans1);
        applyMat(start, trans1);
    }
    else {
        for(QVector<QPointF>::Iterator it = vertices.begin(); it != vertices.end(); ++it)
            applyMat(*it, trans2);
        applyMat(start, trans2);
    }
}

void Poly::leftright(int arg) {
    QMatrix trans1(1, 0, 0, 1, 1, 0), trans2(1, 0, 0, 1, -1, 0);

    if(arg > lastLR) {
        for(QVector<QPointF>::Iterator it = vertices.begin(); it != vertices.end(); ++it)
            applyMat(*it, trans1);
        applyMat(start, trans1);
    }
    else {
        for(QVector<QPointF>::Iterator it = vertices.begin(); it != vertices.end(); ++it)
            applyMat(*it, trans2);
        applyMat(start, trans2);
    }
}

void Poly::rotate(int arg) {
    QMatrix rotate1(cos(DEGREE), -sin(DEGREE), sin(DEGREE), cos(DEGREE), 0, 0);
    QMatrix rotate2(cos(-DEGREE), -sin(-DEGREE), sin(-DEGREE), cos(-DEGREE), 0, 0);

    if(arg > lastR) {
        for(QVector<QPointF>::Iterator it = vertices.begin(); it != vertices.end(); ++it)
            applyMat(*it, rotate1);
        applyMat(start, rotate1);
    }
    else {
        for(QVector<QPointF>::Iterator it = vertices.begin(); it != vertices.end(); ++it)
            applyMat(*it, rotate2);
        applyMat(start, rotate2);
    }
}

void Poly::zoom(int arg) {
    QMatrix translate1(1, 0, 0, 1, -xc, -yc), translate2(1, 0, 0, 1, xc, yc);
    QMatrix zoom1(1.25, 0, 0, 1.25, 0, 0), zoom2(0.8, 0, 0, 0.8, 0, 0);

    for(QVector<QPointF>::Iterator it = vertices.begin(); it != vertices.end(); ++it)
        applyMat(*it, translate1);
    applyMat(start, translate1);

    if(arg > lastZ) {
        for(QVector<QPointF>::Iterator it = vertices.begin(); it != vertices.end(); ++it)
            applyMat(*it, zoom1);
        applyMat(start, zoom1);
    }
    else {
        for(QVector<QPointF>::Iterator it = vertices.begin(); it != vertices.end(); ++it)
            applyMat(*it, zoom2);
        applyMat(start, zoom2);
    }

    for(QVector<QPointF>::Iterator it = vertices.begin(); it != vertices.end(); ++it)
        applyMat(*it, translate2);
    applyMat(start, translate2);
}
