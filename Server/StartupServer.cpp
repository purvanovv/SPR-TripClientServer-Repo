#include <iostream>
#include <WS2tcpip.h>

#pragma comment (lib, "ws2_32.lib")

using namespace std;

void main(){

	// initialize winsock
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsok = WSAStartup(ver, &wsData);
	if (wsok != 0) {
		cerr << "Can't initialize winsock!" << endl;
		return;
	}

	// createsock
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET) {
		cerr << "Can't create a socket!" << endl;
		return;
	}

	//bind sock to an ip address and port
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(listening, (sockaddr*)&hint, sizeof(hint));

	//tell winsock for a listening
	listen(listening, SOMAXCONN);

	//wait for a connection
	sockaddr_in client;
	int clientSize = sizeof(client);

	SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

	char host[NI_MAXHOST];	//client's remote name
	char service[NI_MAXSERV];	//service (i.e port) the client is connected on

	ZeroMemory(host, NI_MAXHOST); // same as memset (host, 0, NI_MAXHOST);
	ZeroMemory(service, NI_MAXSERV);

	if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
	{
		cout << host << "connected on port" << service << endl;
	}
	else
	{
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		cout << host << "connected on port" << ntohs(client.sin_port) << endl;
	}

	//close listening sock
	closesocket(listening);

	//while loop: accecp message and back to client
	char buf[4096];

	while (true)
	{
		ZeroMemory(buf, 4096);

		//Wait for client to send data
		int bytesReceived = recv(clientSocket, buf, 4096, 0);
		if (bytesReceived == SOCKET_ERROR)
		{
			cerr << "Error in receive!" << endl;
			break;
		}

		if (bytesReceived == 0)
		{
			cout << "Client disconnected" << endl;
			break;
		}

		//Echo message back to client
		cout << buf << endl;
		send(clientSocket, buf, bytesReceived + 1, 0);
	}

	//closesock
	closesocket(clientSocket);

	//cleanup winsock
	WSACleanup();

}