//----Author: Yuxiang LIU
//----Facility: Nanjing University
//----Email: lyx970124@gmail.com
//----Github: https://github.com/lyx0124

#include "mainwindow.h"
#include "ui_mainwindow.h"

//---------------------------------------------------------------------------------------------------------------------------------
//public

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSize s1 = ui->pushButton_black->size();
    ui->pushButton_black->setIcon(QIcon(":/icons/resource/black.png"));
    ui->pushButton_black->setIconSize(s1);
    ui->pushButton_black->setFlat(true);

    QSize s2 = ui->pushButton_red->size();
    ui->pushButton_red->setIcon(QIcon(":/icons/resource/red.png"));
    ui->pushButton_red->setIconSize(s2);
    ui->pushButton_red->setFlat(true);

    QSize s3 = ui->pushButton_green->size();
    ui->pushButton_green->setIcon(QIcon(":/icons/resource/green.png"));
    ui->pushButton_green->setIconSize(s3);
    ui->pushButton_green->setFlat(true);

    QSize s4 = ui->pushButton_blue->size();
    ui->pushButton_blue->setIcon(QIcon(":/icons/resource/blue.png"));
    ui->pushButton_blue->setIconSize(s4);
    ui->pushButton_blue->setFlat(true);

    QSize s5 = ui->pushButton_thin->size();
    ui->pushButton_thin->setIcon(QIcon(":/icons/resource/thin.png"));
    ui->pushButton_thin->setIconSize(s5);
    ui->pushButton_thin->setFlat(true);

    QSize s6 = ui->pushButton_medium->size();
    ui->pushButton_medium->setIcon(QIcon(":/icons/resource/medium.png"));
    ui->pushButton_medium->setIconSize(s6);
    ui->pushButton_medium->setFlat(true);

    QSize s7 = ui->pushButton_heavy->size();
    ui->pushButton_heavy->setIcon(QIcon(":/icons/resource/heavy.png"));
    ui->pushButton_heavy->setIconSize(s7);
    ui->pushButton_heavy->setFlat(true);

    QSize s8 = ui->pushButton_fill->size();
    ui->pushButton_fill->setIcon(QIcon(":/icons/resource/fill.png"));
    ui->pushButton_fill->setIconSize(s8);
    ui->pushButton_fill->setFlat(true);

    QSize s9 = ui->pushButton_clip->size();
    ui->pushButton_clip->setIcon(QIcon(":/icons/resource/clip.png"));
    ui->pushButton_clip->setIconSize(s9);
    ui->pushButton_clip->setFlat(true);

    QSize s10 = ui->pushButton_clear->size();
    ui->pushButton_clear->setIcon(QIcon(":/icons/resource/clear.png"));
    ui->pushButton_clear->setIconSize(s10);
    ui->pushButton_clear->setFlat(true);

    QSize s11 = ui->pushButton_deletenode->size();
    ui->pushButton_deletenode->setIcon(QIcon(":/icons/resource/delete.png"));
    ui->pushButton_deletenode->setIconSize(s11);
    ui->pushButton_deletenode->setFlat(true);

    ui->updown->setMinimum(-600); ui->updown->setMaximum(600);
    ui->leftright->setMinimum(-800); ui->leftright->setMaximum(800);
    ui->rotate->setMinimum(-360); ui->rotate->setMaximum(360);
    ui->zoom->setMinimum(-10); ui->zoom->setMaximum(10);

    //get
    connect(ui->paintwidget, SIGNAL(clearTrans()),
            this, SLOT(clearSpinbox()));

    //emit
    connect(this, SIGNAL(newW2W()),
            ui->paintwidget, SLOT(newPainting()));
    connect(this, SIGNAL(saveW2W()),
            ui->paintwidget, SLOT(savePainting()));
    connect(this, SIGNAL(changeCurrentShape(Shape::shape_code)),
            ui->paintwidget, SLOT(setCurrentShape(Shape::shape_code)));
    connect(this, SIGNAL(changeCurrentColor(Shape::color_code)),
            ui->paintwidget, SLOT(setCurrentColor(Shape::color_code)));
    connect(this, SIGNAL(changeCurrentThick(Shape::thick_code)),
            ui->paintwidget, SLOT(setCurrentThick(Shape::thick_code)));
    connect(this, SIGNAL(deleteW2W()),
            ui->paintwidget, SLOT(deleteNode()));
    connect(this, SIGNAL(orderW2W(int)),
            ui->paintwidget, SLOT(orderChange(int)));
    connect(this, SIGNAL(currentK(int)),
            ui->paintwidget, SLOT(setCurrentK(int)));
    connect(this, SIGNAL(fillW2W()),
            ui->paintwidget, SLOT(fillStart()));
    connect(this, SIGNAL(clipW2W()),
            ui->paintwidget, SLOT(clipStart()));
    connect(this, SIGNAL(clearScreen()),
            ui->paintwidget, SLOT(clearCurrentScreen()));
    connect(this, SIGNAL(updownW2W(int)),
            ui->paintwidget, SLOT(startUpdown(int)));
    connect(this, SIGNAL(leftrightW2W(int)),
            ui->paintwidget, SLOT(startLeftright(int)));
    connect(this, SIGNAL(rotateW2W(int)),
            ui->paintwidget, SLOT(startRotate(int)));
    connect(this, SIGNAL(zoomW2W(int)),
            ui->paintwidget, SLOT(startZoom(int)));
    connect(this, SIGNAL(show3dW2W()),
            ui->paintwidget, SLOT(showThreeD()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//---------------------------------------------------------------------------------------------------------------------------------
//private slots

void MainWindow::on_actionNew_triggered()
{
    emit newW2W();
}

void MainWindow::on_actionSave_triggered()
{
    emit saveW2W();
}

void MainWindow::on_actionLine_triggered()
{
    emit changeCurrentShape(Shape::LINE);
}

void MainWindow::on_actionCurve_triggered()
{
    emit changeCurrentShape(Shape::CURVE);
}

void MainWindow::on_actionRect_triggered()
{
    emit changeCurrentShape(Shape::RECT);
}

void MainWindow::on_actionPoly_triggered()
{
    emit changeCurrentShape(Shape::POLY);
}

void MainWindow::on_actionCircle_triggered()
{
    emit changeCurrentShape(Shape::CIRCLE);
}

void MainWindow::on_actionEllip_triggered()
{
    emit changeCurrentShape(Shape::ELLIP);
}

void MainWindow::on_actionThreeD_triggered()
{
    emit show3dW2W();
}

void MainWindow::on_pushButton_black_clicked()
{
    emit changeCurrentColor(Shape::BLACK);
}

void MainWindow::on_pushButton_red_clicked()
{
    emit changeCurrentColor(Shape::RED);
}

void MainWindow::on_pushButton_green_clicked()
{
    emit changeCurrentColor(Shape::GREEN);
}

void MainWindow::on_pushButton_blue_clicked()
{
    emit changeCurrentColor(Shape::BLUE);
}

void MainWindow::on_pushButton_thin_clicked()
{
    emit changeCurrentThick(Shape::THIN);
}

void MainWindow::on_pushButton_medium_clicked()
{
    emit changeCurrentThick(Shape::MEDIUM);
}

void MainWindow::on_pushButton_heavy_clicked()
{
    emit changeCurrentThick(Shape::HEAVY);
}

void MainWindow::on_pushButton_deletenode_clicked()
{
    emit deleteW2W();
}

void MainWindow::on_curveorder_currentIndexChanged(int index)
{
    emit orderW2W(index);
    emit currentK(index + 1);
}

void MainWindow::on_pushButton_fill_clicked()
{
    emit fillW2W();
}

void MainWindow::on_pushButton_clip_clicked()
{
    emit clipW2W();
}

void MainWindow::on_pushButton_clear_clicked()
{
    emit clearScreen();
}

void MainWindow::on_updown_valueChanged(int arg)
{
    emit updownW2W(arg);
}

void MainWindow::on_leftright_valueChanged(int arg)
{
    emit leftrightW2W(arg);
}

void MainWindow::on_rotate_valueChanged(int arg)
{
    emit rotateW2W(arg);
}

void MainWindow::on_zoom_valueChanged(int arg)
{
    emit zoomW2W(arg);
}

void MainWindow::clearSpinbox() {
    ui->updown->setValue(0);
    ui->leftright->setValue(0);
    ui->rotate->setValue(0);
    ui->zoom->setValue(0);
}
