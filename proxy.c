// Manis, Anthony: 71461439
// Mukesh, Kastala: 40646351
// Cockins, Ryan: 92859394

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/socket.h>

void listenForConnection(int port);
void listenForConnection(int port) {
    
}

int main(int argc, char** argv) {
    if (argc < 2)
        printf("Port number required.\n")
    int portNumber = atoi(argv[1]);
    listenForConnection(portNumber);
}
