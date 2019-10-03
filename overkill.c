#include"global.h"

void call_overkill(int len)
{
    if(len!=1)
    {
        fprintf(stderr,"Error: Invalid arguements\n");
        return;
    }
    for(int h=0;h<size;h++)
    {
        if(runn_proc[h].pid!=-1)
        {
            kill(runn_proc[h].pid,9);
        }
    }
}
