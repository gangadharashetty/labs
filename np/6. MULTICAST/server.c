/*
Program: Multicast Server
Author: Gangadhara Shetty P J
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main ()
{
    int sockfd;
    char msg[1024];
    struct sockaddr_in groupaddr = { AF_INET, htons(1236), inet_addr("226.1.1.1") };;
    struct in_addr localInterface = { INADDR_ANY };

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_IF, (char *)&localInterface, sizeof(localInterface));
    
    printf("Enter message : ");
    fgets(msg, 1024, stdin);
    msg[strlen(msg)-1] = '\0'; // to remove '\n' from string

    sendto(sockfd, msg, sizeof(msg), 0, (struct sockaddr*)&groupaddr, sizeof(groupaddr));
    printf("Message Sent.\n");
            
    return 0;
}