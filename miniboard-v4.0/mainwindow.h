//----Author: Yuxiang LIU
//----Facility: Nanjing University
//----Email: lyx970124@gmail.com
//----Github: https://github.com/lyx0124

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "paintwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void newW2W();
    void saveW2W();
    void changeCurrentShape(Shape::shape_code);
    void changeCurrentColor(Shape::color_code);
    void changeCurrentThick(Shape::thick_code);
    void deleteW2W();  //delete curve control point
    void orderW2W(int);  //change curve order
    void currentK(int);  //set current curve order for paintwidget
    void fillW2W();
    void clipW2W();
    void clearScreen();
    void updownW2W(int);
    void leftrightW2W(int);
    void rotateW2W(int);
    void zoomW2W(int);
    void show3dW2W();

private slots:
    void on_actionNew_triggered();
    void on_actionSave_triggered();
    void on_actionLine_triggered();
    void on_actionCurve_triggered();
    void on_actionRect_triggered();
    void on_actionPoly_triggered();
    void on_actionCircle_triggered();
    void on_actionEllip_triggered();
    void on_actionThreeD_triggered();

    void on_pushButton_black_clicked();
    void on_pushButton_red_clicked();
    void on_pushButton_green_clicked();
    void on_pushButton_blue_clicked();
    void on_pushButton_thin_clicked();
    void on_pushButton_medium_clicked();
    void on_pushButton_heavy_clicked();
    void on_pushButton_deletenode_clicked();
    void on_curveorder_currentIndexChanged(int);
    void on_pushButton_fill_clicked();
    void on_pushButton_clip_clicked();
    void on_pushButton_clear_clicked();
    void on_updown_valueChanged(int);
    void on_leftright_valueChanged(int);
    void on_rotate_valueChanged(int);
    void on_zoom_valueChanged(int);

    void clearSpinbox();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
