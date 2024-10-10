#include <iostream>
#include <vector>
using namespace std;


class GameOfLife
{
private:
	int rows,cols;
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
				if (neighbor_Row >= 0 && neighbor_Row < rows && neighbor_Col >= 0 && neighbor_Col < cols) {
					liveAround += grid[neighbor_Row][neighbor_Col];
				}
			}
		}
		return liveAround;
	}

public:
	GameOfLife(int r, int c): rows(r),cols(c), grid(r, vector<int>(c,0)), tempGrid(r,vector<int>(c,0))
	{
		
	}

};
int main()
{
	return 0;

	
}