#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include "csapp.h"

bool nlnl(char *buf) {
    char pattern[5] = "\r\n\r\n\0";
    return !strcmp(buf - 4, pattern);
}

char *read_whole_http_request(int fd) {
    int buf_size = 2, result_size = 8192;
    char buf[buf_size];
    char *result = malloc(result_size);

    int rc;
    int next = 0;
    bzero(result, result_size);
    while ( result_size - next > 1) {
        bzero(buf, buf_size);
        rc = Rio_readn(fd, buf, buf_size - 1);
        if (rc == 1) {
            strncat(result, buf, result_size - next - 1);
            next++;
            if ( next >= 4 && nlnl(result+next) )
                break;
        }
        
    }
    printf("request read, returning\n");
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
        clientlen = sizeof(clientaddr);
        connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);

        hp = Gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr,
            sizeof(clientaddr.sin_addr.s_addr), AF_INET);
        haddrp = inet_ntoa(clientaddr.sin_addr);
        // printf("server connected to %s (%s)\n", hp->h_name, haddrp);

        buf = read_whole_http_request(connfd);
        Fputs(buf, stdout);

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