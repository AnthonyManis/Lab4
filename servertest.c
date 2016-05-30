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

void servertest(char *port) {
    char *buf, *host, *request, *response, *haddrp;
    struct sockaddr_in clientaddr;
    struct hostent *hp;
    int clientlen, connfd;
    int listenfd = Open_listenfd(port);

    // Server runs indefinitely
    while (1) {

        // Accept the connection of the client
        clientlen = sizeof(clientaddr);
        connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);

        // Get some information from the client
        hp = Gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr,
            sizeof(clientaddr.sin_addr.s_addr), AF_INET);
        haddrp = inet_ntoa(clientaddr.sin_addr);

        // Read from the client until two endlines are reached
        buf = read_until(connfd, "\r\n\r\n\0");
        Fputs(buf, stdout);

        // Pass on the client's request
        // stuff

        // Free the buffer created by read_until
        free(buf);

        Close(connfd);
    }
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Provide a port number.");
        exit(0);
    }
    servertest(argv[1]);
}