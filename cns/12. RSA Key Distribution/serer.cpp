# include <bits/stdc++.h>
# include <arpa/inet.h> 
using namespace std;

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
	{
        res = res * num;
        res = res %  n;
	}
	return res;
}
int ctoi(char buf[100])
{
	int i=0, n1=0;
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
    int port=1234, sid, sid1, cid, nonces,nonces1, noncec, pue, ns, nc, pus, prs;
    int sock = createServer(port);
	char buffer[100];
	srand(time(NULL));
	nonces = rand()%100;
	
	recv(sock, &buffer, sizeof(buffer), 0);
	ctoi(buffer, pue,nc);
	cout<<"received pue|n "<<buffer<<endl;
	
	cout<<"3. Enter server (e|n): ";
	cin>>buffer;
	ctoi(buffer, pus, ns);
	send(sock, &buffer, sizeof(buffer), 0);
	cout<<"4. Enter server (d): ";
	cin>>buffer;
	prs = ctoi(buffer);
	
	cout<<"5. Enter server ID: ";
	cin>>sid;
	string s = to_string(powModN(sid, pue,nc))+"|"+to_string(powModN(nonces, pue,nc));
	cout<<"sending plain sid|nonces "<<sid<<"|"<<nonces<<endl;
	cout<<"sending encrypted sid|nonces "<<s<<endl;
	strcpy(buffer, s.c_str());
	send(sock, &buffer, sizeof(buffer), 0);
	
	recv(sock, &buffer, sizeof(buffer), 0);
	ctoi(buffer, nonces, noncec);
	nonces1 = powModN(nonces,prs,ns);
	noncec= powModN(noncec, prs,ns);
	cout<<"received encrypted nonces|noncec "<<buffer<<endl;
	cout<<"received decrypted nonces|noncec "<<nonces1<<"|"<<noncec<<endl;
	
	s = to_string(powModN(cid, pue, nc));
	strcpy(buffer, s.c_str());
	send(sock, &buffer, sizeof(buffer), 0);
	cout<<"Sending plain noncec "<<noncec<<endl;
	cout<<"Sending encrypted noncec "<<noncec<<endl;
	
	cout<<"6. Enter the key: ";
	cin>>buffer;
	cout<<"Sending plain key "<<buffer<<endl;
	s = to_string(powModN(ctoi(buffer), pue, nc));
	strcpy(buffer, s.c_str());
	send(sock, &buffer, sizeof(buffer), 0);
	cout<<"Sending encrypted key "<<buffer<<endl;
	//recv(sock, &s, sizeof(s), 0);
    
  
    //send(sock, &s, sizeof(s), 0); 
  
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
