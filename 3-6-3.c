#include<stdio.h>
#include<stdlib.h>

#define NUM 128
#define SUB 16

int main(){
	FILE *file;
	int num[1]; //受験番号取得変数
	int data[16]; //科目別得点取得変数
    int seiseki[NUM][SUB] = {{}}; //成績反映用変数
	int i = 1, j = 0;
    int count = 1;//データの行数をカウントする変数

	file = fopen("seiseki_data.csv", "r");

	if(file == NULL){
		printf("Can't File Open\n");
	}
	
    /*データの読み込み*/
	while(fscanf(file, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", 
					&num[0], &data[0], &data[1],&data[2], &data[3], &data[4], &data[5], 
					&data[6], &data[7],&data[8], &data[9], &data[10], &data[11]) != EOF){
			
		for(j = 0; j < 12; j++){
           seiseki[i][j] = data[j];
		}
            i++; //受験番号を更新
            count++; //行数をカウント
	}

	fclose(file);

    /*総合得点を求める*/
    for(i = 1; i < count; i++){
            for(j = 0; j < 3; j++){
                seiseki[i][12] += seiseki[i][j]; //試験の合計得点
            }
            for(j = 3; j < 12; j++){
                seiseki[i][13] += seiseki[i][j]; //成績の合計得点
            }
    }

    /*結果の出力*/
    printf("番号 国 数 英  国 社 数 理 音 美 体 技 英 試験 成績\n");
    for(i = 1; i < count; i++){
        printf(" %3d", i); //受験番号
        for(j = 0; j < 12; j++){
            printf("%3d", seiseki[i][j]); //個々の成績データ
        }

        printf("  %3d %3d", seiseki[i][12], seiseki[i][13]); //試験と成績の総合点
        
        printf("\n");
    }

    /*結果ファイルの保存*/
    FILE *writefile;
    writefile = fopen("sum_seiseki.csv", "w");

    if (writefile == NULL) {
        printf("Can't file open.\n");
        return -1;
    }

    fprintf(writefile, "番号, 国, 数, 英,  国, 社, 数, 理, 音, 美, 体, 技, 英, 試験, 成績\n");
    for(i = 1; i < count; i++){
        fprintf(writefile, " %3d,", i); //受験番号
        for(j = 0; j < 12; j++){
            fprintf(writefile, "%3d,", seiseki[i][j]); //個々の成績データ
        }

        fprintf(writefile, "  %3d, %3d", seiseki[i][12], seiseki[i][13]); //試験と成績の総合点
        
        fprintf(writefile, "\n");
    }

    printf("\n");
    printf("Success.\n");

    fclose(writefile);

	return 0;
}