#include"kernel/types.h"
#include"kernel/stat.h"
#include"user/user.h"
#define SIZE 5
int 
main(int argc,char **argv){
    int parent_fd[2],child_fd[2];
    char receive[SIZE];int pid;
    pipe(parent_fd);
    pipe(child_fd);
    if(fork()==0){
        pid=getpid();
        close(child_fd[0]);
        write(child_fd[1],"pong",SIZE);
        close(child_fd[1]);
        close(parent_fd[1]);
        read(parent_fd[0],receive,SIZE);
        fprintf(1,"%d:receive from parent %s\n",pid,receive);
        close(parent_fd[0]);

    }else{
        pid=getpid();
        close(child_fd[1]);
        read(child_fd[0],receive,SIZE);
        fprintf(1,"%d:receive from child %s\n",pid,receive);
        close(child_fd[0]);
        close(parent_fd[0]);
        write(parent_fd[1],"ping",SIZE);
        close(parent_fd[1]);
        
    }
    exit(1);
}