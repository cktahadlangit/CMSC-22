#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void blackenSaColumn(int rowLen, int colLen, int grid[rowLen][colLen], int val, int i, int j);
void blackenSaRow(int rowLen, int colLen, int grid[rowLen][colLen], int val, int i, int j);


typedef struct{
	int x;
	int y;
} Coord;

//i-explain unsay gamit ani later
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

//Mangita sa nearest coordinate sa grid[i][j] na pareha sa val
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

//maghuna-huna ani later

/*CoordsForUnedges sameColCoordForNonEdges(int rowLen, int colLen, int grid[rowLen][colLen], int val, int i, int j){
	Coord paubos = sameColCoordPaubos(rowLen, colLen, grid, val, i, j);
	Coord pataas = sameColCoordPataas(rowLen, colLen, grid, val, i, j);
	return (CoordsForUnedges){paubos, pataas};
}*/

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

/*CoordsForUnedges sameRowCoordForNonEdges(int rowLen, int colLen, int grid[rowLen][colLen], int val, int i, int j){
	Coord right = sameRowCoordRight(rowLen, colLen, grid, val, i, j);
	Coord left = sameRowCoordLeft(rowLen, colLen, grid, val, i, j);
	return (CoordsForUnedges){right, left};
}*/

TwoNearestCoords sameRowCoord(int rowLen, int colLen, int grid[rowLen][colLen], int val, int i, int j){
	Coord right = sameRowCoordRight(rowLen, colLen, grid, val, i, j);
	Coord left = sameRowCoordLeft(rowLen, colLen, grid, val, i, j);
	return (TwoNearestCoords){right, left};
}


/*void blacken(int rowLen, int colLen, int grid[rowLen][colLen], int val, int i, int j){

	while ((rowCount(rowLen, colLen, grid, val, i, j) != 0) or (colCount(rowLen, colLen, grid, val, i, j) != 0)){
		if (colCount(rowLen, colLen, grid, val, i, j) == 0){
			if (i == 0){
				Coord sameColCoord = sameColCoordPaubos(rowLen, colLen, grid, val, i, j);
			} else if (i > 0 && i < )
		}
	}
}*/

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


/*//for numbers not on the edge
void eliminateAroundNonEdges(int row, int col, int grid[row][col], int i, int j){
	grid[i][j + 1] = 000;
	grid[i][j - 1] = 000;
	grid[i + 1][j] = 000;
	grid[i - 1][j] = 000; 
}

//for numbers on the corner
void eliminateAroundCorner(int row, int col, int grid[row][col], int i, int j){
	if (i == 0 && j == 0){
		grid[i + 1][j] = 000;
		grid[i][j + 1] = 000;
	} else if (i == 0 && j == (col - 1)){
		grid[i][j - 1] = 000;
		grid[i + 1][j] = 000;
	} else if (i == (row - 1) && j == 0){
		grid[i - 1][j] = 000;
		grid[i][j + 1] = 000;
	} else{
		grid[i][j - 1] = 000;
		grid[i - 1][j] = 000;
	}		
}

//for numbers with indexes on the edge
void eliminateAroundEdges(int row, int col, int grid[row][col], int i, int j){
	if (i == 0){
		grid[i][j + 1] = 000;
		grid[i][j - 1] = 000;
		grid[i + 1][j] = 000;
	} else if (j == 0){
		grid[i - 1][j] = 000;
		grid[i][j + 1] = 000;
		grid[i + 1][j] = 000;
	} else if (j == (col - 1)){
		grid[i - 1][j] = 000;
		grid[i][j - 1] = 000;
		grid[i + 1][j] = 000;
	} else{
		grid[i - 1][j] = 000;
		grid[i][j + 1] = 000;
		grid[i][j - 1] = 000;
	}
}*/


//KITAON PA NI UNYA
/*void blacken(int rowLen, int colLen, int grid[rowLen][colLen], int val, int i, int j){
	if (isSafe(rowLen, colLen, grid, i, j)){
		grid[i][j] = 111;
		if (isEdge(rowLen, colLen, grid, i, j)){
			if (isCorner(rowLen, colLen, grid, i, j)){
				eliminateAroundCorner(rowLen, colLen, grid, i, j);
			} else{
				eliminateAroundEdges(rowLen, colLen, grid, i, j);
			}
			
		} else {
			eliminateAroundNonEdges(rowLen, colLen, grid, i, j);
		}
	} else{
		//whiten(rowLen, colLen, grid, grid[i][j], i, j);
	}
} */

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

				//WORK ON THIS ONE TOMORROW
				//Find the appropriate step on what to do
				//Find the appropriate if loop below
				/*if (if sa original kay daghan sila, MEANING MORE THAN ONE, then siya nalang usa sa row or column kay i-black){
					grid[i][j] = 111;
				}*/
		}
	}
}

