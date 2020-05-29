#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


/**********************************
* メイン関数
* @param  argc  コンソールでのコマンド引数
* @param  *argv[]  コンソールでのコマンド文字列配列ポインタ
* @return なし
************************************/
int main(int argc, char *argv[]){
	int stop;	/*キーボード入力待ち変数*/
	int arrowKey;	/*方向キー*/
	
	arrowKey = getchar();
	printf("arrowKey = %d\n",arrowKey);
	if(arrowKey == 27){
		printf("矢印キーが入力されました\n");
	}
	
	
	
	/*「q」を入力して終了*/
	printf("「q」を入力して終了\n");
	while(1){
		stop = getchar();
		if(stop == 'q'){
			break;
		}
	}
	
	return 0;
}
