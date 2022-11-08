#include "Matrix.h"

extern int matrix_size;
Matrix::Matrix(int size)
	:size(size) {}

void Matrix::initalMatrix(int auctual_size, vector<int>& data_medium, vector<Character>& matrix)
{
	int j = -1;
	int medium_i = 0;

	for (int i = 0; i < auctual_size * auctual_size; i++)
	{
		if (!(i % auctual_size))j++;
		//首行
		if (i < auctual_size)
		{
			matrix.push_back(Character(i % auctual_size, j, 0));
		}
		//尾行
		else if (i >= auctual_size * (auctual_size - 1)) {

			matrix.push_back(Character(i % auctual_size, j, 0));
		}
		//中部
		else
		{
			if ((auctual_size - 1 == i % auctual_size) || (i % auctual_size == 0))
			{

				matrix.push_back(Character(i % auctual_size, j, 0));
			}
			else {
				matrix.push_back(Character(i % auctual_size, j, data_medium[medium_i]));
				medium_i++;
			}
		}
	}
}

void Matrix::showMatrix(int auctual_size, vector<int>& data_medium, vector<Character>& matrix)
{
	int i = 0;
	for (auto it = matrix.begin(); it != matrix.end(); i++, it++) {

		if (!(i % auctual_size)) cout << endl;
		if ((*it).showData() == 0)
		{
			cout << "_" << "\t";
		}
		else
		{
			cout << (*it).showData() << "\t";

		}
		
		//cout << "(" << (*it).showX() << "," << (*it).showY() << ")" << "\t";
	}
}

int Matrix::getSize() const
{
	return this->size;
}

bool Matrix::IsHLinked(int x1, int y1, int x2, int y2, vector<Character>& matrix)
{
	if (x1 == x2 || y1 != y2)
	{
		// 横向不在一条线
		return false;
	}
	unsigned int minX = min(x1, x2); // 找到左边的点
	unsigned int maxX = max(x1, x2); // 找到右边的点

	unsigned int i = 0;
	
	i = (matrix_size + 2) * y1 + minX;
	//while (++i)
	//{
	//	if (matrix[i].showX() == minX && matrix[i].showY() == y1)
	//		break;
	//}


	unsigned int jud = y1 * this->size + maxX;
	for (unsigned int j = i + 1; j < jud /*matrix.size()*/; j++) // 从左到右检查中间的点是不是空的
	{
		if (matrix[j].showData() != 0)
		{
			return false;
		}
	}
	return true;
}

bool Matrix::IsVLinked(int x1, int y1, int x2, int y2, vector<Character>& matrix)
{
	if (y1 == y2 || x1 != x2)
	{
		// 横向不在一条线
		return false;
	}
	unsigned int minY = min(y1, y2); // 找到上边的点
	unsigned int maxY = max(y1, y2); // 找到右边的点
	unsigned int i = 0;
	i = (matrix_size + 2) * minY + x1;
	//for (i = 0; i < matrix.size(); i++)
	//{
	//	if (matrix[i].showY() == minY && matrix[i].showX() == x2)break;
	//}


	unsigned int jud = maxY * this->size + x1;
	for (unsigned int j = i + 1 * size; j < jud/*matrix.size()*/; j += size) // 从上到下检查中间的点是不是空的
	{
		if (matrix[j].showData() != 0)
		{
			return false;
		}
	}
	return true;
}

bool Matrix::IsZeroTurnLinked(int x1, int y1, int x2, int y2, vector<Character>& matrix)
{
	if (IsHLinked(x1, y1, x2, y2, matrix))
	{
		return true;
	}
	if (IsVLinked(x1, y1, x2, y2, matrix))
	{
		return true;
	}
	return false;
}

