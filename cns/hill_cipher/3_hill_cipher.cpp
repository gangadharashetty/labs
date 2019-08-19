/*
Program: Hill cipher
Author: Gangadhara Shetty P J
B
Algorithm
---------
    The 'key' for a playfair cipher is generally a word, for the sake of example we will choose 'monarchy'. 
	This is then used to generate a 'key square'. Any sequence of 25 letters can be used as a key, 
	so long as all letters are in it and there are no repeats. Note that there is no 'j', it is combined with 'i'. 
	We now apply the encryption rules to encrypt the plaintext.

    1. Remove any punctuation or characters that are not present in the key square (this may mean spelling out numbers, punctuation etc.).
    2. Identify any double letters in the plaintext and replace the second occurence with an 'x' e.g. 'hammer' -> 'hamxer'.
    3. If the plaintext has an odd number of characters, append an 'x' to the end to make it even.
    4. Break the plaintext into pairs of letters, e.g. 'hamxer' -> 'ha mx er'
    5. The algorithm now works on each of the letter pairs.
    6. Locate the letters in the key square, (the examples given are using the key square above)

        a. If the letters are in different rows and columns, replace the pair with the letters on the same row respectively 
		   but at the other pair of corners of the rectangle defined by the original pair. 
		   The order is important – the first encrypted letter of the pair is the one that lies on the same row as the first plaintext letter.

        b. If the letters appear on the same row of the table, replace them with the letters to their immediate right respectively 
		   (wrapping around to the left side of the row if a letter in the original pair was on the right side of the row).

        c. If the letters appear on the same column of the table, replace them with the letters immediately below respectively 
		   (wrapping around to the top side of the column if a letter in the original pair was on the bottom side of the column).

*/

#include<iostream>

using namespace std;

float keyMatrix[100][100], inverseMatrix[100][100];
int order;

string FormatMessage(string message)
{
    // STEP 1 in algorithm
    for(int i=0;i<message.length();i++)
    {
        if(message[i] == ' ')   // add conditions here for any other special characters
            message = message.replace(i, 1, "");
        if(message[i] == 'j')
            message = message.replace(i, 1, "i");
    }

    // STEP 2 in algorithm
    for(int i=1;i<message.length();i++)
         if(message[i-1] == message[i])
            message = message.insert(i, "x"), i++;
    // STEP 3 in algorithm
    if(message.length()%2)
        message += "x";
    return message;
}

int GetInverseDeterminant(int a, int m)
{
    a = a%m;
    for (int x=1; x<m; x++)
        if ((a*x) % m == 1)
            return x;
}

int GetDeterminant()
{
    int determinant = 0;
    if(order==2)
        determinant = keyMatrix[0][0] * keyMatrix[1][1] - keyMatrix[0][1] * keyMatrix[1][0];
    else
        for(int i = 0; i < 3; i++)
            determinant = determinant + (keyMatrix[0][i] * (keyMatrix[1][(i+1)%3] * keyMatrix[2][(i+2)%3] - keyMatrix[1][(i+2)%3] * keyMatrix[2][(i+1)%3]));

    if(determinant<0)
        determinant = 26 - (int(-determinant)%26);
    else
        determinant = int(-determinant)%26;
    return GetInverseDeterminant(determinant, 26);
}

string Multiply(string msg_group, float matrix[][100])
{
    string result;
    for(int i=0; i<order; i++)
    {
        float val = 0 ;
        for(int j=0;j<order; j++)
            val = val + matrix[j][i] * (msg_group[j] - 'a');

        if(val>=0)
            val =  int(val)%26 + 'a';
        else
            val = 26 - (int(-val)%26) + 'a'; 

        result += int(val);
    }
    return result;
}

void FindInverse(int determinant)
{
    if(order==2)
    {
        inverseMatrix[0][0] = keyMatrix[1][1]*determinant;
        inverseMatrix[1][1] = keyMatrix[0][0]*determinant;
        inverseMatrix[0][1] = -keyMatrix[0][1]*determinant;
        inverseMatrix[1][0] = -keyMatrix[1][0]*determinant;
    }
    else
        for(int j=0; j<order; j++)
            for(int i=0; i<order; i++)
                inverseMatrix[i][j] = ((keyMatrix[(j+1)%3][(i+1)%3] * keyMatrix[(j+2)%3][(i+2)%3]) - (keyMatrix[(j+1)%3][(i+2)%3] * keyMatrix[(j+2)%3][(i+1)%3]))*determinant;
}

string Encrypt(string message) 
{
    string enc_msg;
    for(int i=0;i<message.length();i+=order)
    {
        string msg_group = message.substr(i, order);
        msg_group = Multiply(msg_group, keyMatrix);
        enc_msg = enc_msg.append(msg_group);
    }
    return enc_msg;
}

string Decrypt(string message)
{
    string msg;
    FindInverse(GetDeterminant());
    for(int i=0;i<message.length();i+=order)
    {
        string msg_group = message.substr(i, order);
        msg_group = Multiply(msg_group, inverseMatrix);
        msg = msg.append(msg_group);
    }
    return msg;
}

int main()
{
	string message;
    cout << "Enter the key matrix order: ";
    cin >> order;
    
	cout << "Enter the keys:";
	for(int i = 0; i < order; i++)
	    for(int j=0;j<order; j++)
	        cin >> keyMatrix[i][j];
    cin.get();

    cout<<"Enter a message to be encrypted: ";
    getline(cin, message);

    FormatMessage(message);
    string enc_msg = Encrypt(message);
    string dec_msg = Decrypt(enc_msg);
    cout<<"Message: "<<message<<endl;
    cout<<"Encrypted Message: "<<enc_msg<<endl;
    cout<<"Decrypted Message: "<<dec_msg<<endl;
    
	return 0;
}

/*
-------------
Sample Output
-------------
Enter the key matrix order: 3
Enter the keys:17 17 5
21 18 21
2 2 19
Enter a message to be encrypted: paymoremoney
Message: paymoremoney
Encrypted Message: rrlmwbkaspdh
Decrypted Message: paymoremoney








*/
