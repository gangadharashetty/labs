/*
Program: TCP Server
Author: Gangadhara Shetty P J
*/
#include <stdio.h> 
#include <stdlib.h> 
#include <fcntl.h> 
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define FRAME_SIZE 5 //( actual size + 1)
int main()
{
    int server_fd, soc, i, j=0;
    char buffer[1024], frame[FRAME_SIZE];
    struct sockaddr_in addr = { AF_INET, htons(1234), inet_addr("127.0.0.1") };

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    bind(server_fd, (struct sockaddr *) &addr, sizeof(addr));
	printf("Enter message: ");
	gets(buffer);

    listen(server_fd, 5);

    soc = accept(server_fd, NULL, NULL);

	for( i = 0; buffer[i]; i++){
		if(i%FRAME_SIZE + 1==FRAME_SIZE){
			j=0;
			printf("Frame %d : %s\n\n", i/5, frame);
			send(soc, frame, FRAME_SIZE, 0);
			recv(soc, frame, 1, 0);
			if(frame[0]=='0') {
				printf("Resending the frame %d again\n", i/FRAME_SIZE);
				i-=FRAME_SIZE;
			}
		}
		else frame[j++] = buffer[i];
	}
	send(soc, frame, FRAME_SIZE, 0);
	send(soc, "EXIT", 4, 0);
	close(server_fd);
    return 0;
}

/*
OUTPUT
------
Enter message: 123456789123456789123456789123456789123456789123456789123456789123456789123456789
Frame 0 : 1234

Resending the frame 0 again
Frame 0 : 1234

Frame 1 : 6789

Frame 2 : 2345

Frame 3 : 7891

Frame 4 : 3456

Frame 5 : 8912

Frame 6 : 4567

Frame 7 : 9123

Resending the frame 7 again
Frame 7 : 9123

Frame 8 : 5678

Frame 9 : 1234

Frame 10 : 6789

Frame 11 : 2345

Frame 12 : 7891

Resending the frame 12 again
Frame 12 : 7891

Frame 13 : 3456

Frame 14 : 8912

Frame 15 : 4567

Resending the frame 15 again
Frame 15 : 4567
*/