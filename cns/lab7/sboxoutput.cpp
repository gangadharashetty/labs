#include<bits/stdc++.h>
using namespace std;

string key;
int permute[]={
    32,1,2,3,4,5,
    4,5,6,7,8,9,
    8,9,10,11,12,13,
    12,13,14,15,16,17,
    16,17,18,19,20,21,
    20,21,22,23,24,25,
    24,25,26,27,28,29,
    28,29,30,31,32,1
};

void findPermutation()
{
    string key1;
    for(int i=0;i<48;i++)
        key1 += key[permute[i]-1+32];
    key=key1;
}

int main()
{

    unsigned long long hexKey;
    string inputkey;
    cout<<"Enter a 64 bit key in hex: ";
    cin>>hex>>hexKey;
        key=bitset<64>(hexKey).to_string();
        findPermutation();
        cout<<"Enter a 48 bit input key in hex: ";
        cin>>hex>>hexKey;

        inputkey=bitset<48>(hexKey).to_string();

        for(int i=0;i<48;i++)
            if(key[i]==inputkey[i]) key[i]='0';
            else key[i]='1';

        cout<<"S-BOX INPUT: "<<hex<< bitset<48>(key).to_ulong()<<endl;

}


/*

ro = 1111 0000 1010 1010 1111 0000 1010 1010
aaaaaaaaf0aaf0aa

k1 = 0001 1011 0000 0010 1110 1111 1111 1100 0111 0000 0111 0010
1b02effc7072

xor = 011110 100001 010101 010101 011110 100001 010101 010101

R1 = 0110 0001 0001 0111 1011 1010 1000 0110 0110 0101 0010 0111
6117ba866527


OUTPUT
------
Enter a 64 bit key in hex: aaaaaaaaf0aaf0aa
Enter a 48 bit input key in hex: 1b02effc7072
S-BOX INPUT: 6117ba866527

*/