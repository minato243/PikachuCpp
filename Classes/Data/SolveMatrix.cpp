#include "SolveMatrix.h"

vector<int> SolveMatrix::createCardCountMatrix(int iconNum, const int imageNum) {
	vector<int> cardCount;

	int cardNum = 0;
	for (int i = 0; i < imageNum; i++) {
		if (rand() % 7 > 0)
			cardCount.push_back(2);
		else
			cardCount.push_back(0);
		cardNum += cardCount[i];
	}

	while (cardNum < iconNum) {

		for (int i = 0; i < imageNum; i++) {
			if (cardNum == iconNum)
				break;
			else {
				if (rand() % 7 > 0) {
					cardCount[i] += 2;
					cardNum += 2;
				}
			}
		}
	}
	return cardCount;
}

vector<vector<int>> SolveMatrix::createMatrix(vector<int> cardCount, int imageNo, int height, int width){
	vector<vector<int>> cardMatrix;
	for (int i = 0; i < height + 2; i++){
		vector<int> row;
		for (int j = 0; j < width + 2; j++){
			row.push_back(0);
		}
		cardMatrix.push_back(row);
	}

	for (int i = 0; i <= height + 1; i++) {
		cardMatrix[i][0] = -1;
		cardMatrix[i][width + 1] = -1;
	}

	for (int j = 0; j <= width + 1; j++) {
		cardMatrix[0][j] = -1;
		cardMatrix[height + 1][j] = -1;
	}

	int k;
	for (int i = 1; i < height + 1; i++) {
		for (int j = 1; j < width + 1; j++) {
			do {
				k = rand() % imageNo;
			} while (cardCount[k] == 0);
			cardMatrix[i][j] = k;
			cardCount[k]--;
		}
	}
	return cardMatrix;
}


