#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include "../map/map.h"
using namespace std;

struct Direction
{
	Node* position = NULL;
	int direction = -1;
};

class Cleaner
{
    protected:
        string manufacturer;
        string serial_number;
        int current_battery;
		int battery_threshold;
        Map map_data;
		Direction current;

    public:
		void SetBatteryThreshold(int threshold)
		{
			this->battery_threshold = threshold;
		}

		bool CheckBattery(int threshold)
		{
			if (current_battery <= threshold)
				return false;
			else
				return true;
		}

		void ShowLowBattery()
		{
			int temp = battery_threshold;
			if (!CheckBattery(0.05*temp))
			{
				cout << "LUU Y: Nguon pin duoi 5%. Xin hay sac robot cua ban." << endl;
			}
			else
			{
				if (!CheckBattery(0.1*temp))
				{
					cout << "LUU Y: Nguon pin duoi 10%. Xin hay sac robot cua ban." << endl;
				}
				else
				{
					if (!CheckBattery(0.15*temp))
					{
						cout << "LUU Y: Nguon pin duoi 15%. Xin hay sac robot cua ban." << endl;
					}
				}
			}
		}

		int GetBattery()
		{
			return this->current_battery;
		}

		void Init(Map n_map)
		{
			cout << "Nhap manufacturer: ";
			getline(cin, manufacturer);
			cout << "Nhap serial number: ";
			getline(cin, serial_number);
			map_data = n_map;
			
			cout << "Nhap dung luong pin toi da: ";
			cin >> battery_threshold;
			cout << "Nhap dung luong pin hien tai: ";
			cin >> current_battery;
			
			int x, y;
			cout << "Nhap toa do x cua may hut bui (bat dau tu 0, tu tren xuong duoi): ";
			cin >> x;
			cout << "Nhap toa do y cua may hut bui (bat dau tu 0, tu trai qua phai): ";
			cin >> y;
			current.position = map_data.FindNode(x, y);
			
			cout << "Nhap huong cua may hut bui (0.North, 1.East, 2.South, 3.West): ";
			cin >> current.direction;
	
			current.position->cell.type = 0;
		}

		void RotateRight90()
		{
			current.direction++;
			if (current.direction == 4)
			{
				current.direction = 0;
			}
		}

		void RotateLeft90()
		{
			current.direction--;
			if (current.direction == -1)
			{
				current.direction = 3;
			}
		}

		void Rotate180()
		{
			for (int i = 0; i < 2; i++)
			{
				RotateRight90();
			}
		}

		//int FindPath()
		//{
		//	int attempt = 0;
		//	int flag = 0;
		//	int old_direction = current->direction;
		//	do
		//	{
		//		Node* p = position;

		//		switch (current_direction)
		//		{
		//		case 0: //North
		//			p = p->pNorth;
		//			break;
		//		case 1:	//East
		//			p = p->pEast;
		//			break;
		//		case 2: //South
		//			p = p->pSouth;
		//			break;
		//		case 3: //West
		//			p = p->pWest;
		//			break;
		//		default:
		//			break;
		//		}
		//		if (p != NULL && p->cell.type != 1 && p->cell.type != 4)
		//		{
		//			position->cell.type = 2;
		//			position = p;
		//			flag = 1;
		//		}
		//		else
		//		{
		//			current_direction = old_direction;
		//			switch (++attempt)
		//			{
		//			case 1:
		//				RotateRight90();
		//				break;
		//			case 2:
		//				RotateLeft90();
		//				break;
		//			case 3:
		//				Rotate180();
		//				break;
		//			default:
		//				break;
		//			}
		//		}
		//	} while (flag == 0 || attempt == 4);
		//	return flag;
		//}

		int isComplete()
		{
			Node* p1 = map_data.pHead;
			while (p1)
			{
				Node* p2 = p1;
				while (p2)
				{
					if (p2->cell.type == 3)
						return false;
					p2 = p2->pEast;
				}
				p1 = p1->pSouth;
			}
			return true;
		}

		void PrintInfo()
		{
			cout << "*Manufacturer: " << manufacturer << ". Serial Number: " << serial_number << endl;
			cout << "- Current postion: " << current.position->cell.x << "," << current.position->cell.y << endl;
			cout << "- Current direction: ";
			switch (current.direction)
			{
			case 0:
				cout << "North.";
				break;
			case 1:
				cout << "East.";
				break;
			case 2:
				cout << "South.";
				break;
			case 3:
				cout << "West.";
				break;
			default:
				break;
			}
			cout << endl;
			cout << "- Current battery: " << GetBattery() << "/" << battery_threshold << endl;
			cout << "- Current map: " << endl;
			map_data.ShowMap();
			ShowLowBattery();
		}

		void SetDirection(int x, int y, int direction)          // Chuyen vi tri va huong cua may hut bui
		{
			this->current.position->cell.x = x;
			this->current.position->cell.y = y;
			this->current.direction = direction;
		}

		Direction* CheckNextPosition(int direction, bool allowCleaned = false) // kiem tra vi tri va huong tiep theo
		{
			Direction* result = new Direction;
			*result = current;
			int cell_check;

			//Gan x, y va huong cua vi tri moi vao result
			switch (direction)
			{
			case 0: // North
				result->position = result->position->pNorth;
				result->direction = 0;
				break;
			case 1: // East
				result->position = result->position->pEast;
				result->direction = 1;
				break;
			case 2: // South
				result->position = result->position->pSouth;
				result->direction = 2;
				break;
			case 3: // West
				result->position = result->position->pWest;
				result->direction = 3;
				break;
			default:
				cout << "ERROR" << endl;
				break;

			}
			//Lay tu ban do kiem tra vi tri do la loai nao
			cell_check = result->position->cell.type;
			// Obstacle or Wall . Neu vi tri do la tuong hoac chuong ngai vat thi tra ve NULL
			if (cell_check == 1 || cell_check == 4)
				return NULL;
			// Cleaned. Neu hien tai o che do khong cho phep di qua vi tri da don va o do da don thi tra ve NULL
			else
				if (!allowCleaned && cell_check == 2)
					return NULL;
				else
					return result;
			return NULL;
		}
		bool FindPath(bool isAllowCleaned) {
			int instruction[4][4] = { {0,1,3,2},{1,2,0,3},{2,3,1,0},{3,0,2,1} };      //Cac bo so lan luot can nhac cac huong
			int direction;
			for (int i = 0; i < 4; i++)
			{
				direction = instruction[current.direction][i];
				Direction* res = CheckNextPosition(direction, isAllowCleaned);    //isAllowCleaned = true cho phep di o da don, false la khong
				if (res)
				{
					this->current = *res;
					return true;
				}
			}
			return false;
		}

		void Manual(int action, int steps) 
		{
			
		}
		void Auto()
		{
			int timer;
			timer = 0;
			cout << "*Timer: " << timer << endl;
			PrintInfo();

			timer++;
			while (!isComplete())
			{
				cout << "*Timer: " << timer << endl;
				Node* p = current.position; //
				if (current_battery != 0)
				{
					bool kq_findpath = FindPath(false);
					if (kq_findpath == 0)
					{
						bool kq_findpath = FindPath(true);
					}
					p->cell.type = 2; //
					current.position->cell.type = 0; //
					current_battery--;
					PrintInfo();
					Sleep(1000);
				}
				else
				{
					cout << "Het pin. Khong the tien hanh di chuyen. Xin hay sac." << endl;
					return;
				}
				timer++;
				cout << "-----------------------" << endl;
				
			}
			if (isComplete())
			{
				cout << "DA DON SACH! :)" << endl;
			}
		}
};
