/*
Program: BBS Algorithm
Author: Gangadhara Shetty P J
*/

#include<bits/stdc++.h>
#define BIT_SIZE 16

using namespace std;

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

bool rabinMiller(int n)
{
	int k, q=n-1;
	for(k=0; q%2==0; k++, q/=2);

    for(int i=0; i<4; i++)
    {
        int a = rand()%(n-1)+1;
        if(powModN(a,q,n) == 1)	
			return true;
        for(int j=0; j<=k-1; j++)
            if(powModN(a, pow(2,j)*q, n) == n-1)
                return true;
	}
    return false;
}

int main()
{
    long long int s, p, q, n;
    string bits="";
	srand(time(NULL));
    cout<<"Enter P, Q and Seed value: ";
    cin>>p>>q>>s;
    n = p*q;
    s=(s*s)%n;
	cout<<"bits generated: ";
    for(int i=0;i<BIT_SIZE;i++)
        s=(s*s)%n, bits+=(s%2+'0'), cout<<s%2<<" ";
    int num = bitset<BIT_SIZE>(bits).to_ulong(); 
    cout<<endl<<"Random Number: "<<num<<endl;
	cout<<"Rabin Miller test: ";
    if(rabinMiller(num))
		cout<<"Composite"<<endl;
	else
		cout<<"InConclusive"<<endl;
	
    
}
/*
output:
Enter P, Q and Seed value: 7 11 7
bits generated: 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1
Random Number: 4369
Rabin Miller test: InConclusive
*/