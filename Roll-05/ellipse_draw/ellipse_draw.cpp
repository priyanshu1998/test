#include "ellipse_draw.hpp"
#include <vector>
#include <cmath>

#define PI 3.141592

int rnd(double x){
    if(x>=0) return static_cast<int>(static_cast<double>(x)+0.5);
    else return -static_cast<int>(static_cast<double>(-x)+0.5);
}


void ellipse:: setEllipse_points(std::vector<point> &onCurve, int x, int y){
    onCurve.push_back({C.x+x, C.y+y});
    onCurve.push_back({C.x-x, C.y+y});
    onCurve.push_back({C.x+x, C.y-y});
    onCurve.push_back({C.x-x, C.y-y});
}


std::vector<point>ellipse:: simpEllip_draw(){
    std::vector<point> onCurve;
    double theta = 0;
    double x = rx,
           y = 0;
    while(theta < 360){
        onCurve.push_back({static_cast<int>(rnd(C.x+x)), static_cast<int>(rnd(C.y+y))});
        theta += 1;

        x = (rx * cos(PI * theta/180));
        y = (ry * sin(PI * theta/180)); 
    }
    return onCurve;
}

std::vector<point>ellipse:: midpt_Ellip_draw(){
    std::vector<point> onCurve;

    int rx2 = rx*rx,
        ry2 = ry*ry,
        two_rx2 = 2*rx2,
        two_ry2 = 2*ry2;

    int p, x, y, px, py;

    x = 0;
    y = ry;
    px = 0;
    py = two_rx2 * y;

    setEllipse_points(onCurve, x, y);

    //points in first region**********************************************
    p = rnd(static_cast<double>(ry2 -(rx2*ry)) + (0.25*static_cast<double>(rx2)));

    while(px < py){
        x++;
        px += two_ry2;

        if(p < 0)
            p += ry2 + px;
        else{
            y--;
            py -= two_rx2;
            p  += ry2 + px - py;
        }
        setEllipse_points(onCurve, x, y);
    }
    //********************************************************************


    //points in second region**********************************************
    p = rnd((static_cast<double>(ry2) * (static_cast<double>(x*x + x)+0.25)) + static_cast<double>(rx2 * (y*y-2*y+1)) - static_cast<double>(rx2*ry2));
    while(y > 0){
        y--;
        py -= two_rx2;

        if(p > 0)
            p += rx2 - py;

        else{
            x++;
            px += two_ry2;
            p  += rx2 - py + px;
        }
        setEllipse_points(onCurve, x, y);
    }
    return onCurve;
}
