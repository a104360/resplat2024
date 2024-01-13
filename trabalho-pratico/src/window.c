#include "../include/window.h"

typedef struct window {
    WINDOW * win;
    int x;
    int y;
    int width;
    int height;
};

Window * drawWindow(int height,int width,int y,int x){
    Window * window = malloc(sizeof(struct window));
    window->win = newwin(height,width,y,x);
    refresh();
    wrefresh(window->win);
    window->x = x;
    window->y = y;
    window->height = height;
    window->width = width;
    return window;
}

Window * drawWindowB(int height,int width,int y,int x){
    Window * window = malloc(sizeof(struct window));
    window->win = newwin(height,width,y,x);
    refresh();
    box(window->win,0,0);
    wrefresh(window->win);
    window->x = x;
    window->y = y;
    window->height = height;
    window->width = width;
    return window;
}

void printOnWindow(Window * window,const char * message){

}