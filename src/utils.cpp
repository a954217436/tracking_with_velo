
#include <math.h>
#include <eigen3/Eigen/Eigen>
#include "utils.h"


#define PI 3.1415926


void translation_angle(float& theta)
{
    if(theta >= PI)
    {
        theta -= (2 * PI);
    }
    if(theta < -PI)
    {
        theta += (2 * PI);
    }
}


void correction_angle(float& theta)
{
    theta = atan2(sin(theta), cos(theta));
}