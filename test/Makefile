#注意事項:設定変数後の空白は入れないこと
#コンパイラ
CC = gcc

#拡張子
EXTENSION = c

#コンパイルオプション
CFLAGS  = -g -Wall

#リンクオプション
LDFLAGS = -lncursesw

#ライブラリオプション
LIBS = 

#インクルードファイルのディレクトリパス
INCLUDE = -I./include

#実行ファイル名
TARGET  = ./bin/test

#ソースファイルのディレクトリパス
SRCDIR = ./src

#オブジェクトファイルのディレクトリパス
OBJDIR    = ./obj

#ソースファイル
SRCS = $(wildcard $(SRCDIR)/*.$(EXTENSION))

#オブジェクトファイル
OBJS = $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.$(EXTENSION)=.o)))

#実行ファイル作成
#解説:$@ = $(TARGET) $^ = $(OBJS),$(LIBS)[すべての依存するファイル名]
$(TARGET): $(OBJS) $(LIBS)
	$(CC) -o $@ $^ $(LDFLAGS)

#オブジェクトファイル作成a
#解説:$< = $(SRCS)[最初の依存するファイル名]
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<
	
	
#clean実行コマンド
clean:
	rm  -f $(OBJDIR)/*.o
	@echo "clean finish"