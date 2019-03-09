#include <Eigen/Dense>
#include "gnuplot-iostream.h"
#include <boost/tuple/tuple.hpp>
#include "Plot.h"






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

