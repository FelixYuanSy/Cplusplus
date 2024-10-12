#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <set> //avoid same element
#include <chrono> //use sleep time
#include <thread> // maybe unit of times
#include <conio.h> //get user input in the game
using namespace std;


class GameOfLife
{
private:
	int rows, cols;
	vector<vector<int>> grid;
	vector<vector<int>> tempGrid;
	const string alive = "O";
	const string dead = " ";

	int getLiveAround(int row, int col)
	{
		int liveAround = 0;

		for (int i = -1; i < 2; i++)
		{
			for (int j = -1;  j < 2; j++)
			{
				if (i == 0 && j == 0) { continue; }
				int neighbor_Row = row + i;
				int neighbor_Col = col + j;

				if (neighbor_Row >= 0 && neighbor_Row < rows && neighbor_Col >= 0 && neighbor_Col < cols && grid[neighbor_Row][neighbor_Col]==1)
				{
					liveAround ++;
				}
			}
		}
		return liveAround;
	}

public:
	GameOfLife(int r, int c) : rows(r), cols(c), grid(r, vector<int>(c, 0)), tempGrid(r, vector<int>(c, 0))
	{
	}

	void initialize(int numliveCells)
	{
		srand(time(0));
		set<pair<int, int>> liveCells;
		while (liveCells.size() < numliveCells)
		{
			int row = rand() % rows;
			int col = rand() % cols;
			liveCells.insert({ row,col });
		}
		for (auto cell : liveCells) //set generate cell to be live cell
		{
			grid[cell.first][cell.second] = 1;
		}
	}

	void print_Grid()
	{
		cout << "   ";
		for (int j = 0; j < cols; j++)
		{
			if (j < 9) cout << " " << j;
			else if (j == 9) cout << " " << j << " ";
			else cout <<j;
		}
		cout << endl;
		for (int i = 0; i < rows; i++)
		{
			if(i<10) cout << " " << i << " ";
			else cout << i <<" ";

			for (int j = 0; j < cols; j++)
			{
				cout << ".";
				if (grid[i][j] == 1)
				{
					cout << alive;
				}
				else
				{
					cout << dead;
				}				
			}
			cout << ".";
			cout << endl;
		}
	}

	void update()
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j ++)
			{
				switch (getLiveAround(i, j)) {
				case 2:
					tempGrid[i][j] = grid[i][j];
					break;
				case 3:
					tempGrid[i][j] = 1;
					break;
				default: 
					tempGrid[i][j] = 0;
				}
			}
		}

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				grid[i][j] = tempGrid[i][j];
				
			}
		}
	}
	void play_game()
	{
		int step = 1;
		int run = 1;
		bool pause = false;
		while (run)
		{
			/*print_initialize();*/
			if (!pause) 
			{
				cout << "steps: " << step++ << endl;
				print_Grid();
				update();
			}
			if (_kbhit())
			{
				char input = _getch();
				if (input == 'p')
				{
					pause = true;
					cout << "Game paused. Press 'r' to resume, 'q' to quit."<<endl;
				}
				else if (input == 'r')
				{
					pause = false;
					cout << "game resumed" << endl;
				}
				else if (input == 'q')
				{
					cout << "game terminated" << endl;
					break;
				}
				else if (input == 'a') {
					int newRow, newCol;
					cout << "input the new cell row and col : ";
					cin >> newRow >> newCol;
					if (newRow > 0 && newRow < rows && newCol > 0 && newCol < cols) // maybe < rows/cols-1
					{
						grid[newRow][newCol] = 1;
						cout << "live cell added at" << newRow << "," << newCol << endl;
					}
					else
					{
						cout << "Invalid position" << endl;
					}
					
				}
			}
			this_thread::sleep_for(chrono::milliseconds(1000));
		}
	}

};
	int main()
	{
		int rows, cols,inicial_number;
		cout << "determined your grid size,rows and cols: ";
		cin >> rows >> cols;
		cout << "initial alive number:";
		cin >> inicial_number;
		GameOfLife game(rows, cols); 
		game.initialize(inicial_number); 
		game.print_Grid();
		game.play_game();


	}
