#include <iostream>
#include <vector>
#include "trackData.h"

using namespace std;


int main_mm()
{
    Box7DoF local_box;
    local_box.cx = 10;
    local_box.cy = 20;
    local_box.cz = 2;
    local_box.dx = 4;
    local_box.dy = 2;
    local_box.dz = 1.8;
    local_box.heading = 3.1415926 * 3;

    Eigen::Affine3d pose = Eigen::Affine3d::Identity();

    pose.matrix() << -9.96016725e-01,  8.41224012e-02,  2.95652754e-02, -2.08246733e+03,
            -8.41366020e-02, -9.96453936e-01,  7.65596193e-04,  1.26895037e+04,
            2.95248389e-02, -1.72497520e-03,  9.99562558e-01, -1.52739000e+02,
            0.00000000e+00,  0.00000000e+00,  0.00000000e+00,  1.00000000e+00;  // seq_0_frame_0.pkl 

    TrackData t(0, 1, 0.88, 0.8988, local_box, pose);

    cout << "trackdata :" << endl << t << endl;

    t.world_box_filtered_ = t.world_box_;
    t.world2local(t.world_box_filtered_, t.local_box_filtered_);

    cout << "trackdata :" << endl << t << endl;

    return 0;
}