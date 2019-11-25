#include<QColor>
#include<QImage>

extern int box_size;

QRgb get_col(QImage&, int, int);
void fill_col(QImage&, int, int, QRgb);
void boundaryFill(int, int, QRgb, QRgb, QImage&);
void floodFill(int, int, QRgb, QRgb, QImage&);
