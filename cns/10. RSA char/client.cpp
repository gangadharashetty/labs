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
	{
        res = res * num;
        res = res %  n;
	}
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
int main()
{
    char ip[50]="127.0.0.1";
    int port=1234;
	long long int p, q, e, d, n, fi, C;
    int sock = connectToServer(ip, port);

    cout << "\nEnter two prime numbers : "; 
	cin >> p >> q;
    n = p*q;
    fi=(p-1)*(q-1);
    for(int i=2;i<fi; i++)
        if(gcd(i, fi) ==1)
            {e=i;  break;}
	d = GetInverseDeterminant(e, fi);
	
	cout<<"d= "<<d<<endl;
	itoc(e,n);
    send(sock, &buffer, sizeof(buffer), 0); 
    cout << "\nSent Public key to server." << endl;

    recv(sock, &C, sizeof(C), 0); 
    cout << "\nCiphertext received from server : " << C << endl;

    int M = powModN(C, d, n); 
    cout << "\nDecrypted Text : " << M << endl << endl;
}

/*
Enter two prime numbers : 11 7                                                        
d= 43                                                                                                                                                                       
Sent Public key to server.                                                                                                                                                  
Ciphertext received from server : 64                                                                                                                                        
Decrypted Text : 36
*/