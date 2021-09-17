#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct CELL
{
	int x = -1; // row index
	int y = -1; // column index
	int type = -1; // 0.Robot, 1.Obstacle, 2.Cleaned, 3.UnCleaned, 4. Wall
};

struct Node
{
	CELL cell;
	Node* pNorth = NULL;
	Node* pEast = NULL;
	Node* pWest = NULL;
	Node* pSouth = NULL;
};

Node* CreateNode(int status)
{
	Node* p = new Node;
	p->cell.x = -1;
	p->cell.y = -1;
	p->cell.type = status;
	p->pNorth = NULL;
	p->pEast = NULL;
	p->pWest = NULL;
	p->pSouth = NULL;
	return p;
}

class Map
{
protected:
	int rows;
	int cols;
	Node* pHead;			//Luu lai Node dau tien

	Node* pPivotHead;		//Luu lai Node dau tien cua mot dong
	Node* pTail;			//Luu lai Node sau cung hien tai
public:
	Node* getpHead()
	{
		return pHead;
	}
	void KhoiTaoBanDo(int n_rows, int n_cols)
	{
		rows = n_rows;
		cols = n_cols;
		pHead = NULL;
		pTail = NULL;
	}

	// Robot (x), Obstackle (*), Cleaned (.), UnCleaned ( ), Wall (-) 
	void Insert(Node* p)
	{
		if (pHead == NULL)
		{
			p->cell.x = 0;
			p->cell.y = 0;
			pHead = p;
			pTail = p;
			pPivotHead = pHead;
		}
		else
		{
			if (pTail->cell.y != cols - 1)		//Truong hop hang hien tai chua day
			{
				p->cell.x = pTail->cell.x ;
				p->cell.y = pTail->cell.y + 1;
				if (pTail->cell.x == 0)		 //Neu dang insert hang dau tien khong can ket noi voi node phia Bac 		
				{

					p->pWest = pTail;
					pTail->pEast = p;
					pTail = p;
				}
				else	//Neu insert hang tiep theo phai quan tam Node phia Bac
				{
					Node* pCurrentNorth  = pTail->pNorth;
					pCurrentNorth = pCurrentNorth->pEast; //Chuyen pPivotNorth sang Node phia Bac node muon chen vao
					p->pNorth = pCurrentNorth;			
					p->pWest = pTail;
					pCurrentNorth->pSouth = p;
					pTail->pEast = p;
					pTail = p;
				}
			}
			else	//Truong hop Hang hien tai da du so node
			{
				//Tao Node dau hang moi
				p->pNorth = pPivotHead;
				p->cell.y = 0;
				p->cell.x = pPivotHead->cell.x + 1;
				pPivotHead->pSouth = p;
				pTail = p;
				pPivotHead = p;		//Luu lai Node dau hang moi tao vao pPivotHead

			}
		}
	}
	void Insert(int x)
	{
		Node* p = CreateNode(x);
		Insert(p);
	}

	void ShowMap()
	{
		Node* p1 = pHead;
		while (p1)
		{
			Node* p2 = p1;
			while (p2)
			{
				switch (p2->cell.type)
				{
				case 0:
					cout << "x";
					break;
				case 1:
					cout << "*";
					break;
				case 2:
					cout << ".";
					break;
				case 3:
					cout << " ";
					break;
				case 4:
					cout << "=";
					break;
				default:
					break;
				}
				cout << " ";
				p2 = p2->pEast;
			}
			cout << endl;
			p1 = p1->pSouth;
		}
	}

	Node* FindNode(int n_x, int n_y)
	{
		Node* p = pHead;
		while (p->cell.x != n_x)
		{
			p = p->pSouth;
		}
		while (p->cell.y != n_y)
		{
			p = p->pEast;
		}
		return p;
	}

	void Nhap(string filename)		//Nhap ma tran tu file .txt, cac phan tu trong so do phan biet nhau boi ki tu tab
	{
		string line;
		ifstream myfile;
		myfile.open(filename);

		if (myfile.is_open())
		{
			myfile >> rows;
			myfile >> cols;
			KhoiTaoBanDo(rows, cols);
			while (getline(myfile, line))	//tien hanh duyet tung dong du lieu trong file .txt
			{
				string line_s = line;		//chuyen dong du lieu sang kieu string
				for (int i = 0; i < line_s.size(); i++)
				{
					if ((int)line_s[i] != 9)		//kiem tra co phai ki tu "tab"
					{
						int temp = line_s[i] - '0';
						Insert(temp);
					}
				}
			}
		}
	}


	void XoaMap()
	{
		if (pHead != NULL)
		{
			Node* p1 = pHead;
			while (true)
			{
				Node* p2 = p1->pEast;
				while (p2)
				{
					Node* p_del = p2;
					p2 = p2->pEast;
					delete p_del;
				}
				if (p1->pSouth != NULL)
				{
					p1 = p1->pSouth;
				}
				else
				{
					break;
				}
			}
			p1 = p1->pNorth;
			while (p1)
			{
				Node* p_del = p1;
				p1 = p1->pNorth;
				delete p_del;
			}
		}
	}
};
