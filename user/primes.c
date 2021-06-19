#include"kernel/types.h"
#include"kernel/stat.h"
#include"user/user.h"

#define R 0
#define W 1
int cnt=0;
int trans(int fdR,int fdW);
int subdone(int pd[2]);
int main(int argc , char **argv ){
    int fd[2];
    pipe(fd);
    if(fork()==0){
        close(fd[W]);
        subdone(fd);
        close(fd[R]);
    }else{
        close(fd[R]);
        printf("prime 2\n");
        for(int i=2;i<=35;i++){
            if(i%2!=0){
                write(fd[W],&i,sizeof(i));
            }
        }
        close(fd[W]);
    }
    wait();
    close(1);
    exit();
    return 1;
}
int trans(int fdR,int fdW){
    int rec,tag;
    if(read(fdR,&tag,sizeof(rec))==0){
        return 0;
    }
    printf("prime %d\n",tag);
    while(read(fdR,&rec,sizeof(rec))!=0){
        if(rec%tag!=0){
            write(fdW,&rec,sizeof(rec));
        }
    }
    return 1;
}
int subdone(int pd[2]){
    int fd[2];
    if(pipe(fd)!=0){
        return 0;
    }
    if(fork()==0){
        close(fd[W]);
        
        subdone(fd);

        close(fd[R]);
    }else{
        close(fd[R]);
        trans(pd[R],fd[W]);
        close(fd[W]);
    }
    wait();
    close(1);
    exit();
    return 1;
}