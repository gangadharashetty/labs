/*
Program: TCP Server
Author: Gangadhara Shetty P J
*/
#include <stdio.h> 
#include <stdlib.h> 
#include <fcntl.h> 
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int server_fd, soc, fd, n;
    char buffer[1024], fname[50];
    struct sockaddr_in addr = { AF_INET, htons(1234), inet_addr("127.0.0.1") };

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    bind(server_fd, (struct sockaddr *) &addr, sizeof(addr));
    printf("\nServer is Online");

    listen(server_fd, 5);

    soc = accept(server_fd, NULL, NULL);

    recv(soc, fname, 50, 0);
    printf("\nRequesting for file: %s\n", fname);

    fd = open(fname, O_RDONLY);

    if (fd < 0)	
        send(soc, "\nFile not found\n", 15, 0);
    else
        while ((n = read(fd, buffer, sizeof(buffer))) > 0)
            send(soc, buffer, n, 0);
		
    printf("\nFile content sent\n");
    close(fd);

    return 0;
}