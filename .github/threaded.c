#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>    // pthread_t: Represents thread IDs., pthread_create, pthread_join
#include <stdio.h>      // printf, printf_s, scanf_s, gets, NULL
#include <stdlib.h>     // malloc, free, rand, srand, exit, _sleep
#include <string.h>     // strcpy_s, strcat_s, strlen
#include <sys/socket.h> // socket(), bind(), listen()
#include <unistd.h>
#include <stdbool.h> // bool

#define MAX_MESSAGE_SIZE 1000
#define DEFAULT_PORT 8888
#define LISTEN_BACKLOG 10

bool terminal_print = false;

void handleConnection(int* sock_fd_ptr)
{
    int sock_fd = *sock_fd_ptr;
    printf("Handling connection on %d\n", sock_fd);
    
    // handle a message
    char buf;
    char msg [MAX_MESSAGE_SIZE];
    int msg_index = 0;
    while (1) {
        int chars = read(sock_fd, &buf, sizeof(buf)); // read the input data
        // break if connection is closed
        if (chars == 0 || chars == -1) { 
            close(sock_fd);
            break;
        }
        
        // store the message
        msg[msg_index++] = buf;
        if (buf == '\n' || msg_index == MAX_MESSAGE_SIZE) {
            write(sock_fd, msg, msg_index*sizeof(msg[0])); // write the input data
            if (terminal_print == true) {
                printf("%s", msg); // print to the terminal
            }
            msg_index = 0;
        }
    }
    printf("done with connection %d\n", sock_fd);
}

int main(int argc, char* argv[])
{
    int port = DEFAULT_PORT;
    for (int ix = 1; ix < argc; ix++) {
        if(strlen(argv[ix]) == 2 && argv[ix][0] == '-') {
            if (argv[ix][1] == 'p' && argc > ix+1) {port = *argv[++ix];}
            if (argv[ix][1] == 'v') {terminal_print = true;}
        }
    }
    
    // Create and bind listening socket
    // socket()
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in socket_address;
    memset(&socket_address, '\0', sizeof(socket_address));
    socket_address.sin_family = AF_INET;
    socket_address.sin_addr.s_addr = htonl(INADDR_ANY);
    socket_address.sin_port = htons(port);

    printf("Binding to port %d\n", port);

    int returnval;
    
    // bind()
    returnval = bind(socket_fd, (struct sockaddr*)&socket_address, sizeof(socket_address));
    if (returnval < 0) {
        perror("bind");
        return 1;
    }
    
    // listen()
    returnval = listen(socket_fd, LISTEN_BACKLOG); 

    // Accept
    struct sockaddr_in client_address;
    socklen_t client_address_len = sizeof(client_address);
    
    while (1) {
        pthread_t thread;
        int* client_fb_buf = malloc(sizeof(int));
        
        // accept()
        *client_fb_buf = accept(socket_fd, (struct sockaddr*)&client_address, &client_address_len);
        
        printf("accepted connection on %d\n", *client_fb_buf);
        // Handle the connection
        pthread_create(&thread, NULL, (void* (*)(void*))handleConnection, (void*)client_fb_buf);
    }

    return 0;
}