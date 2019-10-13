#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 

int main() 
{ 
	int fd, fd1; 
	char arr1[80], arr2[80];

	char * myfifo = "/tmp/myfifo"; 
	char * myfifo1 = "/tmp/myfifo1"; 

	mkfifo(myfifo, 0666); 
	mkfifo(myfifo1, 0666); 	
	
	fd = open(myfifo, O_RDONLY);
	fd1 = open(myfifo1, O_WRONLY);
 
	while (1) 
	{  
		read(fd, arr1, sizeof(arr1)); 
		printf("User2: %s\n", arr1);
		
		fgets(arr2, 80, stdin); 
		write(fd1, arr2, strlen(arr2)+1);
	} 
	close(fd);
	close(fd1);
	return 0; 
} 
