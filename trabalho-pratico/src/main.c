#include "../include/controller.h"
#include "../include/ui.h"

bool interactive = false;   

int main(int argc,char **argv){

    if(argc == 1){
        interactive = true;
        menus();
        return 0;
    }
    if(argc == 3){
        run(argv);
        return 0;
    }
    if(argc == 4){
        test(argv);
        return 0;
    }

    return 0;
}