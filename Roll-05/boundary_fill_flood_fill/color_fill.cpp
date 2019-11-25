#include "color_fill.h"

QRgb get_col(QImage &img, int x, int y){
    int X = x*box_size+350;
    int Y = 350-y*box_size;
    return img.pixel(X,Y);
}

void fill_col(QImage &img, int x, int y, QRgb col){
    int X = x*box_size+350;
    int Y = 350-y*box_size;

    int r = (box_size)/2;

    for(int i = -r; i <= r ;i++){
        for(int j = -r; j<= r;j++){
            if(X+j<700 && X+j>0 && Y+i<700 && Y+i>0){
                  img.setPixelColor(X+j,Y+i,col);
             }
        }
    }
}

void boundaryFill(int x, int y, QRgb fill, QRgb boundary, QImage& img){
    QRgb current = get_col(img, x, y);

    if (current!=boundary && current != fill){
        fill_col(img, x, y, fill);
        boundaryFill(x+1, y, fill, boundary, img);
        boundaryFill(x-1, y, fill, boundary, img);
        boundaryFill(x, y-1, fill, boundary, img);
        boundaryFill(x, y+1, fill, boundary, img);
    }
}

void floodFill(int x, int y, QRgb fill, QRgb old_c, QImage &img){
    QRgb current = get_col(img,x, y);
    if(current == old_c || current == qRgb(40, 180, 99)){ //qRgb(40, 180, 99) is the color used to mark axis adding this allow filling across axis
        fill_col(img, x, y, fill);
        floodFill(x+1, y, fill, old_c,img);
        floodFill(x-1, y, fill, old_c,img);
        floodFill(x, y-1, fill, old_c,img);
        floodFill(x, y+1, fill, old_c,img);
    }
}
