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
    void draw_car(double x,double y,double theta,std::string color);
    void show();
};

