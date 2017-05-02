// CodeIQ_3133.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <sstream>
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

#define WHITE		0x00
#define BLACK		0x01

#define MATRIX_SIZE	8
#define SEPARATOR	","

void initializeMatrix(unsigned char matrix[MATRIX_SIZE][MATRIX_SIZE], string input);
int  countDown(unsigned char matrix[MATRIX_SIZE][MATRIX_SIZE]);
int  countUp(unsigned char matrix[MATRIX_SIZE][MATRIX_SIZE]);
int  countRight(unsigned char matrix[MATRIX_SIZE][MATRIX_SIZE]);
int  countLeft(unsigned char matrix[MATRIX_SIZE][MATRIX_SIZE]);

int main()
{
	// 標準入力よりインプット取得
	string input;
	getline(cin, input);

	// debug
	//input = "f78f447ae68f20af";	// 出力：16,17,11,12
	//input = "ffbc94fc89a34523";	// 出力：10,15,12,13

	// 8×8のマス目
	unsigned char matrix[MATRIX_SIZE][MATRIX_SIZE];

	// マトリックス初期化
	initializeMatrix(matrix, input);

	// 下の境界数カウント
	int downCnt = countDown(matrix);
	// 上の境界数カウント
	int upCnt = countUp(matrix);
	// 右の境界数カウント
	int rightCnt = countRight(matrix);
	// 左の境界数カウント
	int leftCnt = countLeft(matrix);

	// 結果
	std::stringstream stringstream;
	stringstream << downCnt << SEPARATOR << upCnt << SEPARATOR << rightCnt << SEPARATOR << leftCnt;

	// 標準出力へ結果出力
	cout << stringstream.str() << endl;
    return 0;
}

void initializeMatrix(unsigned char matrix[MATRIX_SIZE][MATRIX_SIZE], string input)
{
	for (int i = 0; i < MATRIX_SIZE; i++) {
		string hexStr;
		hexStr += input.at(i * 2);
		hexStr += input.at(i * 2 + 1);

		// 文字列から16進数に変換
		unsigned int hex;
		std::stringstream stringstream;
		stringstream << std::hex << hexStr;
		stringstream >> hex;

		// マトリックスを初期化
		for (int j = 0; j < MATRIX_SIZE; j++) {
			int tmp = hex >> (MATRIX_SIZE - j - 1); // シフトして黒白判定

			unsigned char color;
			if ((tmp & 0x01) == BLACK) {
				color = BLACK;
			}
			else {
				color = WHITE;
			}

			// 色をセット
			matrix[i][j] = color;
		}
	}
}

int  countDown(unsigned char matrix[MATRIX_SIZE][MATRIX_SIZE])
{
	int countResult = 0;

	for (int i = 0; i < MATRIX_SIZE; i++) {
		if (i == MATRIX_SIZE - 1) {
			// 一番下のマスは計算しない
			continue;
		}

		for (int j = 0; j < MATRIX_SIZE; j++) {
			if ((matrix[i][j] == WHITE) && (matrix[i + 1][j] == BLACK)) {
				countResult++;
			}
		}
	}

	return countResult;
}
int  countUp(unsigned char matrix[MATRIX_SIZE][MATRIX_SIZE])
{
	int countResult = 0;

	for (int i = 0; i < MATRIX_SIZE; i++) {
		if (i == 0) {
			// 一番上のマスは計算しない
			continue;
		}

		for (int j = 0; j < MATRIX_SIZE; j++) {
			if ((matrix[i][j] == WHITE) && (matrix[i - 1][j] == BLACK)) {
				countResult++;
			}
		}
	}

	return countResult;
}
int  countRight(unsigned char matrix[MATRIX_SIZE][MATRIX_SIZE])
{
	int countResult = 0;

	for (int i = 0; i < MATRIX_SIZE; i++) {
		for (int j = 0; j < MATRIX_SIZE; j++) {
			if (j == MATRIX_SIZE - 1) {
				// 一番右のマスは計算しない
				continue;
			}

			if ((matrix[i][j] == WHITE) && (matrix[i][j + 1] == BLACK)) {
				countResult++;
			}
		}
	}

	return countResult;
}
int  countLeft(unsigned char matrix[MATRIX_SIZE][MATRIX_SIZE])
{
	int countResult = 0;

	for (int i = 0; i < MATRIX_SIZE; i++) {
		for (int j = 0; j < MATRIX_SIZE; j++) {
			if (j == 0) {
				// 一番左のマスは計算しない
				continue;
			}

			if ((matrix[i][j] == WHITE) && (matrix[i][j - 1] == BLACK)) {
				countResult++;
			}
		}
	}

	return countResult;
}
