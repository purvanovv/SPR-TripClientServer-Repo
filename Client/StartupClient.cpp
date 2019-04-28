#include <iostream>
#include <string>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

void main()
{
	string ipAddress = "192.168.0.104";
	int port = 54000;

	//initialize winsock
	WSADATA data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0)
	{
		cerr << "Can't start Winsock,Err #" << wsResult << endl;
		return;
	}

	//create socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		cerr << "Can't create socket,Err #" << WSAGetLastError() << endl;
		WSACleanup();
		return;
	}

	//fill in hint structure
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

	//connnect to server
	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		cerr << "Can't connect to server, Err #" << WSAGetLastError() << endl;
		closesocket(sock);
		WSACleanup();
		return;
	}

	//do-while loop to send and receive data
	char buf[4096];
	string userInput;

	do
	{
		//Prompt the user for some text
		cout << "> ";
		getline(cin, userInput);

		if (userInput.size() > 0) // make sure the user has typed in something
		{
			//send the text
			int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
			if (sendResult != SOCKET_ERROR)
			{
				//wait for response
				ZeroMemory(buf, 4096);
				int bytesReceived = recv(sock, buf, 4096, 0);
				if (bytesReceived > 0) {
					//echo response to console
					cout << "SERVER> " << string(buf, 0, bytesReceived) << endl;

				}

			}
		}

	} while (userInput.size() > 0);

	//gracefully close down everything
	closesocket(sock);
	WSACleanup();
}