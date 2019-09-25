#include"global.h"

void call_kjob(char **parsed,int len)
{
    if(len!=3)
        fprintf(stderr,"Error: invalid input\n");
    else
    {
        int num1;
        sscanf(parsed[1],"%d",&num1);

        if(num1>size)
            fprintf(stderr,"Error: No such job\n");
        else
        {
            int num2;
            sscanf(parsed[2],"%d",&num2);

            kill(runn_proc[num1-1].pid,num2);
            printf("%d\n",runn_proc[num1-1].pid);
            //runn_proc[num1-1].pid=-1;
        }
    }
}
