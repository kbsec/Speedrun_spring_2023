#include "execute.h"


int main(int argc, char** argv){

    char *cmd[] = {"whoami"};
    //char *cmd[] = {"whoami", "arp -a", "ipconfig /all", "ping 1.1.1.1"};
    
    int cmd_size = 1;
    for(int i =0; i < cmd_size; i++){
        SIZE_T out_size = 0;
        LPBYTE x = ExecuteCmd(cmd[i], &out_size);
        printf("And the winner is!: %s: %zu\n",x, out_size);
        free(x);
    }
    return 0 ;
}