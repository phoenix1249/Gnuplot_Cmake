#include "../include/roblib.h"
#include <algorithm> 
#include <iostream>
#include <cmath>



using namespace Eigen;


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