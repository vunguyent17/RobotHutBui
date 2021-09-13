#include "map/map.h"
#include "robot/robot.h"

int main()
{
    Cleaner VC;
	cout << "Tien hanh nhap thong tin robot:" << endl;
	VC.Init();
	Map room_map;
	cout << "Chinh sua ban do tren file input.txt... Nhan bat ki phim nao de tiep tuc chuong trinh." << endl;;
	system("pause");
	room_map.Nhap("input.txt");
	cout << "Da nhap xong du lieu ban do. Ban do hien tai:" << endl;
	room_map.ShowMap();

	VC.SetMap(room_map);
	cout << "Da dua thong tin ban do vao robot. Thiet lap vi tri robot:" << endl;
	VC.SetRobotInMap();
	VC.Menu();
    return 1;
}
