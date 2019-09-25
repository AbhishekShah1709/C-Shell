#include"global.h"

void call_redirection(char **parsed,int len)
{
    char *new_parsed[40];
    int iter1=-1,iter2=-1,iter3=-1,iter4=-1;
    int new_flag=0;

    for(int x=len-1;x>=0;x--)
    {
        if(strcmp(parsed[x],">")==0)
        {
            iter1=x;
            break;
        }
    }

    for(int x=len-1;x>=0;x--)
    {
        if(strcmp(parsed[x],"<")==0)
        {
            iter2=x;
            break;
        }
    }

    for(int x=len-1;x>=0;x--)
    {
        if(strcmp(parsed[x],">>")==0)
        {
            iter4=x;
            break;
        }
    }

    if(iter4>iter1)
    {
        iter1=iter4;
        new_flag=1;
    }

    for(int x=0;x<len;x++)
    {
        if(strcmp(parsed[x],">")==0 || strcmp(parsed[x],"<")==0)
        {
            iter3=x;
            break;
        }
    }

    int j=0;
    for(int x=0;x<iter3;x++)
    {
        new_parsed[j]=parsed[x];
        j++;
    }

    new_parsed[j]=NULL;
//    if(new_parsed[1]!=NULL)
  //      printf("%s\n",new_parsed[1]);

    int fd;
    int fd1;
    int fd2;
    int fd3;

    if(iter1!=-1)
    {
        if(new_flag==0)
            fd = open(parsed[iter1+1], O_WRONLY | O_CREAT | O_TRUNC , 0777);
        else
        {
            fd = open(parsed[iter1+1], O_WRONLY | O_CREAT , 0777);
            lseek(fd,0,SEEK_END);
        }

        fd1=dup(1);
        dup2(fd,1);
    }

    if(iter2!=-1)
    {
        fd2 = open(parsed[iter2+1], O_RDONLY | O_CREAT , 0777);
        fd3=dup(0);
        dup2(fd2,0);
    }



    //if(fd==-1)
      //  printf("pro\n");

    int pd = fork();

    if(pd==0)
    {
//        sprintf(fd1,"stirng");
        execvp(new_parsed[0],new_parsed);
//        int val = call_exec(new_parsed);
        exit(0);
    }
    else if(pd>0)
    {
        int status;
        waitpid(pd,&status,WUNTRACED);
    }
//    close(fd2);
    if(iter1!=-1)
        dup2(fd1,1);
//    close(fd);
  //  close(fd1);
    if(iter2!=-1)
        dup2(fd3,0);
}
