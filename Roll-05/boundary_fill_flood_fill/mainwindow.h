#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <QObject>
#include <QLineEdit>
#include <QColor>
#include <QImage>
#include "line_draw.hpp"
#include "color_fill.h"
#include <vector>
#include <chrono>

using namespace std::chrono;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT //this macro must appear in the private section of a class definition that declares its own signals and slots or that uses other services provided by Qt's meta-object system

public slots:
    void showMousePosition(QPoint&);
    void Mouse_Pressed_draw();          //similiar to mouse pressed but draws a staight line line between the current point and previous point(no line is drawn for the first point).
    void set_mini_box(int);
    void boundary_fill_clicked();
    void flood_fill_clicked();


private slots:
    void on_show_axes_clicked();
    void on_lineEdit_returnPressed();
    void Bres_clicked();
    void reset_pts();
    void join_ends();


private:
    Ui::MainWindow *ui;
    point prev_p,start_p,curr_p;
    line obj;
    int mini_box = 7;

    void mark_point(int,int, QRgb);
    void plot_points(std::vector<point>&,QRgb);


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void make_table();
    void make_box_grid();
    //QRgb get_col(int, int);
    bool is_first_pt = 1;
    QImage img;
    QRgb prev_col = qRgb(0,0,0);

    //friend void boundaryFill(int, int, QRgb, QRgb, QImage&);
    //friend void floodFill(int, int, QRgb, QRgb, QImage&);
};

#endif // MAINWINDOW_H
