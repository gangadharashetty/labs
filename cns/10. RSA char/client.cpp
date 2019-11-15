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

long long int gcd(int p, int q)
{
    if(q==0)    return p;
    gcd(q, p%q);
}

int GetInverseDeterminant(int R , int D){ //R is the remainder or determinant
	int i =0 ;
	int p0= 0 , p1 =1 ; 
	int q = 1 , q0 , q1 = D/R; 
	int fi=D;
	while(R!=0){
		q = D/R ;
		int tempD = D ; 
		D = R ; 
		R = tempD%R ; 

		if(i==0) { p0 = 0 ; q0 = q ; }
		else if(i==1){ p1==1 ;q1 = q ; }
		else{
			int temp = p1 ;
			p1 = (p0-p1*(q0))% fi; 
			if(p1<0)p1 = fi-((-p1)%fi) ; 
			p0 = temp ;
			
			q0 = q1; 
			q1 = q ;
		}

		i++ ; 
	}
	p1 = (p0-p1*(q0))%fi ; 
	return p1 ; 
}

int main()
{
    char ip[50]="127.0.0.1";
    int port=1234;
	long long int p, q, e, d, n, fi;
    int sock = connectToServer(ip, port);

    cout << "\nEnter two prime numbers : "; 
	cin >> p >> q;
    n = p*q;
    fi=(p-1)*(q-1);
    for(int i=2;i<fi; i++)
        if(gcd(i, fi) ==1)
            {e=i;  break;}
	d = GetInverseDeterminant(e, fi);
	if(d<0) d = fi - (-d%fi);
    else d = d%fi;
	
	cout<<"d= "<<d<<endl;
	char pu[3]={e, n, '\0'};
    send(sock, &pu, sizeof(pu), 0); 
    cout << "\nSent Public key to server." << endl;

    int C; 
    recv(sock, &C, sizeof(C), 0); 
    cout << "\nCiphertext received from server : " << C << endl;

    int M = powModN(C, d, n); 
    cout << "\nDecrypted Text : " << M << endl << endl;
}
