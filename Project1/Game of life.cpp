#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <set> //avoid same element
#include <chrono> //use sleep time
#include <thread> // maybe unit of times
#include <conio.h> //get user input in the game
#include <fstream> //save and load
#include <string>
#include <map>
using namespace std;


class GameOfLife
{
private:
	int rows, cols;
	//int step = 1;
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
	int step = 1;
	bool block = 0;
	bool beehive = 0;
	bool blinker = 0;
	bool LWSS = 0;
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

		for (int i = 0; i < rows; i++)
		{


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
		bool pause = false;
		while (true)
		{
			if (!pause) 
			{
				cout << "steps: " << step++ << endl;
				print_Grid();
				detect_patterns(grid);
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
				else if (input == 'a') 
				{
					int newRow, newCol;
					cout << "input the new cell row and col : ";
					cin >> newRow >> newCol;
					if (newRow > 0 && newRow < rows && newCol > 0 && newCol < cols) // maybe < rows/cols-1
					{
						grid[newRow][newCol] = 1;
						cout << "live cell added at" << newRow << "," << newCol << endl;
					}
			
				}
				else if (input == 's')
				{
					string filename;
					cout << "enter the game name: ";
					cin >> filename;
					saveFile(filename);
				}
				else
				{
					cout << "Invalid position" << endl;
				}

			}

			this_thread::sleep_for(chrono::milliseconds(1000));
		}
	}
	void saveFile(const string &filename)
	{
		ofstream outfile(filename);
		if (outfile.is_open())
		{
			outfile << rows << " " << cols;
			for (int i = 0; i < rows; i++) 
			{
				for (int j = 0; j < cols; j++)
				{
					outfile << grid[i][j];
				}
				outfile << endl;
			}
		}
	
		cout << "game saved in" << filename << endl;
		outfile.close();
	}
	void loadFile(const string& filename)
	{
		ifstream infile(filename);
		if (infile.is_open())
		{
			infile >> rows >> cols;
			grid.resize(rows,vector<int>(cols,0));
			tempGrid.resize(rows, vector<int>(cols, 0));
			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < cols; j++)
				{
					infile >> grid[i][j];
				}
				cout << endl;
			}
			cout << "game loaded" << endl;
			infile.close();
		}
		else
		{
			cout << "not found this game" << endl;
		}
	}
	void detect_patterns(vector<vector<int>>& grid)
	{
		int rows = grid.size();
		int cols = grid[0].size();
		if (block==0)
		{
		for (int i = 0; i < rows - 1; i++)   
					{
						for (int j = 0; j < cols - 1; j++)
						{
							if (grid[i][j] == 1 && grid[i][j + 1] == 1 &&
								grid[i + 1][j] == 1 && grid[i + 1][j + 1] == 1)
							{
								cout << "generate block used"<<step << endl;
								block = 1;
								return;
						
							}
						}
					}

		}
		if (beehive == 0)
		{
			for (int i = 0; i < rows - 2; i++)
			{
				for (int j = 0; j < cols - 3; j++)
					{
					if (grid[i][j + 1] == 1 && grid[i][j + 2] == 1 &&
						grid[i + 1][j] == 1 && grid[i + 1][j + 3] == 1 &&
						grid[i + 2][j + 1] == 1 && grid[i + 2][j + 2] == 1)
					{
						cout << "generate beehive used" << step << endl;
						beehive = 1;
						return;
					}
				}

			}
		}
		if (blinker == 0)
		{
			for (int i = 0; i < rows - 1; i++)
			{
				for (int j = 0; j < cols - 2; j++)
				{
					if (grid[i][j] == 1 && grid[i][j + 1] == 1 &&
						grid[i][j + 2] == 1)
					{
						cout << "Generate Blinker used" << step << endl;
						blinker = 1;
						return;
					}
				}
			}
		}
		if (LWSS = 0)
		{
			for (int i = 0; i < rows - 3; i++)  
			{
				for (int j = 0; j < cols - 4; j++)  
				{
					if (grid[i][j + 1] == 1 && grid[i][j + 4] == 1 && grid[i+1][j] == 1 &&
						grid[i + 2][j] == 1 && grid[i + 3][j] == 1 &&
						grid[i + 3][j + 1] == 1 &&
						grid[i + 3][j+2] == 1 && grid[i + 3][j + 3] == 1)
					{
						cout << "Generate LWSS used " << step << "steps" << endl;
						LWSS = 1;
						return;
					}
				}
			}
		}	
	}
};
	int main()
	{
		int rows, cols,inicial_number;
		string choice,filename;
		cout << "Do you want to start new game or loaded a game? (N/L)" << endl;
		cin >> choice;
		if (choice == "L")

		{	
			cout << "filename: ";
			cin >> filename;
			ifstream inFile(filename);
			if (inFile.is_open())
			{
				inFile >> rows >> cols;
				GameOfLife game(rows,cols);
				game.loadFile(filename);
				game.print_Grid();
				game.play_game();
			}

		}
		else
		{
			cout << "determined your grid size,rows and cols: ";
			cin >> rows >> cols;
			cout << "initial alive number:";
			cin >> inicial_number;
			GameOfLife game(rows, cols); 
			game.initialize(inicial_number); 
			game.print_Grid();
			game.play_game();

		}
	}
