#ifndef WINDOW_H
#define WINDOW_H
#include <stdlib.h>
#include <ncurses.h>

typedef struct window Window;

Window * drawWindow(int,int,int,int);

Window * drawWindowB(int,int,int,int);

void printOnWindow(Window *,const char *);

#endif
