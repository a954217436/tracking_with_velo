#include <iostream>
#include "trackData.h"


TrackData::TrackData(int id, 
            int label, 
            float score, 
            double timestamp,
            Box7DoF local_box,
            Eigen::Affine3d pose)
{
    id_ = id;
    pose_ = pose;
    label_ = label;
    score_ = score;
    timestamp_ = timestamp;
    local_box_ = local_box;
    correction_angle(local_box_.heading);
    local2world(local_box_, world_box_);
}


void TrackData::local2world(const Box7DoF& local_box, Box7DoF& world_box)
{
    Eigen::Vector3d local_center(local_box.cx, local_box.cy, local_box.cz);
    Eigen::Vector3d world_center = pose_ * local_center;

    world_box.cx = world_center(0);
    world_box.cy = world_center(1);
    world_box.cz = world_center(2);

    world_box.dx = local_box.dx;
    world_box.dy = local_box.dy;
    world_box.dz = local_box.dz;

    float angle = atan2(-pose_(1, 0), pose_(0, 0));
    world_box.heading = local_box.heading + angle;
    correction_angle(world_box.heading);
}


void TrackData::world2local(const Box7DoF& world_box, Box7DoF& local_box)
{
    Eigen::Vector3d world_center(world_box.cx, world_box.cy, world_box.cz);
    Eigen::Vector3d local_center = pose_.inverse() * world_center;

    local_box.cx = local_center(0);
    local_box.cy = local_center(1);
    local_box.cz = local_center(2);

    local_box.dx = world_box.dx;
    local_box.dy = world_box.dy;
    local_box.dz = world_box.dz;

    float angle = atan2(-pose_(1, 0), pose_(0, 0));
    local_box.heading = world_box.heading - angle;
    correction_angle(local_box.heading);
}


std::ostream &operator<<(std::ostream &out, Box7DoF &b)
{
    std::cout << "[" << b.cx 
            << "," << b.cy
            << "," << b.cz
            << "," << b.dx
            << "," << b.dy
            << "," << b.dz
            << "," << b.heading
            << "]";
    return out;
}


std::ostream &operator<<(std::ostream &out, TrackState &s)
{
    if(s == NEW)
        std::cout << "New" << std::endl;
    if(s == STABLE)
        std::cout << "Stable" << std::endl;
    if(s == LOSE)
        std::cout << "Lose" << std::endl;
    if(s == DELETE)
        std::cout << "Delete" << std::endl;
    return out;
}


std::ostream &operator<<(std::ostream &out, TrackData &t)
{
	std::cout << "<<<<<<<<" << std::endl;

	std::cout << "  id="               << t.id_ 
            << ",score="               << t.score_
            << ",label="               << t.label_
            << ",timestamp="           << t.timestamp_
            << ",state="               << t.state_
            << ",\n  local_box="           << t.local_box_
            << ",\n  world_box="           << t.world_box_
            << ",\n  local_box_filtered="  << t.local_box_filtered_
            << ",\n  world_box_filtered="  << t.world_box_filtered_
            << ",\n  output_velocity=\n"     << t.output_velocity_
            << ",\n  pose=\n"                << t.pose_.matrix()
            << ",\n  state_string="        << t.state_string_
            << std::endl;

    std::cout << ">>>>>>>>" << std::endl;
	return out;
}

