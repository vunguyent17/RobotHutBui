#include "map/map.h"
#include "robot/robot.h"

int main()
{
    Cleaner VC;
	cout << "Tien hanh nhap thong tin robot:" << endl;
	VC.Init();
	VC.Reset();
	VC.Menu();
    return 1;
}
