#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include "csapp.h"

char *parseRequest(char *buf) {
    char* pos = strstr(buf, "www.");
    printf("%s", pos);

    if (!pos)
        return NULL;

    int len = strlen(pos);
    char *host;
    host = (char *) malloc(len);
    bzero(host, len);
    strncpy(host, pos, len - 2);
    // printf("%s", host);

    return host;
    
}

int main() {
    char * request = "GET /~harris/test.html HTTP/1.1\nhost: www.ics.uci.edu\n\n";
    char * host = parseRequest(request);
    if ( strcmp(host, "www.ics.uci.edu") == 0) {
        printf("good shit\n");
    }
    // printf("%s\n", host);
    free(host);
}