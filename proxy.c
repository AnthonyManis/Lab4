// Manis, Anthony: 71461439
// Mukesh, Kastala: 40646351
// Cockins, Ryan: 92859394

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/socket.h>
#include "csapp.h"

void listenForConnection(int port);

void listenForConnection(int port) {
    // Buffer for the http request
    int buf_len = 1024;
    char buf[buf_len];

    // Socketaddr and length
    struct sockaddr *addr;
    socklen_t *addrlen;
    // Socket file descriptor
    int socketfd = Open_listenfd(port);

    // Listen for client connections
    for(;;) {
        // When a client sends a request
        int ac = Accept(socketfd, addr, addrlen);
        // Zero the buffer and read into it.
        b0(buf, buf_len);
        Rio_readn(socketfd, buf, buf_len - 1);


    }
}

int main(int argc, char** argv) {
    if (argc < 2)
        printf("Port number required.\n")
    int portNumber = atoi(argv[1]);
    listenForConnection(portNumber);
}
