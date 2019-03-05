#include "Plot.h"
#include <string>
#include <iostream>

int main(int argc, char **argv){
    Plot plt;
    //plt.draw_ellipse(point(0,0),2,1,"'red'");
    //plt.draw_circle(1,0.5,1,"'blue'");
    plt.set_x_limit(-3,3);
    plt.set_y_limit(-3,3);
    for (int i = 0;i<360;i++){
        plt.clear();
        plt.draw_car(1,0.5,i,"'blue'");
        usleep(100000);
        plt.show();
    }
    return 0;
}