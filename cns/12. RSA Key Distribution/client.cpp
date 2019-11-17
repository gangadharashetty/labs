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
int GetInverseDeterminant(int e ,int fi){ 
	for(int i=1;i<fi;i++)
		if((i*e)%fi==1) return i;
	return -1;
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
void ctoi(char buf[100], int &n1, int &n2)
{
	int i=0;
	n1=0;n2=0;
	while(buf[i]!='|')
		n1*=10, n1+=(buf[i++]-'0');
	while(buf[++i])
		n2*=10, n2+=(buf[i]-'0');
}
void itoc(int n1, int n2)
{
	string s = to_string(n1)+"|"+to_string(n2);
	strcpy(buffer, s.c_str());
}
int gcd(int p, int q)
{
    if(q==0)    return p;
    gcd(q, p%q);
}
void generateKey(int p, int q, int &e, int &d, int &n)
{
	n = p*q;
    int fi=(p-1)*(q-1);
    for(int i=2;i<fi; i++)
        if(gcd(i, fi) ==1)
            {e=i;  break;}
	d = GetInverseDeterminant(e, fi);
	cout<<"Public key of client: ("<<e<<"|"<<d<<")"<<endl;
	cout<<"Private key of client: ("<<d<<"|"<<d<<")"<<endl;
}

int main()
{
    char ip[50]="127.0.0.1";
    int port=1234, pue, pre, pus, sid, nonces, noncec, cid, noncec1, ns, nc, p, q;
    int sock = connectToServer(ip, port);
	srand(time(NULL));
	
	cout << "\n1. Enter two prime numbers : "; 
	cin >> p >> q;
	
	generateKey(p, q, pue, pre, nc);
	itoc(pue, nc);
	cout<<"Sending pue|n "<<buffer<<endl;
	send(sock, &buffer, sizeof(buffer), 0);
	
	recv(sock, &buffer, sizeof(buffer), 0);
	ctoi(buffer, pus, ns);
	cout<<"received server pus|n "<<buffer<<endl;
	
	
	recv(sock, &buffer, sizeof(buffer), 0);
	ctoi(buffer, sid,nonces);
	nonces = powModN(nonces, pre, nc);
	sid=powModN(sid, pre, nc);
	cout<<"received encrypted sid|nonces "<<buffer<<endl;
	cout<<"received decrypted sid|nonces "<<sid<<"|"<<nonces<<endl;
	
	noncec = rand()%100;
	itoc(powModN(nonces, pus, ns), powModN(noncec, pus, ns));
	send(sock, &buffer, sizeof(buffer), 0);
	cout<<"Sending plain nonces|noncec "<< nonces<<"|"<<noncec<<endl;
	cout<<"Sending encrypted nonces|noncec "<< buffer<<endl;
	
	recv(sock, &buffer, sizeof(buffer), 0);
	noncec1 = atoi(buffer);
	noncec1 = powModN(noncec1, pre, nc);
	cout<<"received encrypted noncec "<<buffer<<endl;
	cout<<"received decrypted noncec "<<noncec1<<endl;
	if(noncec!=noncec1)
		{	cout<<"Nonce din't match"<<endl;	exit(0);	}
	else	cout<<"Server Authenticated"<<endl;
	
	recv(sock, &buffer, sizeof(buffer), 0);
	cout<<"received encrypted key "<<buffer<<endl;
	int key = powModN(atoi(buffer), pre, nc);
	key = powModN(key, pus, ns);
	cout<<"received decrypted key "<<key<<endl;
	return 0;
}

/*
1. enter client (e|n): 7477|18281                                                                                                                                                                                  
Sending pue|n 7477|18281   
2. enter client (d): 14413 
received server pus|n 4551|13231 
received encrypted sid|nonces 4168|11880                                                                                                                                                                           
received decrypted sid|nonces 29|28 
Sending plain nonces|noncec 28|28       
Sending encrypted nonces|noncec 6840|6840  
received encrypted noncec 6726  
received decrypted noncec 14381
received encrypted key 5502  
received decrypted key 454
*/