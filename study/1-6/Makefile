#注意事項:設定変数後の空白は入れないこと
#コンパイラ
CC = gcc

#拡張子
EXTENSION = c

#コンパイルオプション
CFLAGS  = -g -Wall

#リンクオプション
LDFLAGS = 

#ライブラリオプション
LIBS = 

#インクルードファイルのディレクトリパス
INCLUDE = 

#実行ファイル名
TARGET  = test

#ソースファイルのディレクトリパス
SRCDIR = ./

#オブジェクトファイルのディレクトリパス
OBJDIR    = ./

#ソースファイル
SRCS = $(wildcard $(SRCDIR)/*.$(EXTENSION))

#オブジェクトファイル
OBJS = $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.$(EXTENSION)=.o)))

#実行ファイル作成
#解説:$@ = $(TARGET) $^ = $(OBJS),$(LIBS)[すべての依存するファイル名]
$(TARGET): $(OBJS) $(LIBS)
	$(CC) -o $@ $^ $(LDFLAGS)
	@echo "exec file"

#オブジェクトファイル作成a
#解説:$< = $(SRCS)[最初の依存するファイル名]
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<
	
	
#clean実行コマンド
clean:
	rm  -f $(OBJDIR)/*.o
	@echo "clean finish"