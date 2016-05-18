#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void newArray(int row, int col, int grid[row][col], int newArray[row][col]) {
	for (int i = 0; (i < row); i++) {
		for (int j = 0; (j < col); j++) {
			newArray[i][j] = grid[i][j];
		}
	}
}

void finalPrint(int row, int col, int grid[row][col], int newArray[row][col]) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (newArray[i][j] == 111) {
				grid[i][j] = '#';
			} 
		}
	}
}

void printFinal(int row, int col, int grid[row][col]) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (grid[i][j] == '#') {
				printf("%c ", '#');
			} else {
				printf("%d ", grid[i][j]);
			}
		}
		printf("\n");
	}
}


void blackenSaColumn(int rowLen, int colLen, int grid[rowLen][colLen], int val, int i, int j);
void blackenSaRow(int rowLen, int colLen, int grid[rowLen][colLen], int val, int i, int j);


typedef struct{
	int x;
	int y;
} Coord;


typedef struct{
	Coord first;
	Coord second;
} TwoNearestCoords;

void printGrid(int row, int col, int grid[row][col]){
	int colFlag = 0;
	for (int i = 0; i < row; i++){
		for (int j = 0; j < col; j++){
			if (j < (col - 1)){
				colFlag++;
				printf("%.3d ", grid[i][j]);
			} else{
				colFlag = 0;
				printf("%.3d\n", grid[i][j]);
			}
		}
	}
	printf("\n");
}


bool isSafe(int row, int col, int grid[row][col], int i, int j) {
	if (i == 0 && j == 0) {
		if (grid[i + 1][j] == 111 || grid[i][j + 1] == 111) {
			return false;
		} else {
			return true;
	    }
	} else if (i == 0 && j == col - 1) {
		if (grid[i - 1][j] == 111 || grid[i][j - 1] == 111) {
			return false;
		} else {
			return true;
		}
	} else if (i == row - 1 && j == 0) {
		if (grid[i - 1][j] == 111 || grid[i][j + 1] == 111) {
			return false;
		} else {
			return true;
		}
	} else if (i == row - 1 && j == col - 1) {
		if (grid[i - 1][j] == 111 || grid[i][j - 1] == 111) {
			return false;
		} else {
			return true;
		}
	} else if (i == 0) {
		if (grid[i + 1][j] == 111 || grid[i][j + 1] == 111 || grid[i][j - 1] == 111) {
			return false;
		} else {
			return true;
		}
	} else if (i == row - 1) {
		if (grid[i - 1][j] == 111 || grid[i][j + 1] == 111 || grid[i][j - 1] == 111) {
			return false;
		} else {
			return true;
		}
	} else if (j == 0) {
		if (grid[i - 1][j] == 111 || grid[i + 1][j] == 111 || grid[i][j + 1] == 111) {
			return false;
		} else {
			return true;
		}
	} else if (j == col - 1) {
		if (grid[i - 1][j] == 111 || grid[i + 1][j] == 111 || grid[i][j - 1] == 111) {
			return false;
		} else {
			return true;
		}
	} else {
		if (grid[i - 1][j] == 111 || grid[i + 1][j] == 111 || grid[i][j - 1] == 111 || 
		    grid[i][j + 1] == 111) {
				return false;
		} else {
				return true;
		}
    }
}


int colCountPaubos(int rowLen, int colLen, int grid[rowLen][colLen], int val, int i, int j){
	int colCountResult = 0;
	for (int rowIndex = (i + 1); rowIndex < rowLen; rowIndex++){
		if (grid[rowIndex][j] == val){
			colCountResult ++;
		}
	}

	return colCountResult;
}

int colCountPataas(int rowLen, int colLen, int grid[rowLen][colLen], int val, int i, int j){
	int colCountResult = 0;
	for (int rowIndex = (i - 1); rowIndex >= 0; rowIndex--){
		if (grid[rowIndex][j] == val){
			colCountResult ++;
		}
	}

	return colCountResult;
}

