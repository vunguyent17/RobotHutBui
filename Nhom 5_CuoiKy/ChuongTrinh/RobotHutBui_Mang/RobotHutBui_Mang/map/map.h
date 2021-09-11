#pragma once
#include <iostream>
using namespace std;

struct CELL
{
    int x;  // row index
    int y;  //column index
    int type; // 0.Robot, 1.Obstacle, 2.Cleaned, 3.UnCleaned, 4.Wall
};


class Map
{
    public:
        int cols;
        int rows;
        CELL data[5][5];
    
    public:
        void ShowMap()
        {
            for (int row_idx=0; row_idx<this->rows; row_idx++)
            {
                for (int col_idx=0; col_idx<this->cols; col_idx++)
                {
                    switch (data[row_idx][col_idx].type)
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
                }
                cout << endl;
            }
        };

        Map()        
        {
            this->cols = 5;
            this->rows = 5;
            for (int row_idx = 0; row_idx < this->rows; row_idx++)
            {
                for (int col_idx = 0; col_idx < this->cols; col_idx++)
                {
                    CELL temp;
                    temp.x = row_idx;
                    temp.y = col_idx;
                    temp.type = 3;
                    if (row_idx==0) temp.type = 4;
                    if (row_idx==4) temp.type = 4;
                    if (col_idx==0) temp.type = 4;
                    if (col_idx==4) temp.type = 4;
                    if (row_idx==1 && col_idx==1) temp.type = 1;
                    if (row_idx==3 && col_idx==2) temp.type = 1;
                    if (row_idx==1 && col_idx==2) temp.type = 1;
                    if (row_idx==3 && col_idx==3) temp.type = 1;
                    this->data[row_idx][col_idx] = temp;
                }
            }
        };

        int isComplete()
        {
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    if (data[i][j].type == 3)
                    {
                        return false;
                    }
                }
            }
            return true;
        }

        /*void updateCleanerPosition(CELL* current_position, CELL* new_position)
        {
            if (current_position != NULL)
            {
                current_position->type = 2;
            }
            new_position->type = 0;
        }*/
        ~Map(){};
};
