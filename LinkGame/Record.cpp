#include "Record.h"

extern int mytime;
Record::Record(int matrix_size)
{
	sprintf(this->filename, "%s%d%s", "file", matrix_size, ".txt");
	this->fp = fopen(this->filename, "r");
}

void Record::showInfo()
{
		FILE* fp1;
		int result = 0;
		int i = fscanf(this->fp, "%d", &result);
		fclose(fp);
		if (mytime < result)
		{
			fp1 = fopen(this->filename, "w+");
			printf("您的成绩成功打破最佳记录!\n");
			printf("该模式下的最好成绩为%ds\n", mytime);
		
			fprintf(fp1, "%d", mytime);
			fclose(fp1);
		}
		else
		{
			printf("您的成绩没有打破最佳记录，请再接再厉\n");
			printf("该模式下的最好成绩为%ds\n", result);
		}
			
}
