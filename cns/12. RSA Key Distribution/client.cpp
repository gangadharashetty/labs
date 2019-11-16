# include <bits/stdc++.h>
# include <arpa/inet.h> 
using namespace std;

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

int ctoi(char buf[100])
{
	int i=0;
	int n1=0;
	while(buf[i])
		n1*=10, n1+=(buf[i++]-'0');
	return n1;
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

int main()
{
    char ip[50]="127.0.0.1";
    int port=1234;
	int pue, pre, pus, sid, nonces, noncec, cid, noncec1, ns, nc;
    int sock = connectToServer(ip, port);
	char buffer[100];
	srand(time(NULL));
	noncec = rand()%100;
	cout<<"1. enter client (e|n): ";
	cin>>buffer;
	ctoi(buffer, pue,nc);
	cout<<"Sending pue|n "<<buffer<<endl;
	send(sock, &buffer, sizeof(buffer), 0); 
	cout<<"2. enter client (d): ";
	cin>>buffer;
	pre = ctoi(buffer);
	
	
	recv(sock, &buffer, sizeof(buffer), 0);
	ctoi(buffer, pus, ns);
	cout<<"received server pus|n "<<buffer<<endl;
	
	
	recv(sock, &buffer, sizeof(buffer), 0);
	ctoi(buffer, sid,nonces);
	nonces = powModN(nonces, pre, nc);
	sid=powModN(sid, pre, nc);
	cout<<"received encrypted sid|nonces "<<buffer<<endl;
	cout<<"received decrypted sid|nonces "<<sid<<"|"<<nonces<<endl;
	
	string s = to_string(powModN(nonces, pus, ns))+"|"+to_string(powModN(noncec, pus, ns));
	strcpy(buffer, s.c_str());
	send(sock, &buffer, sizeof(buffer), 0);
	cout<<"Sending plain nonces|noncec "<< nonces<<"|"<<noncec<<endl;
	cout<<"Sending encrypted nonces|noncec "<< buffer<<endl;
	
	recv(sock, &buffer, sizeof(buffer), 0);
	noncec1 = ctoi(buffer);
	cout<<"received encrypted noncec "<<noncec1<<endl;
	cout<<"received decrypted noncec "<<powModN(noncec1, pre, nc)<<endl;
	
	recv(sock, &buffer, sizeof(buffer), 0);
	cout<<"received encrypted key "<<buffer<<endl;
	cout<<"received decrypted key "<<powModN(ctoi(buffer), pre, nc)<<endl;
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