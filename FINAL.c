#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void blackenSaColumn(int rowLen, int colLen, int grid[rowLen][colLen], int val, int i, int j);
void blackenSaRow(int rowLen, int colLen, int grid[rowLen][colLen], int val, int i, int j);


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
				printf("%s ", "**");
			} else {
				printf("%.2d ", grid[i][j]);
			}
		}
		printf("\n");
	}
}


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


bool isNeitherShadedOrUnshaded(int rowLen, int colLen, int grid[rowLen][colLen], int i, int j){
	return ((grid[i][j] != 000) && (grid[i][j] != 111));
}

void blackenSaColumn(int rowLen, int colLen, int grid[rowLen][colLen], int val, int i, int j){
	for (int ii = 0; ii < rowLen; ii++){
		if ((grid[ii][j] == val) && isNeitherShadedOrUnshaded(rowLen, colLen, grid, ii, j)){
			if (isSafe(rowLen, colLen, grid, ii, j)){
				grid[ii][j] = 111;
			}
		}
	}
}

void blackenSaRow(int rowLen, int colLen, int grid[rowLen][colLen], int val, int i, int j){
	for (int jj = 0; jj < colLen; jj++){
		if ((grid[i][jj] == val) && isNeitherShadedOrUnshaded(rowLen, colLen, grid, i, jj)){
			if (isSafe(rowLen, colLen, grid, i, jj)){
				grid[i][jj] = 111;
			}
		}
	}
}


void whiten(int rowLen, int colLen, int grid[rowLen][colLen], int val, int i, int j){
	int currentVal = grid[i][j];
	if ((rowCount(rowLen, colLen, grid, val, i, j) == 0 || colCount(rowLen, colLen, grid, val, i, j) == 0) && isNeitherShadedOrUnshaded(rowLen, colLen, grid, i, j)){
		if (colCount(rowLen, colLen, grid, val, i, j) == 0){
			grid[i][j] = 000;
			blackenSaRow(rowLen, colLen, grid, currentVal, i, j);
		}

		if (rowCount(rowLen, colLen, grid, val, i, j) == 0){
			grid[i][j] = 000;
			blackenSaColumn(rowLen, colLen, grid, currentVal, i, j);
		}
	} else if (rowCount(rowLen, colLen, grid, currentVal, i, j) > 0 && colCount(rowLen, colLen, grid, currentVal, i, j) > 0){
		grid[i][j] = 000;
		blackenSaRow(rowLen, colLen, grid, currentVal, i, j);
		blackenSaColumn(rowLen, colLen, grid, currentVal, i, j);
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
		whiten(rowLen, colLen, grid, grid[i + 1][j], i + 1, j);
		whiten(rowLen, colLen, grid, grid[i][j + 1], i, j + 1);
	} else if (i == 0 && j == (colLen - 1)){
		whiten(rowLen, colLen, grid, grid[i][j - 1], i, j - 1);
		whiten(rowLen, colLen, grid, grid[i + 1][j], i + 1, j);
	} else if (i == (rowLen - 1) && j == 0){
		whiten(rowLen, colLen, grid, grid[i - 1][j], i - 1, j);
		whiten(rowLen, colLen, grid, grid[i][j + 1], i, j + 1);
	} else{
		whiten(rowLen, colLen, grid, grid[i][j - 1], i, j - 1);
		whiten(rowLen, colLen, grid, grid[i - 1][j], i - 1, j);
	}		
}

//for numbers with indexes on the edge
void eliminateAroundEdges(int rowLen, int colLen, int grid[rowLen][colLen], int i, int j){
	if (i == 0){
		whiten(rowLen, colLen, grid, grid[i][j + 1], i, j + 1);
		whiten(rowLen, colLen, grid, grid[i][j - 1], i, j - 1);
		whiten(rowLen, colLen, grid, grid[i + 1][j], i + 1, j);
	} else if (j == 0){
		whiten(rowLen, colLen, grid, grid[i - 1][j], i - 1, j);
		whiten(rowLen, colLen, grid, grid[i][j + 1], i, j + 1);
		whiten(rowLen, colLen, grid, grid[i + 1][j], i + 1, j);
	} else if (j == (colLen - 1)){
		whiten(rowLen, colLen, grid, grid[i - 1][j], i - 1, j);
		whiten(rowLen, colLen, grid, grid[i][j - 1], i, j - 1);
		whiten(rowLen, colLen, grid, grid[i + 1][j], i + 1, j);
	} else{
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
					grid[i][j] = 111; //shaded
					grid[i][j + 2] = 111; //shaded
					whiten(rowLen, colLen, grid, grid[i][j + 1], i, j + 1);
					//}
				} else if (((i + 2) < rowLen) && (grid[i][j] == grid[i + 1][j]) && (grid[i][j] == grid[i + 2][j])){
					grid[i][j] = 111; //shaded
					grid[i + 2][j] = 111; //shaded
					whiten(rowLen, colLen, grid, grid[i + 1][j], i + 1, j);
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
						whiten(rowLen, colLen, grid, grid[i][j], i, j);
					}
					//eliminateAroundShadedParts(rowLen, colLen, grid);

				} else if ((j == 0) || (j == (colLen - 1))) {
					if ((grid[i - 1][j] == grid[i + 1][j]) && isNeitherShadedOrUnshaded(rowLen, colLen, grid, i - 1, j) && 
						isNeitherShadedOrUnshaded(rowLen, colLen, grid, i + 1, j)) {
						whiten(rowLen, colLen, grid, grid[i][j], i, j);
					}
				} else {
					if ((isNeitherShadedOrUnshaded(rowLen, colLen, grid, i, j - 1) && isNeitherShadedOrUnshaded(rowLen, colLen, grid, i, j + 1)) ||
						(isNeitherShadedOrUnshaded(rowLen, colLen, grid, i - 1, j) && isNeitherShadedOrUnshaded(rowLen, colLen, grid, i + 1, j))){
						if (((grid[i][j - 1] == grid[i][j + 1]) || (grid[i - 1][j] == grid[i + 1][j]))) {
							whiten(rowLen, colLen, grid, grid[i][j], i, j);
						}
					}
				}
			}
			eliminateAroundShadedParts(rowLen, colLen, grid);
		}
	}
}

void solveHitori(int row, int col, int grid[row][col]){
	for (int j = 0; j < col; j++){
		for (int i = 0; i < row; i++){
			if ((colCount(row, col, grid, grid[i][j], i, j) == 0 || rowCount(row, col, grid, grid[i][j], i, j) == 0) && isNeitherShadedOrUnshaded(row, col, grid, i, j)){
				whiten(row, col, grid, grid[i][j], i, j); //i-whiten ang katu na coordinate, so ang kapareha niya na nag-inusara ra sa either row or column kay i-blacken
				eliminateAroundShadedParts(row, col, grid);
			}
		}
	}
}


//#define N 6 5 10 5 5 9 7 5 12 9 20
#define N 20

int main() {
	int A[N][N];
	int B[N][N];
	FILE *fp;
	fp = fopen("INPUT-20.txt","r");
	if (fp == NULL){
    	printf("INVALID\n");
	}else{
    	for(int i = 0; i < N; i++) {
        	for(int j = 0; j < N; j++) {
            	fscanf(fp, "%d", &A[i][j]);
        }
    }
    	newArray(N, N, A, B);
    	threeAdjacentNumEliminate(N,N,B);
    	betweenAPairEliminate(N,N,B);
    	solveHitori(N, N, B);
    	finalPrint(N, N, A, B);
    	printFinal(N, N, A);
        printf("\n");
	}
	
	return 0;
}