//i and j are of base zero
int colCount(int rowLen, int colLen, int grid[rowLen][colLen], int val, int i, int j){
	if (i == 0){
		return colCountPaubos(rowLen, colLen, grid, val, i, j);
		
	} else if (i > 0 && i < (rowLen - 1)){
		return colCountPaubos(rowLen, colLen, grid, val, i, j) + colCountPataas(rowLen, colLen, grid, val, i, j);
	}

	return colCountPataas(rowLen, colLen, grid, val, i, j);
}

int rowCountRight(int rowLen, int colLen, int grid[rowLen][colLen], int val, int i, int j){
	int rowCountResult = 0;
	for (int colIndex = (j + 1); (colIndex < rowLen); colIndex++){
		if (grid[i][colIndex] == val){
			rowCountResult ++;
		}
	}

	return rowCountResult;
}

int rowCountLeft(int rowLen, int colLen, int grid[rowLen][colLen], int val, int i, int j){
	int rowCountResult = 0;
	for (int colIndex = (j - 1); colIndex >= 0; colIndex--){
		if (grid[i][colIndex] == val){
			rowCountResult ++;
		}
	}

	return rowCountResult;
}

int rowCount(int rowLen, int colLen, int grid[rowLen][colLen], int val, int i, int j){
	if (j == 0){
		return rowCountRight(rowLen, colLen, grid, val, i, j);
		
	} else if (j > 0 && j < (rowLen - 1)){
		return rowCountLeft(rowLen, colLen, grid, val, i, j) + rowCountRight(rowLen, colLen, grid, val, i, j);
		
	}
		
	return rowCountLeft(rowLen, colLen, grid, val, i, j);
}

//searches the nearest coordinate in grid[i][j] that is equal to val
Coord sameColCoordPaubos(int rowLen, int colLen, int grid[rowLen][colLen], int val, int i, int j){
	int row_coord = i;
	int col_coord = j;
	for (int rowIndex = (i + 1); rowIndex < rowLen; rowIndex++){
		if (grid[rowIndex][j] == val){
			row_coord = rowIndex;
			col_coord = j;
			break;
		}
	}

	return (Coord){row_coord, col_coord};
}

Coord sameColCoordPataas(int rowLen, int colLen, int grid[rowLen][colLen], int val, int i, int j){
	int row_coord = i;
	int col_coord = j;

	for (int rowIndex = (i - 1); rowIndex >= 0; rowIndex--){
		if (grid[rowIndex][j] == val){
			row_coord = rowIndex;
			col_coord = j;
			break;
		}
	}

	return (Coord){row_coord, col_coord};
}


TwoNearestCoords sameColCoord(int rowLen, int colLen, int grid[rowLen][colLen], int val, int i, int j){
	Coord paubos = sameColCoordPaubos(rowLen, colLen, grid, val, i, j);
	Coord pataas = sameColCoordPataas(rowLen, colLen, grid, val, i, j);
	return (TwoNearestCoords){paubos, pataas};
}

Coord sameRowCoordRight(int rowLen, int colLen, int grid[rowLen][colLen], int val, int i, int j){
	int row_coord = i;
	int col_coord = j;

	for (int colIndex = (j + 1); (colIndex < rowLen); colIndex++){
		if (grid[i][colIndex] == val){
			row_coord = i;
			col_coord = colIndex;
			break;
		}
	}

	return (Coord){row_coord, col_coord};
}

Coord sameRowCoordLeft(int rowLen, int colLen, int grid[rowLen][colLen], int val, int i, int j){
	int row_coord = i;
	int col_coord = j;

	for (int colIndex = (j - 1); colIndex >= 0; colIndex--){
		if (grid[i][colIndex] == val){
			row_coord = i;
			col_coord = colIndex;
			break;
		}
	}

	return (Coord){row_coord, col_coord};
}


