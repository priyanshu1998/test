#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <QObject>
#include <QLineEdit>
#include <QColor>
#include <QImage>
#include "ellipse_draw.hpp"
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
    void simple_ellipse_click();
    void ellipse_midpoint_click();


private slots:
    void on_show_axes_clicked();
    void on_lineEdit_returnPressed();

    void set_the_center();

private:
    Ui::MainWindow *ui;
    QPoint p1,p2;
    ellipse obj;
    int mini_box = 10;
    void mark_point(QImage&, int,int);
    void display_points(std::vector<point>&);


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void make_table(QImage&);


};

#endif // MAINWINDOW_H
