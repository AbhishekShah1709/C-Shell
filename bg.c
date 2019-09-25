#include"global.h"

void call_bg(char **parsed)
{
    int pg,num;
    sscanf(parsed[1],"%d",&num);

    if(num>size)
    {
        fprintf(stderr,"Error: Given job number does not exist\n");
        return;
    }


    pg = runn_proc[num-1].pid;

    if(pg==-1)
        fprintf(stderr,"Error: Given job number does not exist\n");
    else
    {
        printf("%s\n",runn_proc[num-1].proc_name);
        kill(pg, SIGCONT);
    }
}

