#pragma once

#include <math.h>
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <eigen3/Eigen/Eigen>

#include "utils.h"

struct Box7DoF
{
    float cx=0., cy=0., cz=0.;
    float dx=0., dy=0., dz=0.;
    float heading=0.; 
};


enum TrackState 
{
    NEW       = 0,
    STABLE    = 1,
    LOSE      = 2,
    DELETE    = 3
};


struct TrackData 
{
    TrackData(){};
    TrackData(int id, 
            int label, 
            float score, 
            double timestamp,
            Box7DoF local_box,
            Eigen::Affine3d pose);
    ~TrackData(){};
    void local2world(const Box7DoF& local_box, Box7DoF& world_box);
    void world2local(const Box7DoF& world_box, Box7DoF& local_box);

    int id_;
    int label_;
    float score_;
    double timestamp_;

    bool is_static_;
    bool is_predict_;

    TrackState state_;
    std::string state_string_;

    Box7DoF local_box_;
    Box7DoF world_box_;

    Box7DoF local_box_filtered_;
    Box7DoF world_box_filtered_;

    Eigen::Vector2d output_velocity_ = Eigen::Vector2d(0.0, 0.0);
    Eigen::Affine3d pose_;

};

std::ostream &operator<<(std::ostream &out, Box7DoF &b);
std::ostream &operator<<(std::ostream &out, TrackState &s);
std::ostream &operator<<(std::ostream &out, TrackData &t);



