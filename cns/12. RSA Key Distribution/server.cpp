/*
Program: RSA Key Exchange server
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
void itoc(int n1)
{
	string s = to_string(n1);
	strcpy(buffer, s.c_str());
}
int GetInverseDeterminant(int e ,int fi){ 
	for(int i=1;i<fi;i++)
		if((i*e)%fi==1) return i;
	return -1;
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
	cout<<"Public key of server: ("<<e<<"|"<<n<<")"<<endl;
	cout<<"Private key of server: ("<<d<<"|"<<n<<")"<<endl;
}

int main()
{
    int port=1234, sid, sid1, cid, nonces,nonces1, noncec, pue, ns, nc, pus, prs, key, p, q;
    int sock = createServer(port);
	srand(time(NULL));
	
	recv(sock, &buffer, sizeof(buffer), 0);
	ctoi(buffer, pue,nc);
	cout<<"received pue|n "<<buffer<<endl;
	
	cout << "\n2. Enter two prime numbers : "; 
	cin >> p >> q;
	
	generateKey(p, q, pus, prs, ns);
	itoc(pus, ns);
	cout<<"Sending pue|n "<<buffer<<endl;
	send(sock, &buffer, sizeof(buffer), 0);
	
	cout<<"3. Enter server ID: ";
	cin>>sid;
	nonces = rand()%100;
	itoc(powModN(sid, pue,nc), powModN(nonces, pue,nc));
	send(sock, &buffer, sizeof(buffer), 0);
	cout<<"sending plain sid|nonces "<<sid<<"|"<<nonces<<endl;
	cout<<"sending encrypted sid|nonces "<<buffer<<endl;
	
	recv(sock, &buffer, sizeof(buffer), 0);
	ctoi(buffer, nonces1, noncec);
	nonces1 = powModN(nonces1,prs,ns);
	noncec= powModN(noncec, prs,ns);
	cout<<"received encrypted nonces|noncec from client "<<buffer<<endl;
	cout<<"received decrypted nonces|noncec from client "<<nonces1<<"|"<<noncec<<endl;
	if(nonces!=nonces1)
		{	cout<<"Nonce din't match"<<endl;	exit(0);	}
	else	cout<<"Client Authenticated"<<endl;
	
	itoc(powModN(noncec, pue, nc));
	send(sock, &buffer, sizeof(buffer), 0);
	cout<<"Sending plain noncec "<<noncec<<endl;
	cout<<"Sending encrypted noncec "<<buffer<<endl;
	
	cout<<"4. Enter the key: ";
	cin>>key;
	cout<<"Sending plain key "<<key<<endl;
	key = powModN(key, prs, ns);
	key = powModN(key, pue, nc);
	itoc(key);
	send(sock, &buffer, sizeof(buffer), 0);
	cout<<"Sending encrypted key "<<buffer<<endl;
  
}

/*
received pue|n 7477|18281
3. Enter server (e|n): 4551|13231  
4. Enter server (d): 1951   
5. Enter server ID: 29    
sending plain sid|nonces 29|28       
sending encrypted sid|nonces 4168|11880  
received encrypted nonces|noncec 6840|6840  
received decrypted nonces|noncec 28|28
Sending plain noncec 28 
Sending encrypted noncec 28
6. Enter the key: 454
Sending plain key 454                                                                                                                                                                                              
Sending encrypted key 5502 
*/
