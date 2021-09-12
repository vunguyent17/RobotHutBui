#include "map/map.h"
#include "robot/robot.h"

int main()
{
	Map prob;
	prob.Nhap("input.txt");
	cout << "Map hien tai:" << endl;
	prob.ShowMap();
    Cleaner VC;
	VC.Init(prob);
	
	cout << "Chon mot trong hai che do: 1. Manual, 2. Auto: ";
	int option = -1;
	cin >> option;
	
	switch (option)
	{
	case 1:
		VC.Manual();
		break;
	case 2:
		VC.Auto();
		break;
	default:
		break;
	}
    return 1;
}
