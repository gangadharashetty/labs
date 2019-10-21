/*
Program: FIFO Server
Author: Gangadhara Shetty P J
*/
#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <arpa/inet.h>
#include <unistd.h> 

int main() 
{ 
	int fd, fd1, file, n; 
	char arr1[80], buffer[1024]; 

	mkfifo("/myfifo", 0666); 
	mkfifo("/myfifo1", 0666); 
	
	fd = open("/myfifo", O_WRONLY);
	fd1 = open("/myfifo1", O_RDONLY);

	read(fd1, arr1, sizeof(arr1)); 
	printf("File name: %s\n", arr1); 
	file = open(arr1, O_RDONLY);
	
	while ((n = read(file, buffer, sizeof(buffer)) > 0))
		buffer[n]='\n', write(fd, buffer, sizeof(buffer));
	
	write(fd, "EXIT", 5);
	
	close(fd);
	close(fd1);
	return 0; 
} 
