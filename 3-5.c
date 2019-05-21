#include<stdio.h>
#include<stdlib.h>

#define Row 8

void swap(int *x, int *y){
	int temp;
	
	temp = *x;
	*x = *y;
	*y = temp;
}

void sort(int japanese[], int math[], int english[], int size){ //Insertion Sort
	int i, j;
	
	for(i = 1; i < size; i++) {
		j = i;
		while((j > 0) && (japanese[j-1] > japanese[j])) {
			swap(&japanese[j-1], &japanese[j]);
			swap(&math[j-1], &math[j]);
			swap(&english[j-1], &english[j]);
			j--;
		}
	}
}	

int main(int argc, char *argv[])
{
	FILE *file;
	file = fopen("data.csv", "r");
	
	int get_japanese;
	int get_math;
	int get_english;
	
	int jp_data[Row];
	int ma_data[Row];
	int en_data[Row];

	int i = 0, j = 0;

	//fgetcで一文字ずつ読み込み、EOFを返すまで繰り返す。
	printf(" 国  数  英\n");
	while(fscanf(file, "%d %d %d", &get_japanese, &get_math, &get_english) != EOF){
		printf("%3d %3d %3d\n", get_japanese, get_math, get_english);

		jp_data[i] = get_japanese;
		ma_data[i] = get_math;
		en_data[i] = get_english;
		i++;
	}
	
	sort(jp_data, ma_data, en_data, 3);

	printf("\n============\n");
	printf("# 整 列 後 #\n");
	printf("============\n\n");

	printf(" 国  数  英\n");
	for(i = 3; i >= 0; i--){
		printf("%3d %3d %3d\n", jp_data[i], ma_data[i], en_data[i]);
	}

	fclose(file);

	//ファイル書き出し
	FILE *writefile;
	writefile = fopen("Sorted_data2.csv", "w");
	if(writefile == NULL)	{
		printf("Can't File Opened.\n");
	}
	
	fprintf(writefile, " 国, 数, 英\n");
	for(i = 3; i >= 0; i--){
		fprintf(writefile, "%3d,%3d,%3d\n", jp_data[i], ma_data[i], en_data[i]);
	}
	
	printf("\n");
	printf("Success. File Writed.\n");
	fclose(writefile);

	return 0;
}
