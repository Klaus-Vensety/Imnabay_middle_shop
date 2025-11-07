#include <iostream>
#include <Windows.h>
#include <string>
#include <iomanip>
#include <ctime>

// Сначала объявляем userStatus, так как она используется ниже
std::string userStatus[3]{ "Супер администратор", "Администратор", "Сотрудник" };

// -------------------------Учетные записи-----------------------------------------------------------------------------------------------------------------------------
size_t userSize = 2;
std::string* loginArr = new std::string[userSize]{ "admin", "user" };
std::string* passArr = new std::string[userSize]{ "admin", "user" };
std::string* statusArr = new std::string[userSize]{ userStatus[0], userStatus[2] };
std::string currentStatus;

//  --------------------------------------------------------------------------------------------------------------------------------------------------------------------






// -------------------------Склад----------------------------------------------------------------------------------------------------------------------------------------

size_t storageSize = 10;
int* idArr = new int[storageSize];
std::string* nameArr = new std::string[storageSize]{};
double* priceArr = new double[storageSize] {};
unsigned int* count = new unsigned int[storageSize] {};



// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Start();
bool Login();

void CreateStorage()
{
	const size_t staticSize = 10;

	int id[staticSize]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	std::string name[staticSize]{
		"Пистолет = Glock 19",
		"Автомат = M4A1",
		"Дробовик = Benelli M4",
		"Граната = M67",
		"Пулемет = M240",
		"Пистолет-пулемет = MP5",
		"Дрон = MQ-1 Predator",
		"FPV-Дрон = SkyDrone",
		"Мина = GMM-140",
		"Гранатамет = M32"
	};
	double price[staticSize]{
		700.00, // Glock 19
		1500.00, // M4A1
		2000.00, // Benelli M4
		40.00,   // M67
		3000.00, // M240
		1200.00, // MP5
		70000.00,// MQ-1 Predator
		5000.00, // SkyDrone
		100.00,  // GMM-140
		3000.00  // M32
	};
	int count[staticSize]{
		50, // Glock 19
		50, // M4A1
		50, // Benelli M4
		50, // M67
		50, // M240
		50, // MP5
		25, // MQ-1 Predator
		25, // SkyDrone
		25, // GMM-140
		50  // M32
	};


}



inline void Getline(std::string& str);
inline void Err();








int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));

	Start();

	// Правильное освобождение памяти
	delete[] loginArr;
	delete[] passArr;
	delete[] statusArr;

	return 0;
}

void Start()
{
	std::cout << "\n\n\nСчастливая смерть - лучший поставшик оружия на ближнем востоке.\nПродажи для граждан и жителей израиля запрешены по политическим мативам.";
	std::cout << "\nПродажа для террористических оргонизаций и группировок запрешена.\n\n\n";

	std::string choose;

	if (Login())
	{
		if (currentStatus == userStatus[0])
		{
			while (true)
			{
				std::cout << "Выберите тип склада\n1 - Готовый\n2 - Новый\nВвод: ";
				Getline(choose);

				if (choose == "1")
				{
					//создание готового склада.
					break;
				}
				else if (choose == "2")
				{
					//создание нового склада
					break;
				}
			}
		}
		else if (currentStatus == userStatus[1])
		{
			//готовый склад
		}
		else if (currentStatus == userStatus[2])
		{
			//готовый склад
		}
	}
	else
	{
		std::cout << "Завершение работы.";  // Добавлен недостающий <<
		Sleep(2000);
		system("cls");
	}
}

bool Login()
{
	std::string login, pass;

	while (true)
	{
		std::cout << "Введите логин: ";
		Getline(login);
		std::cout << "Введите пароль: ";
		Getline(pass);

		if (login == "exit" && pass == "exit")
		{
			currentStatus = "";
			return false;
		}

		if (login == loginArr[0] && pass == passArr[0])
		{
			std::cout << "\nПользователь: " << loginArr[0] << "\n\nДобро пожаловать\n\n";
			std::cout << "Ваш статус: " << statusArr[0] << "\n\n";
			currentStatus = statusArr[0];
			return true;
		}

		for (size_t i = 1; i < userSize; i++)
		{
			if (login == loginArr[i] && pass == passArr[i])
			{
				std::cout << "\nПользователь: " << loginArr[i] << "\n\nДобро пожаловать\n\n";
				std::cout << "Ваш статус: " << statusArr[i] << "\n\n";
				currentStatus = statusArr[i];
				return true;
			}
		}
		Err();
	}
}

void Getline(std::string& str)
{
	std::getline(std::cin, str, '\n');
}

void Err()
{
	std::cout << "\n Некоректный ввод\n\n";
}


