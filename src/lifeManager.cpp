#include <string>
#include "lifeManager.h"


LifeManager::LifeManager(StateTransCfg st_cfg)
{
    hits_ = 0;
    hit_streak_ = 0;
    age_ = 0;
    time_since_update_ = 0;

    first_continuing_hit_ = 1;
    still_first_ = true;
    state_ = NEW;

    stage_trans_cfg_ = st_cfg;
}


LifeManager::~LifeManager()
{   
}


void LifeManager::Update()
{
    hits_++;
    hit_streak_++;
    time_since_update_ = 0;
    state_transition();
}


void LifeManager::Predict()
{
    age_++;
    if(time_since_update_ > 0)
        hit_streak_ = 0;
    time_since_update_++;
    state_transition();
}


void LifeManager::state_transition()
{
    switch (state_)
    {
    case NEW:
        if(hit_streak_ >= stage_trans_cfg_.NEW2STABLE)
            state_ = STABLE;
        if(time_since_update_ >= stage_trans_cfg_.NEW2DELETE)
            state_ = DELETE;
        break;
    case STABLE:
        if(time_since_update_ >= stage_trans_cfg_.STABLE2LOSE)
            state_ = LOSE;
        break;
    case LOSE:
        if(hit_streak_ >= stage_trans_cfg_.LOSE2STABLE)
            state_ = STABLE;
        if(time_since_update_ >= stage_trans_cfg_.LOSE2DELETE)
            state_ = DELETE;
        break;
    default:
        break;
    }
}


bool LifeManager::is_state_valid()
{
    return state_ == NEW || state_ == STABLE;
    // return state_ != DELETE;
}

bool LifeManager::is_state_delete()
{
    return state_ == DELETE;
}

std::string LifeManager::get_state_string() 
{
    std::string state_str;
    switch (state_)
    {
    case NEW:
        state_str = "New";
        break;
    case STABLE:
        state_str = "Sta";
        break;
    case LOSE:
        state_str = "Los";
        break;
    case DELETE:
        state_str = "Del";
        break;
    
    default:
        break;
    }
    char ss[30]; 
    sprintf(ss, "%s,ht=%d,ag=%d,hs=%d,tsu=%d", state_str.c_str(), hits_, age_, hit_streak_, time_since_update_); 
    return ss;
}


