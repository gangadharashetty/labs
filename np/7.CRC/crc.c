/*
Program: CRC
Author: Gangadhara Shetty P J
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int keylen,msglen;
char input[100], key[30],temp[30],quot[100],rem[30],key1[30], check[100];

char* divide()
{
	int i,j;
	for (i=0;i<keylen;i++)
	 temp[i]=input[i];
	for (i=0;i<msglen;i++) {
		quot[i]=temp[0];
		if(quot[i]=='0')
			for (j=0;j<keylen;j++)
				key[j]='0'; 
		else
			for (j=0;j<keylen;j++)
				key[j]=key1[j];
		for (j=keylen-1;j>0;j--) {
			if(temp[j]==key[j])
				rem[j-1]='0'; 
			else
				rem[j-1]='1';
		}
		rem[keylen-1]=input[i+keylen];
		strcpy(temp,rem);
	}
}

 void main() {
	int i,j;
	
	printf("Enter Data: ");
	scanf("%s",input);
	printf("Enter Key: ");
	scanf("%s",key);
	keylen=strlen(key);
	msglen=strlen(input);
	strcpy(key1,key);
	for (i=0;i<keylen-1;i++)
		input[msglen+i]='0';
	
	divide();
	
	printf("\nRemainder is ");
	for (i=0;i<keylen-1;i++)
		printf("%c",rem[i]);
	
	printf("\nFinal data is: ");
	for (i=0;i<msglen;i++)
		printf("%c",input[i]);
	for (i=0;i<keylen-1;i++)
		printf("%c",rem[i]);
 
	printf("\nEnter key to be checked: ");
	scanf("%s",input);
	divide();
	for (i=0;i<keylen-1;i++)
		if(rem[i]!='0'){
			printf("INVALID");
			exit(0);
		}
	printf("VALID");
 
}