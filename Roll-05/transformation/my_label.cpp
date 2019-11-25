#include "my_label.h"

my_label::my_label(QWidget *parent)
    :QLabel(parent)
{
    this->setMouseTracking(false);
    /*
    *If mouse tracking is enabled, the widget receives mouse move events even if no buttons are pressed.
    *If mouse tracking is disabled (the default), the widget only receives mouse move events when at least one mouse button is pressed while the mouse is being moved.
    */
}

void my_label::mouseMoveEvent(QMouseEvent *ev)
{
    QPoint mouse_pos=ev->pos();
    /*
      Qpoint MouseEvent::pos() const; in our case ev->pos()
      Returns the position of the mouse cursor, relative to the widget that received the event.
    */

    if(mouse_pos.x()<=this->size().width() && mouse_pos.y()<=this->size().height()){
        if(mouse_pos.x()>0 && mouse_pos.y()>0){
            emit sendMousePosition(mouse_pos);
        }
    }

    /*
      Returns the x position of the mouse cursor, relative to the widget that received the event.
           int QMouseEvent::x() const; Returns the x position of the mouse cursor, relative to the widget that received the event.
           int QMouseEvent::y() const; Returns the y position of the mouse cursor, relative to the widget that received the event.
    */


    //redefined mouseMoveEvent instead of QWidget's function implementaion.

}

void my_label::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button()==Qt::LeftButton){
        this->x=ev->x();
        this->y=ev->y();
        emit Mouse_Pos();
    }
    /*
     QMouseEvent::button() const; Returns the mouse button of the mouse event.
    */
}
