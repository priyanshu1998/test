class mat_3x3;
class mat_3x1;

class mat_3x1{
    public:
    double arr[3][1];

    mat_3x1(double arr[3][1]);
    friend mat_3x1 operator*(const mat_3x3 &ob1, const mat_3x1 &ob2);
};



class mat_3x3{
    public:
    double arr[3][3];

    public:
    mat_3x3(double arr[3][3]);

    friend mat_3x1 operator*(const mat_3x3 &ob1, const mat_3x1 &ob2);
    friend mat_3x3 operator*(const mat_3x3 &ob1, const mat_3x3 &ob2);
};


double get_x(mat_3x1 ob);
double get_y(mat_3x1 ob);
