/*
Program: Columnar Transposition Cipher
Author: Gangadhara Shetty P J
Algorithm
---------
In a transposition cipher, the order of the alphabets is re-arranged to obtain the cipher-text.
	1. The message is written out in rows of a fixed length, and then read out again column by column, 
		and the columns are chosen in some scrambled order.
	2. Width of the rows and the permutation of the columns are usually defined by a keyword.
	3. Any spare spaces are filled with nulls or left blank or placed by a character to 
		construct the rectangular matrix (Example: $).
	4. Finally, the message is read off in columns, in the order specified by the keyword.
*/

#include<bits/stdc++.h>

using namespace std;


string Encrypt(string message, string keys) 
{
    string enc_msg;
    int key[keys.length()], i;
    
    for(int k=0;k<keys.length();k++)
        key[keys[k]-'0'-1] = k;
    
    for(int k=0;k<keys.length();k++){
        for(i=key[k]; i<message.length(); i+=keys.length())
            enc_msg+=message[i];
        if(i%keys.length() >= message.length()%keys.length())
            enc_msg+="$";
    }
    return enc_msg;
}

string Decrypt(string message, string keys)
{
    string msg;
    int key[keys.length()], i, len = message.length()/ keys.length();
    
    for(int k=0;k<len;k++)
        for(i=0;i<keys.length();i++)
            msg+=message[(keys[i]-'0'-1)*len + k];
    return msg;
}

int main()
{
	string message, keys;
    
    cout<<"Enter a message to be encrypted: ";
    getline(cin, message);
    
	cout << "Enter the keys as a string:";
	getline(cin, keys);
	
    string enc_msg = Encrypt(message, keys);
    string dec_msg = Decrypt(enc_msg, keys);
    cout<<"Encrypted Message: "<<enc_msg<<endl;
    cout<<"Decrypted Message: "<<dec_msg<<endl;
    
	return 0;
}

/*
-------------
Output
-------------
Enter a message to be encrypted: hidethegold
Enter the keys as a string:14253
Encrypted Message: hhddg$tl$ie$eo$
Decrypted Message: hidethegold$$$$
*/
