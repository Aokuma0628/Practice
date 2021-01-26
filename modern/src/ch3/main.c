#include <stdio.h>
#include <stdbool.h>
#include "main.h"

int buf[16];
int top = 0;

bool isStackFull(void) {
  return top == sizeof(buf) / sizeof(int);
}

bool isStackEmpty(void) {
  return top == 0;
}

bool push(int val) {
  if (isStackFull()) return false;
  buf[top++] = val;
  return true;
}

bool pop(int *pRet) {
  if (isStackEmpty()) return false;
  *pRet = buf[--top];
  return true;
}

int main(void) {
  int p = 0;

  push(1);
  push(2);
  pop(&p);

  printf("1:%d\n", p);
  pop(&p);
  printf("1:%d\n", p);

  return 0;
}
