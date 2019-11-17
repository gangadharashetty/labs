/*
Program: RC4 Algorithm
Author: Gangadhara Shetty P J
*/
#include<iostream>
using namespace std;
int main()
{
    int s[256], t[256], k[256], p[256], c[256], j=0;
    string plain, cipher, key;
    cout<<"Enter plain text:";
    cin>>plain;
    cout<<"Enter key:";
    cin>>key;
	
    cout<<"plaintext in bytes : " ;
	for(int i =0 ;i < plain.length() ; i++) cout<< (int)plain[i]<<" " ;
	cout<<endl;

    for(int i=0;i<255;i++)
        s[i] = i, t[i] = (int)key[i % key.length()];
	
    for(int i=0, j=0; i<256; i++){
        j = (j+s[i]+t[i])%256;
        int t = s[i],   s[i] = s[j],   s[j] = t;
    }

    int i=0;
    j=0;
    for(int l=0;l<plain.length();l++){
        i = (i+1)%256;
        j=(j+s[i])%256;

        int t = s[i],   s[i] = s[j],   s[j] = t;

        t= (s[i]+s[j])%256;
        k[l] = s[t];
    }
    cout<<"keystream in bytes : " ;
    for(int i =0 ;i < plain.length() ; i++) cout<< k[i]<<" " ;
    cout<<endl;

    cout<<"cipher text in bytes : " ;
    for(int i=0;i<plain.length();i++)
        c[i] = (plain[i] ^ k[i]), cout<< (int)(plain[i] ^ k[i])<< "  ";
    cout<<endl;

    cout<<"plain text in bytes after decryption : " ;
    for(int i=0;i<plain.length();i++)
        cout<<  (int)(c[i] ^ k[i])<< "  ";
    cout<<endl;
}
/*
output:
Enter plain text:CNSLAB
Enter key:BALSNC
plaintext in bytes : 67 78 83 76 65 66
keystream in bytes : 170 24 147 247 205 32
cipher text in bytes : 233  86  192  187  140  98
plain text in bytes after decryption : 67  78  83  76  65  66
*/