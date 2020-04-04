#ifndef _PRINTOUT_H
#define _PRINTOUT_H

int NcursesInit(void);
int NcursesEnd(void);
int SubPrint(char *txt, ...);
void SetX(int x);
void SetY(int y);

#endif
