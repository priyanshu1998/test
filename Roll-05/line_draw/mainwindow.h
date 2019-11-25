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
    void Mouse_Pressed();
    void set_mini_box(int =10);


private slots:
    void on_show_axes_clicked();
    void on_lineEdit_returnPressed();
    void simple_draw_clicked();
    void DDA_clicked();
    void Bres_clicked();
    void set_point1();
    void set_point2();


private:
    Ui::MainWindow *ui;
    point p1,p2;
    line obj;
    int mini_box = 10;
    void mark_point(QImage&, int,int, QRgb);
    void plot_points(std::vector<point>&,QRgb);


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void make_table(QImage&);


};

#endif // MAINWINDOW_H
