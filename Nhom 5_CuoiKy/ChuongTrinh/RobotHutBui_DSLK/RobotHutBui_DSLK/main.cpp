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
	VC.Auto();
    return 1;
}
