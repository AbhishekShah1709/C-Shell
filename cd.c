#include"global.h"

void call_cd(char **parsed,char *dir,int time,int freq)
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
        if(parsed[1]!=NULL)
        {
            if(!strcmp(parsed[1],"-"))
            {
                char temp[1000];
                strcpy(temp,prev1);
                getcwd(prev1,1000);
                chdir(temp);
                return ;
            }
        }

        getcwd(prev1,1000);
        if(parsed[1]==NULL)
        {
            if(chdir(dir)!=0)
            {
                perror("Cannot access");
            }
        }
        else if(!strcmp(parsed[1],"~"))
        {
            if(chdir(dir)!=0)
            {
                perror("Cannot access");
            }
        }
        else if(parsed[1][0]=='~')
        {
            char d[100];
            strcpy(d,dir);
            int len3 = strlen(d);
            int len2 = strlen(parsed[1]);
            for(int i=1;i<len2;i++)
            {
                d[len3]=parsed[1][i];
                len3++;
            }

            if(chdir(d)!=0)
            {
                perror("Cannot access");
            }
        }
        else
        {
            if(chdir(parsed[1])!=0)
            {
                perror("Cannot access");
            }
        }
        if(freq-time*(i+1)<time)
            sleep(freq-time*(i+1));
        i++;
    }
}
