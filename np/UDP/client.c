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
	int sock;
	struct sockaddr_in addr;
	char buffer[100];
	char *msg = "This is client";
	
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(1236);
	addr.sin_addr.s_addr = INADDR_ANY;
	int len = sizeof(addr);
	
	connect(sock, (struct sockaddr*)& addr, sizeof(addr));
	
	sendto(sock, msg, strlen(msg), 0, (struct sockaddr *) &addr,sizeof(addr));
	recvfrom(sock, (char *)buffer, sizeof(buffer), 0, ( struct sockaddr *) &addr, &len); 
	printf("%s\n", buffer);
	close(sock);
	return 0;
}
