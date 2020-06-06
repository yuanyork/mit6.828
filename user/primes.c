#include"kernel/types.h"
#include"kernel/stat.h"
#include"user/user.h"
int main(void){
    int p,rec;int fd[2];
    pipe(fd);
    for(int i=2;i<=35;i++){
        write(fd[1],i,4)
    }
    if()
    read(fd[0],p,4);
    fprintf("prime %d",p);
    while(1){
        read(fd[0],rec,4);
        if(rec%p!=0){
            write(fd[1],rec,4);
        }
    }

}