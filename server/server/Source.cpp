#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#pragma warning(disable: 4996)

SOCKET Connections[100];
int Counter = 0;

void ClientHandler(int index)
{
	int distance;
	int last_eating;
	bool choice;
	while (true)
	{
		recv(Connections[index], (char*)&choice, sizeof(choice), NULL);
		recv(Connections[index], (char*)&distance, sizeof(distance), NULL);
		recv(Connections[index], (char*)&last_eating, sizeof(last_eating), NULL);
		for (int i = 0; i < Counter; i++)
		{
			if (index == i)
				continue;
			send(Connections[i], (char*)&choice, sizeof(choice), NULL);
			send(Connections[i], (char*)&distance, sizeof(distance), NULL);
			send(Connections[i], (char*)&last_eating, sizeof(last_eating), NULL);
		}
	}
}

int main()
{
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0)
	{
		std::cout << "Error!" << std::endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL); 
	bind(sListen, (SOCKADDR*)&addr, sizeofaddr);
	listen(sListen, SOMAXCONN);

	SOCKET newConnection;

	for (int i = 0; i < 100; i++)
	{
		newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);

		if (newConnection == 0)
			std::cout << "Error #2" << std::endl;
		else
		{
			std::cout << "connecting" << std::endl;
			char msg[256] = "Connect is ready to work!";
			send(newConnection, msg, sizeof(msg), NULL);
			Connections[i] = newConnection;
			Counter++;
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler,(LPVOID)(i), NULL, NULL);
		}
	}

	return 0;
}