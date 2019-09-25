#include "global.h"

void print_list(DIR *dir,int flag3,char *con)
{
    char cwd[1024];
    getcwd(cwd,sizeof(cwd));

    struct dirent *thefile;
    struct stat thestat;
    struct passwd *tf; 
    struct group *gf;

    char buf[512];

    while((thefile = readdir(dir)) != NULL) 
    {   
        if(flag3==1)
        {
            if(thefile->d_name[0]!='.')
            {
                sprintf(buf, "%s/%s", con, thefile->d_name);


                //                printf("%c\n",thefile->d_name[0]);
                stat(buf, &thestat);

                switch (thestat.st_mode & S_IFMT) {
                    case S_IFBLK:  printf("b "); break;
                    case S_IFCHR:  printf("c "); break; 
                    case S_IFDIR:  printf("d "); break; //It's a (sub)directory 
                    case S_IFIFO:  printf("p "); break; //fifo
                    case S_IFLNK:  printf("l "); break; //Sym link
                    case S_IFSOCK: printf("s "); break;
                    default:       printf("- "); break;
                }

                printf( (thestat.st_mode & S_IRUSR) ? " r" : " -");
                printf( (thestat.st_mode & S_IWUSR) ? "w" : "-");
                printf( (thestat.st_mode & S_IXUSR) ? "x" : "-");
                printf( (thestat.st_mode & S_IRGRP) ? "r" : "-");
                printf( (thestat.st_mode & S_IWGRP) ? "w" : "-");
                printf( (thestat.st_mode & S_IXGRP) ? "x" : "-");
                printf( (thestat.st_mode & S_IROTH) ? "r" : "-");
                printf( (thestat.st_mode & S_IWOTH) ? "w" : "-");
                printf( (thestat.st_mode & S_IXOTH) ? "x" : "-");

                printf("\t%lu ", thestat.st_nlink);

                tf = getpwuid(thestat.st_uid);
                printf("\t%s ", tf->pw_name);

                gf = getgrgid(thestat.st_gid);
                //        printf("\t%s ", gf->gr_name);

                printf("%zu",thestat.st_size);
                printf(" %s", thefile->d_name);
                printf(" %s", ctime(&thestat.st_mtime));
            }
        }

        else
        {
            sprintf(buf, "%s/%s", con, thefile->d_name);


                //                printf("%c\n",thefile->d_name[0]);
                stat(buf, &thestat);

                switch (thestat.st_mode & S_IFMT) {
                    case S_IFBLK:  printf("b "); break;
                    case S_IFCHR:  printf("c "); break; 
                    case S_IFDIR:  printf("d "); break; //It's a (sub)directory 
                    case S_IFIFO:  printf("p "); break; //fifo
                    case S_IFLNK:  printf("l "); break; //Sym link
                    case S_IFSOCK: printf("s "); break;
                    default:       printf("- "); break;
                }

                printf( (thestat.st_mode & S_IRUSR) ? " r" : " -");
                printf( (thestat.st_mode & S_IWUSR) ? "w" : "-");
                printf( (thestat.st_mode & S_IXUSR) ? "x" : "-");
                printf( (thestat.st_mode & S_IRGRP) ? "r" : "-");
                printf( (thestat.st_mode & S_IWGRP) ? "w" : "-");
                printf( (thestat.st_mode & S_IXGRP) ? "x" : "-");
                printf( (thestat.st_mode & S_IROTH) ? "r" : "-");
                printf( (thestat.st_mode & S_IWOTH) ? "w" : "-");
                printf( (thestat.st_mode & S_IXOTH) ? "x" : "-");

                printf("\t%lu ", thestat.st_nlink);

                tf = getpwuid(thestat.st_uid);
                printf("\t%s ", tf->pw_name);

                gf = getgrgid(thestat.st_gid);
                //        printf("\t%s ", gf->gr_name);

                printf("%zu",thestat.st_size);
                printf(" %s", thefile->d_name);
                printf(" %s", ctime(&thestat.st_mtime));
        }

    }
    closedir(dir);
}
