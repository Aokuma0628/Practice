
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

#include "printout.h"
#include "logout.h"
#include "common.h"
#include "memory.h"

#define PRINTF  101     /*出力方法(printf)*/
#define NCURSES 102     /*出力方法(ncerses)*/
#define BLOCK   103     /*表示方法(ブロック)*/
#define NUMBER  104     /*表示方法(数値)*/
#define OTHER   105     /*ブロック以外の文字列*/    
#define SAME    0       /*文字列比較で一致*/

#define BLOCK_H 4    /*ブロックの高さ*/
#define BLOCK_W 4    /*ブロックの広さ*/

#define FIELD_H 20    /*フィールドの高さ*/
#define FIELD_W 18    /*フィールドの広さ*/

/*グローバル変数*/
int gOutputFlg = NCURSES;    /*カーサス選択フラグ*/
int gOutputMtd = BLOCK;        /*表示方法のフラグ*/

/*ブロック形状*/
int gBlockShape[BLOCK_H][BLOCK_W] = {
    {0,0,0,0},
    {0,1,1,0},
    {0,1,1,0},
    {0,0,0,0}
};

/*ステージ(ブロックの途中状態を保存)*/
int gStage[FIELD_H][FIELD_W];

/*ブロックとステージを合わせた画面に表示する前の状態を保存*/
int gField[FIELD_H][FIELD_W];

/*ステージ上でのブロックの位置*/
int gBlock[BLOCK_H][BLOCK_W];

/*ログ出力用フィールドストック*/
char *gStockField[FIELD_H - BLOCK_H]; 

int gBlockX;                             
int gBlockY;

/**********************************
* キーボード入力判定
* @param  なし
* @return int 数値
************************************/
int JudgeKBhit(void)
{
    struct termios oldt, newt;
    int ch = 0;
    int oldf = 0;
    const int ok = 1;
    const int no = 0;
    
	/*fdに関するパラメータ―取得*/
    tcgetattr(STDIN_FILENO, &oldt);
    
    newt = oldt;
    
    /*ローカルモードに
     (カノニカルモード又は入力文字エコー)の反転のAND
     を取ったものを代入*/
    newt.c_lflag &= ~(ICANON | ECHO);
    
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    
    /*ファイルのアクセスモードとファイル状態フラグを取得*/
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    /*ファイル状態をセットする*/
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return ok;
    }

    return no;
}



/**********************************
* ブロック変換専用
* @param  char *befText(変換前文字) 
* @return char *afText(変換後文字)
************************************/
char* Convertion(char *befText){
    char *afText = NULL;    /*変換後文字*/
    int len = 0;            /*文字列長*/
    
    len = strlen(befText);
    if(len < 1 || len > 2){
        printf("ブロック変換ができません\n");
        goto l_err;
    }
    
    afText = (char *)NewMem(sizeof(char) * len * 2);
    if(afText == NULL){
        goto l_err;
    }
    StockMem(afText);
    
    /*ブロック変換*/
    if(strcmp(befText,"9") == SAME){
        afText = "＃";
    }
    else if(strcmp(befText,"1") == SAME){
        afText = "ロ";
    }
    else if(strcmp(befText,"0") == SAME){
        afText = "  ";
    }
    else{
        afText = befText; 
        printf("想定外の文字です\n");
    }  
    
    l_err:
    
    return afText;
}



/**********************************
* 画面表示
* @param  *text 表示文字列
* @return なし
************************************/
void Output(char *text, int flag){
    /*ブロック方法で変換するかの分岐*/
    if(BLOCK == gOutputMtd && flag == BLOCK){
        text = Convertion(text);
    }
    
    if(PRINTF == gOutputFlg){
        printf("%s",text);
    }else{
        SubPrint(text);
    }
    
    return ;
}

/**********************************
* 初期化
* @param  なし
* @return なし
************************************/
void Init(){
    int x,y;
    int ret = D_OK;
    
    /*ステージの囲いを作成*/
    for(y = 0; y < FIELD_H; y++){
        gStage[y][0] = 9;
        gStage[y][1] = 9;
        gStage[y][FIELD_W-1] = 9;
        gStage[y][FIELD_W-2] = 9;
    }
    for(x = 0; x < FIELD_W; x++){
        gStage[FIELD_H-1][x] = 9;
        gStage[FIELD_H-2][x] = 9;
    }
    
    
    gBlockX = 7;
    gBlockY = 0;
    
    
    /*ログファイルの初期化*/
    ret = InitFile();
    if(ret == D_ERROR){
        printf("[ERROER] file_init\n");
    }
    
    return;
}


/**********************************
* ブロック生成
* @param  なし
* @return なし
************************************/
void MakeBlock(){
    int x,y;
    
    for(y = 0; y < BLOCK_H; y++){
        for(x = 0; x < BLOCK_W; x++){
            gBlock[y][x] = gBlockShape[y][x];
        }
    }
    
    return ;
}


