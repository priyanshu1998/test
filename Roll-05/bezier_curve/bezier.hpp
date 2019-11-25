#include <vector>
#include <QImage>

extern int mini_box;

namespace two_D {
    class point{
    public:
        double x,y;

    public:
        point();
        point(double x,double y);

        point operator*(double c);
        point operator+(const point &operand);

        void mark_point(QImage &img,QRgb col);
        void round();
    };
}

class bezier{
private:
    int n = 0;
    std::vector<two_D::point> p;

public:
    QImage plot_bezier(int x, int y, QImage img);
    void clear_point_set();
};