TwoNearestCoords sameRowCoord(int rowLen, int colLen, int grid[rowLen][colLen], int val, int i, int j){
	Coord right = sameRowCoordRight(rowLen, colLen, grid, val, i, j);
	Coord left = sameRowCoordLeft(rowLen, colLen, grid, val, i, j);
	return (TwoNearestCoords){right, left};
}

bool isNeitherShadedOrUnshaded(int rowLen, int colLen, int grid[rowLen][colLen], int i, int j){
	return ((grid[i][j] != 000) && (grid[i][j] != 111));
}


void whiten(int rowLen, int colLen, int grid[rowLen][colLen], int val, int i, int j){
	int currentVal = grid[i][j];
	/*int newI = i;
	int newJ = j;*/
	// if (grid[i][j] != 000 && grid[i][j] != 111){
		if ((rowCount(rowLen, colLen, grid, val, i, j) == 0 || colCount(rowLen, colLen, grid, val, i, j) == 0) && isNeitherShadedOrUnshaded(rowLen, colLen, grid, i, j)){
			if (colCount(rowLen, colLen, grid, val, i, j) == 0){
				grid[i][j] = 000;
				TwoNearestCoords theSameRowCoord = sameRowCoord(rowLen, colLen, grid, currentVal, i, j);

				if (theSameRowCoord.first.y != j){
					/*newI = theSameRowCoord.first.x;
					newJ = theSameRowCoord.first.y;*/
					if (isSafe(rowLen, colLen, grid, theSameRowCoord.first.x, theSameRowCoord.first.y)){
						//blackenSaRow(rowLen, colLen, grid, grid[theSameRowCoord.first.x][theSameRowCoord.first.y], theSameRowCoord.first.x, theSameRowCoord.first.y);
						grid[theSameRowCoord.first.x][theSameRowCoord.first.y] = 111;
					} else{
						whiten(rowLen, colLen, grid, grid[theSameRowCoord.first.x][theSameRowCoord.first.y], theSameRowCoord.first.x, theSameRowCoord.first.y);
					}
				}

				if (theSameRowCoord.second.y != j){
					/*newI = theSameRowCoord.second.x;
					newJ = theSameRowCoord.second.y;*/
					if (isSafe(rowLen, colLen, grid, theSameRowCoord.second.x, theSameRowCoord.second.y)){
						//blackenSaRow(rowLen, colLen, grid, grid[theSameRowCoord.second.x][theSameRowCoord.second.y], theSameRowCoord.second.x, theSameRowCoord.second.y);
						/*blacken(rowLen, colLen, grid, val, theSameColCoord.second.x, j);*/
						grid[theSameRowCoord.second.x][theSameRowCoord.second.y] = 111;
					} else{
						whiten(rowLen, colLen, grid, grid[theSameRowCoord.second.x][theSameRowCoord.second.y], theSameRowCoord.second.x, theSameRowCoord.second.y);
					}
				}
			}

			if (rowCount(rowLen, colLen, grid, val, i, j) == 0){
				grid[i][j] = 000;
				TwoNearestCoords theSameColCoord = sameColCoord(rowLen, colLen, grid, currentVal, i, j);
				if (theSameColCoord.first.x != i){
					/*newI = theSameColCoord.first.x;
					newJ = theSameColCoord.first.y;*/
					if (isSafe(rowLen, colLen, grid, theSameColCoord.first.x, theSameColCoord.first.y)){
						/*blacken(rowLen, colLen, grid, val, i, theSameRowCoord.first.y);*/
						grid[theSameColCoord.first.x][theSameColCoord.first.y] = 111;
						//blackenSaColumn(rowLen, colLen, grid, grid[theSameColCoord.first.x][theSameColCoord.first.y], theSameColCoord.first.x, theSameColCoord.first.y);
					} else{
						whiten(rowLen, colLen, grid, grid[theSameColCoord.first.x][theSameColCoord.first.y], theSameColCoord.first.x, theSameColCoord.first.y);
					}
				}


				if(theSameColCoord.second.x != i){
					/*newI = theSameColCoord.second.x;
					newJ = theSameColCoord.second.y;*/
					if (isSafe(rowLen, colLen, grid, theSameColCoord.second.x, theSameColCoord.second.y)){
						/*blacken(rowLen, colLen, grid, val, i, theSameRowCoord.second.y);*/
						grid[theSameColCoord.second.x][theSameColCoord.second.y] = 111;
						//blackenSaColumn(rowLen, colLen, grid, grid[theSameColCoord.second.x][theSameColCoord.second.y], theSameColCoord.second.x, theSameColCoord.second.y);
					} else{
						whiten(rowLen, colLen, grid, grid[theSameColCoord.second.x][theSameColCoord.second.y], theSameColCoord.second.x, theSameColCoord.second.y);
					}
				}
			}
		} else{
			//grid[i][j] = 000;
			//break;
			/*if (newI != i && newJj != j){
				while ((rowCountRight(rowLen, colLen, grid, currentVal, newI, newJ) > 0 || colCountPaubos(rowLen, colLen, grid, currentVal, newI, newJ) > 0)){
					whiten(rowLen, colLen, grid, grid[newI][newJ], newI, newJ);
				}
			}*/	
		}
}

