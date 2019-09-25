#include "global.h"

void addhistory(char *argu,char *path_h)
{
    int fd4=open(path_h,O_WRONLY | O_CREAT ,0777);
    if(fd4==-1)
        perror("not opened");
    lseek(fd4,0,SEEK_END);

    write(fd4,argu,strlen(argu));
    write(fd4,"!",1);
    close(fd4);

    int j=0;
    int fd3=open(path_h,O_RDWR);
    int sz=read(fd3,bbuffer,100000);
    

    for(int i=sz-1,c=0;i>=0 && c<=20;i--)
    {
        if(bbuffer[i]=='!')
        {
            c++;
            if(c>20)
            {
                j=i+1;
            }
        }
    }

    truncate(path_h,0);
    close(fd3);

    int fd7=open(path_h,O_RDWR);
    write(fd7,bbuffer+j,sz-j);
    close(fd7);
}
