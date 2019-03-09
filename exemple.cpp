#include "include/roblib.h"
#include <string>
#include <iostream>


int main(int argc, char **argv){
    Plot plt;
    //plt.draw_ellipse(point(0,0),2,1,"'red'");
    //plt.draw_circle(1,0.5,1,"'blue'");
    plt.set_x_limit(-10,10);
    plt.set_y_limit(-10,10);
    for (int i = 0;i<360;i++){
        plt.clear();
        plt.draw_tank(1,0.5,i,"'blue'");
        plt.draw_circle(-2,1,5,"'red'");
        plt.draw_sailboat(0,0,i,0.1,0.2,40,1);
        //usleep(100000);
        plt.show();
    }
    return 0;
}