#include"global.h"

void call_pwd(int time,int freq)
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
        char cwd[1024];
        getcwd(cwd,sizeof(cwd));
        printf("%s\n",cwd);

        if(freq-time*(i+1)<time)
            sleep(freq-time*(i+1));
        i++;

    }
}
