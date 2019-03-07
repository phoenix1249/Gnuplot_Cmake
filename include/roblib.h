#include <Eigen/Dense>
#include "gnuplot-iostream.h"
#include <boost/tuple/tuple.hpp>
#include <vector>
#include <string>
#include <map>

#define PI 3.14159265
typedef std::pair<double, double> point;


class Plot
{
private:
    Gnuplot gp;
    std::vector<std::vector<point>> points;
    std::vector<std::string> colors;
    double x_min;
    double x_max;
    double y_min;
    double y_max;



public:
    Plot();
    ~Plot();
    void set_x_limit(double xmin, double xmax);
    void set_y_limit(double ymin, double ymax);
    void clear();
    void draw_circle(point Center,double radius,std::string color);
    void draw_circle(double x,double y,double radius,std::string color);
    void draw_ellipse(point Center,double a, double b,std::string color);
    void draw_ellipse(double x,double y,double a, double b,std::string color);
    void plot(std::vector<point> & p,std::string color);
    void plot(Eigen::MatrixXd & M,std::string color);
    void draw_tank(double x,double y,double theta,std::string color,double r);
    void draw_tank(double x,double y,double theta,std::string color);
    void draw_disk(double x, double y,double radius,std::string color);//TODO
    void draw_sailboat(double x,double y,double theta,double deltas,double deltar,double psi,double awind);
    void draw_car(double x,double y,double theta,std::string color);//TODO
    void show();
};



Eigen::MatrixXd eulermat(double phi,double theta,double psi);
Eigen::MatrixXd eulerderivate(double phi,double theta,double psi);
double angle(double x,double y);
double angle(point p);
Eigen::MatrixXd adjoint(Eigen::VectorXd w);
Eigen::MatrixXd move_motif(Eigen::MatrixXd M,double x,double y,double theta);
Eigen::MatrixXd translate_motif(Eigen::MatrixXd M,double x);
Eigen::MatrixXd ones(int rows,int cols);
void kalman_predict(Eigen::MatrixXd & xup,Eigen::MatrixXd & Gup,Eigen::MatrixXd &u,Eigen::MatrixXd & Ga,Eigen::MatrixXd & A,Eigen::MatrixXd & x_out,Eigen::MatrixXd & G_out);
void kalman_correct(Eigen::MatrixXd & x0,Eigen::MatrixXd & G0,Eigen::MatrixXd & y,Eigen::MatrixXd & Gb,Eigen::MatrixXd & C,Eigen::MatrixXd & xup,Eigen::MatrixXd & Gup);
std::vector<Eigen::MatrixXd> kalman(Eigen::MatrixXd & x0,Eigen::MatrixXd & G0,Eigen::MatrixXd & u,Eigen::MatrixXd & y,Eigen::MatrixXd & Ga,Eigen::MatrixXd & Gb,Eigen::MatrixXd &A,Eigen::MatrixXd & C);
double sawtooth(double x);

