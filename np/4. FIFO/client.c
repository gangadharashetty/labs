/*
Program: FIFO Client
Author: Gangadhara Shetty P J
*/
#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 

int main() 
{ 
	int fd, fd1; 
	char arr1[1024], arr2[80];

	mkfifo("/myfifo", 0666); 
	mkfifo("/myfifo1", 0666); 	
	
	fd = open("/myfifo", O_RDONLY);
	fd1 = open("/myfifo1", O_WRONLY);
 
	printf("File name: ");
	scanf("%s", arr2);
	write(fd1, arr2, strlen(arr2)+1);
 
	printf("FILE CONTENT\n\n");
	while (strcmp(arr1, "EXIT")) 
	{  
		read(fd, arr1, sizeof(arr1)); 
		printf("%s", arr1);
		
	}
	close(fd);
	close(fd1);
	return 0; 
} 
