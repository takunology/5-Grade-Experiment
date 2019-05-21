#include<stdio.h>
#include<stdlib.h>

#define NUM 128
#define SUB 32

/*スワップ用関数*/
void swap(int *x, int *y){
	int temp;
	
	temp = *x;
	*x = *y;
	*y = temp;
}

/*挿入ソート*/
void sort(int student_num[], int exam_jp[], int exam_math[], int exam_eng[], int japanese[], int social[],
         int math[], int science[], int music[], int art[], int pe[], int technology[], int english[], 
         int jyuken_sum[], int naisin_sum[], int naisin_exchenge[], int sougou[], int gouhi[], int count){ 
	
    int i, j;
	
	for(i = 1; i < count; i++) {
		j = i;
		while((j > 0) && (sougou[j-1] > sougou[j])) {
            swap(&student_num[j-1], &student_num[j]);
			swap(&exam_jp[j-1], &exam_jp[j]);
            swap(&exam_math[j-1], &exam_math[j]);
            swap(&exam_eng[j-1], &exam_eng[j]);
            swap(&japanese[j-1], &japanese[j]);
            swap(&social[j-1], &social[j]);
            swap(&math[j-1], &math[j]);
            swap(&science[j-1], &science[j]);
            swap(&music[j-1], &music[j]);
            swap(&art[j-1], &art[j]);
            swap(&pe[j-1], &pe[j]);
            swap(&technology[j-1], &technology[j]);
            swap(&english[j-1], &english[j]);

            swap(&jyuken_sum[j-1], &jyuken_sum[j]);
            swap(&naisin_sum[j-1], &naisin_sum[j]);
            swap(&naisin_exchenge[j-1], &naisin_exchenge[j]);
            swap(&gouhi[j-1], &gouhi[j]);

            swap(&sougou[j-1], &sougou[j]);
			j--;
		}
	}
}	

int main(){
	FILE *file;
	int num[1]; //受験番号取得変数
	int data[16]; //科目別得点取得変数
    int seiseki[NUM][SUB] = {{}}; //成績反映用変数
	int i = 1, j = 0;
    int count = 1;//データの行数をカウントする変数
    double rikei_sum, sougou; //理系科目を1.4倍し、保持しておく変数, 総合点変数
    int nomal_sum; //中学校の成績を加算する変数
    int sougou_all; //受験学生全体での総合点
    int ave; //平均点

    /*グローバル化した変数*/
    int student_num[NUM]; //受験番号 num[0]

    int japanese[NUM]; //国語の成績 data[3]
    int math[NUM]; //数学の成績 data[5]
    int english[NUM]; //英語の成績 data[11]
    int social[NUM]; //社会の成績 data[4]
    int science[NUM]; //理科の成績 data[6]
    int art[NUM]; //美術の成績 data[8]
    int pe[NUM]; //保健体育の成績 data[9]
    int technology[NUM]; //技術家庭の成績 data[10]
    int music[NUM]; //音楽の成績 data[7]
    
    int exam_math[NUM]; //数学試験の得点 data[1]
    int exam_eng[NUM]; //英語試験の得点 data[2]
    int exam_jp[NUM]; //国語試験の得点 data[0]

    int jyuken_sum[NUM]; //受験の総合点 seiseki[i][12]
    int naisin_sum[NUM]; //内申成績の総合点 seiseki[i][13]
    int naisin_exchenge[NUM]; //内申成績を700点満点に換算した点 seiseki[i][14]
    int sougou_g[NUM]; //受験と成績を換算した総合点 seiseki[i][15]
    int gouhi[NUM]; //合否判定 "1" or "0" seiseki[i][16]
    int rank[NUM] = {}; //受験者の順位 seiseki[i][17]

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

        student_num[i] = i;

        exam_jp[i] = data[0];
        exam_math[i] = data[1];
        exam_eng[i] = data[2];

        japanese[i] = data[3];
        social[i] = data[4];
        math[i] = data[5];
        science[i] = data[6];
        music[i] = data[7];
        art[i] = data[8];
        pe[i] = data[9];
        technology[i] = data[10];
        english[i] = data[11];

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

            jyuken_sum[i] = seiseki[i][12];
            naisin_sum[i] = seiseki[i][13];
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
        seiseki[i][15] = seiseki[i][12] + seiseki[i][14]; //個人の総合点
        sougou_all += seiseki[i][15]; //受験学生全体での総合点 人数分forで加算
        
        naisin_exchenge[i] = seiseki[i][14];
        sougou_g[i] = seiseki[i][15];
    }

    ave = (double)(sougou_all / count) + 0.9;//全体の平均点

    /*合否判定*/
    for(i = 1; i < count; i++){
        if(ave <= seiseki[i][15]){
            seiseki[i][16] = 1;
        }
        else{
            seiseki[i][16] = 0;
        }

        gouhi[i] = seiseki[i][16];
    }

    sort(student_num, exam_jp, exam_math, exam_eng, japanese, social, math,
        science, music, art, pe, technology, english, 
        jyuken_sum, naisin_sum, naisin_exchenge, sougou_g, gouhi, count); //並べ替え

    /*ソートされたものをランク付け*/
    printf("ランキング順\n");
    printf("番号 国  数  英 国 社 数 理 音 美 体 技 英 試験 成績 換算 総合 合否 順位\n");
    //EOFの分のカウントを省く
    for(i = count - 1; i > 0; i--){
        rank[j] = rank[j] + 1; //順位1位以降は加算してランク付け
        printf("%3d %3d %3d %3d %2d %2d %2d %2d %2d %2d %2d %2d %2d  %3d %3d  %3d  %3d  %2d   %2d\n", 
        student_num[i], exam_jp[i], exam_math[i], exam_eng[i], japanese[i], social[i], math[i],
        science[i], music[i], art[i], pe[i], technology[i], english[i], 
        jyuken_sum[i], naisin_sum[i], naisin_exchenge[i], sougou_g[i], gouhi[i], rank[j]);
        
        seiseki[i][17] = rank[j];
    }

    /*検索用*/
    int index;
    printf("\n参照する受験番号:");
    scanf("%d", &index);

    printf("番号 国 数 英  国 社 数 理 音 美 体 技 英 試験 成績 換算 総合 合否 順位\n");
    printf(" %3d", index); //受験番号
    
    for(j = 0; j < 12; j++){
        printf("%3d", seiseki[index][j]); //個々の成績データ
    }

    printf("   %3d %3d", seiseki[index][12], seiseki[index][13]); //試験と成績の総合点
    printf("  %3d", seiseki[index][14]); //換算得点
    printf("  %3d", seiseki[index][15]); //総合得点
    printf(" %3d", seiseki[index][16]); //合否判定
    printf("   %3d", seiseki[index][17]); //順位
        
    printf("\n");

	return 0;
}