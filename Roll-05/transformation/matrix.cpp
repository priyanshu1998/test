#include "matrix.hpp"

double get_x(mat_3x1 ob){
    return ob.arr[0][0];
}

double get_y(mat_3x1 ob){
    return ob.arr[1][0];
}



mat_3x1::mat_3x1(double arr[3][1]){
    for(int i=0;i<3;i++){
        this->arr[i][0] = arr[i][0];
    }
}

mat_3x3::mat_3x3(double arr[3][3]){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                this->arr[i][j] = arr[i][j];
            }
        }
    }

mat_3x3 operator*(const mat_3x3 &ob1, const mat_3x3 &ob2){
        double res[3][3] = {{0,0,0},{0,0,0},{0,0,0}};

        for(int p=0;p<3;p++){
            for(int q=0;q<3;q++){
                for(int idx=0;idx<3;idx++){
                    res[p][q] += ob1.arr[p][idx] * ob2.arr[idx][q];
                }
            }
        }
        return mat_3x3(res);
}

mat_3x1 operator*(const mat_3x3 &ob1, const mat_3x1 &ob2){
    double res[3][1]={{0},{0},{0}};

    for(int p=0; p<3; p++){
        for(int q = 0; q <3;q++){
            res[p][0] += ob1.arr[p][q] * ob2.arr[q][0];
        }
    }
    return mat_3x1(res);
}
