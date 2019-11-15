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
    long long int p, q, n, fi, e, d;
    string msg, plain, enc;
    string bits="";
    cout<<"Enter P , Q & message values(all small letters): ";
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
		cout<<msg[i]-'a'<< "  ";
	
	for(int i=0; i<msg.length();i++){
		enc+=powModN(msg[i]-'a', e, n);
		plain+=powModN(enc[i], d, n);
	}
	
	cout<<endl<<"encrypted text = ";
	for(int i=0; i<msg.length();i++)
		cout<<(int)enc[i]<< "  ";
	
	cout<<endl<<"decrypted text = ";
	for(int i=0; i<msg.length();i++)
		cout<<(int)plain[i]<< "  ";
}
/*
Enter P , Q & message values: (all small letters)11 7 thisiscnslab
fi = 60
e = 7
d = 43
plain text = 19  7  8  18  8  18  2  13  18  11  0  1
encrypted text = 68  28  57  39  57  39  51  62  39  11  0  1
decrypted text = 19  7  8  18  8  18  2  13  18  11  0  1
*/