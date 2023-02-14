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
        string manufacturer = "RobotCleanerABC";
        string serial_number = "vunt1";
        float current_battery = 0;
		float battery_threshold = 0;
        Map map_data;
		Direction current;
		
		int uncleaned_direction = 4;

    public:
		void Menu()
		{
			int option = -1;
			do
			{
				cout << "Choose an option: 1. Run with Manual Mode, 2. Run with Auto Mode, 3. Reset Program, 4. Exit: ";
				cin >> option;
				switch (option)
				{
				case 1:
					Manual();
					break;
				case 2:
					Auto();
					break;
				case 3:
					Reset();
					break;
				default:
					break;
				}
			} while (option != 4);
			cout << "Program ends. Thank you for using :)" << endl;
		}

		void Reset()
		{
			Map room_map;
			cout << "Before we continue, open file input.txt and modify it ... \nWhen you're done modifying the map, return to this window and type any key to continue this program." << endl;;
			system("pause");
			room_map.Nhap("input.txt");
			cout << "Map data has been imported. This is the map we received:" << endl;
			room_map.ShowMap();

			map_data.XoaMap();
			SetMap(room_map);
			cout << "The map has been given to robot. Proceed to set robot's location in the map:" << endl;
			SetRobotInMap();
		}
	
		//NHAP va XUAT
		void Init()
		{
			cout << "- Input robot's battery capacity: ";
			cin >> battery_threshold;
			cout << "- Input current baterry level : ";
			cin >> current_battery;

		}

		void SetMap(Map input)
		{
			this->map_data = input;
		}

		void SetRobotInMap()
		{
			int x, y;
			cout << "- Input x-coordinate of the robot's location in the map (starts from 0 from the top of the map): ";
			cin >> x;
			cout << "- Input y-coordinate of the robot's location in the map (starts from 0 from the left of the map): ";
			cin >> y;
			current.position = map_data.FindNode(x, y);

			cout << "- Input the current direction of the robot (0.North, 1.East, 2.South, 3.West): ";
			cin >> current.direction;


			current.position->cell.type = current.direction + 5;
			
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
			ControlLowBattery();
		}

		//BATTERY CONTROL
		//Thiet lap dung luong pin toi da
		void SetBatteryThreshold(float threshold)
		{
			this->battery_threshold = threshold;
		}

		//Kiem tra pin
		bool CheckBattery(float threshold)
		{
			if (current_battery <= threshold)
				return false;
			else
				return true;
		}

		//Thong bao khi pin yeu
		void ControlLowBattery()
		{
			float temp = battery_threshold;
			int flag = 0;
			if (!CheckBattery(float(0.05)*temp) && (float(0.05)*temp < (current_battery + 1)))
			{
				cout << "WARNING: Battery's level under 5% of its capacity. Please charge." << endl;
				flag = 1;
			}
			else
			{
				if (!CheckBattery(float(0.1)*temp) && (float(0.1)*temp < (current_battery + 1)))
				{
					cout << "WARNING: Battery's level under 10% of its capacity. Please charge." << endl;
					flag = 1;
				}
				else
				{
					if (!CheckBattery(float(0.15)*temp) && (float(0.15)*temp < (current_battery + 1)))
					{
						cout << "WARNING: Battery's level under 15% of its capacity. Please charge." << endl;
						flag = 1;
					}
				}
			}
			if (flag == 1)
			{
				cout << "Tiep tuc? (y/n): ";
				char ch = 'n';
				cin >> ch;
				if (ch == 'n')
				{
					exit(1);
				}
			}
		}

		//Lay gia tri pin hien tai
		float GetBattery()
		{
			return this->current_battery;
		}

		

		//CAC PHUONG THUC TIM DUONG
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

		bool CheckUncleanedOnDirection(Direction result) //Kiem tra huong hien tai co o nao trong hay khong, co thi luu lai vao uncleaned_direction
		{
			Node* p = result.position;
			switch (result.direction)
			{
			case 0: // North			
				while (p != NULL)
				{
					if (p->cell.type == 3)
					{
						this->uncleaned_direction = 0;
						return true;
					}
					p = p->pNorth;
				}
				break;
			case 1: // East
				while (p != NULL)
				{
					if (p->cell.type == 3)
					{
						this->uncleaned_direction = 1;
						return true;
					}
					p = p->pEast;
				}
				break;
			case 2: // South
				while (p != NULL)
				{
					if (p->cell.type == 3)
					{
						this->uncleaned_direction = 2;
						return true;
					}
					p = p->pSouth;
				}
				break;
			case 3: // West
				while (p != NULL)
				{
					if (p->cell.type == 3)
					{
						this->uncleaned_direction = 3;
						return true;
					}
					p = p->pNorth;
				}
				break;
			}
			return false;
		}

		bool FindPath_Auto()
		{
			int instruction[4][4] = { {0,1,3,2},{1,2,0,3},{2,3,1,0},{3,0,2,1} };      //Cac bo so lan luot can nhac cac huong
			int direction;
			for (int i = 0; i < 4; i++)
			{
				direction = instruction[current.direction][i];
				Direction* res = CheckNextPosition(direction, false);    //isAllowCleaned = true cho phep di o da don, false la khong
				if (res != NULL)
				{
					this->current = *res;
					return true;
				}
			}
			
			for (int i = 0; i < 4; i++)
			{
				direction = instruction[current.direction][i];
				Direction* res = CheckNextPosition(direction, true);    //isAllowCleaned = true cho phep di o da don, false la khong
				if (res != NULL && CheckUncleanedOnDirection(*res))
				{
					this->current = *res;
					return true;
				}
			}
				
			for (int i = 0; i < 4; i++)
			{
				direction = instruction[current.direction][i];
				Direction* res = CheckNextPosition(direction, true);    //isAllowCleaned = true cho phep di o da don, false la khong

				if (res != NULL)
				{

					this->current = *res;
					if (this->uncleaned_direction < 4)
					{
						this->current.direction = this->uncleaned_direction;
					}
					return true;
				}
			}
			return false;
		}
		
		
		//MANUAL MODE
		//Chon hanh dong cho robot
		int ChooseAction(unsigned int flag)
		{
			cout << "Choose action:" << endl;
			cout << "1.GoAhead" << "\n2.TurnRight" << "\n3.GoBack" << "\n4.TurnLeft" << "\n0.Exit" << endl;
			cin >> flag;  //Nhap vao hanh dong
			if (flag == 0)
				return 0;
			else if (flag < 5)
				return flag;
			else
			{
				cout << "Choose Action again!" << endl;
				return ChooseAction(flag);
			}
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

		//Doi huong robot theo hanh dong da chon
		void UpdateDirection(unsigned int flag)
		{
			switch (flag) //hanh dong
			{
			case 1:  //chon di thang
				break;
			case 2:  //chon turn right
			{
				RotateRight90();
				break;
			}
			case 3:  //chon turn back
			{
				Rotate180();
				break;
			}
			case 4:  //chon turn left
			{
				RotateLeft90();
				break;
			}
			}
		}

		void RoBotGo()
		{
			ControlLowBattery();
			if (current_battery < 0.02*battery_threshold)
			{
				cout << "Running out of battery. The robot is unable to move. Please charge." << endl;
				return;
			}

			current.position->cell.type = current.direction + 5;
			current_battery--;
		}

		void LiveControl()
		{
			unsigned int temp = 1;
			while (true)
			{
				temp = ChooseAction(temp);
				UpdateDirection(temp);
				if (temp == 0)
					break;
				current.position->cell.type = 2;
				bool kq_findpath = FindPath(true);
				if (kq_findpath)
					RoBotGo();
				PrintInfo();
			}
		}

		void SetupControl(int n, int flag)
		{
			UpdateDirection(flag);
			for (int i = 0; i < n; i++)
			{
				current.position->cell.type = 2;
				bool kq_findpath = FindPath(true);
				if (kq_findpath)
					RoBotGo();
				PrintInfo();
				Sleep(100);
			}
		}

		void Manual()
		{
			PrintInfo();
			
			int option = -1;
			do
			{
				cout << "Choose how you will manually control this robot: 1. Live Control, 2. Setup Control, 0.Exit: ";
				cin >> option;
				switch (option)
				{
				case 1:
					LiveControl();
					break;
				case 2:
				{
					int step;
					unsigned int flag = 1;
					cout << "Input how many steps you want robot to move: ";
					cin >> step;
					flag = ChooseAction(flag);
					SetupControl(step, flag);
					break;
				}
				default:
					break;
				}
			} while (option != 0);
		}


		//AUTOMATIC MODE

		int CountUncleaned()
		{
			int count_uncleaned = 0;
			Node* p1 = map_data.getpHead();
			while (p1)
			{
				Node* p2 = p1;
				while (p2)
				{
					if (p2->cell.type == 3)
						count_uncleaned++;
					p2 = p2->pEast;
				}
				p1 = p1->pSouth;
			}
			return count_uncleaned;
		}

		void Auto()
		{
			int timer;
			timer = 0;
			int count_uncleaned = CountUncleaned();
			cout << "*Timer: " << timer << endl;
			PrintInfo();
			Sleep(100);

			timer++;
			while (count_uncleaned != 0)
			{
				system("cls");
				cout << "*Timer: " << timer << endl;
				if (current_battery > 0.02*battery_threshold)
				{
					timer++;
					Node* p = current.position;
					FindPath_Auto();
					p->cell.type = 2; //Danh dau tren map o truoc do da don sach
					if (current.position->cell.type == 3)
					{
						count_uncleaned--;
					}

					current.position->cell.type = current.direction + 5; //Danh dau tren map vi tri hien tai cua robot
					current_battery--;
					PrintInfo();
					Sleep(100);
				}
				else
				{
					cout << "Running out of battery. The robot is unable to move. Please charge." << endl;
					return;
				}
				
			}
			if (CountUncleaned() == 0)
			{
				cout << "CLEANING FINISHED! :)" << endl;
			}
			else
			{
				cout << "ERROR" << endl;
			}
		}
};
