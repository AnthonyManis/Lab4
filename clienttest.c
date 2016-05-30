#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include "csapp.h"

bool strmatch(char *buf, char *pattern) {
    int patternlen = strlen(pattern);
    return !strcmp(buf - patternlen, pattern);
}

char *read_until(int fd, char *pattern) {
    int buf_size = 2, result_size = 8192;
    char buf[buf_size];
    char *result = malloc(result_size);

    int rc;
    int next = 0;
    bzero(result, result_size);
    while ( next < result_size - 1) {
        bzero(buf, buf_size);
        rc = Rio_readn(fd, buf, buf_size - 1);
        if (rc > 0) {
            strncat(result, buf, result_size - next - 1);
            next += rc;
            if ( next >= strlen(pattern) && strmatch(result+next, pattern) )
                break;
        }
        
    }
    return result;
}

char * clienttest(char *host, char *request) {
    int clientfd;
    char *port = "80";
    char *result;

    // Opens the socket and sets it up
    clientfd = Open_clientfd(host, port);

    // Writes an http request to end-server
    Rio_writen(clientfd, request, strlen(request));

    // Reads from end-server until it gets a whole http request
    result = read_until(clientfd, "</html>\0");
    Fputs(result, stdout);

    // Free the buffer created by read_until
    free(result);
    // Close the connection and return the end-server's response
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