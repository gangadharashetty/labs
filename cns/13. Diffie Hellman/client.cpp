/*
Program: Diffie Hellman client
Author: Gangadhara Shetty P J
*/
# include <bits/stdc++.h>
# include <arpa/inet.h> 
using namespace std;
char buffer[100];
int connectToServer(const char* ip, int port)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {AF_INET, htons(port), inet_addr(ip)};
    connect(sock, (struct sockaddr *) &addr, sizeof(addr));
    return sock;
}
int powModN(int num,int p,int n)
{
	int res=1;
	for(int i=0; i<p; i++)
        res = (res * num) % n;
	return res;
}
void itoa(int x)
{
	string s= to_string(x);
	strcpy(buffer, s.c_str());
}
int main()
{
    char ip[50]="127.0.0.1";
    int port=1234;
	int sock = connectToServer(ip, port);
	int q, alpha, xa, ya, yb, cipher, key, message;
    
	cout<<"1. Enter prime number  and primitive root: ";
    cin>>q>>alpha;
    
	cout<<"2. Enter private key of client (<"<<q<<") : ";
    cin>>xa;
    
	ya =powModN(alpha, xa, q);
	
	recv(sock, &buffer, sizeof(buffer), 0);
	yb =  atoi(buffer);
	
	itoa(ya);
	send(sock, &buffer, sizeof(buffer), 0);
    
	cout<<"public key of client = "<<ya<<endl;
	cout<<"received public key of server is : "<<yb<<endl;
	
    key = powModN(yb, xa,q);
    cout <<"secret key of client = "<< key<<endl;
    
	cout<<"Enter a message: ";
    cin>>message;
    cipher = message ^ key;
	cout<<"Encrypted message :"<<cipher<<endl;
	itoa(cipher);
	send(sock, &buffer, sizeof(buffer), 0);
	
	recv(sock, &buffer, sizeof(buffer), 0);
	cipher = atoi(buffer);
	message = cipher ^ key;
	cout<<"received encrypted message is: "<<cipher<<endl;
	cout<<"received decrypted message is: "<<(cipher^key)<<endl;
	
	return 0;
}

/*
1. Enter prime number  and primitive root: 761  6                                                                                     
2. Enter private key of client (<761) : 100                                           
public key of client = 399                                                            
received public key of server is : 152                                                
secret key of client = 357                                                            
Enter a message: 76                                                                   
Encrypted message :297                                                                
received encrypted message is: 325                                                    
received decrypted message is: 32
*/