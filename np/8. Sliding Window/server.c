/*
Program: Sliding window Server
Author: Gangadhara Shetty P J
*/
#include <stdio.h> 
#include <stdlib.h> 
#include <fcntl.h> 
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define FRAME_SIZE 5 
char buffer[1024], frame[FRAME_SIZE], ack[2];
int server_fd, soc, i, j=0, fr;
void sendframe()
{
	send(soc, frame, FRAME_SIZE, 0);
	recv(soc, ack, 2, 0);
	if(ack[0]=='0')
		sendframe(), printf("Resending the frame %d\n\n", i/5);	
}
int main()
{
    struct sockaddr_in addr = { AF_INET, htons(1239), inet_addr("127.0.0.1") };

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    bind(server_fd, (struct sockaddr *) &addr, sizeof(addr));
    listen(server_fd, 5);
    soc = accept(server_fd, NULL, NULL);
	
	printf("Enter message: ");
	scanf("%s",buffer);

	for( i = 0, fr=0; buffer[i] ; ){
		for(j=0;j<FRAME_SIZE && buffer[i];j++, i++)
			frame[j] = buffer[i];
		frame[j]='\0';
		printf("Frame %d : %s\n\n", fr++, frame);
		sendframe();
	}
	send(soc, "EXIT", 4, 0);
	close(server_fd);
    return 0;
}

/*
OUTPUT
------
Enter message: 12124123879658723958612783569874123890512783568723                     
Frame 0 : 12124                                                                                                                                                             
Frame 1 : 12387                                                                                                                                                             
Frame 2 : 96587                                                                                                                                                             
Frame 3 : 23958                                                                                                                                                             
Resending the frame 4                                                                                                                                                       
Frame 4 : 61278
Frame 5 : 35698
Frame 6 : 74123
Resending the frame 7
Resending the frame 7
Resending the frame 7
Resending the frame 7
Resending the frame 7
Frame 7 : 89051
Frame 8 : 27835
Resending the frame 9
Frame 9 : 68723
*/