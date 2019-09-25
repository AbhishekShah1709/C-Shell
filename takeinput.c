#include"global.h"

int takeInput(char* s,char *dir)
{
    size_t bufsize = 1000;
    getline(&buffer,&bufsize,stdin);

    char buff[100000];

    if(((int)buffer[0])==27)
    {
        char temp_str[1000];
        long int len = strlen(buffer);
        len--;

        int no_of_ups = len/3;

        int fd = open(dir,O_RDONLY,0777);
        if(fd==-1)
            perror("not opened");

        else
        {
            int siz = read(fd,buff,100000);
            lseek(fd,0,SEEK_END);
            int j;
            int c=0;

            for(int i=siz-1;i>=0;i--)
            {
                if(buff[i]=='!')
                {
                    c++;
                    if(c==no_of_ups+1)
                    {
                        j=i+1;
                    }
                }
            }

            int x=0;


            for(int k=j;k<siz;k++)
            {
                if(buff[k]!='!')
                {
                    temp_str[x]=buff[k];
                    x++;
                }
                else
                {
                    temp_str[x]='\0';
                    x++;
                }
            }
        }

        printf("%s\n",temp_str);
        strcpy(s, temp_str);
        addhistory(temp_str,dir); 
        return 0;
    }

    else if(strlen(buffer) != 0) 
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
