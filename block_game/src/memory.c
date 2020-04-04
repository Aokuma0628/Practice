#include <stdio.h>
#include <stdlib.h>

#include "memory.h"

typedef struct gMemStock {
    void *freeMem;
    struct gMemStock *prev;
    struct gMemStock *next;
}MEMSTOCK;

MEMSTOCK *gStart = NULL;  


/**********************************
* メモリ確保
* @param  size_t size  
* @return void *retMem
************************************/
void *NewMem(size_t size){

	void *retMem = NULL;
	
	if (0 == size) {
		return NULL;
	}
	
	retMem = malloc(size);
	if (NULL == retMem) {
		printf("メモリ確保失敗");
	}
	else {
		StockMem(retMem);
	}
	
	return retMem;
	
}


/**********************************
* メモリ開放ストック
* @param  void *freeMem 
* @return なし
************************************/
void StockMem(void *mem) {
    
    MEMSTOCK *newStock = NULL;
    MEMSTOCK *temp = NULL;
    
    if(mem == NULL){
        printf("引数memはNULLです\n");
        goto l_err;
    }
    
    newStock = (MEMSTOCK *)malloc(sizeof(MEMSTOCK)); 
    if(newStock == NULL){
        printf("メモリ確保エラー\n");
        goto l_err;
    }
    newStock->freeMem = mem;
    newStock->prev = NULL;
    newStock->next = NULL;
    
    if(gStart == NULL){
        gStart = newStock;
    }
    else{
        temp = gStart;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newStock;
        newStock->prev = temp;
    }
    
    l_err:
    return ;
}

/**********************************
* メモリストック開放
* @param  なし
* @return なし
************************************/
void FreeStock(void){
    MEMSTOCK *temp = NULL;
    MEMSTOCK *delTemp = NULL;
    
    temp = gStart;
    if(temp == NULL){
        printf("メモリを開放するものがありません\n");
        goto l_finish;
    }
    else{
        while(temp != NULL){
            delTemp = temp;
            temp = temp->next;
            free(delTemp->freeMem);
            free(delTemp);
        }
        printf("メモリ開放が終了しました\n");
    }
    
    l_finish:
    return ;
}