//int, int, int arr[][], int, int -> int
//Returns 1 if a row and column index (i and j) is at the corner of a 2D array
int isCorner(int rowLen, int colLen, int grid[rowLen][colLen], int i, int j){
	return ((i == 0 && j == 0) || (i == 0 && j == (colLen - 1)) || (i == (rowLen - 1) && j == 0) || (i == (rowLen - 1) && j == (colLen - 1)));
}

//int, int, int arr[][], int, int -> int
//Determines if a row or index (i and j) is at the edge of a 2D array
int isEdge(int rowLen, int colLen, int grid[rowLen][colLen], int i, int j) {
    return (((rowLen - 1) == i) || ((colLen - 1) == j) || (0 == i) || (0 == j));
}

//for numbers not on the edge
void eliminateAroundNonEdges(int rowLen, int colLen, int grid[rowLen][colLen], int i, int j){
	whiten(rowLen, colLen, grid, grid[i][j + 1], i, j + 1);
	whiten(rowLen, colLen, grid, grid[i][j - 1], i, j - 1);
	whiten(rowLen, colLen, grid, grid[i + 1][j], i + 1, j);
	whiten(rowLen, colLen, grid, grid[i - 1][j], i - 1, j);
}

//for numbers on the corner
void eliminateAroundCorner(int rowLen, int colLen, int grid[rowLen][colLen], int i, int j){
	if (i == 0 && j == 0){
		/*grid[i + 1][j] = 000;
		grid[i][j + 1] = 000;*/
		whiten(rowLen, colLen, grid, grid[i + 1][j], i + 1, j);
		whiten(rowLen, colLen, grid, grid[i][j + 1], i, j + 1);
	} else if (i == 0 && j == (colLen - 1)){
		/*grid[i][j - 1] = 000;
		grid[i + 1][j] = 000;*/
		whiten(rowLen, colLen, grid, grid[i][j - 1], i, j - 1);
		whiten(rowLen, colLen, grid, grid[i + 1][j], i + 1, j);
	} else if (i == (rowLen - 1) && j == 0){
		/*grid[i - 1][j] = 000;
		grid[i][j + 1] = 000;*/
		whiten(rowLen, colLen, grid, grid[i - 1][j], i - 1, j);
		whiten(rowLen, colLen, grid, grid[i][j + 1], i, j + 1);
	} else{
		/*grid[i][j - 1] = 000;
		grid[i - 1][j] = 000;*/
		whiten(rowLen, colLen, grid, grid[i][j - 1], i, j - 1);
		whiten(rowLen, colLen, grid, grid[i - 1][j], i - 1, j);
	}		
}

