#include "../include/roblib.h"

using namespace Eigen;

void draw_crank(MatrixXd & x,Plot & plot){
    double theta1(x(0));
    double theta2(x(1));
    double L1(4),L2(3);
    MatrixXd z(1,2);
    MatrixXd y(1,2);
    MatrixXd zy(2,3);

    z <<  cos(theta1),sin(theta2);
    z *= L1;

    y << cos(theta1+theta2),sin(theta1+theta2);
    y = z+L2*y;
    zy <<   0,z(0),y(0),
            0,z(1),y(1);
    plot.plot(zy,"'blue'");
}

MatrixXd f(MatrixXd x){
    MatrixXd dtheta(1,2);
    dtheta << 1,2;
    return dtheta;
}

int main(int argc, char **argv){
    Plot plot;

    MatrixXd x(1,2);
    x<< -1,1;
    
    plot.set_x_limit(-4,8);
    plot.set_y_limit(-4,8);

    double dt(0.05);
    double t(0);
    while (t<1){
        plot.clear();
        t+=dt;
        draw_crank(x,plot);
        x = x + dt*f(x);
        usleep(100000);
        plot.show();
    }
    return 0;
}