#include "matrix.hpp"
#include "line_draw.hpp"

extern double tx,ty,sx,sy,ang;

mat_3x1 translate(point pt);
mat_3x1 scale(point pt);
mat_3x1 rotate_about_pivot(point pt);
void reflect_about_the_line(point a,point b,std::vector<line> &l_list);
