/* 
    a finite state machine to manage the life cycle
    states: 
        - new:    new object
        - stable: stable object
        - lose:   without high score association, about to die
        - delete: may it eternal peace
*/

#ifndef __LIFE_MANAGER__
#define __LIFE_MANAGER__

#include "trackData.h"

typedef struct StateTransitionCfg_
{
    int NEW2STABLE  = 1;
    int STABLE2LOSE = 2;
    int LOSE2DELETE = 3;
    int NEW2DELETE  = 2;
    int LOSE2STABLE = 1;
} StateTransCfg;


class LifeManager
{
    public:
        LifeManager(){};
        LifeManager(StateTransCfg st_cfg);
        ~LifeManager();

        void Update();
        void Predict();
        void state_transition();

        bool is_state_valid();
        bool is_state_delete();

        std::string get_state_string();

    private:
        int age_;
        int hits_;
        int hit_streak_;
        int time_since_update_;
        int first_continuing_hit_;
        bool still_first_;
        StateTransCfg stage_trans_cfg_;
        TrackState state_;
};

#endif  //__LIFE_MANAGER__