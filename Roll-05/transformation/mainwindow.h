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
#include "transformation.hpp"
#include <vector>

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
    //void set_the_center();

    void translate_click();
    void rotate_click();
    void scale_click();

    void set_first_pt_true();
    void set_the_pivot();

    void reflect_about_line_click();

private slots:
    void on_show_axes_clicked();
    void on_lineEdit_returnPressed();
    void Bres_clicked();
    void reset_pts();
    void join_ends();


private:
    Ui::MainWindow *ui;
    point prev_p,start_p,curr_p,pivot_p = {0,0};
    line l_obj;

    int mini_box = 7;
    void mark_point(QImage&, int,int, QRgb);
    void plot_points(std::vector<point>&,QRgb);
    QImage img;


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void make_table();
    void make_box_grid();
    void replot();
    bool is_first_pt = 1;

    std::vector<line> l_obj_list;
};
#endif // MAINWINDOW_H
