#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include "../map/map.h"
using namespace std;


class Cleaner
{
    protected:
        string manufacturer;
        string serial_number;
        int current_direction;
        int current_battery;
        Map map;
        CELL current_position;

    public:

		void init(Map n_map)
		{
			cout << "Nhap manufacturer: ";
			getline(cin, manufacturer);
			cout << "Nhap serial number: ";
			getline(cin, serial_number);
			map = n_map;
			current_battery = 100;
			int x, y;
			cout << "Nhap toa do x cua may hut bui (bat dau tu 0, tu tren xuong duoi): ";
			cin >> x;
			cout << "Nhap toa do y cua may hut bui (bat dau tu 0, tu trai qua phai): ";
			cin >> y;
			cout << "Nhap huong cua may hut bui (0.North, 1.East, 2.South, 3.West): ";
			cin >> current_direction;
			current_position = map.data[x][y];
			map.data[current_position.x][current_position.y].type = 0;		//gan vi tri cua may hut bui len ban do (3 -> 0)
		}
		void RotateRight90()
		{
			current_direction++;
			if (current_direction == 4)
			{
				current_direction = 0;
			}
		}

		void RotateLeft90()
		{
			current_direction--;
			if (current_direction == -1)
			{
				current_direction = 3;
			}
		}

		void Rotate180()
		{
			for (int i = 0; i < 2; i++)
			{
				RotateRight90();
			}
		}

		int FindPath()
		{
			int attempt = 0;
			int flag = 0;
			int old_direction = current_direction;
			do
			{
				int temp_x = current_position.x;
				int temp_y = current_position.y;

				switch (current_direction)
				{
				case 0: //North
					temp_x -= 1;
					break;
				case 1:	//East
					temp_y += 1;
					break;
				case 2: //South
					temp_x += 1;
					break;
				case 3: //West
					temp_y -= 1;
					break;
				default:
					break;
				}
				if (temp_x >= 0 && temp_y >= 0 && temp_x <= map.rows - 1 && temp_y <= map.cols - 1
					&& map.data[temp_x][temp_y].type != 1 && map.data[temp_x][temp_y].type != 4)
				{
					current_position = map.data[temp_x][temp_y];
					flag = 1;
				}
				else
				{
					current_direction = old_direction;
					switch (++attempt)
					{
					case 1:
						RotateRight90();
						break;
					case 2:
						RotateLeft90();
						break;
					case 3:
						Rotate180();
						break;
					default:
						break;
					}
				}
			} while (flag == 0 || attempt == 4);
			return flag;
		}

		//In thong tin cua may hut bui hien tai va ban do
		void printInfo()
		{
			cout << "*Manufacturer: " << manufacturer << ". Serial Number: " << serial_number << endl;
			cout << "- Current postion: " << current_position.x << "," << current_position.y << endl;
			cout << "- Current direction: ";
			switch (current_direction)
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
			cout << "- Current battery: " << current_battery << endl;
			cout << "- Current map: " << endl;
			map.ShowMap();

		}
		void Manual(int action, int steps) 
		{
			/*CELL target = CalculateTarget(this.current_position, action, steps);
			FindPath(this.current_position, this.current_direction, target);
			Execute();*/
		}
		void Auto()
		{
			int timer;
			timer = 0;
			cout << "*Timer: " << timer << endl;
			printInfo();

			timer++;
			while (!map.isComplete())
			{
				cout << "*Timer: " << timer << endl;
				if (current_battery != 0)
				{
					map.data[current_position.x][current_position.y].type = 2;	//Chinh lai o hien tai da don sach (0 -> 2)
					int kq_findpath = FindPath();
					if (kq_findpath == 0)
					{
						cout << "ERROR! Khong tim duoc duong di" << endl;
						return;
					}
					else
					{
						map.data[current_position.x][current_position.y].type = 0;
						current_battery--;
						printInfo();
						Sleep(1000);
					}
				}
				else
				{
					cout << "Het pin. Khong the tien hanh di chuyen. Xin hay sac." << endl;
					return;
				}
				timer++;
				cout << "-----------------------" << endl;
			}
			if (map.isComplete())
			{
				cout << "DA DON SACH! :)" << endl;
			}
		}
};
