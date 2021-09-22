#Linux上でビルドする前提
CC		  := gcc
INCLUDE := -I./include
CFLAGS	:= -W -Wall -g  $(INCLUDE)
LDFLAGS :=
#LDFLAGS := -ljansson -lmosquitto


OBJS	:= $(shell find -type f -name "*.c" | sed -e 's/\.c/\.o/g')
EXES	:= main

.c.o:
	$(CC) $(CFLAGS)  -c $<

$(EXES):  $(OBJS)
	$(CC) -o $(EXES) $(shell find -type f -name "*.o") $(LDFLAGS)

clean:
	-@rm -f  $(OBJS) $(EXES)
	 @echo "clean finish"
