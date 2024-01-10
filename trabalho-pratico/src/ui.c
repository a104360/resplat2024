#include "../include/ui.h"


WINDOW * drawMainMenu(WINDOW * background){
    int mainW = 0,mainH = 0;
    getmaxyx(background,mainH,mainW);
    int width = (int) (mainW * 0.8);
    int height = (int) (mainH * 0.8);
    WINDOW * menu = newwin(height,width,(0.1 * mainH),(0.1 * mainW));
    box(menu,0,0);
    wrefresh(menu);
    return menu;
}