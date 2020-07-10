#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#pragma warning(disable: 4996)

SOCKET Connection;
void ClientHandler()
{
	int data = 0;
	int last_eating = 0;
	int eaten_back = 0;
	int weight = 0;
	bool choice;
	while (true)
	{
		Sleep(100);
		recv(Connection, (char*)&choice, sizeof(choice), NULL);
		recv(Connection, (char*)&data, sizeof(data), NULL);
		recv(Connection, (char*)&eaten_back, sizeof(eaten_back), NULL);
		recv(Connection, (char*)&weight, sizeof(weight), NULL);
		std::cout << "Ваш питомец сегодня съел " << eaten_back << " грамм корма" << std::endl;
		if (choice == true)
		{
			switch (data)
			{
			case 0:
				std::cout << "Не накладывать корм!" << std::endl;
				break;
			case 1:
				std::cout << "Наложить " << (weight * 40) / 3 << " грамм порции!" << std::endl;
				break;
			case 2:
				std::cout << "Наложить полную порцию " << (weight * 40) / 6 << " грамм!" << std::endl;
				break;
			}
		}
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

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, NULL, NULL, NULL);
	
	char msg[256];
	while (true)
	{
		std::cin.getline(msg, sizeof(msg));
		send(Connection, msg, sizeof(msg), NULL);
		Sleep(10);
	}
	/*char msg[256];
	int data = 0;
	int last_eating = 0;
	int eaten_back = 0;
	int weight = 0;
	bool choice;
	while (true)
	{
		Sleep(100);
		recv(Connection, (char*)&choice, sizeof(choice), NULL);
		recv(Connection, (char*)&data, sizeof(data), NULL);
		recv(Connection, (char*)&eaten_back, sizeof(eaten_back), NULL);
		recv(Connection, (char*)&weight, sizeof(weight), NULL);
		std::cout << "Ваш питомец сегодня съел " << eaten_back << " грамм корма" << std::endl;
		if (choice == true)
		{
			switch (data)
			{
			case 0:
				std::cout << "Не накладывать корм!" << std::endl;
				break;
			case 1:
				std::cout << "Наложить "<<(weight*40)/3<<" грамм порции!" << std::endl;
				break;
			case 2:
				std::cout << "Наложить полную порцию " << (weight * 40) / 6 << " грамм!" << std::endl;
				break;
			}
		}
	}*/

	return 0;
}