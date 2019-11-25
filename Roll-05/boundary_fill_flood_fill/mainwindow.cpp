#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QImage>
#include <QColor>
#include <QMouseEvent>
#include <QPaintDevice>
#include <QPoint>

int box_size = 7;

void MainWindow::make_box_grid(){
    for(int i=mini_box/2;i<350;i+=mini_box){
        for(int j=0;j<700;j++){
            img.setPixelColor(350+i,j,qRgb(25,111,61));
            img.setPixelColor(350-i,j,qRgb(25,111,61));
            img.setPixelColor(j,350+i,qRgb(25,111,61));
            img.setPixelColor(j,350-i,qRgb(25,111,61));
        }
    }
}

void MainWindow::make_table(){

    int h  = mini_box/2;


    for(int i=350-h;i<=350+h;i++){
        for(int j=0; j<700;j++){
            img.setPixelColor(i,j,qRgb(40, 180, 99));
            img.setPixelColor(j,i,qRgb(40, 180, 99));
        }
    }//create y,x axis.


    make_box_grid();
}//normal O(n_sq) algo.


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), obj({0,0},{0,0}),img(QImage(700,700,QImage::Format_RGB32))//call for construction of base class members
{
    ui->setupUi(this);

    ui->x_axis->hide(); //hides x-axis
    ui->y_axis->hide(); //hides y-axis

    img.fill(0);
    make_table();
    ui->frame->setPixmap(QPixmap::fromImage(img));

    connect(ui->frame,SIGNAL(sendMousePosition(QPoint&)),this,SLOT(showMousePosition(QPoint&)));
    connect(ui->frame,SIGNAL(Mouse_Pos()),this,SLOT(Mouse_Pressed_draw()));

    connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),this,SLOT(set_mini_box(int)));
    connect(ui->lineEdit,SIGNAL(returnPressed()),this,SLOT(on_lineEdit_returnPressed()));

    connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(reset_pts()));
    connect(ui->pushButton_5,SIGNAL(clicked()),this,SLOT(join_ends()));

    connect(ui->boundaryfill_button,SIGNAL(clicked()),this,SLOT(boundary_fill_clicked()));
    connect(ui->floodfill_button,SIGNAL(clicked()),this,SLOT(flood_fill_clicked()));
}//constructor for MainWindow class

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mark_point(int x,int y,QRgb col = qRgb( 183, 149, 11 ))
{

    int X = x*mini_box+350;
    int Y = 350-y*mini_box;
    prev_col = img.pixel(X,Y);

    int r = (mini_box)/2;

    for(int i = -r; i <= r ;i++){
        for(int j = -r; j<= r;j++){
            if(X+j<700 && X+j>0 && Y+i<700 && Y+i>0){
                  img.setPixelColor(X+j,Y+i,col);
             }
        }
    }
}



void MainWindow::showMousePosition(QPoint &pos)
{
    int offset = mini_box/2;
    ui->mouse_movement->setText(" X : "+QString::number((pos.x()>350)?((pos.x()-350+offset)/mini_box):((pos.x()-350-offset)/mini_box))+", Y : "+QString::number((pos.y()>350)?((350 - pos.y() - offset)/mini_box):((350 - pos.y() + offset)/mini_box)));
}
void MainWindow::Mouse_Pressed_draw()
{
    int offset = mini_box/2;
    int X = (ui->frame->x > 350)?((ui->frame->x - 350 + offset)/mini_box):((ui->frame->x - 350 - offset)/mini_box);
    int Y = (ui->frame->y > 350)?((350 - ui->frame->y - offset)/mini_box):((350 - ui->frame->y + offset)/mini_box);


    ui->mouse_press->setText(" X : "+QString::number(X)+", Y : "+QString::number(Y));

    curr_p = {X,Y};

    if(is_first_pt){
        start_p = curr_p;
        is_first_pt = 0;
    }
    else Bres_clicked();

    prev_p = curr_p;

    mark_point(X,Y);
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

void MainWindow::set_mini_box(int col){
    mini_box = col;
    box_size = mini_box;
    img=QImage(700,700,QImage::Format_RGB32);
    img.fill(0);
    make_table();
    ui->frame->setPixmap(QPixmap::fromImage(img));
}



void MainWindow::on_lineEdit_returnPressed()
{
    mini_box = ui->lineEdit->text().toInt();
    set_mini_box(mini_box);
}

void MainWindow::plot_points(std::vector<point> &set_of_points, QRgb col){
    for(auto pt:set_of_points){
        mark_point(pt.x, pt.y ,col);           //point translation required
    }
    set_of_points.clear();
}



void MainWindow::Bres_clicked(){
    obj.a = prev_p;
    obj.b = curr_p;


    line temp = obj;
    std::vector<point>pts = temp.lineBres();


    plot_points(pts,qRgb(255,0,0));
}

void MainWindow::reset_pts()
{
    img = QImage(700,700,QImage::Format_RGB32);
    img.fill(0);
    make_table();
    ui->frame->setPixmap(QPixmap::fromImage(img));
    start_p = {0,0};
    is_first_pt=1;
}

void MainWindow::join_ends()
{
    curr_p = start_p;
    Bres_clicked();
    is_first_pt = 1;
    ui->frame->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::boundary_fill_clicked(){
    boundaryFill(curr_p.x,curr_p.y,qRgb(0,0,255),qRgb(255,0,0),img);
    make_box_grid();
    ui->frame->setPixmap(QPixmap::fromImage(img));
    is_first_pt = 1;
}

void MainWindow::flood_fill_clicked(){
    QRgb old_color(prev_col);
    mark_point(curr_p.x,curr_p.y,prev_col);

    floodFill(curr_p.x,curr_p.y,qRgb(0,255,0),old_color,img);
    make_box_grid();
    ui->frame->setPixmap(QPixmap::fromImage(img));
    is_first_pt = 1;
}


