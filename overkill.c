#include"global.h"

void call_overkill()
{
    for(int h=0;h<size;h++)
    {
        printf("h -- %d, name -- %s, pid -- %d\n",h,runn_proc[h].proc_name,runn_proc[h].pid);
        if(runn_proc[h].pid!=-1)
        {
            kill(runn_proc[h].pid,9);
        }
    }
}
