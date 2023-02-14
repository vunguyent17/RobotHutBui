#include "map/map.h"
#include "robot/robot.h"

int main()
{
    Cleaner VC;
	cout << "Welcome to Robot Vacuum Cleaner Simulator.\nYou will control a robot cleaner" << endl;
	cout << "Before we begin , we need some Robot's specification:" << endl;
	VC.Init();
	VC.Reset();
	VC.Menu();
    return 1;
}
