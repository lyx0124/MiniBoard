//----Author: Yuxiang LIU
//----Facility: Nanjing University
//----Email: lyx970124@gmail.com
//----Github: https://github.com/lyx0124

#include "line.h"

Line::Line() : Shape(LINE) {;}
Line::~Line() {;}

void Line::paint(QPainter & painter) {
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

    int x = start.x(), y = start.y();
    const float dx = end.x() - start.x();
    const float dy = end.y() - start.y();
    int p;
    //0<m<1, l2r
    if ((dy / dx) >= 0 && (dy / dx) <= 1 && dx >= 0 && dy >= 0) {
        p = 2 * dy - dx;
        for (x = start.x(); x < end.x(); ++x) {
            painter.drawPoint(x, y);
            if (p >= 0) {
                y += 1;
                p = p + 2 * dy - 2 * dx;
            }
            else
                p = p + 2 * dy;
        }
    }
    //0<m<1, r2l
    else if ((dy / dx) >= 0 && (dy / dx) <= 1 && dx <= 0 && dy <= 0) {
        p = 2 * dy + dx;
        for (x = start.x(); x > end.x(); --x) {
            painter.drawPoint(x, y);
            if (p < 0) {
                y -= 1;
                p = p + 2 * dy - 2 * dx;
            }
            else
                p = p + 2 * dy;
        }
    }
    //m>1, l2r
    else if ((dy / dx) > 1 && dx >= 0 && dy >= 0) {
        p = 2 * dx - dy;
        for (y = start.y(); y < end.y(); ++y) {
            painter.drawPoint(x, y);
            if (p >= 0) {
                x += 1;
                p = p + 2 * dx - 2 * dy;
            }
            else
                p = p + 2 * dx;
        }
    }
    //m>1, r2l
    else if ((dy / dx) > 1 && dx <= 0 && dy <= 0) {
        p = 2 * dx + dy;
        for (y = start.y(); y > end.y(); --y) {
            painter.drawPoint(x, y);
            if (p < 0) {
                x -= 1;
                p = p + 2 * dx - 2 * dy;
            }
            else
                p = p + 2 * dx;
        }
    }
    //m<-1, l2r
    else if ((dy / dx) < -1 && dx >= 0 && dy <= 0) {
        p = 2 * dx - dy;
        for (y = start.y(); y > end.y(); --y) {
            painter.drawPoint(x, y);
            if (p >= 0) {
                x += 1;
                p = p + 2 * dx + 2 * dy;
            }
            else
                p = p + 2 * dx;
        }
    }
    //m<-1, r2l
    else if ((dy / dx) < -1 && dx <= 0 && dy >= 0) {
        p = 2 * dx - dy;
        for (y = start.y(); y < end.y(); ++y) {
            painter.drawPoint(x, y);
            if (p < 0) {
                x -= 1;
                p = p + 2 * dx + 2 * dy;
            }
            else
                 p = p + 2 * dx;
        }
    }
    //-1<m<0, l2r
    else if ((dy / dx) < 0 && (dy / dx) > -1 && dx >= 0 && dy <= 0) {
        p = 2 * dy - dx;
        for (x = start.x(); x < end.x(); ++x) {
            painter.drawPoint(x, y);
            if (p < 0) {
                y -= 1;
                p = p + 2 * dy + 2 * dx;
            }
            else
                p = p + 2 * dy;
        }
    }
    //-1<m<0, r2l
    else if ((dy / dx) < 0 && (dy / dx) > -1 && dx <= 0 && dy >= 0) {
        p = 2 * dy - dx;
        for (x = start.x(); x > end.x(); --x) {
            painter.drawPoint(x, y);
            if (p >= 0) {
                y += 1;
                p = p + 2 * dy + 2 * dx;
            }
            else
                p = p + 2 * dy;
        }
    }

    QPen penRect(Qt::darkYellow);
    penRect.setWidth(1);
    penRect.setStyle(Qt::DashDotDotLine);
    painter.setPen(penRect);
    painter.drawRect(clipRect);
}

