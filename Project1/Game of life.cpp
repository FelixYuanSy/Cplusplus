#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <set>
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
			for (int j = -1; i = j < 2; j++)
			{
				if (i == 0 && j == 0) { continue; }
				int neighbor_Row = row + i;
				int neighbor_Col = col + j;
				if (neighbor_Row >= 0 && neighbor_Row < rows && neighbor_Col >= 0 && neighbor_Col < cols) 
				{
					liveAround += grid[neighbor_Row][neighbor_Col];
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
			int row = rand() % (rows-2)+1;
			int col = rand() % (cols-2)+1;
			liveCells.insert({ row,col });
		}
		for (auto cell : liveCells) //set generate cell to be live cell
		{
			grid[cell.first][cell.second] = 1;
		}
	}

	void print_initialize()
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (grid[i][j] == 1)
				{
					cout << "." << alive;
				}
				else
				{
					cout << "." << dead;
				}
				
			}
			cout << endl;
		}
	}

};
	int main()
	{
		GameOfLife game(11, 11); // 创建一个 5x5 的游戏网格

		game.initialize(5); // 随机生成5个活细胞
		game.print_initialize();         // 打印当前的网格状态
		return 0;


	}
