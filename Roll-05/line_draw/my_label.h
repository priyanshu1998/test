#ifndef MY_LABEL_H
#define MY_LABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QEvent>

class my_label : public QLabel
{
    Q_OBJECT//this macro must appear in the private section of a class definition that declares its own signals and slots or that uses other services provided by Qt's meta-object system


public:
    //explicit my_label(QWidget *parent = 0);
    my_label(QWidget *parent = nullptr);
    int x,y;

protected:
    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
signals:
    void sendMousePosition(QPoint&);
    void Mouse_Pos();
};

#endif // MY_LABEL_H
