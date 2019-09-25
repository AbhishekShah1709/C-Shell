#include"global.h"

void printDir(char *fixed)
{
    char cwd[1024];
    getcwd(cwd,sizeof(cwd));

    int len = strlen(fixed);
    int len1 = strlen(cwd);

    int cnt=0;
    for(int i=0;i<len;i++)
    {
        if(fixed[i]==cwd[i])
            cnt++;
    }

    int k=0;
    if(cnt==len)
    {
        cwd[k]='~';
        k++;
        for(int i=len;i<len1;i++)
        {
            cwd[k] = cwd[i]; 
            k++;
        }
        cwd[k]='\0';
        printf("%s",cwd);
    }

    else
        printf("%s",cwd);
}
