#include <iostream>
#include <vector>
#include <eigen3/Eigen/Eigen>

using namespace Eigen;
using namespace std;


void main1()
{
    Eigen::Vector2d v1, v2;
    v1 << 5,6;
    cout << "v1 = " << v1 << endl;

    v2 << 100,10;
    Matrix2d res = v1 * v2.transpose();

    cout << "res = " << endl << res << endl;
}


void main2()
{
    Eigen::Affine3d ppp = Eigen::Affine3d::Identity();
    ppp(0,3) = 5;
    ppp(1,3) = 6.1;
    ppp(2,3) = 7.3;

    cout << ppp.rotation() << endl;
    cout << ppp.translation() << endl;
    cout << ppp.matrix() << endl;

}