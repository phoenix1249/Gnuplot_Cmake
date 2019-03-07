#include "../include/roblib.h"
#include <algorithm> 
#include <iostream>
#include <cmath>
#include <Eigen/Dense>



using namespace Eigen;


///Class Plot
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
    /*std::vector<point> p;

    MatrixXd M(2,10);



    MatrixXd RM (move_motif(M,x,y,theta));

    for (int i=0;i<10;i++){
        p.push_back( point(RM(0,i),RM(1,i)));
    }

    points.push_back(p);
    colors.push_back(color);*/

}

void Plot::plot(std::vector<point> & p,std::string color){
    points.push_back(p);
    colors.push_back(color);
}

void Plot::plot(MatrixXd & M,std::string color){

    std::vector<point>p;
    for (int i = 0;i<M.cols();i++){
        p.push_back(point(M(0,i),M(1,i)));
    }

    points.push_back(p);
    colors.push_back(color);
}

void Plot::draw_tank(double x,double y,double theta,std::string color,double r){
    double L(1),l(0.4),h(1),Lr(0.5);
    MatrixXd M(2,10);
    M <<L, -L,    -L,    -L, -L, -l, l, L, L   , L    ,
        0,  0,  Lr/2, -Lr/2,  0,   h, h, 0, Lr/2, -Lr/2;
    M = r*move_motif(M,x,y,theta);

    std::vector<point> p;
    for (int i=0;i<10;i++){
        p.push_back( point(M(0,i),M(1,i)));
    }

    points.push_back(p);
    colors.push_back(color);
}

void Plot::draw_tank(double x,double y,double theta,std::string color){
    draw_tank(x,y,theta,color,1);
}

void Plot::draw_sailboat(double x,double y,double theta,double deltas,double deltar,double psi,double awind){
    MatrixXd hull(3,8);
    MatrixXd sail(3,2);
    MatrixXd rudder(3,2);
    MatrixXd R(3,3);
    MatrixXd Rs(3,3);
    MatrixXd Rr(3,3);
    
    hull << -1, 5, 7,7,5,-1,-1,-1,
            -2,-2,-1,1,2, 2,-2,-2,
            1 , 1, 1,1,1, 1, 1, 1;
    
    sail <<-7,0,
            0,0,
            1,1;
    
    rudder <<  -1,1,
                0,0,
                1,1;

    double th = theta * PI/180;

    R<< cos(th),-sin(th),x,
        sin(th), cos(th),y,
            0  ,       0,1;
    
    Rs<<cos(deltas)  ,-sin(deltas),3,
        sin(deltas)  , cos(deltas),0,
                    0,           0,1;
    
    Rr<<cos(deltar)  ,-sin(deltar),-1,
        sin(deltar)  , cos(deltar), 0,
                    0,           0, 1;

    MatrixXd Ph(R*hull);
    MatrixXd Ps(R*Rs*sail);
    MatrixXd Pr(R*Rr*rudder);

    plot(Ph,"'black'");
    plot(Ps,"'red'");
    plot(Pr,"'red'");

}

void Plot::show(){
    gp.clearTmpfiles();
    gp<<"set yrange ["<<y_min<<":"<<y_max<<"]\n";
    gp<<"set xrange ["<<x_min<<":"<<x_max<<"]\n";
    
    for (int i=0;i<colors.size();i++){
        gp<<"set linetype "<<i+1<<" linecolor rgb "<<colors[i]<<std::endl;
        
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


///Other Function

/*MatrixXd eulermat(double phi,double theta,double psi){
    MatrixXd Ad_i(3,3);
    MatrixXd Ad_j(3,3);
    MatrixXd Ad_k(3,3);

    Ad_i << 0,0, 0,
            0,0,-1,
            0,1, 0;
    
    Ad_i = phi*Ad_i;

    Ad_j << 0 ,0,1,
            0 ,0,0,
            -1,0,0;
    
    Ad_j = theta*Ad_j;

    Ad_k << 0,-1,0,
            1, 0,0,
            0, 0,0;
    
    Ad_k = psi*Ad_k;
    
    return Ad_k.exp() * Ad_j.exp() * Ad_i.exp(); // exp of matrix not present in Eigen
}*/



MatrixXd eulerderivate(double phi,double theta,double psi){
    double cph(cos(phi)),sph(sin(phi)),cth(cos(theta)),sth(sin(theta)),tth(tan(theta)),cps(cos(psi)),sps(sin(psi));
    MatrixXd A(3,3);
    A <<1,sph*tth,cph*tth,
        0,cps,-sps,
        0,sps/cth,cps,cth;
    return A;
}

double angle(double x,double y){
    return atan2(y,x);
}

double angle(point p){
    return atan2(p.second,p.first);
}

MatrixXd adjoint(VectorXd w){
    MatrixXd temp(3,3);
    temp <<     0,-w(2), w(1),
            w(2) ,    0,-w(0),
            -w(1), w(0),    0;
    return temp;
}

MatrixXd ones(int rows,int cols){
    MatrixXd Ones(rows,cols);
    for (int i=0;i<rows;i++){
        for (int j=0;j<cols;j++){
            Ones(i,j) = 1;
        }
    }
    return Ones;
}

MatrixXd move_motif(MatrixXd M,double x,double y,double theta){
    MatrixXd M1(ones(1,M.cols()));
    MatrixXd M2(M.rows()+1,M.cols());
    M2 << M,M1;
    MatrixXd R(2,3);

    R<< cos(theta * PI/180), -sin(theta * PI/180), x,
        sin(theta * PI/180),  cos(theta * PI/180), y;
    return R*M2;

}

MatrixXd translate_motif(MatrixXd R,double x){
    return R + x*ones(R.rows(),R.cols());
}



void kalman_predict(MatrixXd & xup,MatrixXd & Gup,MatrixXd &u,MatrixXd & Ga,MatrixXd & A,MatrixXd & x_out,MatrixXd & G_out){
    G_out = A*Gup*A.transpose() + Ga;
    x_out = A * xup + u;
}

void kalman_correct(MatrixXd & x0,MatrixXd & G0,MatrixXd & y,MatrixXd & Gb,MatrixXd & C,MatrixXd & xup,MatrixXd & Gup){
    MatrixXd S( C*G0+C.transpose()+Gb);
    MatrixXd K(G0*C.transpose()*S.inverse());
    MatrixXd ytilde(y-C*x0);
    double len = std::max(x0.rows(),x0.cols());
    Gup = (MatrixXd::Identity(len,len)-K*C) * G0;
    xup = x0 + K*ytilde;
}
std::vector<MatrixXd> kalman(MatrixXd & x0,MatrixXd & G0,MatrixXd & u,MatrixXd & y,MatrixXd & Ga,MatrixXd & Gb,MatrixXd& A,MatrixXd & C){
    MatrixXd xup(MatrixXd::Zero(x0.rows(),x0.cols()));
    MatrixXd Gup(MatrixXd::Zero(G0.rows(),G0.cols()));

    MatrixXd x1(MatrixXd::Zero(x0.rows(),x0.cols()));
    MatrixXd G1(MatrixXd::Zero(G0.rows(),G0.cols()));

    kalman_correct(x0,G0,y,Gb,C,xup,Gup);
    kalman_predict(xup,Gup,u,Ga,A,x1,G1);
    std::vector<MatrixXd> Out;
    Out.push_back(x1);
    Out.push_back(G1);
    return Out;
}

double sawtooth(double x){
    return 2*atan(tan(x/2));
}