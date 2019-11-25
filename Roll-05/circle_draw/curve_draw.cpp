#include "curve_draw.hpp"
#include <cmath>

#define PI  3.141592


void curve::CirclePlotPoints(std::vector<point>&onCurve, int x_offset, int y_offset){
    onCurve.push_back({C.x + x_offset, C.y + y_offset});
    onCurve.push_back({C.x - x_offset, C.y + y_offset});
    onCurve.push_back({C.x + x_offset, C.y - y_offset});
    onCurve.push_back({C.x - x_offset, C.y - y_offset});
    onCurve.push_back({C.x + y_offset, C.y + x_offset});
    onCurve.push_back({C.x - y_offset, C.y + x_offset});
    onCurve.push_back({C.x + y_offset, C.y - x_offset});
    onCurve.push_back({C.x - y_offset, C.y - x_offset});
}

std::vector<point> curve::circleSimple(){
   	std::vector<point> onCurve;
    std::vector<std::vector<char>>is_marked(r+1,std::vector<char>(r+1,false));
    //double tuner = 40;
    double x_offset, y_offset;

    x_offset = r;
    y_offset = 0;

    double theta = 0;

    is_marked[r][0] = true;
    bool add_flag = 1;

    while(x_offset >= y_offset){
        if(add_flag) {
            CirclePlotPoints(onCurve,static_cast<int>(x_offset+0.5),static_cast<int>(y_offset+0.5));
            add_flag = 0;
        }

        //double chng = tuner / (r * cos(PI*theta/180));

        // if(fabs(chng) < 0.001){
        //     chng = 0.001;
        // }
        //theta += chng;

        theta += 1/static_cast<double>(r);
        //qDebub()<<theta;

        x_offset = (r*cos(PI * theta/180));
        y_offset = (r*sin(PI * theta/180)); 


        if(is_marked[static_cast<int>(x_offset+0.5)][static_cast<int>(y_offset+0.5)] == false){
            add_flag = 1;
            is_marked[static_cast<int>(x_offset+0.5)][static_cast<int>(y_offset+0.5)] = true;
        }
    }

    return onCurve;
}


std::vector<point> curve:: bresMidCircle(){
    std::vector<point>onCurve;
    int x_offset = 0;
    int y_offset = r;

    int p = 1 - r;

    CirclePlotPoints(onCurve,x_offset, y_offset);

    while(x_offset < y_offset){
        x_offset++;
        if(p < 0){
            p += 2*x_offset+1;
        }
        else{
            y_offset--;
            p += 2*(x_offset-y_offset)+1;
        }
        CirclePlotPoints(onCurve,x_offset,y_offset);
    }
    return onCurve;
}


