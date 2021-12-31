#include <iostream>
#include <vector>
#include "tracker.h"

using namespace std;

int main()
{
    std::string res;
    KalmanBoxTrackerCA tracker = KalmanBoxTrackerCA();
    cout << tracker.getID() << endl;
    tracker.GetState(res);
    cout << res << endl;

    {
        KalmanBoxTrackerCA tracker2 = KalmanBoxTrackerCA();
        cout << tracker2.getID() << endl;
    }

    KalmanBoxTrackerCA tracker3 = KalmanBoxTrackerCA();
    cout << tracker3.getID() << endl;

    tracker3.Predict();
    tracker3.GetState(res);
    cout << res << endl;

    tracker3.Update();
    tracker3.GetState(res);
    cout << res << endl;

    cout << tracker3.kalman_filter_.F_ << endl;
    cout << tracker3.kalman_filter_.H_ << endl;
    cout << tracker3.kalman_filter_.P_ << endl;
    cout << tracker3.kalman_filter_.R_ << endl;
    cout << tracker3.kalman_filter_.Q_ << endl;
    return 0;
}
