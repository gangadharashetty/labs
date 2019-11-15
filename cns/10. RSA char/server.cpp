# include <bits/stdc++.h>
# include <arpa/inet.h> 
using namespace std;

int createServer(int port)
{
    int sersock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {AF_INET, htons(port), INADDR_ANY};
    bind(sersock, (struct sockaddr *) &addr, sizeof(addr));

    listen(sersock, 5);
    int sock = accept(sersock, NULL, NULL);

    return sock;
}
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
int main()
{
    int port=1234;
    int sock = createServer(port);

    char PU[3];
    recv(sock, &PU, sizeof(PU), 0); // receive public key from client
    cout << "\nPublic key received from client : {" << (int)PU[0] << ", " << (int)PU[1] << "}" << endl;

    int M; // plaintext message
    cout << "\nEnter message(M<" << (int)PU[1] << ") to encrypt : "; cin >> M;

    int C = powModN(M, PU[0], PU[1]);
    cout << "\nEncrypted Text : " << C << endl;
    send(sock, &C, sizeof(C), 0); // send ciphertext to client
    cout << "\nSent ciphertext to client." << endl << endl;
}
