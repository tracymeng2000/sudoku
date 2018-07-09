#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

const int UNASSIGNED = 0;
const int N = 9;
const int SHUFFLE = 30;

bool findUnassigned(int grid[][N], int& row, int& col){
	for(row = 0; row < N; row++){
		for(col = 0; col < N; col++){
			if(grid[row][col] == UNASSIGNED){
				return true;
			}
		}
	}
	return false;
}

bool usedInRow(int grid[][N], int row, int num){
	for(int i = 0; i < N; i++){
		if(grid[row][i] == num) return true;
	}
	return false;
}

bool usedInColumn(int grid[][N], int col, int num){
	for(int i = 0; i < N; i++){
		if(grid[i][col] == num) return true;
	}
	return false;
}

bool usedInBox(int grid[][N], int startRow, int startCol, int num){
	for(int i = startRow; i < startRow + 3; i++){
		for(int j = startCol; j < startCol + 3; j++){
			if(grid[i][j] == num) return true;
		}
	}
	return false;
}

bool isSafe(int grid[][N], int row, int col, int num){
	return !usedInRow(grid, row, num)
		&& !usedInColumn(grid, col, num)
		&& !usedInBox(grid, row - row % 3, col - col % 3, num);
}

void print(int grid[][N]){
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			if(grid[i][j] == UNASSIGNED) cout << "*";
			else cout << grid[i][j];
			cout << " ";
		}
		cout << endl;
	}
	cout << endl;
}

vector<int> shuffledNums(int size){
	vector<int> result(size);
	for(int i = 0; i < size; i++){
		result[i] = i + 1;
	}
	for(int i = 0; i < SHUFFLE; i++){
		int j = rand() % size;
		int k = rand() % (j + 1);
		int temp = result[k];
		result[k] = result[j];
		result[j] = temp;
	}
	return result;
}

void copyArray(int original[][N], int copy[][N]){
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			copy[i][j] = original[i][j];
		}
	}
}

bool findSolution(int grid[][N]){
	int row = 0, col = 0;
	if(!findUnassigned(grid, row, col)){
		return true;
	}

	for(int i = 1; i <= 9; i++){
		if(isSafe(grid, row, col, i)){
			grid[row][col] = i;
			if(findSolution(grid)){
				return true;
			}
			grid[row][col] = UNASSIGNED;
		}

	}

	return false;
}

bool isUnique(int grid[][N], int removed, int row, int col){
	for(int i = 1; i <= 9; i++){
		if(i != removed && isSafe(grid, row, col, i)){
			int gridCopy[N][N];
			copyArray(grid, gridCopy);
			gridCopy[row][col] = i;
			if(findSolution(gridCopy)) return false;
		}
	}
	return true;
}

bool newCompleteBoard(int grid[][N]){
	int row = 0, col = 0;

	if(!findUnassigned(grid, row, col)) return true;

	vector<int> order = shuffledNums(N);
	for(int i = 0; i < 9; i++){
		int num = order[i];
		if(isSafe(grid, row, col, num)){
			grid[row][col] = num;
			if(newCompleteBoard(grid)){
				return true;
			}
			grid[row][col] = UNASSIGNED;
		}

	}
	return false;
}

void generateBoard(int grid[][N]){
	vector<int> order = shuffledNums(N*N);
	for(int i = 0; i < N*N; i++){
		int row = order[i] / N, col = order[i] % N;
		int removed_num = grid[row][col];
		grid[row][col] = UNASSIGNED;
		if(!isUnique(grid, removed_num, row, col))
			grid[row][col] = removed_num;
	}
}



int main(){
	srand(time(0));
	int grid[N][N] = {{0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0}};

      if(newCompleteBoard(grid)) print(grid);
      generateBoard(grid);
      cout << endl << endl;
      print(grid);
}