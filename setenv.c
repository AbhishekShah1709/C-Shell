#include"global.h"

void call_setenv(char **parsed,int len,int time,int freq)
{
    int y = (freq/time);

    if(time==-1 || freq==-1)
    {
        time=0;
        freq=0;
        y=1;
    }

    int i=0;

    while(i<y)
    {
        sleep(time);
        if(len>3)
            fprintf(stderr,"Error: Too many arguements\n");
        else if(len<2)
            fprintf(stderr,"Error: Too few arguements\n");

        else 
        {
            if(parsed[2]==NULL)
                setenv(parsed[1],"",1);
            else
                setenv(parsed[1],parsed[2],1);
        }
        if(freq-time*(i+1)<time)
            sleep(freq-time*(i+1));

        i++;
    }
}
