#pragma once

#include <stdio.h>
class Record {

public:
	Record(int matrix_size = 4);
public:
	void showInfo();

private:
	FILE* fp;
	char filename[16];
};

