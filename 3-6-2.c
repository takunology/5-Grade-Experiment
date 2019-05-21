#include<stdio.h>
#include<stdlib.h>

#define NUM 128
#define SUB 16

int main(){
	FILE *file;
	int num[1];
	int data[16];
    int seiseki[NUM][SUB];
	int i = 1, j = 0;


	file = fopen("seiseki_data.csv", "r");

	if(file == NULL){
		printf("Can't File Open\n");
	}
	
	while(fscanf(file, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", 
					&num[0], &data[0], &data[1],&data[2], &data[3], &data[4], &data[5], 
					&data[6], &data[7],&data[8], &data[9], &data[10], &data[11]) != EOF){
			
		for(j = 0; j < 12; j++){
           seiseki[i][j] = data[j];
		}
            i++; //受験番号を更新
	}

	fclose(file);

	printf("番号 国 数 英  国 社 数 理 音 美 体 技 英\n");
    for(i = 1; i < 101; i++){
        printf(" %3d", i); //受験番号
        for(j = 0; j < 12; j++){
            printf("%3d", seiseki[i][j]); //個々の成績データ
        }
        printf("\n");
    }

	return 0;
}
