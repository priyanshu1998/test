#include <vector>
struct point{
    int x = 0;
    int y = 0;
};


class curve{
    void CirclePlotPoints(std::vector<point>&, int, int);

    public:
        point C = {0,0};
        int r = 0;
        //CS_point(point, int);
        std::vector<point> circleSimple();
        std::vector<point> bresMidCircle();
        //std::vector<point> ellipse();
};
