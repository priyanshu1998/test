#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QImage>
#include <QColor>
#include <QMouseEvent>
#include <QPaintDevice>
#include <QPoint>

void MainWindow::make_table(QImage &img){

    int h  = mini_box/2;


    for(int i=350-h;i<=350+h;i++){
        for(int j=0; j<700;j++){
            img.setPixelColor(i,j,qRgb(40, 180, 99));
            img.setPixelColor(j,i,qRgb(40, 180, 99));
        }
    }//create y,x axis.


    for(int i=h;i<350;i+=mini_box){
        for(int j=0;j<700;j++){
            img.setPixelColor(350+i,j,qRgb(25,111,61));
            img.setPixelColor(350-i,j,qRgb(25,111,61));
            img.setPixelColor(j,350+i,qRgb(25,111,61));
            img.setPixelColor(j,350-i,qRgb(25,111,61));
        }
    }
}//normal O(n_sq) algo.

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)//call for construction of base class members
{
    ui->setupUi(this);

    ui->x_axis->hide(); //hides x-axis
    ui->y_axis->hide(); //hides y-axis

    QImage img=QImage(700,700,QImage::Format_RGB32);
    img.fill(0);
    make_table(img);
    ui->frame->setPixmap(QPixmap::fromImage(img));

    connect(ui->frame,SIGNAL(sendMousePosition(QPoint&)),this,SLOT(showMousePosition(QPoint&)));
    connect(ui->frame,SIGNAL(Mouse_Pos()),this,SLOT(Mouse_Pressed()));

    connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),this,SLOT(set_mini_box(int)));
    connect(ui->lineEdit,SIGNAL(returnPressed()),this,SLOT(on_lineEdit_returnPressed()));
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(circleSimple_clicked()));
    connect(ui->pushButton_1,SIGNAL(clicked()),this,SLOT(bresMidCircle_clicked()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(set_the_center()));
}//constructor for MainWindow class

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mark_point(QImage &img,int x,int y)
{

    int X = x*mini_box+350;
    int Y = 350-y*mini_box;


    int r = (mini_box-1)/2;

    for(int i = -r; i <= r ;i++){
        for(int j = -r; j<= r;j++){
            if(X+j<700 && X+j>0 && Y+i<700 && Y+i>0){
                  img.setPixelColor(X+j,Y+i,qRgb( 183, 149, 11 ));
             }
        }
    }
}




void MainWindow::showMousePosition(QPoint &pos)
{
    int offset = mini_box/2;
    ui->mouse_movement->setText(" X : "+QString::number((pos.x()>350)?((pos.x()-350+offset)/mini_box):((pos.x()-350-offset)/mini_box))+", Y : "+QString::number((pos.y()>350)?((350 - pos.y() - offset)/mini_box):((350 - pos.y() + offset)/mini_box)));
}

void MainWindow::Mouse_Pressed()
{
    int offset = mini_box/2;

    QImage img=QImage(700,700,QImage::Format_RGB32);
    img.fill(0);
    make_table(img);

    int X = (ui->frame->x > 350)?((ui->frame->x - 350 + offset)/mini_box):((ui->frame->x - 350 - offset)/mini_box);
    int Y = (ui->frame->y > 350)?((350 - ui->frame->y - offset)/mini_box):((350 - ui->frame->y + offset)/mini_box);


    ui->mouse_press->setText(" X : "+QString::number(X)+", Y : "+QString::number(Y));
    obj.C.x = X;
    obj.C.y = Y;


    mark_point(img,X,Y);
    //point(ui->frame->x,ui->frame->y,3);
    ui->x_axis->move(0,ui->frame->y);
    ui->y_axis->move(ui->frame->x,0);

    ui->frame->setPixmap(QPixmap::fromImage(img));
}


void MainWindow::on_show_axes_clicked()
{
    if(ui->show_axes->isChecked())
    {
        ui->x_axis->show();
        ui->y_axis->show();
    }
    else{
        ui->x_axis->hide();
        ui->y_axis->hide();
    }
}

void MainWindow::set_mini_box(int val){
    mini_box = val;
    QImage img=QImage(700,700,QImage::Format_RGB32);
    img.fill(0);
    make_table(img);
    ui->frame->setPixmap(QPixmap::fromImage(img));

//    std::vector<QPoint>pts = obj.lineBres();
//    display_points(pts);
}



void MainWindow::on_lineEdit_returnPressed()
{
    mini_box = ui->lineEdit->text().toInt();
    set_mini_box(mini_box);
}

void MainWindow::display_points(std::vector<point> &set_of_points){
    QImage img(700,700,QImage::Format_RGB32);
    img.fill(0);

    make_table(img);
    mark_point(img,obj.C.x,obj.C.y);
    for(auto pt:set_of_points){
        mark_point(img, pt.x, pt.y);           //point translation required
    }
    ui->frame->setPixmap(QPixmap::fromImage(img));
}



void MainWindow::circleSimple_clicked(){
    //obj.C.x = ui->x1->text().toInt();
    //obj.C.y = ui->y1->text().toInt();
    obj.r = ui->radius->text().toInt();

    std::vector<point> onCurve = obj.circleSimple();

    display_points(onCurve);
}


void MainWindow::bresMidCircle_clicked(){
    //obj.C.x = ui->x1->text().toInt();
    //obj.C.y = ui->y1->text().toInt();
    obj.r = ui->radius->text().toInt();

    std::vector<point> onCurve = obj.bresMidCircle();

    display_points(onCurve);
}

void MainWindow::set_the_center(){

}
