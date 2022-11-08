#pragma once
using namespace std;
#include <iostream>
#include "Character.h"
#include <vector>

class Matrix
{
public:
	Matrix(int size);
public:
	void initalMatrix(int auctual_size, vector<int>& data_medium, vector<Character>& matrix);

	void showMatrix(int auctual_size, vector<int>& data_medium, vector<Character>& matrix);

	int getSize()const;

	bool IsHLinked(int x1, int y1, int x2, int y2, vector<Character>& matrix);

	bool IsVLinked(int x1, int y1, int x2, int y2, vector<Character>& matrix);

	bool IsZeroTurnLinked(int x1, int y1, int x2, int y2, vector<Character>& matrix);

	bool IsOneTurnLinked(int x1, int y1, int x2, int y2, vector<Character>& matrix);

	bool IsTwoTurnLinked(int x1, int y1, int x2, int y2, vector<Character>& matrix);

private:
	int size;
};

