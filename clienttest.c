#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include "csapp.h"

char * clienttest(char *host, char *request) {
    int clientfd, buf_size = 256, result_size = 8192;
    char *port = "80";
    char buf[buf_size];
    char *result = malloc(result_size);
    rio_t rio;

    clientfd = Open_clientfd(host, port);
    Rio_readinitb(&rio, clientfd);

    Rio_writen(clientfd, request, strlen(request));
    int rc;
    int used = 1;
    bzero(result, result_size);
    while ( used < result_size ) {
        bzero(buf, buf_size);
        rc = Rio_readn(clientfd, buf, buf_size - 1);
        if ( rc <= 0 )
            break;
        strncat(result, buf, result_size - used);
        used += rc;
        // Fputs(buf, stdout);
    }
    Close(clientfd);
    return result;
}

int main(int argc, char **argv) {
    char host[50] = "www.ics.uci.edu";
    char request[500] = "GET /~harris/test.html HTTP/1.1\nhost: www.ics.uci.edu\n\n";
    // char host[50] = "www.yahoo.com";
    // char request[500] = "GET / HTTP/1.1\nhost: www.yahoo.com\n\n";
    clienttest(host, request);
}