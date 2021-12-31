#include <iostream>
#include <vector>
#include "lifeManager.h"

using namespace std;


int main_mm123()
{
    StateTransCfg cfg;
    LifeManager lm = LifeManager(cfg);
    cout << "state: " << lm.get_state_string() << endl;

    lm.predict();
    cout << "state: " << lm.get_state_string() << endl;
    lm.update();
    cout << "state: " << lm.get_state_string() << endl;

    lm.predict();
    cout << "state: " << lm.get_state_string() << endl;
    lm.predict();
    cout << "state: " << lm.get_state_string() << endl;

    lm.update();
    cout << "state: " << lm.get_state_string() << endl;

    return 0;
}
