#include "map/map.h"
#include "robot/robot.h"

int main()
{
    Map prob;
    prob.ShowMap();
    Cleaner VC;
	VC.init(prob);
	VC.Auto();
    return 1;
}
