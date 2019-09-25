#include"global.h"

void call_echo(char **parsed,int time,int freq)
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
        if(parsed[1]==NULL)
        {
            printf("Insufficient arguements for this command\n");
        }
        else
        {
            char* sep = strtok(parsed[1],"\'");

            if(sep!=parsed[1])
                printf("%s\n",sep);

            else
            {
                char* sep1 = strtok(parsed[1],"\"");
                printf("%s\n",sep1);
            }
        }
        if(freq-time*(i+1)<time)
            sleep(freq-time*(i+1));
        i++;
    }
}
