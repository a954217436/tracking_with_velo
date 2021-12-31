#include <iostream>
#include <vector>
#include "kalman_filter.h"

using namespace std;

int main_kf()
{
    KalmanFilter kf = KalmanFilter(10, 7);
    kf.Predict();

    cout << kf.x_ << endl;

    Eigen::VectorXd observation = Eigen::VectorXd::Zero(7);
    observation << 1,2,3,4,5,6,7;
    cout << observation << endl;
    kf.Update(observation);

    cout << kf.x_ << endl;

    return 0;
}
