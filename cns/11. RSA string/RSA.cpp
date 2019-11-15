#include<iostream>
#include<cmath>

using namespace std;

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
    long long int p, q, n, fi, e, d;
    string msg, plain, enc;
    string bits="";
    cout<<"Enter P , Q & message values: ";
    cin>>p>>q>>msg;
    n = p*q;
    fi=(p-1)*(q-1);
    cout<<"fi = "<<fi<<endl;
    for(int i=2;i<fi; i++)
        if(gcd(i, fi) ==1)
            {e=i;  break;}
    cout<<"e = "<<e<<endl;
    d = GetInverseDeterminant(e, fi);
    if(d<0) d = fi - (-d%fi);
    else d = d%fi;
    cout<<"d = "<<d<<endl;
	cout<<"plain text = ";
	for(int i=0; i<msg.length();i++)
		cout<<(int)msg[i]<< "  ";
	for(int i=0; i<msg.length();i++){
		enc+=(int)pow(msg[i], e) % n;
		plain+=(int)pow(enc[i], d) % n;
	}
	cout<<endl<<"encrypted text = ";
	for(int i=0; i<msg.length();i++)
		cout<<(int)enc[i]<< "  ";
	cout<<endl<<"decrypted text = ";
	for(int i=0; i<msg.length();i++)
		cout<<(int)plain[i]<< "  ";
}
/*
Enter P , Q & message values: 3
5
adfugehvlehariop
fi = 8
e = 3
d = 3
plain text = 0  3  5  20  6  4  7  21  11  4  7  0  17  8  14  15
encrypted text = 12  10  3  3  7  10  14  7  12  10  14  12  9  14  6  13
decrypted text = 0  3  5  20  6  4  7  21  11  4  7  0  17  8  14  15
*/