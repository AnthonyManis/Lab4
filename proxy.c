// Manis, Anthony: 71461439
// Mukesh, Kastala: 40646351
// Cockins, Ryan: 92859394

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/socket.h>
#include "csapp.h"

int parseURL(char *buf, char *host, char *request);
void listenForConnection(char *port);

int parseURL(char *buf, char *host, char *request) {

}
void listenForConnection(char *port) {
    // Buffer for the client request
    int buf_len = 1024;
    char buf[buf_len];
    // Buffers for the host and request parts
    char host[buf_len];
    char request[buf_len];
    // Buffer for the server response.
    int response_len = 4096;
    char response[response_len];

    // Socketaddr and length
    struct sockaddr *addr;
    socklen_t *addrlen;
    // Socket file descriptor
    int socketfd = Open_listenfd(port);

    // Listen for client connections
    for(;;) {
        // When a client sends a request
        int clientfd = Accept(socketfd, addr, addrlen);
        // Zero the buffer and read into it.
        bzero(buf, buf_len);
        Rio_readn(clientfd, &buf, buf_len - 1);

        // Get the host and request parts
        parseURL(buf, host, request);

        // Opening connection to end-server
        int serverfd = Open_clientfd(host, "80");

        // Sending the request to the end-server
        Rio_writen(serverfd, request, sizeof(request));

        // Reading the end-server's response
        bzero(&response, response_len);
        Rio_readn(serverfd, response, response_len - 1);

        // Close end-server connection
        Close(serverfd);

        // Send response to client
        Rio_writen(clientfd, response, sizeof(response));

        // Close
        Close(clientfd);
    }
}

int main(int argc, char** argv) {
    if (argc < 2)
        printf("Port number required.\n");
    listenForConnection(argv[1]);
}
