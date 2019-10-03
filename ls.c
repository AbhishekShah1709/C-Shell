#include"global.h"

void call_ls(char **parsed,char *dir,int len,int time,int freq)
{
    int y = (freq/time);
    if(time==-1 || freq==-1)
    {
        time=0;
        freq=0;
        y=1;
    }

    int x=0;

    while(x<y)
    {
        sleep(time);
        int itr=1;
        int br1=0;
        int br2=0;
        int br3=0;
        int itr2=0;
        int k=0;
        char f_str[100]="";
        strcpy(f_str,"-");
        k=1;

        while(itr<len)
        {
            if(!strcmp(parsed[itr],"-l"))
            {
                if(br1==0 && br3==0)
                {
                    br1 = 1;
                    f_str[k]='l';
                    k++;
                }
            }

            else if(!strcmp(parsed[itr],"-a"))
            {
                if(br2==0 && br3==0)
                {
                    br2 = 1;
                    f_str[k]='a';
                    k++;
                }
            }

            else if((!strcmp(parsed[itr],"-la")) || (!strcmp(parsed[itr],"-al")))
            {
                br3 = 1;
                f_str[1]='l';
                f_str[2]='a';
            }

            else 
            {
                if(parsed[itr][0]=='-')
                {
                    printf("Invalid flag\n");
                    return;
                }
                itr2 = itr;
            }
            itr++;
        }

        if(parsed[itr2][0]=='~')
        {
            char d[100];
            strcpy(d,dir);
            int len3 = strlen(d);
            int len2 = strlen(parsed[itr2]);
            for(int i=1;i<len2;i++)
            {
                d[len3]=parsed[1][i];
                len3++;
            }

            strcpy(parsed[itr2],d);
        }

        if(len==1)
        {
            char cwd[1024];
            getcwd(cwd,sizeof(cwd));
            char *pointer=NULL;
            pointer=cwd;

            DIR *dp=NULL;
            dp=opendir((char*)pointer);

            struct dirent *sd=NULL;
            while((sd=readdir(dp))!=NULL)
            {
                if(sd->d_name[0]!='.')
                    printf("%s\n",sd->d_name);
            }
        }


        else if(!strcmp(f_str,"-"))
        {
            int su = access(parsed[itr2],F_OK);
            if(su==-1)
            {
                perror("Cannot access this directory");
                return;
            }
            char *pointer=NULL;
            DIR *dp=NULL;
            struct dirent *sd=NULL;

            pointer = parsed[itr2]; 
            dp=opendir((char*)pointer);

            while((sd=readdir(dp))!=NULL)
            {
                if(sd->d_name[0]!='.')
                    printf("%s\n",sd->d_name);
            }
        } 

        else
        {
            if(itr2==0)
            {
                char cwd[1024];
                getcwd(cwd,sizeof(cwd));

                DIR *thedirectory;
                thedirectory = opendir(cwd);

                if(!strcmp(f_str,"-a"))
                {
                    struct dirent *thefile;
                    struct stat thestat;

                    char buf[512];

                    while((thefile = readdir(thedirectory)) != NULL) 
                    {   
                        sprintf(buf, "%s/%s", cwd, thefile->d_name);
                        stat(buf, &thestat);

                        printf("%s\n", thefile->d_name);
                    }
                    closedir(thedirectory);
                }

                else if(!strcmp(f_str,"-l"))
                {
                    print_list(thedirectory,1,cwd);
                }

                else if(!strcmp(f_str,"-la") || !strcmp(f_str,"-al"))
                    print_list(thedirectory,0,cwd);

                else
                    printf("Invalid flag\n");
            }

            else
            {
                int su = access(parsed[itr2],F_OK);
                if(su==-1)
                {
                    perror("Cannot access");
                    return;
                }

                DIR *thedirectory;
                thedirectory = opendir(parsed[itr2]);

                if(!strcmp(f_str,"-a"))
                {
                    struct dirent *thefile;
                    struct stat thestat;

                    char buf[512];


                    while((thefile = readdir(thedirectory)) != NULL) 
                    {   
                        sprintf(buf, "%s/%s", parsed[itr2], thefile->d_name);
                        stat(buf, &thestat);

                        printf("%s\n", thefile->d_name);
                    }
                    closedir(thedirectory);

                }

                else if(!strcmp(f_str,"-l"))
                {
                    print_list(thedirectory,1,parsed[itr2]);
                }

                else if(!strcmp(f_str,"-la") || !strcmp(f_str,"-al"))
                {
                    print_list(thedirectory,0,parsed[itr2]);
                }
                else
                    printf("Invalid flag\n");
            }
        }

        printf("\n");
        if(freq-time*(x+1)<time)
            sleep(freq-time*(x+1));
        x++;

    }
}
