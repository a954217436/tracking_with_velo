#include <iostream>
#include <vector>
#include "tracker.h"

using namespace std;

int main()
{
    std::string res;
    Eigen::VectorXd res_x;

    KalmanBoxTrackerCA tracker = KalmanBoxTrackerCA();
    cout << tracker.getID() << endl;
    tracker.GetStateString(res);
    cout << res << endl;

    res_x = tracker.GetState();
    cout << res_x << endl;

    {
        KalmanBoxTrackerCA tracker2 = KalmanBoxTrackerCA();
        cout << tracker2.getID() << endl;
    }

    KalmanBoxTrackerCA tracker3 = KalmanBoxTrackerCA();
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

    res_x = trackerSS3.GetState();
    cout << "tracker3 after update x = " << res_x << endl;

    // cout << tracker3.kalman_filter_.F_ << endl;
    // cout << tracker3.kalman_filter_.H_ << endl;
    // cout << tracker3.kalman_filter_.P_ << endl;
    // cout << tracker3.kalman_filter_.R_ << endl;
    // cout << tracker3.kalman_filter_.Q_ << endl;
    return 0;
}
