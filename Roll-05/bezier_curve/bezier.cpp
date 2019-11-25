#include "bezier.hpp"
#include <QtDebug>

using namespace two_D;



static double pow(double base, int power){
    double sol = 1;
    while(power--){
        sol*=base;
    }
    return sol;
}

static double C(int n, int k) {
    double res = 1;
    for (int i = 1; i <= k; ++i)
        res = res * (n - k + i) / i;
    return (res + 0.01);
}

point::point(){
    x = 0;
    y = 0;
}

point::point(double x,double y){
    this->x = x;
    this->y = y;
}

void point::mark_point(QImage &img,QRgb col)
{
    this->round();
    int X = static_cast<int>(x)*mini_box+350;
    int Y = 350-static_cast<int>(y)*mini_box;
    //qDebug()<<X<<" "<<Y;

    int r = (mini_box)/2;

    for(int i = -r; i <= r ;i++){
        for(int j = -r; j<= r;j++){
            if(X+j<700 && X+j>0 && Y+i<700 && Y+i>0){
                  img.setPixelColor(X+j,Y+i,col);
             }
        }
    }
}

void point::round(){
    if(x>0) x+=0.5;
    else    x-=0.5;
    if(y>0) y+=0.5;
    else    y-=0.5;
}

point point::operator*(double c){
    return {x*c,y*c};
}

point point::operator+(const point &operand){
    return point(this->x+operand.x ,this->y +operand.y);
}



QImage bezier::plot_bezier(int x,int y,QImage img){
    std::vector<two_D::point> co_efficient;

    p.push_back({static_cast<double>(x),static_cast<double>(y)});
    for(int k=0;k<=n;k++){
        co_efficient.push_back(p[k]*C(n,k));
    }

    for(double u=0;u<=1;u+=0.0001){
        point pt(0,0);
        for(int k=0;k<=n;k++){
            pt = pt + (co_efficient[k]*pow(u,k)*pow(1-u,n-k));
        }
        pt.mark_point(img,qRgb(0,0,255));
    }
    n++;
    return img;
}

void bezier::clear_point_set(){
    p.clear();
    n = 0;
}





