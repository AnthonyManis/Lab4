// Manis, Anthony: 71461439
// Mukesh, Kastala: 40646351
// Cockins, Ryan: 92859394

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include "csapp.h"

int parseURL(char *buf, char *host, char *request);
char *read_all(int fd);
char *read_whole_http_request(int fd);
bool nlnl(char *buf);
char *clienttest(char *host, char *request);
void servertest(char *port);

int parseURL(char *buf, char *host, char *request) {

}

char *read_all(int fd) {
    int buf_size = 2, result_size = 8192;
    char buf[buf_size];
    char *result = malloc(result_size);

    int rc;
    int used = 1;
    bzero(result, result_size);
    while ( used < result_size - 1) {
        bzero(buf, buf_size);
        rc = Rio_readn(fd, buf, buf_size - 1);
        if ( rc <= 0 )
            break;
        strncat(result, buf, result_size - used - 1);
        used += rc;
        Fputs(buf, stdout);
    }
    return result;
}



char * clienttest(char *host, char *request) {
    int clientfd;
    char *port = "80";
    char *result;

    clientfd = Open_clientfd(host, port);

    Rio_writen(clientfd, request, strlen(request));

    result = read_all(clientfd);

    Close(clientfd);
    return result;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Port number required.\n");
        exit(0);
    }
    char host[50] = "www.ics.uci.edu";
    char request[500] = "GET /~harris/test.html HTTP/1.1\nhost: www.ics.uci.edu\n\n";
    // char host[50] = "www.yahoo.com";
    // char request[500] = "GET / HTTP/1.1\nhost: www.yahoo.com\n\n";
    clienttest(host, request);
}
