#include "tracker.h"

int KalmanBoxTrackerCA::count_ = 0;

KalmanBoxTrackerCA::KalmanBoxTrackerCA() : kalman_filter_(11, 7) 
{
    count_++;
    StateTransCfg state_trans_cfg;
    life_manager_ = LifeManager(state_trans_cfg);

    delta_time_ = 0.1;
    // kalman_filter_.F_ <<
    //         1, 0, 0, 0, 0, 0, 0, 0.1, 0, 0.005, 0,
    //         0, 1, 0, 0, 0, 0, 0, 0, 0.1, 0, 0.005,
    //         0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    //         0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
    //         0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
    //         0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
    //         0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
    //         0, 0, 0, 0, 0, 0, 0, 1, 0, 0.1, 0,
    //         0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0.1,
    //         0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0,
    //         0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1;

    kalman_filter_.F_ = Eigen::MatrixXd::Identity(11, 11);
    kalman_filter_.F_(0,7) = kalman_filter_.F_(1,8) = delta_time_;
    kalman_filter_.F_(7,9) = kalman_filter_.F_(8,10) = delta_time_;
    kalman_filter_.F_(0,9) = kalman_filter_.F_(1,10) = 0.5 * delta_time_ * delta_time_;

    kalman_filter_.H_ = Eigen::MatrixXd::Identity(7, 11);

    kalman_filter_.P_ = Eigen::MatrixXd::Identity(11, 11);
    kalman_filter_.P_(7,7) = kalman_filter_.P_(8,8) = kalman_filter_.P_(9,9) = kalman_filter_.P_(10,10) = 1000;

    kalman_filter_.R_ = Eigen::MatrixXd::Identity(7, 7) * 10;
    kalman_filter_.R_.block(2,2,4,4) *= 100;
    kalman_filter_.R_(6,6) *= 0.01;

    kalman_filter_.Q_ = Eigen::MatrixXd::Identity(11, 11);
}

void KalmanBoxTrackerCA::Update(const Eigen::VectorXd& observation)
{
    kalman_filter_.Update(observation);

    life_manager_.update();
}

void KalmanBoxTrackerCA::Predict()
{
    kalman_filter_.Predict();
    life_manager_.predict();
}

void KalmanBoxTrackerCA::GetStateString(std::string& res)
{
    res = life_manager_.get_state_string();
}

Eigen::VectorXd KalmanBoxTrackerCA::GetState()
{
    return kalman_filter_.x_;
}

