#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
	FILE *file;
	char fname[] = "data.csv";
	file = fopen(fname, "r");
	
	int data[8];

	//fgetcで一文字ずつ読み込み、EOFを返すまで繰り返す。
	printf(" 国  数  英\n");
	while(fscanf(file, "%d %d %d", &data[1], &data[2], &data[3]) != EOF){
		printf("%3d %3d %3d\n", data[1], data[2], data[3]);
	}

	fclose(file);

	return 0;
}