int main(){
	int a[5][5] = {
		{1, 4, 5, 6, 2},
		{3, 4, 4, 1, 5},
		{1, 1, 3, 4, 5},
		{5, 2, 1, 2, 3},
		{1, 1, 2, 5, 1}
	};

	int b[6][6] = {
		{3, 6, 2, 6, 5, 6},
		{5, 1, 3, 6, 2, 2},
		{5, 6, 1, 6, 4, 3},
		{6, 2, 6, 5, 1, 5},
		{1, 1, 4, 1, 3, 5},
		{3, 3, 5, 2, 6, 5}
	};

	/*int c[8][8] = {
		{2, 2, 2, 1, 6, 6, 1, 1},
		{3, 6, 7, 2, 1, 7, 5, 4},
		{2, 3, 4, 8, 2, 6, 6, 1},
		{1, 1, 1, 5, 6, 7, 3, 1},
		{7, 2, 2, 1, 1, 5, 1, 2},
		{3, 5, 1, 7, 3, 1, 8, 1},
		{6, 4, 2, 3, 5, 4, 7, 8},
		{1, 2, 1, 4, 2, 3, 9, 1},
	};*/

	int d[12][12] = {
		{4, 10, 3, 3, 11, 2, 3, 12, 6, 12, 5, 12},
		{7, 7, 6, 10, 6, 8, 2, 12, 12, 3, 9, 4},
		{4, 2, 10, 5, 3, 10, 9, 11, 3, 4, 9, 8},
		{12, 8, 3, 4, 4, 11, 8, 2, 3, 7, 10, 2},
		{3, 10, 7, 10, 8, 10, 4, 10, 9, 3, 2, 6},
		{5, 1, 4, 11, 11, 9, 2, 6, 3, 8, 1, 3},
		{1, 10, 12, 12, 9, 4, 7, 10, 5, 2, 3, 11},
		{8, 3, 9, 6, 10, 5, 3, 1, 5, 10, 3, 7},
		{7, 6, 4, 1, 12, 5, 5, 3, 4, 6, 8, 11},
		{11, 9, 8, 6, 7, 6, 10, 11, 1, 12, 4, 2},
		{6, 3, 11, 12, 11, 3, 11, 8, 10, 6, 1, 2},
		{9, 7, 8, 2, 5, 8, 6, 4, 10, 1, 11, 12}
	};

	int e[8][8] = {
		{7, 4, 5, 7, 3, 2, 1, 1},
		{4, 4, 2, 5, 7, 7, 6, 3},
		{5, 6, 2, 3, 3, 4, 3, 1},
		{8, 4, 7, 5, 2, 6, 3, 4},
		{4, 2, 6, 7, 1, 7, 4, 6},
		{3, 2, 8, 2, 2, 1, 3, 7},
		{1, 7, 2, 8, 6, 3, 2, 5},
		{4, 1, 3, 4, 4, 8, 1, 2}
	};

	threeAdjacentNumEliminate(5, 5, a);
	betweenAPairEliminate(5, 5, a);
	solveHitori(5, 5, a);
	printGrid(5, 5, a);

	threeAdjacentNumEliminate(6, 6, b);
	betweenAPairEliminate(6, 6, b);
	solveHitori(6, 6, b);
	printGrid(6, 6, b);

	/*threeAdjacentNumEliminate(8, 8, c);
	betweenAPairEliminate(8, 8, c);
	solveHitori(8, 8, c);
	printGrid(8, 8, c);*/
	
	threeAdjacentNumEliminate(12, 12, d);
	betweenAPairEliminate(12, 12, d);
	solveHitori(12, 12, d);
	printGrid(12, 12, d);

	threeAdjacentNumEliminate(8, 8, e);
	betweenAPairEliminate(8, 8, e);
	solveHitori(8, 8, e);
	printGrid(8, 8, e);

	return 0;
}