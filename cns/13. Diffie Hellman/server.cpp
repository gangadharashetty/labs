/*
Program: Diffie Hellman server
Author: Gangadhara Shetty P J
*/
# include <bits/stdc++.h>
# include <arpa/inet.h> 
using namespace std;
char buffer[100];
int createServer(int port)
{
    int sersock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {AF_INET, htons(port), INADDR_ANY};
    bind(sersock, (struct sockaddr *) &addr, sizeof(addr));
    listen(sersock, 5);
    int sock = accept(sersock, NULL, NULL);
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
    int port=1234, q, alpha, xb, ya, yb, cipher, key, message;
	int sock = createServer(port);
    
	cout<<"3. Enter prime number  and primitive root: ";
    cin>>q>>alpha;
    
	cout<<"4. Enter private key server : ";
    cin>>xb;
    
	yb = powModN(alpha, xb,q);
	itoa(yb);
	send(sock, &buffer, sizeof(buffer), 0);
	
	recv(sock, &buffer, sizeof(buffer), 0);
	ya = atoi(buffer);
    
	cout<<"public key of client = "<<ya<<endl;
	cout<<"public key of server is : "<<yb<<endl;
	
    key = powModN(ya, xb,q);
    cout <<"secret key of server = "<< key<<endl;
	
	recv(sock, &buffer, sizeof(buffer), 0);
	message =atoi(buffer);
	cipher = message^key;
	cout<<"received encrypted message is: "<<message<<endl;
	cout<<"received decrypted message is: "<<cipher<<endl;
	
    cout<<"Enter a message: ";
    cin>>message;
    cipher = message ^ key;
	cout<<"Encrypted message :"<<cipher<<endl;
	itoa(cipher);
	send(sock, &buffer, sizeof(buffer), 0);
	return 0;
}

/*
3. Enter prime number  and primitive root: 761  6                                                                                     
4. Enter private key server : 200                                                     
public key of client = 399                                                            
public key of server is : 152                                                         
secret key of server = 357                                                            
received encrypted message is: 297                                                    
received decrypted message is: 76                                                     
Enter a message: 32                                                                   
Encrypted message :325
*/