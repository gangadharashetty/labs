/*
Program: TCP Client
Author: Gangadhara Shetty P J
*/
#include <stdio.h> 
#include <stdlib.h> 
#include <fcntl.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int soc, n, num=0;
    char buffer[1024], fname[50];
    struct sockaddr_in addr = {AF_INET, htons(1234), inet_addr("127.0.0.1")};

    soc = socket(AF_INET, SOCK_STREAM, 0);

    while(connect(soc, (struct sockaddr *) &addr, sizeof(addr))) ;
    printf("\nRecieved data\n\n");

    while ((n = recv(soc, buffer, 5, 0)) > 0)
    {
		int ran = rand()%10;
		
		if(!strcmp(buffer,"EXIT")) break;
		
		buffer[n]='\0';
		if(ran < 5)
			send(soc, "0", 2, 0);
		else{
			send(soc, "1", 2, 0);
			printf("Frame %d : %s\n",num++, buffer);
		}
    }
	
    return 0;
}

/*

OUTPUT
-------
Recieved data

Frame 0 : 1234
Frame 1 : 6789
Frame 2 : 2345
Frame 3 : 3456
Frame 4 : 8912
Frame 5 : 9123
Frame 6 : 1234
Frame 7 : 2345
Frame 8 : 7891
Frame 9 : 8912
Frame 10 : 4567

*/