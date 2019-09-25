#include"global.h"

void sigintHandler1(int sig_num) 
{
    if(ctrl_z_cond==1)
    {
        signal(SIGTSTP, sigintHandler1);
        int ff=0;
        printf("%s\n",curr_fg_proc_name);

        for(int l=0;l<size;l++)
        {
            if(strcmp(runn_proc[l].proc_name,curr_fg_proc_name)==0 && runn_proc[l].pid!=-1)
            {
                ff=1;
                break;
            }
        }

        if(ff==0)
        {
            strcpy(runn_proc[size].proc_name,curr_fg_proc_name);
            runn_proc[size].pid=curr_fg_pid;
            runn_proc[size].si=size+1;
            size++;
        }

        printf("%d\n",curr_fg_pid);
        kill(curr_fg_pid,SIGTSTP);
    }
}

void sigintHandler(int sig_num) 
{ 
    signal(SIGINT, sigintHandler); 
    int get_idx=-1;

    for(int l=0;l<size;l++)
    {
        printf("%s\n",curr_fg_proc_name);
        if(strcmp(runn_proc[l].proc_name,curr_fg_proc_name)==0 && runn_proc[l].pid!=-1)
        {
            get_idx=l;
            break;
        }
    }

    printf("get_idx -- %d\n",get_idx);
    if(get_idx>=0 && get_idx<size) 
    {
        kill(runn_proc[get_idx].pid,SIGINT);
        runn_proc[get_idx].pid=-1;
    }
    printf("get_idx -- %d\n",get_idx);
}

int main() 
{
    char **wow;
    if(fork()==0)
        execvp("clear",wow);
    else
        wait(NULL);
    char hostbuffer[256]; 
    char* parsedArgs[256]; 
    struct hostent *host_entry; 
    int hostname; 
    int len; 

    hostname = gethostname(hostbuffer, sizeof(hostbuffer)); 
    if(hostname==-1)
    {
        perror("hostname");
        exit(1);
    }

    host_entry = gethostbyname(hostbuffer); 
    if(host_entry==NULL)
    {
        perror("host_entry");
        exit(1);
    }

    getcwd(prev1,1000);
    char dir[100];
    getcwd(dir,sizeof(dir));

    char path_h2[100];

    strcpy(path_h2,dir);
    strcat(path_h2,"/h2.txt");

    signal(SIGINT,sigintHandler);   
    signal(SIGTSTP,sigintHandler1);   

    while(1)
    {

        flag=0;
        val=0;
        char inputString[1000];

        printf("\e[1;32m""%s""\e[m",getenv("USER")); 
        printf("\e[1;32m""@""\e[m"); 
        printf("\e[1;32m");
        printf("\e[1;32m""%s:""\e[m", hostbuffer); 

        printf("\e[1;34m");
        printDir(dir);
        printf("\e[m");
        printf("$");
        printf(" ");

        parsedArgs[0] = NULL;
        parsedArgs[1] = NULL;
        parsedArgs[2] = NULL;

        int pid,pid_status;
        while((pid = waitpid(-1, &pid_status, WNOHANG | WUNTRACED)) > 0){
            char *proc_name;
            if(WIFEXITED(pid_status))
            {
                for(int i=0;i<size;i++)
                {
                    if(runn_proc[i].pid==pid)
                    {
                        proc_name = runn_proc[i].proc_name;
                        runn_proc[i].pid=-1;
                        printf("hello\n");
                        fprintf(stderr, "%s with pid %d exited normally.\n",proc_name,(int)pid);
                        break;
                    }
                }
            }

            else if(WIFSIGNALED(pid_status))
            {
                for(int i=0;i<size;i++)
                {
                    if(runn_proc[i].pid==pid)
                    {
                        proc_name = runn_proc[i].proc_name;
                        runn_proc[i].pid = -1;
                        printf("hello\n");

                        fprintf(stderr,"%s with %d pid terminated by a signal.\n",proc_name,(int)pid);
                        break;
                    }
                }

            }
        }

        if(takeInput(inputString,path_h2))
            continue;   

        int k=0;
        char* store[1000];

        char* arg = strtok(inputString,";");

        while(arg!=NULL)
        {
            store[k]=arg;
            k++;
            arg = strtok(NULL,";");
        }

        int i=0;

        while(i!=k)
        {
            int it=0;
            int redir=0;


            int m=0;
            char* piped_args[1000];

            char* token = strtok(store[i],"|");

            while(token!=NULL)
            {
                piped_args[m]=token;
                m++;
                token= strtok(NULL,"|");
            }   

            if(m==1)
            {
                len = parseSpace(store[i],parsedArgs);

                while(it<len)
                {
                    if((strcmp(parsedArgs[it],">")==0) || (strcmp(parsedArgs[it],"<")==0) || (strcmp(parsedArgs[it],">>")==0))
                    {
                        redir=1;
                    }
                    it++;
                }

                if(redir==1)
                {
                    call_redirection(parsedArgs,len);
                    i++;
                }

                else
                {
                    Check(parsedArgs,dir,len,path_h2,-1,-1);
                    i++;
                }
            }
            else
            {
                int z=0;
                int std_in_fd = dup(0);
                int std_out_fd = dup(1);

                while(z!=m)
                {
                    len = parseSpace(piped_args[z],parsedArgs);
                    int status;
                    int fdd[2];

                    if(z==0)
                    {
                        pipe(fdd);
                        std_out_fd = dup(1);

                        if(dup2(fdd[1],1)==-1)
                            fprintf(stderr,"Error: dup2 failed");
                    }

                    else if(z==m-1)
                    {
                        close(fdd[1]);
                        std_in_fd=dup(0);

                        if(dup2(fdd[0],0)==-1)
                            fprintf(stderr,"Error: dup2 failed");
                        close(fdd[0]);
                    }

                    else
                    {
                        close(fdd[1]);
                        std_in_fd=dup(0);

                        if(dup2(fdd[0],0)==-1)
                            fprintf(stderr,"Error: dup2 failed");
                        close(fdd[0]);

                        pipe(fdd);
                        std_out_fd = dup(1);

                        if(dup2(fdd[1],1)==-1)
                            fprintf(stderr,"Error: dup2 failed");
                    }

                    int pipe_pid = fork();

                    if(pipe_pid==0)
                    {
                        it=0;
                        redir=0;

                        while(it<len)
                        {
                            if((strcmp(parsedArgs[it],">")==0) || (strcmp(parsedArgs[it],"<")==0) || (strcmp(parsedArgs[it],">>")==0))
                            {
                                redir=1;
                            }
                            it++;
                        }

                        if(redir==1)
                        {
                            call_redirection(parsedArgs,len);
                        }

                        else
                        {
                            Check(parsedArgs,dir,len,path_h2,-1,-1);
                        }
                        exit(0);
                    }

                    else
                    {
                        waitpid(pipe_pid,&status,WUNTRACED);
                        dup2(std_in_fd,0);
                        dup2(std_out_fd,1);
                    }

                    z++;
                }
                i++;
            }
        }
    }
    return 0; 
}
