/*
Program: MonoAlphabetic cipher
Author: Gangadhara Shetty P J

Algorithm
---------
A mono-alphabetic cipher is a type of simple substitution cipher. In this cipher technique each letter of 
the plaintext is replaced by another letter in the cipher-text. An example of a mono-alphabetic cipher key follows:
 
Plain Text   >>>   a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z
Cipher Text >>>  z  w  x  y  o  p  r  q  a  h  c  b  e  s  u  t  v  f  g  j  l  k  m  n  d  i
 
This key means that any ‘a’ in the plaintext will be replaced by a ‘z’ in the cipher-text, any ‘z’ in the plaintext will be replaced by a ‘i’ in the cipher-text, and so on.
The following program shows the simple implementation of mono-alphabetic cipher technique in c language for encrypting and decrypting file

*/
#include<bits/stdc++.h>

using namespace std;

int frequency_count[256];
vector<string> keys;

// To encrypt the plain_text with the key
string Encrypt(string plain_text, string unique_characters, string key)
{
    for(int i=0; i<plain_text.length(); i++)
        plain_text[i] = key[ unique_characters.find( plain_text[i] ) ];
    return plain_text;
}

void GenerateKeysByPermutation(string text)
{
    // next_permutation is a readily available function to generate permutation of the string
    while(next_permutation(text.begin(), text.end()))
    {
//        cout<<text<<endl;
        keys.push_back(text);
    }
}

string ReadFile(char* file_name)
{
    string text;
    ifstream fin(file_name);
    fin>>text;
    fin.close();
    return text;
}

void StoreFile(char* file_name, string text)
{
    ofstream fout(file_name);
    fout<<text;
    fout.close();
}

string GetUniqueCharacters(string plain_text)
{
    int flag[255]={0};
    string unique_characters="";
	// To get the list of unique characters in the above string
	// Also get the number of occurence of the characters to find the frequence later
    for(int i=0;i<plain_text.length();i++){
        if( !frequency_count[plain_text[i]] )
            unique_characters+=plain_text[i];
		frequency_count[plain_text[i]]++;
	}
    return unique_characters;
}

void CalculateFrequency(string unique_characters, string key, string text)
{
    float length = text.length();
    cout<<"Frequency\tUnique Characters\tChoosen Key"<<endl;
    cout<<"-----------------------------------------------------------------"<<endl;
	// Frequency / Length * => percentage of occurance of the character in the entire string
	for(int i=0; i<unique_characters.length();i++)
		cout << frequency_count[ unique_characters[i] ] / length * 100 << "\t\t\t" << unique_characters[i] << "\t\t" << key[i] << endl;
}

int main() {
	string unique_characters, key, plain_text, cipher_text;

    srand(time(0));

    plain_text = ReadFile("plain_text.txt");

    cout<<"plain_text:\t"<<plain_text<<endl;

    unique_characters = GetUniqueCharacters( plain_text );
	cout<<"unique character:\t"<<unique_characters<<endl;

    GenerateKeysByPermutation( unique_characters );
    key = keys[rand()%100];
    cout<<"Choosen Key:\t"<<key<<endl;

    cipher_text = Encrypt( plain_text, unique_characters, key );
    cout<<"cipher_text:\t"<<cipher_text<<endl;

    StoreFile("cipher_text.txt", cipher_text);

    CalculateFrequency(unique_characters, key, plain_text);

	return 0;
}

/*
-------------
Sample Output
-------------

plain_text:     gauggsdgssgsgsasuuasudduugdsugs
unique character:       gausd
Choosen Key:    sgaud
cipher_text:    sgassudsuususuguaaguaddaasduasu

Frequency       Unique Characters       Choosen Key
-----------------------------------------------------------------
25.8065                 g               s
9.67742                 a               g
22.5806                 u               a
29.0323                 s               u
12.9032                 d               d
*/
