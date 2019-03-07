#include "../include/roblib.h"

using namespace Eigen;

MatrixXd f(MatrixXd & x, MatrixXd u){
    MatrixXd x_dot(x.rows(),x.cols());
    x_dot << u(0) * cos(x(2)),u(0)*cos(x(2)),u(1);
    return x_dot;
}

int main(int argc, char **argv){
    Plot plot;

    MatrixXd u(1,2);
    MatrixXd x(1,3);
    x<< 0,0,1;
    
    plot.set_x_limit(-0.3,0.3);
    plot.set_y_limit(-0.3,0.3);

    double dt(0.01);
    double t(0);
    while (t<1){
        plot.clear();
        t+=dt;
        u<<1,1;
        x = x+dt*f(x,u);
        plot.draw_tank(x(0),x(1),x(2),"'blue'",0.05);
        usleep(100000);
        plot.show();
    }
    return 0;
}