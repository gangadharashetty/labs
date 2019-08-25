/*
Program: Playfair cipher
Author: Gangadhara Shetty P J

Algorithm
---------
    The 'key' for a playfair cipher is generally a word, for the sake of example we will choose 'monarchy'.
	This is then used to generate a 'key square'. Any sequence of 25 letters can be used as a key,
	so long as all letters are in it and there are no repeats. Note that there is no 'j', it is combined with 'i'.
	We now apply the encryption rules to encrypt the plaintext.

    1. Remove any punctuation or characters that are not present in the key square (this may mean spelling out numbers, punctuation etc.).
    2. Identify any double letters in the plaintext and replace the second occurence with an 'x' e.g. 'hammer' -> 'hamxmerx'.
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
#include<cmath>

using namespace std;

char matrix[5][5];

// Generate a matrix from the given key.
// Assuming all 'j' as 'i', since they can be used interchangably.
// Remove spaces in a key.
void GenerateMatrix(string key)
{
    int flag[26]={0};
    int x_ind=0, y_ind=0;
    // Add all characters present in a given key
    for(int i=0;i<key.length();i++)
    {
        if(key[i]==' ') continue;
        if(key[i]=='j') key[i]='i';

        if(!flag[key[i]-97])
            matrix[x_ind][y_ind++] = key[i], flag[key[i]-97]=1;

        if(y_ind==5)    x_ind++, y_ind=0;
    }

    // Add all other characters
    for(int i=0;i<26;i++)
    {
        if(i==9)    continue;
        if(key[i]=='j') key[i]='i';
        if(!flag[i])    matrix[x_ind][y_ind++] = i+97, flag[i]=1 ;

        if(y_ind==5)    x_ind++, y_ind=0;
    }
}

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
    for(int i=1;i<message.length();i+=2)
         if(message[i-1] == message[i])
            message = message.insert(i, "x");
    // STEP 3 in algorithm
    if(message.length()%2)
        message += "x";
    return message;
}

// Returns the row position of the given character in a matrix
int GetRow(char c)
{
    for(int i=0;i<5;i++)
        for(int j=0;j<5;j++)
            if(c==matrix[i][j])
                return i;
}

//Returns the column position of the given character in a matrix
int GetColumn(char c)
{
    for(int i=0;i<5;i++)
        for(int j=0;j<5;j++)
            if(c==matrix[i][j])
                return j;
}


string Encrypt(string message)
{
    string enc_msg;
    for(int i=0;i<message.length();i+=2)    // i is incremented by 2 inorder to group by two two characters
    {
        int xind1 = GetRow(message[i]);
        int xind2 = GetRow(message[i+1]);
        int yind1 = GetColumn(message[i]);
        int yind2 = GetColumn(message[i+1]);

        // STEP 6.a in algoritm
        if( xind1 == xind2 )
        {
            enc_msg.append(1, matrix[xind1][(yind1+1)%5]);
            enc_msg.append(1, matrix[xind2][(yind2+1)%5]);
        }
        //STEP 6.b in algorithm
        else if( yind1 == yind2 )
        {
            enc_msg.append(1, matrix[(xind1+1)%5][yind1]);
            enc_msg.append(1, matrix[(xind2+1)%5][yind2]);
        }
        // STEP 6.c in algorithm
        else
        {
            enc_msg.append(1, matrix[ xind1 ][ yind2 ]);
            enc_msg.append(1, matrix[ xind2 ][ yind1 ]);
        }
    }
    return enc_msg;
}


string Decrypt(string message)
{
    string msg;
    for(int i=0;i<message.length();i+=2)
    {
        int xind1 = GetRow(message[i]);
        int xind2 = GetRow(message[i+1]);
        int yind1 = GetColumn(message[i]);
        int yind2 = GetColumn(message[i+1]);

        // STEP 6.a in algoritm (reveres)
        if( xind1 == xind2 )
        {
            msg.append(1, matrix[xind1][ --yind1<0 ? 4: yind1 ]);   // to handle negative modlus  if(negative) 4 else num-1
            msg.append(1, matrix[xind2][ --yind2<0 ? 4: yind2 ]);
        }
        // STEP 6.b in algoritm (reverse)
        else if( yind1 == yind2 )
        {
            msg.append(1, matrix[ --xind1<0 ? 4: xind1 ][yind1]);
            msg.append(1, matrix[ --xind2<0 ? 4: xind2 ][yind2]);
        }
        // STEP 6.c in algoritm (reverse)
        else
        {
            msg.append(1, matrix[ xind1 ][ yind2 ]);
            msg.append(1, matrix[ xind2 ][ yind1 ]);
        }
    }
    return msg;
}

int main()
{
	string message, keys[100];
	int  num_of_keys;

	cout<<"Enter the number of keys:";
	cin>>num_of_keys;
	cin.get();

	cout<<"Enter the keys:";
	for(int i=0;i<num_of_keys;i++)
	    getline(cin, keys[i]);

    cout<<"Enter a message to be encrypted: ";
    getline(cin, message);

    for(int i=0;i<num_of_keys;i++)
    {
        GenerateMatrix(keys[i]);
        cout<<endl<<endl;
        cout<<"----------------------------"<<endl;
        cout<<"Using key"<<i<<": "<<keys[i]<<endl;
        cout<<"----------------------------"<<endl;
        cout<<"Key Matrix: "<<endl;
        for(int k=0;k<5;k++)
        {
            for(int j=0;j<5;j++)
                cout<<matrix[k][j]<<" ";
            cout<<endl;
        }
        cout<<"Actual Message: "<<message<<endl;
        string for_msg = FormatMessage(message);
        cout<<"Formatted Message: "<<for_msg<<endl;
        string enc_msg = Encrypt(for_msg);
        cout<<"Encrypted Message: "<<enc_msg<<endl;
        string dec_msg = Decrypt(enc_msg);
        cout<<"Decrypted Message: "<<dec_msg<<endl;
    }
	return 0;
}

/*
-------------
Sample Output
-------------

Enter the number of keys:1
Enter the keys:playfair example
Enter a message to be encrypted: hide the gold

----------------------------
Using key0: playfair example
----------------------------
Key Matrix:
p l a y f
i r e x m
b c d g h
k n o q s
t u v w z
Actual Message: hide the gold
Formatted Message: hidethegoldx
Encrypted Message: bmodzbxdnage
Decrypted Message: hidethegoldx
*/
