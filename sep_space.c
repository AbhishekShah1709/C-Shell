#include"global.h"

int parseSpace(char* str, char** parsed) 
{ 
    int i; 

    for (i = 0; i < 1000; i++) { 
        parsed[i] = strsep(&str, " "); 

        if (parsed[i] == NULL) 
            break; 
        if (strlen(parsed[i]) == 0) 
            i--; 
    } 
    return i;
}
