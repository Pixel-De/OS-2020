#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>

int main(int argc, char *argv[]){

    char pname[100],arg1[100];
    
    
    if(argv[1] == NULL){
        printf("command: ");
        scanf("%s", pname);
        printf("argument 1:");
        scanf("%s", arg1);

        int pid = fork();
        printf("creating child process...");
        execlp(pname, pname, arg1, NULL, NULL);
        wait(NULL);
        printf("child process terminated...");
        // if(strcmp(pname,"cd")){
        //     printf("arg1: ");
        //     gets(arg1);
        //     execlp(pname, pname,arg1, NULL, NULL );
        //     }
        // else{
            
        //     execlp(pname,pname, NULL, NULL,NULL);
        // }

        
    }
   

    return 0;

}
