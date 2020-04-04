#include <ncurses.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>

#include "common.h"
#include "logout.h"

int gInitFlg = D_FALSE;    /*初期化フラグ*/
static int sCorY;        /*出力画面のy座標*/
static int sCorX;        /*出力画面のy座標*/


/**********************************
* カーサスの初期化
* @param  なし
* @return なし(今後はエラーログなどを入れたいためにint)
************************************/
int NcursesInit(){
    
    setlocale(LC_ALL,"");    /*全角文字対応*/
    initscr();                /*端末制御の開始*/
    newwin(30, 30, 0, 0);
    
    /*カラーの初期化*/
    start_color();
    init_pair(1,COLOR_RED,COLOR_BLACK);
    init_pair(2,COLOR_WHITE,COLOR_BLACK);
    curs_set(0);
    
    /*座標の初期化*/
    sCorX = 0;
    sCorY = 0;
    
    gInitFlg = D_TRUE;
    
    return 0;
}


/**********************************
* カーサス終了
* @param  なし
* @return なし(今後はエラーログなどを入れたいためにint)
************************************/
int NcursesEnd(void){
    endwin();
    
    return 0;
}


/**********************************
* 画面表示
* @param  なし
* @return なし(今後はエラーログなどを入れたいためにint)
************************************/
int SubPrint(char *txt, ...){
    
    //int ret = OK;
    
    if(gInitFlg == D_FALSE){
        gInitFlg = D_TRUE;
        NcursesInit();
    }
    
    /*色付け分岐*/
    /*if(*txt == '1'){
        attrset(COLOR_PAIR(1));
    }else{
        attrset(COLOR_PAIR(2));
    }
    */
    
    if(strcmp(txt,"\n") == 0){
        sCorY++;
        sCorX = 0;
    }else{    
        /*使い方:[int move(int new_y, int new_x);]*/
        mvprintw(sCorY,sCorX,"%s",txt);    
        
        refresh();
        sCorX++;
        sCorX++;
    }    
    
    return 0;
    
}



/**********************************
* カーサスのx座標セット
* @param  int x
* @return なし
************************************/
void SetX(int x){
    sCorX = x;
    
    return ;
}



/**********************************
* カーサスのy座標セット
* @param  int y
* @return なし
************************************/
void SetY(int y){
    sCorY = y;
    
    return ;
}




