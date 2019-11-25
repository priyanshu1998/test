#include <vector>

struct point{
    int x,y;
};

class ellipse{
    private:
        void setEllipse_points(std::vector<point>&, int, int);
    public:
        point C;
        int rx,ry;

        std::vector<point> simpEllip_draw();
        std::vector<point> midpt_Ellip_draw();
};
