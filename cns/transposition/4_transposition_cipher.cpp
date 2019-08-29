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

string matrix[100], keys;
int rows=0;

// STEP 1 in algorithm
// keys.length() is STEP 2in algorithm
// 
void constructMatrix(string message)
{
	string str="";
    for(int j=0, count=0; count!=message.length(); j++, count++){
        str += message[count];	// constructing each row
        if( j == keys.length() )  matrix[rows] = str, rows++, str="", j=0;	// resetting for the next rows
    }
	matrix[rows] = str;
}

// STEP 4 in algorithm
string Encrypt(string message)
{
    string enc_msg;
    for(int i=0;i<keys.length();i++)
		for(int j=0;j<=rows;j++)
			enc_msg += matrix[j][i];
    return enc_msg;
}

// Reverse steps of algorithm
string Decrypt(string message)
{
    string msg;
	int count=0;
	
	// construct the matrix columnwise
    for(int i=0;i<keys.length();i++)
		for(int j=0;j<=rows && count<message.length(); j++)
			matrix[j][i]=message[count++];
	// read the matrix row wise for the actual message
	for(int i=0;i<=rows;i++)
		msg+=matrix[i];
    return msg;
}

int main()
{
    string message;

    cout<<"Enter a message to be encrypted: ";
    getline(cin, message);

	cout << "Enter the keys as a string:";
	getline(cin, keys);

	// STEP 3 in algorithm (padded with $)
    while(message.length()%keys.length()) message+='$';

    constructMatrix(message);

    string enc_msg = Encrypt(message);
    string dec_msg = Decrypt(enc_msg);
    cout<<"Message: "<<message<<endl;
    cout<<"Encrypted Message: "<<enc_msg<<endl;
    cout<<"Decrypted Message: "<<dec_msg<<endl;

        return 0;
}

/*
------
Output
------
Enter a message to be encrypted: hide the gold
Enter the keys as a string:14253
Message: hide the gold$$
Encrypted Message: hhliedd $eg$ o
Decrypted Message: hide the gold$$

*/
