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
    int port=1234, e,n, M;
    int sock = createServer(port);

    recv(sock, &buffer, sizeof(buffer), 0); // receive public key from client
	ctoi(buffer, e,n);
    cout << "\nPublic key received from client : {" << e << ", " << n << "}" << endl;

    cout << "\nEnter message(M<" << n << ") to encrypt : "; 
	cin >> M;

    int C = powModN(M, e, n);
    cout << "\nEncrypted Text : " << C << endl;
    send(sock, &C, sizeof(C), 0); // send ciphertext to client
    cout << "\nSent ciphertext to client." << endl << endl;
}
/*
Public key received from client : {7, 77}                                                                                                                                   
Enter message(M<77) to encrypt : 36                                                                                                                                         
Encrypted Text : 64                                                                                                                                                         
Sent ciphertext to client.
*/