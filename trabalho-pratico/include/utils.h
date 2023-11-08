#ifndef UTILS_H
#define UTILS_H

#define BUFFERSIZE 100

#define CHECKLEN(line) \
    if(line[0] == '\0') return NULL;\
    char * aux = strdup(line);\
    return aux; \

#define ALLVAR(aux) for(int i = 0;aux[i] != '\0';aux[i] = tolower(aux[i]),i++);

#define TOKENIZE(token,saveptr) token = strtok_r(NULL,";",&saveptr); 

#endif