#include <iostream>
using namespace std;

const int UNASSIGNED = 0;
const int ROWS = 9;
const int COLS = 9;

bool findUnassigned(int grid[][COLS], int& row, int& col){
	for(row = 0; row < ROWS; row++){
		for(col = 0; col < COLS; col++){
			if(grid[row][col] == UNASSIGNED){
				return true;
			}
		}
	}
	return false;
}

bool usedInRow(int grid[][COLS], int row, int num){
	for(int i = 0; i < COLS; i++){
		if(grid[row][i] == num) return true;
	}
	return false;
}

bool usedInColumn(int grid[][COLS], int col, int num){
	for(int i = 0; i < ROWS; i++){
		if(grid[i][col] == num) return true;
	}
	return false;
}

bool usedInBox(int grid[][COLS], int startRow, int startCol, int num){
	for(int i = startRow; i < startRow + 3; i++){
		for(int j = startCol; j < startCol + 3; j++){
			if(grid[i][j] == num) return true;
		}
	}
	return false;
}

bool isSafe(int grid[][COLS], int row, int col, int num){
	return !usedInRow(grid, row, num)
		&& !usedInColumn(grid, col, num)
		&& !usedInBox(grid, row - row % 3, col - col % 3, num);
}

void print(int grid[][COLS]){
	for(int i = 0; i < ROWS; i++){
		for(int j = 0; j < COLS; j++){
			if(grid[i][j] == UNASSIGNED) cout << " ";
			else cout << grid[i][j];
			cout << " ";
		}
		cout << endl;
	}
	cout << endl;
}

bool findSolution(int grid[][COLS]){
	int row, col;

	if(!findUnassigned(grid, row, col)) return true;


	for(int i = 1; i <= 9; i++){
		print(grid);
		if(isSafe(grid, row, col, i)){
			grid[row][col] = i;
			if(findSolution(grid)){
				return true;
			}
			grid[row][col] = UNASSIGNED;
		}

	}

	cout << "row : " << row << " col: " << col << endl;
	return false;
}


int main(){
	int grid[9][9] = {{3, 0, 6, 5, 0, 8, 4, 0, 0},
                      {5, 2, 0, 0, 0, 0, 0, 0, 0},
                      {0, 8, 7, 0, 0, 0, 0, 3, 1},
                      {0, 0, 3, 0, 1, 0, 0, 8, 0},
                      {9, 0, 0, 8, 6, 3, 0, 0, 5},
                      {0, 5, 0, 0, 9, 0, 6, 0, 0},
                      {1, 3, 0, 0, 0, 0, 2, 5, 0},
                      {0, 0, 0, 0, 0, 0, 0, 7, 4},
                      {0, 0, 5, 2, 0, 6, 3, 0, 0}};

      if(findSolution(grid)) print(grid);
      else cout << "no solution found" << endl;
      print(grid);

}