bool Matrix::IsOneTurnLinked(int x1, int y1, int x2, int y2, vector<Character>& matrix)
{
	int tmpPointX[2] = { x1, x2 };
	int tmpPointY[2] = { y2, y1 };// 找到两个黄色点的坐标
	unsigned int position1 = 0;
	unsigned int position2 = 0;
	position1 = (matrix_size + 2) * x2 + x1;
	position2 = (matrix_size + 2) * y1 + y2;
	//for (position1 = 0; position1 < matrix.size(); position1++) {
	//	if (matrix[position1].showX() == tmpPointX[0] && matrix[position1].showY() == tmpPointY[0] /* && matrix[position1].showData() != 0 */)
	//		break;
	//}

	//for (position2 = 0; position2 < matrix.size(); position2++) {
	//	if (matrix[position2].showX() == tmpPointX[1] && matrix[position2].showY() == tmpPointY[1] /* && matrix[position2].showData() != 0 */)
	//		break;
	//}

	for (int i = 0; i < _countof(tmpPointX); i++)
	{
		if (matrix[position1].showData() == 0 || matrix[position2].showData() == 0)
		{
			if (IsZeroTurnLinked(tmpPointX[i], tmpPointY[i], x1, y1, matrix) &&
				IsZeroTurnLinked(tmpPointX[i], tmpPointY[i], x2, y2, matrix))
			{
				return true;
			}
		}
	}
	return false;
}

bool Matrix::IsTwoTurnLinked(int x1, int y1, int x2, int y2, vector<Character>& matrix)
{
#if 1
	for (int j = 0; j < size; j++)
	{
		int tmpX1 = x1;
		int tmpY1 = j;

		if (j == y1)
		{
			continue; // 与图1重合
		}

		if (tmpX1 == x2 && tmpY1 == y2)
		{
			continue; // 与图2重合
		}

		int tmpX2 = x2;
		int tmpY2 = tmpY1; // 另一个点的坐标

		unsigned int position1 = 0;
		unsigned int position2 = 0;
		position1 = (matrix_size + 2) * tmpY1 + tmpX1;
		position2 = (matrix_size + 2) * tmpY2 + tmpX2;
		//for (position1 = 0; position1 < matrix.size(); position1++) {
		//	if (matrix[position1].showX() == tmpX1 && matrix[position1].showY() == tmpY1 /* && matrix[position1].showData() != 0 */)
		//		break;
		//}
		//for (position2 = 0; position2 < matrix.size(); position2++) {
		//	if (matrix[position2].showX() == tmpX2 && matrix[position2].showY() == tmpY2 /* && matrix[position2].showData() != 0 */)
		//		break;
		//}
		if (matrix[position1].showData() == 0 && matrix[position2].showData() == 0)
		{
			if (IsZeroTurnLinked(tmpX1, tmpY1, tmpX2, tmpY2, matrix)
				&& IsZeroTurnLinked(tmpX1, tmpY1, x1, y1, matrix)
				&& IsZeroTurnLinked(tmpX2, tmpY2, x2, y2, matrix))
			{
				return true;
			}
		}
	}
#endif
#if 1
	for (int j = 0; j < size; j++)
	{
		int tmpX1 = j;
		int tmpY1 = y1;

		if (j == x1)
		{
			continue; // 与图1重合
		}

		if (tmpX1 == x2 && tmpY1 == y2)
		{
			continue; // 与图2重合
		}

		int tmpX2 = tmpX1;
		int tmpY2 = y2; // 另一个点的坐标

		unsigned int position1 = 0;
		unsigned int position2 = 0;
		position1 = (matrix_size + 2) * tmpY1 + tmpX1;
		position2 = (matrix_size + 2) * tmpY2 + tmpX2;
		//for (position1 = 0; position1 < matrix.size(); position1++) {
		//	if (matrix[position1].showX() == tmpX1 && matrix[position1].showY() == tmpY1 /* && matrix[position1].showData() != 0 */)
		//		break;
		//}

		//for (position2 = 0; position2 < matrix.size(); position2++) {
		//	if (matrix[position2].showX() == tmpX2 && matrix[position2].showY() == tmpY2 /* && matrix[position2].showData() != 0 */)
		//		break;
		//}

		if (matrix[position1].showData() == 0 && matrix[position2].showData() == 0)
		{
			if (IsZeroTurnLinked(tmpX1, tmpY1, tmpX2, tmpY2, matrix)
				&& IsZeroTurnLinked(tmpX1, tmpY1, x1, y1, matrix)
				&& IsZeroTurnLinked(tmpX2, tmpY2, x2, y2, matrix))
			{
				return true;
			}
		}
	}
#endif
	return false;

}
