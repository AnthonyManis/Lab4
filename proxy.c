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
    char request[1024];

    // Socketaddr and length
    struct sockaddr *addr;
    socklen_t *addrlen;
    int socketfd = Open_listenfd(port);

    // Listen for client connections
    for(;;) {
        // When a client sends a request
        Accept(socketfd, addr, addrlen);


    }
}

int main(int argc, char** argv) {
    if (argc < 2)
        printf("Port number required.\n")
    int portNumber = atoi(argv[1]);
    listenForConnection(portNumber);
}
