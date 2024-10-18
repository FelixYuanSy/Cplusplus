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

				if (neighbor_Row >= 1 && neighbor_Row <= rows && neighbor_Col >= 1 && neighbor_Col <= cols && grid[neighbor_Row][neighbor_Col]==1)
				{
					liveAround ++;
				}
			}
		}
		return liveAround;
	}

public:
	int step = 1;
	int initial_live_number;
	bool block = 0;
	bool beehive = 0;
	bool blinker = 0;
	bool LWSS = 0;
	bool toad = 0;
	bool pause = false;
	GameOfLife(int r, int c) : rows(r), cols(c), grid(r + 2, vector<int>(c + 2, 0)), tempGrid(r + 2, vector<int>(c + 2, 0))
	{
	}

	void initialize(int numliveCells)
	{
		initial_live_number = numliveCells;
		clear_grid();
		srand(time(0));
		set<pair<int, int>> liveCells;
		while (liveCells.size() < numliveCells)
		{
			int row = rand() % rows + 1;
			int col = rand() % cols + 1;
			liveCells.insert({ row,col });
		}
		for (auto cell : liveCells) //set generate cell to be live cell
		{
			grid[cell.first][cell.second] = 1;
		}
	}
	void clear_grid()
	{
		for (int i = 0; i < grid.size(); i++)
		{
			for (int j = 0; j < grid[0].size(); j++)
			{
				grid[i][j] = 0;
			}
		}
	}
	void print_Grid()
	{

		for (int i = 1; i <= rows; i++)
		{


			for (int j = 1; j <= cols; j++)
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
		for (int i = 1; i <= rows; i++)
		{
			for (int j = 1; j <= cols; j++)
			{
				int liveAround = getLiveAround(i, j);
				if (grid[i][j] == 1)  // 活细胞
				{
					if (liveAround == 2 || liveAround == 3)
					{
						tempGrid[i][j] = 1;  // 继续存活
					}
					else
					{
						tempGrid[i][j] = 0;  // 死亡
					}
				}

				else  // 当前是死细胞
				{
					if (liveAround == 3)
					{
						tempGrid[i][j] = 1;  // 复活
					}
					else
					{
						tempGrid[i][j] = 0;  // 保持死亡
					}
				}
			}
		}

		for (int i = 1; i <= rows; i++)
		{
			for (int j = 1; j <= cols; j++)
			{
				grid[i][j] = tempGrid[i][j];
				
			}
		}
	}
	void play_game(int max_step)
	{

		pause = false;
		while (true)
		{
			if (max_step > 0 && step > max_step)
			{
				cout << "reached max step" << endl;
				break;
			}
			if (!pause) 
			{
				print_Grid();
				cout << "steps: " << step << endl;
				detect_patterns(grid);
				step++;
				update();
			}
			if (_kbhit())
			{
				char input = _getch();
				if (input == 'p')
				{
					pause = true;
					cout << "Game paused. Press 'r' to resume, 's' to save"<<endl;
				}
				else if (input == 'r')
				{
					pause = false;
					cout << "game resumed" << endl;
				}
				else if (input == 'a') 
				{
					int newRow, newCol;
					cout << "input the new cell row and col : ";
					cin >> newRow >> newCol;
					if (newRow >= 1 && newRow < rows && newCol >= 1 && newCol < cols) 
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
				else if (input == 't')
				{
					initialize(initial_live_number);
					step = 1;
					block = false;
					beehive = false;
					blinker = false;
					toad = false;
					LWSS = false;
				}
				else
				{
					cout << "Invalid put" << endl;
				}

			}

			this_thread::sleep_for(chrono::milliseconds(500));
		}
	}
	void saveFile(const string &filename)
	{
		ofstream outfile(filename);
		if (outfile.is_open())
		{
			outfile << step << endl;
			outfile << initial_live_number << endl;
			outfile << rows << " " << cols << endl;
			for (int i = 1; i <= rows; i++) 
			{
				for (int j = 1; j <= cols; j++)
				{
					outfile << grid[i][j] << " ";
				}
				outfile << endl;
			}
		}
	
		cout << "Game saved in " << filename << endl;
		outfile.close();
	}
	void loadFile(const string& filename)
	{
		ifstream infile(filename);
		if (infile.is_open())
		{
			infile >> step;
			infile >> initial_live_number;
			infile >> rows >> cols;

			grid.resize(rows + 2,vector<int>(cols + 2, 0));
			tempGrid.resize(rows + 2, vector<int>(cols + 2, 0));
			for (int i = 1; i <= rows; i++)
			{
				for (int j = 1; j <= cols; j++)
				{
					infile >> grid[i][j];
				}
				cout << endl;
			}
			cout << "Game loaded" << endl;
			infile.close();
		}
		else
		{
			cout << "not found this game" << endl;
		}
	}
	bool findPattern(vector<vector<int>>& grid, vector<vector<int>>& pattern)
	{
		int patternRows = pattern.size();
		int patternCols = pattern[0].size();

		for (int i = 1; i + patternRows <= rows + 1; i++)
		{
			for (int j = 1; j + patternCols <= cols + 1; j++)
			{
				bool if_find = true;
				for (int x = 0; x < patternRows; x++)
				{
					for (int y = 0; y < patternCols; y++)
					{
						if (grid[i + x][j + y] != pattern[x][y])
						{
							if_find = false;
							break;
						}
					}
					if (if_find == false)
						break;
				}
			
				if (if_find == true)
					return true;
			}


		}
		return false;
	}
	
	void notice_pattern(bool &if_detect_pattern,vector<vector<int>> &grid,vector<vector<int>> &pattern, int step, string pattern_name, bool & pattern_detect)
	{
		if (if_detect_pattern == false && findPattern(grid, pattern))
		{
			cout << "Generate "  << pattern_name << " used" << step <<" steps"<< endl;
			if_detect_pattern = true;
			pattern_detect = true;
		}
	}
	
	void detect_patterns(vector<vector<int>>& grid)
	{
		vector<vector<int>> block_pattern = {
			{0, 0, 0, 0},
			{0, 1, 1, 0},
			{0, 1, 1, 0},
			{0, 0, 0, 0}
		};

		vector<vector<int>> beehive_pattern = {
			{0, 0, 0, 0, 0, 0},
			{0, 0, 1, 1, 0, 0},
			{0, 1, 0, 0, 1, 0},
			{0, 0, 1, 1, 0, 0},
			{0, 0, 0, 0, 0, 0}
		};

		vector<vector<int>> blinker_pattern = {
			{0, 0, 0, 0, 0},
			{0, 1, 1, 1, 0},
			{0, 0, 0, 0, 0}
		};

		vector<vector<int>> toad_pattern = {
			{0, 0, 0, 0, 0, 0},
			{0, 0, 1, 1, 1, 0},
			{0, 1, 1, 1, 0, 0},
			{0, 0, 0, 0, 0, 0}
		};

		vector<vector<int>> LWSS_pattern = {
			{0, 0, 0, 0, 0, 0, 0},
			{0, 0, 1, 1, 1, 1, 0},
			{0, 1, 0, 0, 0, 1, 0},
			{0, 0, 0, 0, 1, 0, 0},
			{0, 1, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0}
		};
	
		bool pattern_detect = false;
		notice_pattern(block, grid, block_pattern, step, "Block", pattern_detect);
		notice_pattern(beehive, grid, beehive_pattern, step, "Beehive", pattern_detect);
		notice_pattern(blinker, grid, blinker_pattern, step, "Blinker", pattern_detect);
		notice_pattern(toad, grid, toad_pattern, step, "Toad", pattern_detect);
		notice_pattern(LWSS, grid, LWSS_pattern, step, "LWSS", pattern_detect);

		if (pattern_detect == true)
		{
			pause = true;
			cout << "press r to continue" << endl;
		}

	}
};

	int main()
	{
		int rows, cols, inicial_number;
		int max_step = -1;
		string choice,filename, step_choice;
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
				inFile >> max_step;
				GameOfLife game(rows,cols);
				game.loadFile(filename);
				game.play_game(max_step);
			}

		}
		else if (choice == "N")
		{
			cout << "determined your grid size,rows and cols: ";
			cin >> rows >> cols;
			cout << "initial alive number:";
			cin >> inicial_number;
			cout << "Do you want to set max step?(Y/N)";
			cin >> step_choice;
			if (step_choice == "Y")
			{
				cout << "put in max steps: ";
				cin >> max_step;
			}
			GameOfLife game(rows, cols); 
			game.initialize(inicial_number); 
			game.play_game(max_step);

		}
	}
	/*question 5:
	* ERN:
	block ->8
	beehive -> 11
	blinker -> 6
	
	
	
	
	
	*/