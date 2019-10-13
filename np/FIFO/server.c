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

	mkfifo("/myfifo", 0666); 
	mkfifo("/myfifo1", 0666); 
	
	fd = open("/myfifo", O_WRONLY);
	fd1 = open("/myfifo1", O_RDONLY);

	while (1) 
	{  
		fgets(arr2, 80, stdin); 
		write(fd, arr2, strlen(arr2)+1);

		read(fd1, arr1, sizeof(arr1)); 
		printf("User2: %s\n", arr1);  
	} 
	
	close(fd);
	close(fd1);
	return 0; 
} 
