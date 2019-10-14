/*
Program: Multicast Client
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

int main()
{
	int sockfd, reuse = 1;
	char msg[1024];
	struct sockaddr_in addr = { AF_INET, htons(1236), INADDR_ANY };
	struct ip_mreq group = { inet_addr("226.1.1.1"), INADDR_ANY };

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse));
	
	bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
	
	setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&group, sizeof(group));
		
	printf("Waiting for message from server.....");

	read(sockfd, msg, sizeof(msg));
	printf("\nThe message from multicast server is : %s \n", msg);

	close(sockfd);
	return 0;
}