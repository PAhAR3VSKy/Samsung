#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <fstream>
#include <iostream>
#pragma warning(disable: 4996)

using namespace std;

SOCKET Connection;

int main()
{
	setlocale(LC_ALL, "ru");

	bool choice = false;
	int distance;
	int last_eating;
	int weight;

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

	std::cout << "Сколько килограмм весит ваш питомец: ";
	std::cin >> weight;
	std::cout << "Вашему питомцу необходимо " << weight * 40 << " грамм сухого корма в день" << endl;

	while (true)
	{
		std::cout << "Питомец подошел к кормушке?(1-Да 0-Нет)" << std::endl;
		std::cin >> choice;
		if (choice == false)
			continue;
		else
		{
			std::cout << "Сколько прошел питомец с момента последнего приема пищи в метрах: ";
			std::cin >> distance;
			std::cout << "Когда питомец последний раз кушал (указать в часах): ";
			std::cin >> last_eating;
			send(Connection, (char*)&weight, sizeof(weight), NULL);
			Sleep(10);
			send(Connection, (char*)&choice, sizeof(choice), NULL);
			Sleep(10);
			send(Connection, (char*)&distance, sizeof(distance), NULL);
			Sleep(10);
			send(Connection, (char*)&last_eating, sizeof(distance), NULL);
			Sleep(10);
		}
	}

	return 0;
}