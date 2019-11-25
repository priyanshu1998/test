#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <QObject>
#include <QLineEdit>
#include <QColor>
#include <QImage>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT //this macro must appear in the private section of a class definition that declares its own signals and slots or that uses other services provided by Qt's meta-object system

public slots:
    void Mouse_Pressed();
    void showMousePosition(QPoint& pos);
    void set_mini_box(int =10);


private slots:
    void on_show_axes_clicked();
    //void setText(const QString &);
    //void update_text_box(int val);
    //void update_slide_bar(int val);

    //void on_Draw_clicked();

    //void on_set_point1_clicked();

    //void on_set_point2_clicked();


    void on_lineEdit_returnPressed();

private:
    Ui::MainWindow *ui;
    QPoint p1,p2;
    int mini_box = 10;
    void mark_point(int,int);


public:
    //explicit MainWindow(QWidget *parent = 0);// explicit keyword makes this constructor ineligible for implicit conversions
    MainWindow(QWidget *parent = nullptr); //C++11 std does the required pointer casting.
    ~MainWindow();
    void make_table(QImage&);
    //void fill(QImage&,int,int);

};

#endif // MAINWINDOW_H


/*NOTES:
 * By default, C++ will treat any constructor as an implicit conversion operator.
 *
 *
 * For more info refer to : https://www.learncpp.com/cpp-tutorial/9-13-converting-constructors-explicit-and-delete/
 */
