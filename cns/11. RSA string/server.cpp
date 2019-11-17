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
void ctoi(char buf[100], int &n1, int &n2)
{
	int i=0;
	n1=0;n2=0;
	while(buf[i]!='|')
		n1*=10, n1+=(buf[i++]-'0');
	while(buf[++i])
		n2*=10, n2+=(buf[i]-'0');
}
int powModN(int num,int p,int n)
{
	int res=1;
	for(int i=0; i<p; i++)
	{
        res = res * num;
        res = res %  n;
	}
	return res;
}
int main()
{
    int port=1234, e,n, len;
    int sock = createServer(port);
	string message;

    recv(sock, &buffer, sizeof(buffer), 0); // receive public key from client
	ctoi(buffer, e,n);
    cout << "\nPublic key received from client : {" << e << ", " << n << "}" << endl;

    cout << "\nEnter message to be send : "; 
	cin >> message;
	
	len = message.length();
	send(sock, &len, sizeof(len), 0);
	
	
	cout << "\nEncrypted Message : ";
    for(int i=0; message[i]; i++)
	{
		int C = powModN(message[i], e, n);
		send(sock, &C, sizeof(C), 0); 
		cout<<C<<" ";
	}
	cout<<endl<<"Message Sent"<<endl;
}
/*
Public key received from client : {3, 13231}                                                                                                                                
Enter message to be send : cnslab                                                                                                                                           
Encrypted Message :   4436 7900 12541 2767 12965 1791                                                       
Message Sent 
*/