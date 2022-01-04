#include <iostream>
#include <vector>
#include "lifeManager.h"

using namespace std;


int main_mm123()
{
    StateTransCfg cfg;
    LifeManager lm = LifeManager(cfg);
    cout << "state: " << lm.get_state_string() << endl;

    lm.Predict();
    cout << "state: " << lm.get_state_string() << endl;
    lm.Update();
    cout << "state: " << lm.get_state_string() << endl;

    lm.Predict();
    cout << "state: " << lm.get_state_string() << endl;
    lm.Predict();
    cout << "state: " << lm.get_state_string() << endl;

    lm.Update();
    cout << "state: " << lm.get_state_string() << endl;

    return 0;
}
