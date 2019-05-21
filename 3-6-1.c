#include<stdio.h>
#include<stdlib.h>

int main(){
	FILE *file;
	int num[1];
	int data[16];
	int i = 0;

	file = fopen("seiseki_data.csv", "r");

	if(file == NULL){
		printf("Can't File Open\n");
	}
	
	printf("番号 国 数 英  国 社 数 理 音 美 体 技 英\n");
	while(fscanf(file, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", 
					&num[0], &data[0], &data[1],&data[2], &data[3], &data[4], &data[5], 
					&data[6], &data[7],&data[8], &data[9], &data[10], &data[11]) != EOF){
			
			printf("%3d ", num[0]);
			for(i = 0; i < 12; i++){
				printf("%3d",data[i]);
			}
			printf("\n");
			}

	fclose(file);

	return 0;
}

