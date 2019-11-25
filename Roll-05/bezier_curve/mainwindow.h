#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <QObject>
#include <QLineEdit>
#include <QColor>
#include <QImage>
#include "bezier.hpp"
#include "line_draw.hpp"
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
    void click_func_bezier();


private slots:
    void on_show_axes_clicked();
    void on_lineEdit_returnPressed();
    void Bres_clicked();
    void reset_pts();
    //void load_curve();


private:
    Ui::MainWindow *ui;
    point prev_p={0,0},start_p,curr_p;
    line obj;
    void mark_point(QImage&, int,int, QRgb);
    void plot_points(std::vector<point>&,QRgb);
    QImage img;


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void make_table();
    void make_box_grid();
    bool is_first_pt = 1;
    bezier ob;
    //Bezier curve;
};

#endif // MAINWINDOW_H
