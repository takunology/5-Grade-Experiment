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
    double rikei_sum, sougou; //理系科目を1.4倍し、保持しておく変数, 総合点変数
    int nomal_sum; //中学校の成績を加算する変数

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

    /*中学校成績の換算得点*/
    for(i = 1; i < count; i++){
        rikei_sum = 0; //初期化
        nomal_sum = 0;

        rikei_sum = (seiseki[i][5] * 1.4) + (seiseki[i][6] * 1.4) + 0.9; //理科と数学を1.4倍
        for(j = 7; j < 12; j++){
            nomal_sum += seiseki[i][j]; //音、美、体、技、英の成績加算
        }
        nomal_sum = nomal_sum + seiseki[i][3] + seiseki[i][4];//残った国、社の成績加算

        sougou = (rikei_sum + nomal_sum); //合計する
        seiseki[i][14] = ((sougou / 49) * 700) + 0.9; //700点換算

        seiseki[i][15] = seiseki[i][12] + seiseki[i][14]; //総合点
    }

    /*結果の出力*/
    printf("番号 国 数 英  国 社 数 理 音 美 体 技 英 試験 成績 換算 総合\n");
    for(i = 1; i < count; i++){
        printf(" %3d", i); //受験番号
        for(j = 0; j < 12; j++){
            printf("%3d", seiseki[i][j]); //個々の成績データ
        }

        printf("   %3d %3d", seiseki[i][12], seiseki[i][13]); //試験と成績の総合点
        printf("  %3d", seiseki[i][14]); //換算得点
        printf("  %3d", seiseki[i][15]); //総合得点
        
        printf("\n");
    }

	return 0;
}