#include <arpa/inet.h> // for network programming on Unix; 
    /* Windows equivalent: winsock2.h
    htons, htonl: converting between host & network byte order for 16 & 32 bit integers
    */
#include <netinet/in.h> 
#include <stdio.h>      // printf, printf_s, scanf_s, gets, NULL
#include <string.h>     // strcpy_s, strcat_s, strlen
#include <sys/socket.h> // socket(), listen(), socklen_t, SOCK_STREAM
#include <unistd.h>

#define MAX_MESSAGE_SIZE 1000
#define PORT 8888
#define LISTEN_BACKLOG 10

void handleConnection(int a_client_fd)
{
    char buf;
    char msg [MAX_MESSAGE_SIZE];
    int msg_index = 0;
    while (1) {
        int chars = read(a_client_fd, &buf, sizeof(buf)); // read the input data
        if (chars == 0 || chars == -1){
            close(a_client_fd);
            return;
        }
        
        // store the message
        msg[msg_index++] = buf;
        if (buf == '\n' || msg_index == MAX_MESSAGE_SIZE) {
            write(a_client_fd, msg, msg_index*sizeof(msg[0]));// write the input data
            msg_index = 0;
        }
    }
}

int main(int argc, char* argv[])
{
    // Create listening socket
    // socket()
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in socket_address;
    memset(&socket_address, '\0', sizeof(socket_address));
    socket_address.sin_family = AF_INET;
    socket_address.sin_addr.s_addr = htonl(INADDR_ANY);
    socket_address.sin_port = htons(PORT);

    printf("Binding to port %d\n", PORT);

    int returnval;
    
    // bind()
    returnval = bind(socket_fd, (struct sockaddr*)&socket_address, sizeof(socket_address));
    if (returnval < 0) {
        perror("bind");
        return 1;
    }
    
    // listen()
    returnval = listen(socket_fd, LISTEN_BACKLOG);

    // Accept an incoming connection
    struct sockaddr_in client_address;
    socklen_t client_address_len = sizeof(client_address);

    int client_fd = accept(socket_fd, (struct sockaddr*)&client_address, &client_address_len);
    
    // Handle that connection
    handleConnection(client_fd);

    return 0;
}