#include<bits/stdc++.h>

using namespace std;

int fnPow(int a, int b, int c)
{
    int res = 1;
    for(int i=0;i<a;i++)
    {
        res *= b;
        res %= c;
    }
    return res;
}

int main()
{
    long long int q, alpha, xa, xb, ya, yb, cipher, key, message;
    cout<<"Enter prime number  and primitive root: ";
    cin>>q>>alpha;
    cout<<"enter private key of a and b : ";
    cin>>xa>>xb;
    ya =fnPow(xa, alpha, q);
    yb = fnPow(xb, alpha,q);
    cout<<"public key of a = "<<ya<<"\nprivate key of b is : "<<yb<<endl;
    key = fnPow(xa, yb,q);
    cout <<"secret key of a = "<< key<<endl;
    cout <<"secret key of b = "<< fnPow(xb, ya,q)<<endl;
    cout<<"Enter a message: ";
    cin>>message;
    cipher = message ^ key;
    cout<<"cipher text = "<<cipher<<endl;
    cout<<"plain text = "<< (cipher^key) <<endl;
    
}

/*
Enter prime number  and primitive root: 761
6
enter private key of a and b : 100
200
public key of a = 399
private key of b is : 152
secret key of a = 357
secret key of b = 357
Enter a message: 98
cipher text = 263
plain text = 98
*/