#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "memory.h"
#include "common.h"
#include "printout.h"

FILE *gFp =NULL;

/**********************************
* ファイル初期化
* @param  なし
* @return int ret(ファイルオープン結果)
************************************/
int InitFile(void){
    int ret = D_OK;
    
    /*ファイルの中身を削除*/
    gFp = fopen("./log/blockgame.log","w");
    fclose(gFp);
    
    
    gFp = fopen("./log/blockgame.log","a");
    
    if(gFp == NULL){
        ret = D_ERROR;
    }

    return ret;
    
}


/**********************************
* ファイルクローズ
* @param  なし
* @return なし
************************************/
void FinFile(void){
    
    if(gFp != NULL){
        fclose(gFp);
        printf("file_close\n");
    }
    
    return ;
}


/**********************************
* ファイル出力用文字変換
* @param  char *befText(変換前文字) 
* @return char *afText(変換後文字)
************************************/
char* LogConvertion(char *befText){
    char *afText = NULL;    /*変換後文字*/
    int len = 0;            /*文字列長*/
    int cnt = 0;            /*カウント*/
    char *retStr = NULL;    /*返り値の文字列*/
    
    
    len = strlen(befText);
    if(len < 0){
        goto l_err;
    }
    
    afText = (char *)NewMem(sizeof(char) * len);
    if(afText == NULL){
        goto l_err;
    }
    StockMem(afText);
    
    while(cnt < len){    
        if(befText[cnt] == '9'){
            strncpy(&afText[cnt],"#",1);
        }
        else if(befText[cnt] == '1'){
            strncpy(&afText[cnt],"@",1);
        }
        else if(befText[cnt] == '0'){
            strncpy(&afText[cnt]," ",1);
        }
        else{
            strncpy(&afText[cnt],&befText[cnt],1);
        }
        cnt++;
    }
    
    retStr = afText;
    
    l_err:
    
    return retStr;
}


/**********************************
* ログファイル書き込み
* @param  char *txt
* @return int ret(ファイル書き込み結果)
************************************/
int LogOut(char *txt){
    char *outStr = NULL;
    int ret = D_OK;
    
    /*初期化済ではない場合は呼ぶ*/
    if(gFp == NULL){
        InitFile();
    }
    
    /*文字変換*/
    outStr = LogConvertion(txt);    
    
    ret = fprintf(gFp,"%s",outStr);
    if(ret > 0){
        ret = D_OK;
    }
    

    return ret;
    
}
