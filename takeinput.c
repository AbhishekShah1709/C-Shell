#include"global.h"

int takeInput(char* s,char *dir)
{
    size_t bufsize = 1000;
    getline(&buffer,&bufsize,stdin);

    if (strlen(buffer) != 0) 
    {
        strcpy(s, buffer);

        int s_len = strlen(s);
        s[s_len-1]='\0';

        addhistory(s,dir); 
        
        return 0; 
    } 
    else
        return 1; 
}
