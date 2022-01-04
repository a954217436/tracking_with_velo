#pragma once

#include <memory>
#include <iostream>
#include <eigen3/Eigen/Eigen>

// #include "trackData.h"
#include "lifeManager.h"
#include "kalman_filter.h"


class KalmanBoxTrackerCA
{
    static int count_;

    public:
        // KalmanBoxTrackerCA(){};
        KalmanBoxTrackerCA(TrackData track_data);
        ~KalmanBoxTrackerCA();

        int getID()
        {
            return count_;
        }

        void Update(const Eigen::VectorXd& observation);
        void Predict();
        Eigen::VectorXd GetState();
        void GetStateString(std::string& res);

    // private:
        LifeManager life_manager_;
        KalmanFilter kalman_filter_;

        float delta_time_;
        int id_;

        TrackData track_data_;
};



