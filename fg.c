#include"global.h"

void call_fg(char **parsed)
{
    printf("fg\n");
    int pg,num,status;
    sscanf(parsed[1],"%d",&num);

    if(num>size)
    {
        fprintf(stderr,"Error: Given job number does not exist\n");
        return;
    }

    pg = runn_proc[num-1].pid;
    printf("%d\n",pg);

    if(pg==-1)
        fprintf(stderr,"Error: Given job number does not exist\n");

    else
    {
        printf("%s\n",runn_proc[num-1].proc_name);
        kill(pg, SIGCONT);
        strcpy(curr_fg_proc_name,runn_proc[num-1].proc_name);
        curr_fg_pid = pg;
        waitpid(pg, &status, WUNTRACED);
    }
}