void Line::clipShape() {
    if(clipRect.left() < clipRect.right() && clipRect.top() < clipRect.bottom())
        clip(clipRect.top(), clipRect.bottom(), clipRect.left(), clipRect.right());
    if(clipRect.left() > clipRect.right() && clipRect.top() < clipRect.bottom())
        clip(clipRect.top(), clipRect.bottom(), clipRect.right(), clipRect.left());  //why this doesn't work???
    if(clipRect.left() < clipRect.right() && clipRect.top() > clipRect.bottom())
        clip(clipRect.bottom(), clipRect.top(), clipRect.left(), clipRect.right());  //why this doesn't work???
    if(clipRect.left() > clipRect.right() && clipRect.top() > clipRect.bottom())
        clip(clipRect.bottom(), clipRect.top(), clipRect.right(), clipRect.left());  //why this doesn't work???
}

void Line::clip(int top, int bottom, int left, int right) {
    int x, y;
    int total = 0;
    bool finish = false;
    int codeStart, codeEnd, lineCode;
    codeStart = encode(start.x(), start.y());
    codeEnd = encode(end.x(), end.y());
    while(!finish) {
        if(!(codeStart | codeEnd))
            finish = true;
        else if(codeStart & codeEnd)
            finish = true;
        else {
            if(codeStart != 0)
                lineCode = codeStart;
            else
                lineCode = codeEnd;
            if(lineCode & LEFT) {
                y = start.y() + (end.y() - start.y())*(left - start.x()) / (end.x() - start.x());
                x = (float)left;
            }
            if(lineCode & RIGHT) {
                y = start.y() + (end.y() - start.y())*(right - start.x()) / (end.x() - start.x());
                x = (float)right;
            }
            if(lineCode & TOP) {
                x = start.x() + (end.x() - start.x())*(top - start.y()) / (end.y() - start.y());
                y = (float)top;
            }
            if(lineCode & BOTTOM) {
                x = start.x() + (end.x() - start.x())*(bottom - start.y()) / (end.y() - start.y());
                y = (float)bottom;
            }
            if(lineCode == codeStart) {
                start.rx() = x; start.ry() = y;
                codeStart = encode(start.x(), start.y());
            }
            else {
                end.rx() = x; end.ry() = y;
                codeEnd = encode(end.x(), end.y());
            }
            ++total;
            if(total > 2)
                finish = true;
        }
    }
}

int Line::encode(int x, int y) {
    int code = 0x00;    
    if(x < clipRect.left())
        code = code | 1;
    if(x > clipRect.right())
        code = code | 2;
    if(y < clipRect.top())
        code = code | 4;
    if(y > clipRect.bottom())
        code = code | 8;
    return code;
}

void Line::updown(int arg) {
    QMatrix trans1(1, 0, 0, 1, 0, -1), trans2(1, 0, 0, 1, 0, 1);

    if(arg > lastUD) {
        applyMat(start, trans1);
        applyMat(end, trans1);
        QPoint tl = clipRect.topLeft();
        QPoint br = clipRect.bottomRight();
        applyMat(tl, trans1);
        applyMat(br, trans1);
        clipRect.setTopLeft(tl);
        clipRect.setBottomRight(br);
    }
    else {
        applyMat(start, trans2);
        applyMat(end, trans2);
        QPoint tl = clipRect.topLeft();
        QPoint br = clipRect.bottomRight();
        applyMat(tl, trans2);
        applyMat(br, trans2);
        clipRect.setTopLeft(tl);
        clipRect.setBottomRight(br);
    }
}

void Line::leftright(int arg) {
    QMatrix trans1(1, 0, 0, 1, 1, 0), trans2(1, 0, 0, 1, -1, 0);

    if(arg > lastLR) {
        applyMat(start, trans1);
        applyMat(end, trans1);
        QPoint tl = clipRect.topLeft();
        QPoint br = clipRect.bottomRight();
        applyMat(tl, trans1);
        applyMat(br, trans1);
        clipRect.setTopLeft(tl);
        clipRect.setBottomRight(br);
    }
    else {
        applyMat(start, trans2);
        applyMat(end, trans2);
        QPoint tl = clipRect.topLeft();
        QPoint br = clipRect.bottomRight();
        applyMat(tl, trans2);
        applyMat(br, trans2);
        clipRect.setTopLeft(tl);
        clipRect.setBottomRight(br);
    }
}
