#include"global.h"

void call_pinfo(char **parsed,int time,int freq)
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
            char pp[100];

            int ppp = getpid();
            sprintf(pp, "%d", ppp);    

            char path[100] = "/proc/";
            char path1[100];
            strcat(path,pp);
            strcpy(path1,path);
            strcat(path,"/stat");

            strcat(path1,"/exe");
            char buff[5100];
            char bufff[5100];

            int fd = open(path,O_RDONLY);

            read(fd,buff,5100);

            char *stored[1000];
            int f=0;
            char *del = strtok(buff," ");
            while(del!=NULL)
            {
                stored[f]=del;
                f++;

                del = strtok(NULL," ");
            }

            printf("pid -- %d\n",ppp);
            printf("Process Status -- %s\n",stored[2]);
            printf("Memory -- %s\n",stored[22]);
            realpath(path1,bufff);
            printf("Executable Path -- %s\n",bufff);

        } 

        else
        {
            char pp[100];

            int ppp;
            strcpy(pp,parsed[1]);
            sscanf(pp, "%d",&ppp);    


            char path[100] = "/proc/";
            char path1[100];
            strcat(path,pp);
            strcpy(path1,path);
            strcat(path,"/stat");

            strcat(path1,"/exe");
            char buff[5100];
            char bufff[PATH_MAX+1];

            int fd = open(path,O_RDONLY);

            read(fd,buff,5100);

            char *stored[1000];
            int f=0;
            char *del = strtok(buff," ");
            while(del!=NULL)
            {
                stored[f]=del;
                f++;

                del = strtok(NULL," ");
            }

            printf("pid -- %d\n",ppp);
            printf("Process Status -- %s\n",stored[2]);
            printf("Memory -- %s\n",stored[22]);
            realpath(path1,bufff);
            printf("Executable Path -- %s\n",bufff);
        }
        if(freq-time*(i+1)<time)
            sleep(freq-time*(i+1));
        i++;
    } 
}
