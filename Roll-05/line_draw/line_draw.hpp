#include <vector>

struct point{
    int x = 0;
    int y = 0;
};

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
