// CodeIQ_3133.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
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
	// �W�����͂��C���v�b�g�擾
	string input;
	getline(cin, input);

	// debug
	//input = "f78f447ae68f20af";	// �o�́F16,17,11,12
	//input = "ffbc94fc89a34523";	// �o�́F10,15,12,13

	// 8�~8�̃}�X��
	unsigned char matrix[MATRIX_SIZE][MATRIX_SIZE];

	// �}�g���b�N�X������
	initializeMatrix(matrix, input);

	// ���̋��E���J�E���g
	int downCnt = countDown(matrix);
	// ��̋��E���J�E���g
	int upCnt = countUp(matrix);
	// �E�̋��E���J�E���g
	int rightCnt = countRight(matrix);
	// ���̋��E���J�E���g
	int leftCnt = countLeft(matrix);

	// ����
	std::stringstream stringstream;
	stringstream << downCnt << SEPARATOR << upCnt << SEPARATOR << rightCnt << SEPARATOR << leftCnt;

	// �W���o�͂֌��ʏo��
	cout << stringstream.str() << endl;
    return 0;
}

void initializeMatrix(unsigned char matrix[MATRIX_SIZE][MATRIX_SIZE], string input)
{
	for (int i = 0; i < MATRIX_SIZE; i++) {
		string hexStr;
		hexStr += input.at(i * 2);
		hexStr += input.at(i * 2 + 1);

		// �����񂩂�16�i���ɕϊ�
		unsigned int hex;
		std::stringstream stringstream;
		stringstream << std::hex << hexStr;
		stringstream >> hex;

		// �}�g���b�N�X��������
		for (int j = 0; j < MATRIX_SIZE; j++) {
			int tmp = hex >> (MATRIX_SIZE - j - 1); // �V�t�g���č�������

			unsigned char color;
			if ((tmp & 0x01) == BLACK) {
				color = BLACK;
			}
			else {
				color = WHITE;
			}

			// �F���Z�b�g
			matrix[i][j] = color;
		}
	}
}

int  countDown(unsigned char matrix[MATRIX_SIZE][MATRIX_SIZE])
{
	int countResult = 0;

	for (int i = 0; i < MATRIX_SIZE; i++) {
		if (i == MATRIX_SIZE - 1) {
			// ��ԉ��̃}�X�͌v�Z���Ȃ�
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
			// ��ԏ�̃}�X�͌v�Z���Ȃ�
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
				// ��ԉE�̃}�X�͌v�Z���Ȃ�
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
				// ��ԍ��̃}�X�͌v�Z���Ȃ�
				continue;
			}

			if ((matrix[i][j] == WHITE) && (matrix[i][j - 1] == BLACK)) {
				countResult++;
			}
		}
	}

	return countResult;
}
