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

void writeLogEntry(char *browserIP, char *URL, int size);
int parseRequest(char *buf, char *host);
char *read_until(int fd, char *pattern);
bool strmatch(char *buf, char *pattern);
char *clienttest(char *host, char *request);
void servertest(char *port);

int parseRequest(char *buf, char *host) {

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

bool strmatch(char *buf, char *pattern) {
    int patternlen = strlen(pattern);
    return !strcmp(buf - patternlen, pattern);
}

char * clienttest(char *host, char *request) {
    int clientfd;
    char *port = "80";
    char *result;

    // Open the socket and set it up
    clientfd = Open_clientfd(host, port);
    // Write an http request to end-server
    Rio_writen(clientfd, request, strlen(request));
    // Read response from end-server until ending html tag encountered
    result = read_until(clientfd, "</html>\0");
    // Fputs(result, stdout);
    // Close the connection and return the end-server's response
    Close(clientfd);
    return result;
}

void servertest(char *port) {
    char *request, *hostname, *response, *client_ip_address;
    struct sockaddr_in clientaddr;
    struct hostent *hp;
    int clientlen, connfd;

    // start listening and enter infinite listening loop
    int listenfd = Open_listenfd(port);
    while (1) {
        // accept a connection
        clientlen = sizeof(clientaddr);
        connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
        // get some information from the client
        hp = Gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr,
            sizeof(clientaddr.sin_addr.s_addr), AF_INET);
        client_ip_address = inet_ntoa(clientaddr.sin_addr);
        // read the request from the end-user
        request = read_until(connfd, "\r\n\r\n\0");
        // Store the hostname from the request
        parseRequest(request, hostname);
        // Fputs(request, stdout);
        // Pass on the client's request
        response = clienttest(hostname, request);
        //check that the response isn't empty (end-server responded)

        // respond to the end-user
        Rio_writen(connfd, response, strlen(response));
        // Finished, close connection & write log entry.
        Close(connfd);
        // writeLogEntry(client_ip_address, hostname, response);
        // Free the buffers except
        // client_ip_address is statically managed by inet_ntoa
        free(request);
        free(hostname);
        free(response);
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Port number required.\n");
        exit(0);
    }
    // char host[50] = "www.ics.uci.edu";
    // char request[500] = "GET /~harris/test.html HTTP/1.1\nhost: www.ics.uci.edu\n\n";
    // char host[50] = "www.yahoo.com";
    // char request[500] = "GET / HTTP/1.1\nhost: www.yahoo.com\n\n";
    // clienttest(host, request);
    servertest(argv[1]);
    return 0;
}
