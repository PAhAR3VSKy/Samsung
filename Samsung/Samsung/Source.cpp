#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#pragma warning(disable: 4996)

SOCKET Connection;


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

	

	int data;
	int last_eating = 0;
	int eaten_back = 0;
	int weight = 0;
	bool choice;
	while (true)
	{
		recv(Connection, (char*)&choice, sizeof(choice), NULL);
		if (choice == true)
		{
			recv(Connection, (char*)&data, sizeof(data), NULL);
			recv(Connection, (char*)&eaten_back, sizeof(eaten_back), NULL);
			recv(Connection, (char*)&weight, sizeof(weight), NULL);
			std::cout << "��� ������� ������� ���� " << eaten_back << " ����� �����" << std::endl;
			switch (data)
			{
			case 0:
				std::cout << "�� ����������� ����!" << std::endl;
				break;
			case 1:
				std::cout << "�������� " << (weight * 40) / 3 << " ����� ������!" << std::endl;
				break;
			case 2:
				std::cout << "�������� ������ ������ " << (weight * 40) / 6 << " �����!" << std::endl;
				break;
			}
		}
	}


	return 0;
}