/**********************************
* フィールド生成
* @param  なし
* @return なし
************************************/
void MakeField(){
    int x,y;
    
    /*フィールド生成*/
    for(y = 0; y < FIELD_H; y++){
        for(x = 0; x < FIELD_W; x++){
            gField[y][x] = gStage[y][x];
        }
    }
    
    /*不明？*/
    for(y = 0; y < BLOCK_H; y++){
        for(x = 0; x < BLOCK_W; x++){
            gField[gBlockY + y][gBlockX + x] += gBlock[y][x];
        }
    }
    
    
    return ;
}


/**********************************
* フィールド描画
* @param  なし
* @return なし
************************************/
void DrawField(){
    int x,y;
    //char stop;    /*キーボード入力待ち変数*/
    
    /*垂直方向の検索*/
    for(y = 0; y < FIELD_H; y++){
        
        /*水平方向の検索*/
        for(x = 0; x < FIELD_W; x++){
            if(gField[y][x] == 0){
                Output("0",BLOCK);
            }else if(gField[y][x] == 1){
                //print("\x1b[36m1\x1b[39m");    文字色付きの標準出力
                Output("1",BLOCK);
            }else if(gField[y][x] == 9){
                //print("\x1b[36m1\x1b[39m");    文字色付きの標準出力
                Output("9",BLOCK);
            }
        }
        Output("\n",OTHER);
    }
    
    return ;
}



/**********************************
* フィールドのクリア
* @param  なし
* @return なし
************************************/
void FieldClear(){
    int x,y;
    
    /*フィールドのクリア*/
    for(y = 0; y < FIELD_H; y++){
        for(x = 0; x < FIELD_W; x++){
            gField[y][x] = 0;
        }
    }
    
    return ;
}


/**********************************
* フィールド情報の出力
* @param  なし
* @return なし
************************************/
void OutputField(void){
	
	int cnt = 0;
	int cnt2 = 0; 
	
	for(cnt2 = 0; cnt2 < (FIELD_H - BLOCK_H); cnt2++){
        str = (void *)test[cnt2];
        for(cnt = 0;cnt < FIELD_H; cnt++){
            LogOut(str[cnt]);
            LogOut("\n");
        }
    }
    free(str);
    
	return ;
}


/**********************************
* フィールド情報のストック
* @param  なし
* @return なし
************************************/
void StockField(
	int x,y;
	
	
	
	/*ログファイル用にフィールド状態の保持*/
    str = NewMem(FIELD_H * (FIELD_W+5) * sizeof(char));
    memset(str, 0, FIELD_H * (FIELD_W+5));
    for(y = 0; y < FIELD_H; y++){
        for(x = 0; x < FIELD_W; x++){
            sprintf(&str[y][x],"%d",gField[y][x]);
        }
    }
    test[cnt] = (char *)str;
    
	
	
	return ;
}


/**********************************
* テトリス運用
* @param  なし
* @return なし
************************************/
void Operation(void){
	int stop;    /*キーボード入力待ち変数*/
    int arrowKey;    /*方向キー*/
    int cnt = 0;
    int x,y;
    char (*str)[FIELD_H];
    char *test[15];
    int cnt2 = 0;
	
	
	/*ブロックおよびフィールド操作*/
    while(gBlockY < FIELD_H - 4){
        
        /*フィールド操作*/
        DrawField();
        FieldClear();
        gBlockY++;
        MakeField();
        
        SetY(FIELD_H+1);
        Output("「f」が左に移動「j」が右に移動します",OTHER);
        
        SetX(0);
        SetY(0);    /*カーサスのy座標リセット*/
        
        /*方向キー操作*/
        int sleepStep = 0;
       	while (sleepStep < 50) {
	        while (JudgeKBhit() != 0){
		        arrowKey = getchar();
		        
		        if(arrowKey == 'f'){
		            if(gBlockX > 2){
		                gBlockX--;
		                break;
		            }
		        }else if(arrowKey == 'j'){
		         
		            if(gBlockX < FIELD_W-6){
		                   gBlockX++;
		                break;
		            }
		        }
	        }
	        usleep(0.01 * 1000 * 1000);
	        sleepStep++;
	   }
	   cnt++;
	   sleepStep = 0;
	        
    }
    
    
    /*「q」を入力して終了*/
    SetY(FIELD_H+1);
    Output("「q」を入力して終了                   ",OTHER);
        while(1){
        stop = getchar();
        if(stop == 'q'){
            break;
        }
        usleep(0.1 * 1000 * 1000);
    }
    
	return ;
}


/**********************************
* メイン関数
* @param  argc  コンソールでのコマンド引数
* @param  *argv[]  コンソールでのコマンド文字列配列ポインタ
* @return なし
************************************/
int main(int argc, char *argv[]){

    
    /*初期処理*/
    Init();
    MakeBlock();
    MakeField();
    usleep(0.2 * 1000 * 1000);
    
    /*テトリス開始*/
    Operation();
    
    /*終了処理*/
    FinFile();
    NcursesEnd();
    FreeStock();
    
    return 0;
}
