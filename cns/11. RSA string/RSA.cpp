#include<iostream>
#include<cmath>

using namespace std;

int gcd(int p, int q)
{
    if(q==0)    return p;
    gcd(q, p%q);
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