/*
Program: Sliding Window Client
Author: Gangadhara Shetty P J
*/
#include <stdio.h> 
#include <stdlib.h> 
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int soc, n, num=0;
    char buffer[1024], fname[50];
    struct sockaddr_in addr = {AF_INET, htons(1239), inet_addr("127.0.0.1")};
	srand(time(NULL));
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
Frame 0 : 12124                                                                       
Frame 1 : 12387                                                                       
Frame 2 : 96587                                                                       
Frame 3 : 23958                                                                       
Frame 4 : 61278                                                                       
Frame 5 : 35698                                                                       
Frame 6 : 74123                                                                       
Frame 7 : 89051                                                                       
Frame 8 : 27835                                                                       
Frame 9 : 68723

*/