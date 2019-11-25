#include <vector>

#ifndef POINTDEF
#define POINTDEF
struct point{
    int x = 0;
    int y = 0;
};
#endif

#ifndef LINEDEF
#define LINEDEF
class line{
    std::vector<point> Bres_pos_m();
    std::vector<point> Bres_neg_m();
    
    public:
        point a,b;
        line(point, point);
        std::vector<point> lineSimple();
        std::vector<point> lineDDA();
        std::vector<point> lineBres();
};
#endif