//int[][] SolveMatrix::moveMiddleToUpBottom(int x1, int y1, int x2, int y2,
//	int[][] matrix) {
//
//	if ((x1 == x2) && (y1 > PlayScreen.height / 2)
//		&& (y2 > PlayScreen.height / 2)) {
//		if (y1 > y2) {
//			matrix = moveDownFromMiddle(x2, y2, matrix);
//			matrix = moveDownFromMiddle(x1, y1, matrix);
//		}
//		else {
//			matrix = moveDownFromMiddle(x1, y1, matrix);
//			matrix = moveDownFromMiddle(x2, y2, matrix);
//		}
//	}
//	else if ((x1 == x2) && (y1 <= PlayScreen.height / 2)
//		&& (y2 <= PlayScreen.height / 2)) {
//		if (y1 < y2) {
//			matrix = moveUPFromMiddle(x2, y2, matrix);
//			matrix = moveUPFromMiddle(x1, y1, matrix);
//		}
//		else {
//			matrix = moveUPFromMiddle(x1, y1, matrix);
//			matrix = moveUPFromMiddle(x2, y2, matrix);
//		}
//	}
//	else {
//		if (y1 > PlayScreen.height / 2) {
//			matrix = moveDownFromMiddle(x1, y1, matrix);
//		}
//		else
//			matrix = moveUPFromMiddle(x1, y1, matrix);
//		if (y2 > PlayScreen.height / 2)
//			matrix = moveDownFromMiddle(x2, y2, matrix);
//		else
//			matrix = moveUPFromMiddle(x2, y2, matrix);
//	}
//	return matrix;
//}
//
//int[][] SolveMatrix::moveMiddleToLeftRight(int x1, int y1, int x2, int y2,
//	int matrix[][]) {
//
//	if ((y1 == y2) && (x1 > PlayScreen.width / 2)
//		&& (x2 > PlayScreen.width / 2)) {
//		if (x1 < x2) {
//			matrix = moveRightFromMiddle(x1, y1, matrix);
//			matrix = moveRightFromMiddle(x2, y2, matrix);
//		}
//		else {
//			matrix = moveRightFromMiddle(x2, y2, matrix);
//			matrix = moveRightFromMiddle(x1, y1, matrix);
//		}
//	}
//	else if ((y1 == y2) && (x1 <= PlayScreen.width / 2)
//		&& (x2 <= PlayScreen.width / 2)) {
//		if (x1 < x2) {
//			matrix = moveLeftFromMiddle(x2, y2, matrix);
//			matrix = moveLeftFromMiddle(x1, y1, matrix);
//		}
//		else {
//			matrix = moveLeftFromMiddle(x1, y1, matrix);
//			matrix = moveLeftFromMiddle(x2, y2, matrix);
//		}
//	}
//	else {
//		if (x1 > PlayScreen.width / 2)
//			matrix = moveRightFromMiddle(x1, y1, matrix);
//		else
//			matrix = moveLeftFromMiddle(x1, y1, matrix);
//		if (x2 > PlayScreen.width / 2)
//			matrix = moveRightFromMiddle(x2, y2, matrix);
//		else
//			matrix = moveLeftFromMiddle(x2, y2, matrix);
//	}
//	return matrix;
//}
//
//int[][] SolveMatrix::moveTopBottomToMiddle(int x1, int y1, int x2, int y2,
//	int[][] matrix) {
//
//	if ((x1 == x2) && (y1 > PlayScreen.height / 2)
//		&& (y2 > PlayScreen.height / 2)) {
//		if (y1 > y2) {
//			matrix = moveBottomToMiddle(x1, y1, matrix);
//			matrix = moveBottomToMiddle(x2, y2, matrix);
//		}
//		else {
//			matrix = moveBottomToMiddle(x2, y2, matrix);
//			matrix = moveBottomToMiddle(x1, y1, matrix);
//		}
//	}
//	else if ((x1 == x2) && (y1 <= PlayScreen.height / 2)
//		&& (y2 <= PlayScreen.height / 2)) {
//		if (y1 > y2) {
//			matrix = moveTopToMiddle(x2, y2, matrix);
//			matrix = moveTopToMiddle(x1, y1, matrix);
//		}
//		else {
//			matrix = moveTopToMiddle(x1, y1, matrix);
//			matrix = moveTopToMiddle(x2, y2, matrix);
//		}
//	}
//	else {
//		if (y1 > PlayScreen.height / 2)
//			matrix = moveBottomToMiddle(x1, y1, matrix);
//		else
//			matrix = moveTopToMiddle(x1, y1, matrix);
//		if (y2 > PlayScreen.height / 2)
//			matrix = moveBottomToMiddle(x2, y2, matrix);
//		else
//			matrix = moveTopToMiddle(x2, y2, matrix);
//	}
//	return matrix;
//}
//
//int[][] SolveMatrix::moveLeftRightToMiddle(int x1, int y1, int x2, int y2,
//	int[][] matrix) {
//
//	if ((y1 == y2) && (x1 > PlayScreen.width / 2)
//		&& (x2 > PlayScreen.width / 2)) {
//		if (x1 > x2) {
//			matrix = moveRightToMiddle(x1, y1, matrix);
//			matrix = moveRightToMiddle(x2, y2, matrix);
//		}
//		else {
//			matrix = moveRightToMiddle(x2, y2, matrix);
//			matrix = moveRightToMiddle(x1, y1, matrix);
//		}
//	}
//	else if ((y1 == y2) && (x1 <= PlayScreen.width / 2)
//		&& (x2 <= PlayScreen.width / 2)) {
//		if (x1 > x2) {
//			matrix = moveLeftToMiddle(x2, y2, matrix);
//			matrix = moveLeftToMiddle(x1, y1, matrix);
//		}
//		else {
//			matrix = moveLeftToMiddle(x1, y1, matrix);
//			matrix = moveLeftToMiddle(x2, y2, matrix);
//		}
//	}
//
//	else {
//		if (x1 > PlayScreen.width / 2)
//			matrix = moveRightToMiddle(x1, y1, matrix);
//		else
//			matrix = moveLeftToMiddle(x1, y1, matrix);
//		if (x2 > PlayScreen.width / 2)
//			matrix = moveRightToMiddle(x2, y2, matrix);
//		else
//			matrix = moveLeftToMiddle(x2, y2, matrix);
//		;
//	}
//	return matrix;
//}
//
//int[][] SolveMatrix::moveUPFromMiddle(int x, int y, int[][] matrix) {
//	int i;
//	for (i = y; i < PlayScreen.height / 2; i++) {
//		matrix[i][x] = matrix[i + 1][x];
//	}
//	matrix[i][x] = -1;
//	return matrix;
//}
//
//int[][] SolveMatrix::moveDownFromMiddle(int x, int y, int[][] matrix) {
//	int i;
//	for (i = y; i > PlayScreen.height / 2 + 1; i--) {
//		matrix[i][x] = matrix[i - 1][x];
//	}
//	matrix[i][x] = -1;
//	return matrix;
//}
//
//int[][] SolveMatrix::moveLeftFromMiddle(int x, int y, int[][] matrix) {
//	int i;
//	for (i = x; i < PlayScreen.width / 2; i++) {
//		matrix[y][i] = matrix[y][i + 1];
//	}
//	matrix[y][i] = -1;
//	return matrix;
//}
//
//int[][] SolveMatrix::moveRightFromMiddle(int x, int y, int[][] matrix) {
//	int i;
//	for (i = x; i > PlayScreen.width / 2 + 1; i--) {
//		matrix[y][i] = matrix[y][i - 1];
//	}
//	matrix[y][i] = -1;
//	return matrix;
//}
//
//
//
//int[][] SolveMatrix::moveTopToMiddle(int x, int y, int[][] matrix) {
//	int i;
//	for (i = y; i > 0; i--) {
//		matrix[i][x] = matrix[i - 1][x];
//	}
//	matrix[i][x] = -1;
//	return matrix;
//}
//
//int[][] SolveMatrix::moveBottomToMiddle(int x, int y, int[][] matrix) {
//	int i;
//	for (i = y; i < PlayScreen.height; i++) {
//		matrix[i][x] = matrix[i + 1][x];
//	}
//	matrix[i][x] = -1;
//	return matrix;
//}
//
//int[][] SolveMatrix::moveLeftToMiddle(int x, int y, int[][] matrix) {
//	int j;
//	for (j = x; j > 0; j--) {
//		matrix[y][j] = matrix[y][j - 1];
//	}
//	matrix[y][j] = -1;
//	return matrix;
//}
//
//int[][] SolveMatrix::moveRightToMiddle(int x, int y, int[][] matrix) {
//	System.out.println("Move From Right");
//	int j;
//	for (j = x; j < PlayScreen.width + 1; j++) {
//		matrix[y][j] = matrix[y][j + 1];
//	}
//	matrix[y][j] = -1;
//	return matrix;
//}
//


