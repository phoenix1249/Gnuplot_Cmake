#include "../include/roblib.h"

using namespace Eigen;

MatrixXd f(MatrixXd & x){
    MatrixXd x_dot(x.rows(),x.cols());
    x_dot << 0,1,2,0;
    return x_dot;
}

int main(int argc, char **argv){
    Plot plot;

    double r(10),g(9.81), dt(0.005);
    double ech = 5;
    MatrixXd x(1,4);
    x<< r,0,0,0;
    
    plot.set_x_limit(r-ech,r+ech);
    plot.set_y_limit(-ech,ech);
    double t(0);
    while (t<1){
        plot.clear();
        t+=dt;
        x = x + dt* (0.25*f(x)+0.75*(x+dt*(2/3)*f(x))); //Runge Kutta
        plot.draw_tank(x(0),x(2),0,"'blue'");
        usleep(100000);
        plot.show();
    }
    return 0;
}