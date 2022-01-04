#include <iostream>
#include <vector>
#include "tracker.h"

using namespace std;

TrackData get_track_data()
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
    return t;
}

int main()
{
    std::string res;
    Eigen::VectorXd res_x;

    TrackData tt = get_track_data();

    KalmanBoxTrackerCA tracker = KalmanBoxTrackerCA(tt);
    cout << tracker.getID() << endl;
    tracker.GetStateString(res);
    cout << res << endl;

    res_x = tracker.GetState();
    cout << res_x << endl;

    {
        KalmanBoxTrackerCA tracker2 = KalmanBoxTrackerCA(tt);
        cout << tracker2.getID() << endl;
    }

    KalmanBoxTrackerCA tracker3 = KalmanBoxTrackerCA(tt);
    cout << tracker3.getID() << endl;

    res_x = tracker3.GetState();
    cout << "tracker3 init x = " << res_x << endl;

    tracker3.Predict();
    tracker3.GetStateString(res);
    cout << res << endl;

    res_x = tracker3.GetState();
    cout << "tracker3 after predict x = " << res_x << endl;

    Eigen::VectorXd observation = Eigen::VectorXd::Zero(7);
    observation << 1,2,3,4,5,6,7;
    cout << observation << endl;

    tracker3.Update(observation);
    tracker3.GetStateString(res);
    cout << res << endl;

    res_x = tracker3.GetState();
    cout << "tracker3 after update x = " << res_x << endl;

    // cout << tracker3.kalman_filter_.F_ << endl;
    // cout << tracker3.kalman_filter_.H_ << endl;
    // cout << tracker3.kalman_filter_.P_ << endl;
    // cout << tracker3.kalman_filter_.R_ << endl;
    // cout << tracker3.kalman_filter_.Q_ << endl;
    return 0;
}
