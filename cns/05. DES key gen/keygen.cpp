/*
lab 5
Program: DES Key generator
Author: Gangadhara Shetty P J
*/
#include <bits/stdc++.h>
using namespace std;

int permChoiceOne[] = {
		57, 49, 41, 33, 25, 17, 9 ,
		1 , 58, 50, 42, 34, 26, 18,
		10, 2 , 59, 51, 43, 35, 27,
		19, 11, 3 , 60, 52, 44, 36,
		63, 55, 47, 39, 31, 23, 15,
		7 , 62, 54, 46, 38, 30, 22,
		14, 6 , 61, 53, 45, 37, 29,
		21, 13, 5 , 28, 20, 12, 4 
	};

int permChoiceTwo[] = {
		14, 17, 11, 24, 1 , 5 , 3 , 28,
		15, 6 , 21, 10, 23, 19, 12, 4 ,
		26, 8 , 16, 7 , 27, 20, 13, 2 ,
		41, 52, 31, 37, 47, 55, 30, 40,
		51, 45, 33, 48, 44, 49, 39, 56,
		34, 53, 46, 42, 50, 36, 29, 32 
	};

int leftShiftTable[] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};
string rotateSubKey(string s , int rot)
{
	return s.substr(rot, s.length()-rot) + s.substr(0, rot) ;
}
string firstPermute(string input)
{
	string res = "" ;
	for(int i=0 ; i<56 ; i++)
		res += input[permChoiceOne[i]-1];
	return res ;
}
string secondPermute(string input)
{
	string res = "" ;
	for(int i=0 ; i<48 ; i++)
		res += input[permChoiceTwo[i]-1];
	return res ;
}
void genKeys(string left, string right)
{
	ofstream fout ;
	fout.open("keygen.txt");
	for (int i=0; i<16; i++)
	{
		left = rotateSubKey(left , leftShiftTable[i]);
		right = rotateSubKey(right, leftShiftTable[i]);
		string key = secondPermute(left+right);
		cout << "key " << i+1 << " \t: " << key << endl; 
		fout << key << endl;
	}
}

int main()
{
	unsigned long long hexkey;
	cout << "\nEnter key in hexadecimal : " ;
	cin >> hex >> hexkey; // to read hex input cin >> hex >> input
	string key = bitset<64>(hexkey).to_string(); // to convert hex to binary string
	cout << "Binary key (k) \t: " << key << endl;
	key = firstPermute(key) ;
	cout << "PC-1 key (k+) \t: " << key << endl;
	cout << "\nSubKeys: " << endl;
	genKeys(key.substr(0,28) , key.substr(28,28));
	cout<<endl<<endl ;
}	

/*
Enter key in hexadecimal : 1FE22472901BB2A3
Binary key (k)  : 0001111111100010001001000111001010010000000110111011001010100011
PC-1 key (k+)   : 11010010000010101100111001111110101100000101001000011001

SubKeys:
key 1   : 110010110110001010101100110001101000000110100011
key 2   : 001101011010010010101111001001011110000110011010
key 3   : 111100110000110010000010011001010001010001000011
key 4   : 011110001010101010110100110011101000000001101110
key 5   : 100101001011010000011110000001001101111111001100
key 6   : 011001100000011001110110000110001001010011110001
key 7   : 111011101101100000100100110010111100110000100001
key 8   : 100010101010001101111010000010100110111100011000
key 9   : 111000111100001011010111100101000001110000110011
key 10  : 001111011101001110000010100011110000101001110100
key 11  : 001100100001000111111011000100011110101111010000
key 12  : 101111010100000001010101001100011000010000010101
key 13  : 000001110100101110011100110010110010010010000110
key 14  : 000111100011000110110101001011000110001110001101
key 15  : 100111110000110001101001001100100101000011000111
key 16  : 010010011010100110011011011010100010100101010110

*/