#include"global.h"

void call_cronjob(char **parsed,int len,char *dir,char *path_h)
{
    int p=0,idx1=0,idx2=0,cnt1=0,cnt2=0,cnt3=0;

    while(p<len)
    {
        if(strcmp(parsed[p],"-c")==0)
            cnt1 = 1;
        else if(strcmp(parsed[p],"-t")==0)
            cnt2 = 1;
        else if(strcmp(parsed[p],"-p")==0)
            cnt3 = 1;
        p++;
    }

    if(cnt1==1 && cnt2==1 && cnt3==1)
    {
        printf("\n");
        p=0;

        while(p<len)
        {
            if(strcmp(parsed[p],"-c")==0)
                idx1 = p;
            else if(strcmp(parsed[p],"-t")==0)
                idx2 = p;
            p++;
        }

        int h=0;
        char *parsed1[40];

        for(int k=idx1+1;k<idx2;k++)
        {
            parsed1[h]=parsed[k];
            h++;
        }

        int ti;
        char tem[100];
        strcpy(tem,parsed[idx2+1]);
        sscanf(tem,"%d",&ti);

        int fr;
        strcpy(tem,parsed[idx2+3]);
        sscanf(tem,"%d",&fr);

        Check(parsed1,dir,idx2-idx1-1,path_h,ti,fr);
    }

    else
        fprintf(stderr,"Error: command not found\n");
}
