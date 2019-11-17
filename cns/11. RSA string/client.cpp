/*
Program: RSA Block client
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
int gcd(int p, int q)
{
    if(q==0)    return p;
    gcd(q, p%q);
}
void itoc(int n1, int n2)
{
	string s = to_string(n1)+"|"+to_string(n2);
	strcpy(buffer, s.c_str());
}
int GetInverseDeterminant(int e ,int fi){ 
	for(int i=1;i<fi;i++)
		if((i*e)%fi==1) return i;
	return -1;
}
void generateKey(int p, int q, int &e, int &d, int &n)
{
	n = p*q;
    int fi=(p-1)*(q-1);
    for(int i=2;i<fi; i++)
        if(gcd(i, fi) ==1)
            {e=i;  break;}
	d = GetInverseDeterminant(e, fi);
	cout<<"Public key of server: ("<<e<<"|"<<n<<")"<<endl;
	cout<<"Private key of server: ("<<d<<"|"<<n<<")"<<endl;
}
int main()
{
    char ip[50]="127.0.0.1";
    int port=1234;
	int p, q, e, d, n, fi, C, m;
    int sock = connectToServer(ip, port);
	string message;

    cout << "\nEnter two prime numbers : "; 
	cin >> p >> q;
    
	generateKey(p, q, e, d, n);
	
	itoc(e,n);
    send(sock, &buffer, sizeof(buffer), 0); 
    cout << "\nSent Public key to server." << endl;

    recv(sock, &C, sizeof(C), 0); 
	cout<<"Received Encrypted Message:  ";
	for(int i=0;i<C;i++)
	{
		recv(sock, &m, sizeof(m), 0); 
		message = message + (char)powModN(m, d, n); 
		cout<<m<<"  ";
	}
	cout<<endl<<"Message is: "<<message<<endl;
}

/*
Enter two prime numbers : 101 131                                                     
Public key of server: (3|13231)                                                       
Private key of server: (8667|13231)                                                                                                                                         
Sent Public key to server.                                                            
Received Encrypted Message:  4436  7900  12541  2767  12965  1791                     
Message is: cnslab 
*/