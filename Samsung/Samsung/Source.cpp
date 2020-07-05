#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#pragma warning(disable: 4996)

SOCKET Connection;

void ServerHandler()
{
	char msg[256];
	int distance;
	int last_eating;
	int data;
	while (true)
	{
		
	}
}

int main()
{
	setlocale(LC_ALL, "ru");
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

	Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeofaddr) != 0)
	{
		std::cout << "Error connect to server" << std::endl;
		return 1;
	}
	std::cout << "Connected" << std::endl;

	/*CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ServerHandler, NULL, NULL, NULL);

	char msgl[256];
	while (true)
	{
		std::cin.getline(msgl, sizeof(msgl));
		send(Connection, msgl, sizeof(msgl), NULL);
		Sleep(10);
	}*/

	char msg[256];
	int data;
	int last_eating;
	bool choice;
	while (true)
	{
		recv(Connection, (char*)&choice, sizeof(choice), NULL);
		recv(Connection, (char*)&data, sizeof(data), NULL);
		if (choice == true)
		{
			switch (data)
			{
			case 0:
				std::cout << "Не накладывать корм!" << std::endl;
				break;
			case 1:
				std::cout << "Наложить 45 грамм порции!" << std::endl;
				break;
			case 2:
				std::cout << "Наложить полную порцию 90 грамм!" << std::endl;
				break;
			}
		}
	}

	return 0;
}