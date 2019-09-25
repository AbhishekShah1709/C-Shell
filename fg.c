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
        kill(pg, 18);
        printf("hii1\n");
        strcpy(curr_fg_proc_name,runn_proc[num-1].proc_name);
        printf("hii2\n");
        curr_fg_pid = pg;
        printf("hii3\n");
        ctrl_z_cond=1;
        printf("hii4\n");
        printf("%d\n",pg);
        waitpid(pg, &status, WUNTRACED);
        printf("%d\n",pg);
        printf("hii5\n");
        ctrl_z_cond=0;
        printf("hii6\n");
    }
}
