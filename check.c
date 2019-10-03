#include"global.h"

void Check(char** parsed,char *dir,int len,char *path_h,int time,int freq)
{
    if(parsed[1]!=NULL)
    {
        if(strcmp(parsed[len-1],"&")==0)
        {
            strcpy(parsed[len-1],"\0");
            flag=1;
            int pid = fork();
            if(pid==0)
            {
                setpgid(0,0);
                close(STDERR_FILENO);

                if(execvp(parsed[0],parsed)==-1)
                    perror("Invalid command");

                exit(0);
            }
            else
            {
                printf("%d\n",pid);
                strcpy(runn_proc[size].proc_name,parsed[0]);
                runn_proc[size].pid=pid;
                runn_proc[size].si=size+1;
                size++;
            }
        } 
    }

    if(strcmp(parsed[0],"cd")==0)
        call_cd(parsed,dir,time,freq);
    else if(strcmp(parsed[0],"ls")==0)
        call_ls(parsed,dir,len,time,freq);
    else if(strcmp(parsed[0],"echo")==0)
        call_echo(parsed,time,freq);
    else if(strcmp(parsed[0],"history")==0)
        printhistory(parsed,len,path_h,time,freq);
    else if(strcmp(parsed[0],"pwd")==0)
        call_pwd(time,freq);
    else if(strcmp(parsed[0],"pinfo")==0)
        call_pinfo(parsed,len,time,freq);
    else if(strcmp(parsed[0],"nightswatch")==0)
        call_nightswatch(parsed,len);
    else if(strcmp(parsed[0],"setenv")==0)
        call_setenv(parsed,len,time,freq);
    else if(strcmp(parsed[0],"unsetenv")==0)
        call_unsetenv(parsed,len,time,freq);
    else if(strcmp(parsed[0],"jobs")==0)
        call_jobs(len,time,freq);
    else if(strcmp(parsed[0],"kjob")==0)
        call_kjob(parsed,len);
    else if(strcmp(parsed[0],"overkill")==0)
        call_overkill(len);
    else if(strcmp(parsed[0],"fg")==0)
        call_fg(parsed,len);
    else if(strcmp(parsed[0],"bg")==0)
        call_bg(parsed,len);
    else if(strcmp(parsed[0],"quit")==0)
    {
        call_overkill(1);
        exit(0);
    }
    else if(strcmp(parsed[0],"cronjob")==0)
    {
        int piddd = fork();
        if(piddd==0)
        {
            call_cronjob(parsed,len,dir,path_h);
            exit(0);
        }
    }
    else
    {
        if(flag!=1)
        {
            int pidd = fork();
       
            if(pidd==0)
            {
                setpgid(0,0);
                val = call_exec(parsed);
                if(val==-1)
                    fprintf(stderr,"Error:command not found\n");
                exit(0);
            }
            else if(pidd>0)
            {
                if(val!=-1)
                {
                    curr_fg_pid = pidd;
                    strcpy(curr_fg_proc_name,parsed[0]);
                }
//                strcpy(runn_proc[size].proc_name,parsed[0]);
//                runn_proc[size].pid=pidd;
//                runn_proc[size].si=size+1;
//                size++;

                ctrl_z_cond=1;
                ctrl_c_cond=1;
                int status;
                waitpid(pidd,&status,WUNTRACED);
                ctrl_z_cond=0;
                ctrl_c_cond=0;
            }
        }
    }
}
