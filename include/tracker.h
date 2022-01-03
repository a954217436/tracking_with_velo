#pragma once

#include <iostream>
#include <eigen3/Eigen/Eigen>

#include "lifeManager.h"
#include "kalman_filter.h"


class KalmanBoxTrackerCA
{
    static int count_;

    public:
        KalmanBoxTrackerCA();
        ~KalmanBoxTrackerCA()
        {
            // std::cout << "deconstruct tracker..." << std::endl;
        };

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
};



