#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <errno.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <sys/socket.h> 
#include <string.h> 
#include <sys/wait.h> 
#include <readline/readline.h> 
#include <readline/history.h> 
#include <fcntl.h> 
#include <dirent.h> 
#include <pwd.h>
#include <time.h>
#include <grp.h>
#include <curses.h>
#include <ncurses.h>
#include <time.h>

struct P{
    char proc_name[128];
    int pid;
    int si;
}proc;

struct P runn_proc[2048];
char bbuffer[100000];
int flag;
int val;
int size;
int curr_fg_pid;
char curr_fg_proc_name[400];
char prev1[1000];
char* buffer;
void printDir(char *fixed);
void addhistory(char *argu,char *dir);
int takeInput(char* s,char *dir);
int parseSpace(char* str, char** parsed);
void call_overkill();
void call_kjob(char **parsed,int len);
void call_bg(char **parsed);
void call_fg(char **parsed);
void call_setenv(char **parsed,int len,int time,int freq);
void call_unsetenv(char **parsed,int len,int time,int freq);
void call_cd(char **parsed,char *dir,int time,int freq);
void call_redirection(char **parsed,int len);
void call_echo(char **parsed,int time,int freq);
void call_pwd(int time,int freq);
void call_jobs(int time,int freq);
void call_ls(char **parsed,int len,int time,int freq);
void print_list(DIR *dir,int len,char *con);
void call_pinfo(char **parsed,int time,int freq);
void call_nightswatch(char **parsed);
void printhistory(char **parsed, char *dir,int time,int freq);
int call_exec(char **parsed);
void Check(char** parsed,char *dir,int len,char *path_h,int time,int freq);
void call_cronjob(char** parsed,int len,char *dir,char *path_h);
