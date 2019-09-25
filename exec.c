#include"global.h"

int call_exec(char **parsed)
{
    int succ = execvp(parsed[0],parsed);
    return succ;
}
