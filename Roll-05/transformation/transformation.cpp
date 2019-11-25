#include "transformation.hpp"
#include <cmath>
#include <vector>

static int rnd(double x){
    if(x>=0) return static_cast<int>(x+0.5);
    return static_cast<int>(-(-x+0.5));
}

static double pi = 3.141592;

mat_3x1 translate(point pt){
    double mat[3][3] =  {{1, 0, tx},
                         {0, 1, ty},
                         {0, 0, 0 }};

    double x = static_cast<double>(pt.x);
    double y = static_cast<double>(pt.y);
    double col_mat[3][1] = {{x}, {y}, {1}};

    return (mat_3x3(mat)*mat_3x1(col_mat));
}

mat_3x1 scale(point pt){
    double mat[3][3] = {{sx, 0, 0},
                        {0, sy, 0},
                        {0,  0, 1}};

    double x = static_cast<double>(pt.x);
    double y = static_cast<double>(pt.y);
    double col_mat[3][1] = {{x}, {y}, {1}};

    return (mat_3x3(mat)*mat_3x1(col_mat));
}

mat_3x1 rotate_about_pivot(point pt){
    double rad_ang = pi * ang/180;

    double neg_trans_mat[3][3] = {{1, 0, -tx},
                                  {0, 1, -ty},
                                  {0, 0,  1 }};

    double rot_mat[3][3] = {{cos(rad_ang), -sin(rad_ang), 0},
                            {sin(rad_ang),  cos(rad_ang), 0},
                            {0           ,  0           , 1}};

    double pos_trans_mat[3][3] = {{1, 0, tx},
                                  {0, 1, ty},
                                  {0, 0, 1 }};

    double x = static_cast<double>(pt.x);
    double y = static_cast<double>(pt.y);
    double col_mat[3][1] = {{x}, {y}, {1}};

    return ((mat_3x3(pos_trans_mat)*mat_3x3(rot_mat)*mat_3x3(neg_trans_mat))*mat_3x1(col_mat));
}
void reflect_about_the_line(point a, point b, std::vector<line> &l_list){

    double neg_trans_mat[3][3] = {{1, 0, -tx},
                                  {0, 1, -ty},
                                  {0, 0,  1 }};

    double pos_trans_mat[3][3] = {{1, 0, tx},
                                  {0, 1, ty},
                                  {0, 0, 1 }};

    double y_sq = static_cast<double>((b.y-a.y)*(b.y-a.y));
    double x_sq = static_cast<double>((b.x-a.x)*(b.x-a.x));

    double hypo = sqrt(y_sq+x_sq);
    double sin_theta = static_cast<double>(b.y-a.y)/hypo;
    double cos_theta = static_cast<double>(b.x-a.x)/hypo;

    double aclk_rot_mat[3][3] = {{cos_theta ,  sin_theta, 0},
                                 {-sin_theta,  cos_theta, 0},
                                 {0         ,  0        , 1}};

    double clk_rot_mat[3][3] = {{cos_theta , -sin_theta, 0},
                                 {sin_theta ,  cos_theta, 0},
                                 {0         ,  0        , 1}};


    double x,y;
    for(auto &l:l_list){
        //reflect pt a
        x = static_cast<double>(l.a.x);
        y = static_cast<double>(l.a.y);

        double pt_mat_a[3][1] = {{x},{y},{1}};
        mat_3x1 temp_pt_a = mat_3x3(aclk_rot_mat)*mat_3x3(neg_trans_mat)*mat_3x1(pt_mat_a);

        pt_mat_a[0][0] = temp_pt_a.arr[0][0];
        pt_mat_a[1][0] = -temp_pt_a.arr[1][0];

        mat_3x1 final_pt_a = mat_3x3(pos_trans_mat)*mat_3x3(clk_rot_mat)*mat_3x1(pt_mat_a);

        l.a = {rnd(get_x(final_pt_a)),rnd(get_y(final_pt_a))};
/*****************************************************************************************/
        //reflect point b
        x = static_cast<double>(l.b.x);
        y = static_cast<double>(l.b.y);

        double pt_mat_b[3][1] = {{x},{y},{1}};
        mat_3x1 temp_pt_b = mat_3x3(aclk_rot_mat)*mat_3x3(neg_trans_mat)*mat_3x1(pt_mat_b);

        pt_mat_b[0][0] = temp_pt_b.arr[0][0];
        pt_mat_b[1][0] = -temp_pt_b.arr[1][0];

        mat_3x1 final_pt_b = mat_3x3(pos_trans_mat)*mat_3x3(clk_rot_mat)*mat_3x1(pt_mat_b);

        l.b = {rnd(get_x(final_pt_b)),rnd(get_y(final_pt_b))};
    }
}

