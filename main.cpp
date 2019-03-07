#include "include/gnuplot-iostream.h"
#include <boost/tuple/tuple.hpp>
#include <iostream>
#include <vector>
#include <string>

typedef std::pair<double, double> point;

int main(int argc, char **argv){
    Gnuplot gp1;
    Gnuplot gp2;

    std::vector<point> plot1;
    std::vector<point> plot2;
    plot1.push_back(point(1,1));
    plot1.push_back(point(0,0));
    plot1.push_back(point(0.5,0.5));
    plot2.push_back(point(2,1));

    std::vector<std::vector<point>> b;
    b.push_back(plot1);
    b.push_back(plot2);

    int a = 'red';

    gp1<<"set linetype 12 linecolor rgb "<<a<<std::endl;
    gp1<<"plot '-'with linespoint ls 12 \n";
    gp1.send1d(plot1);
    gp1.clearTmpfiles();
    gp1<<"plot '-',";
    gp1<<" '-' with points pointtype "<<5<<std::endl;

    gp1.send1d(plot1);
    gp1.send1d(plot2);

    gp2<<"plot";
    gp2<<gp2.file1d(b[0])<<" with linespoint ls 12 notitle,";
    gp2<<gp2.file1d(b[1])<<" with points pointtype "<<-1<<" notitle\n";
    return 0;
}