//for numbers with indexes on the edge
void eliminateAroundEdges(int rowLen, int colLen, int grid[rowLen][colLen], int i, int j){
	if (i == 0){
		/*grid[i][j + 1] = 000;
		grid[i][j - 1] = 000;
		grid[i + 1][j] = 000;*/
		whiten(rowLen, colLen, grid, grid[i][j + 1], i, j + 1);
		whiten(rowLen, colLen, grid, grid[i][j - 1], i, j - 1);
		whiten(rowLen, colLen, grid, grid[i + 1][j], i + 1, j);
	} else if (j == 0){
		/*grid[i - 1][j] = 000;
		grid[i][j + 1] = 000;
		grid[i + 1][j] = 000;*/
		whiten(rowLen, colLen, grid, grid[i - 1][j], i - 1, j);
		whiten(rowLen, colLen, grid, grid[i][j + 1], i, j + 1);
		whiten(rowLen, colLen, grid, grid[i + 1][j], i + 1, j);
	} else if (j == (colLen - 1)){
		/*grid[i - 1][j] = 000;
		grid[i][j - 1] = 000;
		grid[i + 1][j] = 000;*/
		whiten(rowLen, colLen, grid, grid[i - 1][j], i - 1, j);
		whiten(rowLen, colLen, grid, grid[i][j - 1], i, j - 1);
		whiten(rowLen, colLen, grid, grid[i + 1][j], i + 1, j);
	} else{
		/*grid[i - 1][j] = 000;
		grid[i][j + 1] = 000;
		grid[i][j - 1] = 000;*/
		whiten(rowLen, colLen, grid, grid[i - 1][j], i - 1, j);
		whiten(rowLen, colLen, grid, grid[i][j + 1], i, j + 1);
		whiten(rowLen, colLen, grid, grid[i][j - 1], i, j - 1);
	}
}

void eliminateAroundShadedParts(int rowLen, int colLen, int grid[rowLen][colLen]){
	for (int i = 0; i < rowLen; i++){
		for (int j = 0; j < colLen; j++){
			if (grid[i][j] == 111){
				if (isEdge(rowLen, colLen, grid, i, j)){
					if (isCorner(rowLen, colLen, grid, i, j)){
						eliminateAroundCorner(rowLen, colLen, grid, i, j);
					} else{
						eliminateAroundEdges(rowLen, colLen, grid, i, j);
					}
				} else{
					eliminateAroundNonEdges(rowLen, colLen, grid, i, j);
				}
			}
		}
	}
}

void threeAdjacentNumEliminate(int rowLen, int colLen, int grid[rowLen][colLen]){
	for (int i = 0; i < rowLen; i++){
		for (int j = 0; j < colLen; j++){
			if ((grid[i][j] != 111 && grid[i][j] != 000)){
				if (((j + 2) < colLen) && (grid[i][j] == grid[i][j + 1]) && (grid[i][j] == grid[i][j + 2])){
					//if (isNeitherShadedOrUnshaded(rowLen, colLen, grid, i, j + 1) && isNeitherShadedOrUnshaded(rowLen, colLen, grid, i, j + 2)){
					grid[i][j] = 111; //shaded
					grid[i][j + 2] = 111; //shaded
					whiten(rowLen, colLen, grid, grid[i][j + 1], i, j + 1); //grid[i][j + 1] = 000; //unshaded
					//}
				} else if (((i + 2) < rowLen) && (grid[i][j] == grid[i + 1][j]) && (grid[i][j] == grid[i + 2][j])){
					//if (isNeitherShadedOrUnshaded(rowLen, colLen, grid, i + 1, j) && isNeitherShadedOrUnshaded(rowLen, colLen, grid, i + 2, j)){
					grid[i][j] = 111; //shaded
					grid[i + 2][j] = 111; //shaded
					whiten(rowLen, colLen, grid, grid[i + 1][j], i + 1, j); //grid[i + 1][j] = 000; //unshaded
					//}
				}
				eliminateAroundShadedParts(rowLen, colLen, grid);
			}
		}
	}
}

