/*
Program: TCP Client
Author: Gangadhara Shetty P J
*/
#include <stdio.h> 
#include <stdlib.h> 
#include <fcntl.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int soc, n;
    char buffer[1024], fname[50];
    struct sockaddr_in addr = {AF_INET, htons(1234), inet_addr("127.0.0.1")};

    soc = socket(AF_INET, SOCK_STREAM, 0);

    while(connect(soc, (struct sockaddr *) &addr, sizeof(addr))) ;
    
    printf("\nClient is connected to Server");

    printf("\nEnter file name: ");
    scanf("%s", fname);

    send(soc, fname, sizeof(fname), 0);

    printf("\nRecieved file data\n\n");

    while ((n = recv(soc, buffer, sizeof(buffer), 0)) > 0)
    {
		buffer[n]='\0';
        printf("%s", buffer);
    }
	
    return 0;
}