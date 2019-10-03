#include"global.h"

void call_nightswatch(char **parsed,int len)
{
    if(len!=4)
    {
        fprintf(stderr,"Error: Invalid arguements\n");
        return;
    }
    if(parsed[1]==NULL || parsed[2]==NULL || parsed[3]==NULL)
    {
        printf("Insufficient arguements for this command\n");
    }
    else
    {
        clear();
        if(!strcmp(parsed[3],"interrupt"))
        {
            int sec;
            char s_sec[100];
            strcpy(s_sec,parsed[2]);
            sscanf(s_sec,"%d",&sec);

            initscr();
            noecho();
            curs_set(FALSE);
            nodelay(stdscr,TRUE);
            char a = getch();
            int y_co=0;

            while(1)
            {
                nodelay(stdscr,TRUE);
                noecho();
                a = getch();

                if(a=='q')
                {
                    endwin();
                    return;
                }

                int fd1 = open("/proc/interrupts",O_RDONLY);

                char bu[1000000];
                read(fd1,bu,1000000);

                char *stored[1000];
                int f=0;
                char *del = strtok(bu," ");
                while(del!=NULL)
                {
                    stored[f]=del;
                    f++;

                    del = strtok(NULL," ");
                }

                int x_co=0;

                mvprintw(y_co , x_co , "CPU 0 -- %s\n",stored[14]);
                x_co +=20;
                mvprintw(y_co , x_co , "CPU 1 -- %s\n",stored[15]);
                x_co +=20;
                mvprintw(y_co , x_co , "CPU 2 -- %s\n",stored[16]);
                x_co +=20;
                mvprintw(y_co , x_co , "CPU 3 -- %s\n",stored[17]);
                x_co +=20;

                clock_t t = clock();

                while(((clock()-t)/CLOCKS_PER_SEC)<sec)
                {
                    nodelay(stdscr,TRUE);
                    noecho();
                    a = getch();

                    if(a=='q')
                    {
                        endwin();
                        return;
                    }
                }
                y_co+=2;
            }
        }

        if(!strcmp(parsed[3],"dirty"))
        {
            int sec;
            char s_sec[100];
            strcpy(s_sec,parsed[2]);
            sscanf(s_sec,"%d",&sec);

            initscr();
            noecho();
            curs_set(FALSE);
            nodelay(stdscr,TRUE);
            char a = getch();
            int y_co=0;

            while(1)
            {
                nodelay(stdscr,TRUE);
                noecho();
                a = getch();

                if(a=='q')
                {
                    endwin();
                    return;
                }

                int fd5 = open("/proc/meminfo",O_RDONLY);

                char bu[1000000];
                read(fd5,bu,1000000);

                char *stored[1000];
                int f=0;
                char *del = strtok(bu,"\n");
                while(del!=NULL)
                {
                    stored[f]=del;
                    f++;

                    del = strtok(NULL,"\n");
                }

                char *dirt = strtok(stored[16]," ");
                char *di[1000];

                int g=0;
                while(dirt!=NULL)
                {
                    di[g] = dirt;
                    g++;

                    dirt = strtok(NULL," ");
                }

                int x_co=0;
                mvprintw(y_co , x_co , "Dirty -- %s %s\n",di[1],di[2]);

                clock_t t = clock();

                while(((clock()-t)/CLOCKS_PER_SEC)<sec)
                {
                    nodelay(stdscr,TRUE);
                    noecho();
                    a = getch();

                    if(a=='q')
                    {
                        endwin();
                        return;
                    }
                }
                y_co+=2;
            }
        }
    }
}