void betweenAPairEliminate(int rowLen, int colLen, int grid[rowLen][colLen]) {
	for (int i = 0; i < rowLen; i++) {
		for (int j = 0; j < colLen; j++) {
			if (grid[i][j] != 111 && grid[i][j] != 000) {
				if ((i == 0) || (i == (rowLen - 1))) {
					if ((grid[i][j - 1] == grid[i][j + 1]) && isNeitherShadedOrUnshaded(rowLen, colLen, grid, i, j - 1) && 
						isNeitherShadedOrUnshaded(rowLen, colLen, grid, i, j + 1)) {
						//grid[i][j] = 000;
						whiten(rowLen, colLen, grid, grid[i][j], i, j);
					}
					//eliminateAroundShadedParts(rowLen, colLen, grid);

				} else if ((j == 0) || (j == (colLen - 1))) {
					if ((grid[i - 1][j] == grid[i + 1][j]) && isNeitherShadedOrUnshaded(rowLen, colLen, grid, i - 1, j) && 
						isNeitherShadedOrUnshaded(rowLen, colLen, grid, i + 1, j)) {
						//grid[i][j] = 000;
						whiten(rowLen, colLen, grid, grid[i][j], i, j);
					}
					//eliminateAroundShadedParts(rowLen, colLen, grid);
				} else {
					if ((isNeitherShadedOrUnshaded(rowLen, colLen, grid, i, j - 1) && isNeitherShadedOrUnshaded(rowLen, colLen, grid, i, j + 1)) ||
						(isNeitherShadedOrUnshaded(rowLen, colLen, grid, i - 1, j) && isNeitherShadedOrUnshaded(rowLen, colLen, grid, i + 1, j))){
						if (((grid[i][j - 1] == grid[i][j + 1]) || (grid[i - 1][j] == grid[i + 1][j]))) {
							//grid[i][j] = 000;
							whiten(rowLen, colLen, grid, grid[i][j], i, j);
						}
					}
				}
			}
			eliminateAroundShadedParts(rowLen, colLen, grid);
		}
	}
}

/*bool isNotShadedOrUnshaded(int rowLen, int colLen, int grid[rowLen][colLen], int i, j){
	return ((grid[i][j] != ))
}*/

//I-edit ni para sa giingon ni Chezka
void eliminateNonRecurring(int row, int col, int grid[row][col]){
	for (int i = 0; i < row; i++){
		for (int j = 0; j < col; j++){
			if ((rowCount(row, col, grid, grid[i][j], i, j) == 0) && (colCount(row, col, grid, grid[i][j], i, j) == 0)){
				grid[i][j] = 000; //unshaded
			}
		}
	}
}

void solveHitori(int row, int col, int grid[row][col]){
	for (int j = 0; j < col; j++){
		for (int i = 0; i < row; i++){
			//if (grid[i][j] != 111 && grid[i][j] != 000){
				if ((colCount(row, col, grid, grid[i][j], i, j) == 0 || rowCount(row, col, grid, grid[i][j], i, j) == 0) && isNeitherShadedOrUnshaded(row, col, grid, i, j)){
					whiten(row, col, grid, grid[i][j], i, j); //i-whiten ang katu na coordinate, so ang kapareha niya na nag-inusara ra sa either row or column kay i-blacken
					eliminateAroundShadedParts(row, col, grid);
				}
		}
	}
}

// #define N 6 //input1
// #define N 5 //input2
// #define N 10 //input3
// #define N 5 //input4
//#define N 5 //input5
#define N 20 //input6

int main() {
int A[N][N];
int B[N][N];

FILE *fp;
fp = fopen("INPUT-7.txt","r");
if (fp == NULL){
    printf("INVALID\n");
}else{
    for(int i = 0; i < N; i++) {
        for(int j = 0; j <N; j++) {
            fscanf(fp, "%d", &A[i][j]);
        }
    }
newArray(N, N, A, B);
threeAdjacentNumEliminate(N,N,B);
betweenAPairEliminate(N,N,B);
solveHitori(N, N, B);


finalPrint(N, N, A, B);
printFinal(N, N, A);
      
}
return 0;
}