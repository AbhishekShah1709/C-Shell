#include "global.h"

void printhistory(char **parsed,char *path_h,int time,int freq)
{
    int y = (freq/time);

    if(time==-1 || freq==-1)
    {
        time=0;
        freq=0;
        y=1;
    }

    int x=0;


    while(x<y)
    {
        sleep(time);
        int num1;
        if(parsed[1]!=NULL)
        {
            char p1[100];
            strcpy(p1,parsed[1]);
            sscanf(p1,"%d",&num1);
        }
        else
            num1=10;

        char bbb[10000];
        int j=0;
        int fd8=open(path_h,O_RDWR );
        int sz=read(fd8,bbb,100000);


        for(int i=sz-1,c=0;i>=0 && c<=num1;i--)
        {
            if(bbb[i]=='!')
            {
                c++;
                if(c>num1)
                {
                    j=i+1;
                }
            }
        }
        for(int i=j;i<sz;i++)
        {
            if(bbb[i]=='!')
            {
                printf("\n");
                continue;
            }
            printf("%c",bbb[i]);
        }

        close(fd8);

        if(freq-time*(x+1)<time)
            sleep(freq-time*(x+1));
        x++;
    }
}

