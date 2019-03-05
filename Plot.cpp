#include "Plot.h"
#include <iostream>
#include <cmath>
#include <Eigen/Dense>

Plot::Plot()
:x_min(0),x_max(0),y_min(0),y_max(0)
{
    points.reserve(1);
    colors.reserve(1);
}

Plot::~Plot()
{
    points.resize(0);
    colors.resize(0);
    gp.clearTmpfiles();
}

void Plot::clear()
{
    points.resize(0);
    colors.resize(0);
    gp.clearTmpfiles();
}


void Plot::set_x_limit(double xmin, double xmax)
{
    x_min = xmin;
    x_max = xmax;
}

void Plot::set_y_limit(double ymin, double ymax){
    y_min = ymin;
    y_max = ymax;
}

void Plot::draw_circle(point Center,double radius,std::string color)
{   
    draw_ellipse(Center.first,Center.second,radius,radius,color);
}

void Plot::draw_circle(double x,double y,double radius,std::string color)
{
    draw_ellipse(x,y,radius,radius,color);
}

void Plot::draw_ellipse(point Center,double a, double b,std::string color)
{
    draw_ellipse(Center.first,Center.second,a,b,color);
}

void Plot::draw_ellipse(double x,double y,double a,double b,std::string color)
{
    double x_,y_;
    std::vector<point> p;
    for (int i=0;i<360;i++){
        x_ = a*cos(i*PI/180)+x;
        y_ = b*sin(i*PI/180)+y;
        p.push_back(point(x_,y_));
    }
    points.push_back(p);
    colors.push_back(color);
}

void Plot::draw_car(double x,double y,double theta,std::string color)
{
    double L(1),l(0.4),h(1),Lr(0.5);
    std::vector<point> p;

    Eigen::MatrixXd M(3,10);
    M <<L, -L,    -L,    -L, -L, -l, l, L, L   , L    ,
        0,  0,  Lr/2, -Lr/2,  0,   h, h, 0, Lr/2, -Lr/2,
        1,  1,     1,      1, 1,   1, 1, 1,    1,      1;

    
    Eigen::MatrixXd R(2,3);
    R<< cos(theta * PI/180), -sin(theta * PI/180), x,
        sin(theta * PI/180),  cos(theta * PI/180), y;


    //std::cout<<M<<"\n"<<R<<std::endl;
    
    Eigen::MatrixXd RM(2,10);

    RM = R*M;

    for (int i=0;i<10;i++){
        p.push_back( point(RM(0,i),RM(1,i)));
    }

    points.push_back(p);
    colors.push_back(color);

}


void Plot::show(){
    gp.clearTmpfiles();
    gp<<"set yrange ["<<y_min<<":"<<y_max<<"]\n";
    gp<<"set xrange ["<<x_min<<":"<<x_max<<"]\n";
    
    for (int i=0;i<colors.size();i++){
        gp<<"set linetype "<<i+1<<"linecolor rgb "<<colors[i]<<std::endl;
        
    }

    
    gp<<"plot";

    /*for (int i=0;i<colors.size();i++){
        if (i!=colors.size()-1)
        {
            gp<<gp.file1d(points[i])<<" with linespoint ls "<<i+1<<" notitle ,";
        }else{
            gp<<gp.file1d(points[i])<<" with linespoint ls "<<i+1<<" notitle\n";
        }
    }*/

    for (int i=0;i<colors.size();i++){
        if (i!=colors.size()-1)
        {
            gp<<" '-' with linespoint ls "<<i+1<<" points 0 notitle,";
        }else{
            gp<<" '-' notitle with linespoint ls "<<i+1<<" points 0\n";
        }
    }

    for (int i=0;i<colors.size();i++){
        gp.send1d(points[i]);
    }
    

}

