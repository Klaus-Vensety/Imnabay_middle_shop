#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <conio.h>
#include <string>

// ----------------------------- Учётные записи -----------------------------------
size_t userSize = 2;
std::string userStatus[3]{ "Супер администратор", "Администратор", "Сотрудник" };
std::string* loginArr = new std::string[userSize]{ "admin", "user" };
std::string* passArr = new std::string[userSize]{ "admin", "user" };
std::string* statusArr = new std::string[userSize]{ userStatus[0], userStatus[2] };
std::string currentStatus;
// --------------------------------------------------------------------------------

// --------------------------------- Склад ----------------------------------------
size_t storageSize = 0;
size_t maxItemSize = 299;
unsigned int* idArr = nullptr;
std::string* nameArr = nullptr;
long double* priceArr = nullptr;
unsigned int* countArr = nullptr;
bool isStorageCreated = false;

void CreateStorage();
void ShowStorage(int mode = 0);
void AddStorageItem();
void RemoveStorageItem();
void ChangePrice();

void ChangeStorage();
void AddNewItem();
void ChangeName();


template<typename ArrType>
void FillArr(ArrType* dynamicArr, ArrType* staticArr, size_t arraySize);
// --------------------------------------------------------------------------------

// -------------------------------- Служебные -------------------------------------
void Start();
bool Login();
void ShowSuperAdminMenu();
bool IsNumber(const std::string& str);

inline void Getline(std::string& str);
inline void Err();
// --------------------------------------------------------------------------------

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(NULL));
    Start();

    delete[] loginArr, passArr, statusArr;
    if (isStorageCreated)
    {
        delete[] idArr, nameArr, countArr, priceArr;
    }
    return 0;
}

void Start()
{
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
                    CreateStorage();
                    system("cls");
                    ShowSuperAdminMenu();
                    break;
                }
                else if (choose == "2")
                {
                    // Создание нового склада
                    ShowSuperAdminMenu();
                    break;
                }
                else
                {
                    Err();
                }
            }
        }
        else if (currentStatus == userStatus[1])
        {
            // Готовый склад
        }
        else if (currentStatus == userStatus[2])
        {
            // Готовый склад
        }
    }
    else
    {
        system("cls");
        std::cout << "\n\n\tЗавершение работы\n";
        Sleep(2000);
        system("cls");
    }
}

bool Login()
{
    std::string login, pass;

    while (true)
    {
        std::cout << "\nМагазин военной техники 'Счастливая смерть' - лучший поставщик оружия на Ближнем Востоке\n\n";
        std::cout << "Продажа гражданам и жителям Израиля запрещена по политическим причинам.\n\n";
        std::cout << "Продажа террористическим организациям и бандам запрещена\n\n\n";
        std::cout << "Введите логин: ";
        Getline(login);
        std::cout << "Введите пароль: ";
        Getline(pass);
        if (login == "exit" && pass == "exit")
        {
            currentStatus = "";
            return false;
        }
        for (size_t i = 0; i < userSize; i++)
        {
            if (login == loginArr[i] && pass == passArr[i])
            {
                system("cls");
                std::cout << "Пользователь: " << loginArr[i] << "\nДобро пожаловать!\n\n";
                std::cout << "Ваш статус: " << statusArr[i] << "\n\n";
                currentStatus = statusArr[i];
                return true;
            }
        }

        Err();
    }
}

void ShowSuperAdminMenu()
{
    std::string choose;
    while (true)
    {
        std::cout << "1 - Начать продажу\n";
        std::cout << "2 - Показать склад\n";
        std::cout << "3 - Пополнить склад\n";
        std::cout << "4 - Списать товар\n";
        std::cout << "5 - Изменить цену\n";
        std::cout << "6 - Редактировать склад\n";
        std::cout << "7 - Редактировать персонал\n";
        std::cout << "8 - Отчёт о прибыли\n";
        std::cout << "0 - Закрыть смену\n";
        std::cout << "Ввод: ";
        Getline(choose);
        if (choose == "1")
        {
            
        }
        else if (choose == "2")
        {
            ShowStorage();
        }
        else if (choose == "3")
        {
            AddStorageItem();
        }
        else if (choose == "4")
        {
            RemoveStorageItem();
        }
        else if (choose == "5")
        {
            ChangePrice();
        }
        else if (choose == "6")
        {
            ChangeStorage();
        }
        else if (choose == "7")
        {
        }
        else if (choose == "8")
        {
        }
        else if (choose == "0")
        {
        }
        else
        {
            Err();
        }
    }
}

void CreateStorage()
{
    const size_t staticSize = 20;
    unsigned int idStatic[staticSize];
    for (size_t i = 0; i < staticSize; ++i)
    {
        idStatic[i] = static_cast<unsigned int>(i + 1);
    }

    std::string nameStatic[staticSize]{
        "Разведывательный дрон = Bayraktar TB3 (стелс-пакет)",
        "Ударный дрон = Hermes-900X (комплект)",
        "Многоцелевой Истребитель = F-35X (демонстрационный)",
        "Тактический БПЛА = MQ-9 Reaper Pro",
        "Тяжёлый танк = M1A3 Abrams (модификация)",
        "Самоходная артиллерия = PzH 2000 Elite",
        "Ракетная система залпового огня = HIMARS-X (усиленная)",
        "Тактический ракетный комплекс = ATACMS Advanced",
        "Штурмовой вертолёт = AH-64E Guardian",
        "Шифрованный космический спутник-разведчик (малый)",
        "Десантный корабль поддержки = LPD-X",
        "Противокорабельный комплекс = Harpoon NEXT",
        "Авианосец (симуляция) = CVN-XX (демонстрация)",
        "Промежуточный баллистический комплекс = TBM-Alpha (модульный)",
        "Электронная война станция = EW-9000",
        "Многофункциональный беспилотный флот = SkyFleet Pack (3 шт)",
        "Тактическая подводная лодка (модель) = SSK-Pro",
        "Оборонительная платформа ПВО = S-400 Lite",
        "Мобильный ракетный комплекс = MRLS Titan",
        "Гиперзвуковая пусковая установка = Hypersonic Launcher MkI"
    };

    long double priceStatic[staticSize]{
        25000000.00, 18000000.00, 120000000.00, 35000000.00, 95000000.00,
        15000000.00, 40000000.00, 80000000.00, 60000000.00, 500000000.00,
        1000000000.00, 45000000.00, 20000000000.00, 250000000.00, 30000000.00,
        120000000.00, 70000000.00, 90000000.00, 60000000.00, 1500000000.00
    };

    unsigned int countStatic[staticSize]{ 5,8,2,6,3,4,6,2,5,1,1,10,1,1,3,2,2,2,4,1 };

    delete[] idArr;
    delete[] nameArr;
    delete[] priceArr;
    delete[] countArr;

    storageSize = staticSize;
    idArr = new unsigned int[storageSize];
    nameArr = new std::string[storageSize];
    priceArr = new long double[storageSize];
    countArr = new unsigned int[storageSize];

    FillArr(idArr, idStatic, storageSize);
    FillArr(nameArr, nameStatic, storageSize);
    FillArr(priceArr, priceStatic, storageSize);
    FillArr(countArr, countStatic, storageSize);

    isStorageCreated = true;
}

void ShowStorage(int mode)
{
    if (mode == 0)
    {
        system("cls");
        std::cout << "ID\t" << std::left << std::setw(25) << "Название товара\t\t"
            << "Цена\t" << "Кол-во\n";
        for (size_t i = 0; i < storageSize; i++)
        {
            std::cout << idArr[i] << "\t" << std::left << std::setw(25) << nameArr[i] << "\t"
                << priceArr[i] << "\t" << countArr[i] << "\n";
        }
        system("pause");
        system("cls");
    }
    else if (mode == 1)
    {
        std::cout << "ID\t" << std::left << std::setw(25) << "Название товара\t\t"
            << "Кол-во\n";
        for (size_t i = 0; i < storageSize; i++)
        {
            std::cout << idArr[i] << "\t" << std::left << std::setw(25) << nameArr[i] << "\t"
                << "\t" << countArr[i] << "\n";
        }
    }
    else if (mode == 2)
    {
        std::cout << "ID\t" << std::left << std::setw(25) << "Название товара\t\t"
            << "Цена\t";
        for (size_t i = 0; i < storageSize; i++)
        {
            std::cout << idArr[i] << "\t" << std::left << std::setw(25) << nameArr[i] << "\t"
                << priceArr[i] << "\n";
        }
    }
    else if (mode == 3)
    {
        std::cout << "ID\t" << std::left << std::setw(25) << "Название товара\n";
            
        for (size_t i = 0; i < storageSize; i++)
        {
            std::cout << idArr[i] << "\t" << std::left << std::setw(25) << nameArr[i] << "\t";
        }
    }
}

void AddStorageItem()
{
    std::string chooseId, chooseCount, choose;
    unsigned int id = 0, count = 0;
    while (true)
    {
        system("cls");
        ShowStorage(1);
        std::cout << "Введите ID товара или \"exit\" для выхода: ";
        Getline(chooseId);
        if (chooseId == "exit")
        {
            std::cout << "Отмена операции пополнения склада!\n";
            Sleep(1500);
            system("cls");
            break;
        }
        std::cout << "Введите кол-во товара для пополнения: ";
        Getline(chooseCount);
        if (IsNumber(chooseId) && IsNumber(chooseCount))
        {
            id = std::stod(chooseId) - 1;
            count = std::stod(chooseCount);
            if (id < 0 || id > storageSize - 1 || count < 0 || count > maxItemSize)
            {
                std::cout << "Некорректный id или кол-во\nМаксимальное кол-во - " << maxItemSize << "\n\n";
                Sleep(1500);
            }
            else
            {
                std::cout << std::left << std::setw(25) << nameArr[id] << "\t"
                    << countArr[id] << " ---> " << countArr[id] + count << "\n\n";
                std::cout << "Подтвердить?\n1 - Да\n2 - Нет\nВвод: ";
                Getline(choose);

                if (choose == "1")
                {
                    countArr[id] += count;
                    std::cout << "Товара успешно пополнен\n\n";
                    Sleep(1500);
                    system("cls");
                    break;
                }

                else if (choose == "2")
                {
                    std::cout << "Отмена пополнния!";
                    Sleep(1500);

                }
            }
        }
    }
}

void RemoveStorageItem()
{
    std::string chooseId, chooseCount, choose;
    unsigned int id = 0, count = 0;
    while (true)
    {
        system("cls");
        ShowStorage(1);
        std::cout << "Введите ID товара или \"exit\" для выхода: ";
        Getline(chooseId);
        if (chooseId == "exit")
        {
            std::cout << "Отмена операции списания товара!\n";
            Sleep(1500);
            system("cls");
            break;
        }
        std::cout << "Введите кол-во товара для списания: ";
        Getline(chooseCount);
        if (IsNumber(chooseId) && IsNumber(chooseCount))
        {
            id = std::stod(chooseId) - 1;
            count = std::stod(chooseCount);
            if (id < 0 || id > storageSize - 1 || count < 0 || count > countArr[id])
            {
                std::cout << "Некорректный id или кол-во\nМаксимальное кол-во - " << countArr[id] << "\n\n";
                Sleep(1500);
            }
            else
            {
                std::cout << std::left << std::setw(25) << nameArr[id] << "\t"
                    << countArr[id] << " ---> " << countArr[id] - count << "\n\n";
                std::cout << "Подтвердить?\n1 - Да\n2 - Нет\nВвод: ";
                Getline(choose);

                if (choose == "1")
                {
                    countArr[id] -= count;
                    std::cout << "Товара успешно списан\n\n";
                    Sleep(1500);
                    system("cls");
                    break;
                }

                else if (choose == "2")
                {
                    std::cout << "Отмена списания!";
                    Sleep(1500);

                }
            }
        }
    }
}

void ChangePrice()
{
    std::string chooseId, choosePrice, choose;
    unsigned int id = 0, count = 0;
    long double newPrice;

    while (true)
    {
        system("cls");
        ShowStorage(1);
        std::cout << "Введите ID товара или \"exit\" для выхода: ";
        Getline(chooseId);
        if (chooseId == "exit")
        {
            std::cout << "Отмена операции изминения цены!\n";
            Sleep(1500);
            system("cls");
            break;
        }
        std::cout << "Введите новую цену товара: ";
        Getline(choosePrice);
        if (IsNumber(chooseId) && IsNumber(choosePrice))
        {
            id = std::stod(chooseId) - 1;
            newPrice = std::stod(choosePrice);
            if (id < 0 || id > storageSize - 1 || newPrice < 0 || newPrice > 999999999999)
            {
                std::cout << "Некорректный id или кол-во\nМаксимальное кол-во - " << countArr[id] << "\n\n";
                Sleep(1500);
            }
            else
            {
                std::cout << std::left << std::setw(25) << nameArr[id] << "\t"
                    << priceArr[id] << " ---> " << priceArr[id] - newPrice << "\n\n";
                std::cout << "Подтвердить?\n1 - Да\n2 - Нет\nВвод: ";
                Getline(choose);

                if (choose == "1")
                {
                    priceArr[id] = newPrice;
                    std::cout << "Товара успешно списан\n\n";
                    Sleep(1500);
                    system("cls");
                    break;
                }

                else if (choose == "2")
                {
                    std::cout << "Отмена списания!";
                    Sleep(1500);

                }
            }
        }
    }
}

void ChangeStorage()
{
    std::string choose;

    while (true)
    {
        system("cls");

        std::cout << "1 - Добавить новый товар\n";
        std::cout << "2 - Изменить название товара\n";
        std::cout << "3 - Удалить товар\n";
        std::cout << "0 - Выход из редактора склада\n";
        std::cout << "Ввод: ";


        Getline(choose);

        if (choose == "1")
        {
            AddNewItem();
        }
        else if (choose == "2")
        {
            ChangeName();
        }
        else if (choose == "3")
        {

        }
        else if (choose == "0")
        {
            system("cls");
            break;
        }
        else
        {
            Err();
        }

    }

}

void AddNewItem()
{
    std::string newName, newPrice, newCount, choose;
    long double price = 0.0, count = 0.0;
    bool exit = "true";

    while (true) 
    {

        while (true)
        {


            std::cout << "\tДобавление новго товара!\n\nВведите \"exit\" для прекращения операции\n\n";

            std::cout << "Введите названние нового товара: ";
            Getline(newName);

            if (newName == "exit")
            {
                std::cout << "Операция добавления товара прервана!\n\n";
                Sleep(1500);
                exit = false;
                break;
            }

            if (newName.size() <= 0 || newName.size() >= 70)
            {
                std::cout << "Максимальная длинная названия товара 70 символов\n";
                Sleep(1500);
            }

            else
            {
                break;
            }

        }

        while (exit)
        {
            system("cls");

            std::cout << "Введите кол-во нового товара: ";
            Getline(newName);

            if (newName == "exit")
            {
                std::cout << "Операция добавления товара прервана!\n\n";
                Sleep(1500);
                exit = false;
                break;
            }

            if (IsNumber(newCount))
            {
                count = std::stod(newCount);
                if (count > maxItemSize)
                {
                    std::cout << "Ошибка максимального размера товара. Не более " << maxItemSize << " ед.\n\n";
                    Sleep(1500);
                }
                else
                {
                    break;
                }
            }

        }



        while (exit)
        {
            std::cout << "Введите цену нового товара: ";
            Getline(newName);

            if (newPrice == "exit")
            {
                std::cout << "Операция добавления товара прервана!\n\n";
                Sleep(1500);
                exit = false;
                break;
            }

            if (IsNumber(newCount))
            {
                price = std::stod(newCount);
                if (price > maxItemSize)
                {
                    std::cout << "Ошибка максимальной цены товара. Не более " << 999999999999 << " ед.\n\n";
                    Sleep(1500);

                }
                else
                {
                    break;
                }
            }

        }

        if (exit)
        {
            std::cout << "Новый товар: " << newName << "\nКол-во: " << count << "\nЦена: " << price << "\n\n";
            std::cout << "Подвтердить?\n1- Да\n2 - Нет\nВвод: ";

            Getline(choose);

            if (choose == "1")
            {
                storageSize++;
                unsigned int* idArrTemp = new unsigned int[storageSize];
                std::string* nameArrTemp = new std::string[storageSize];
                unsigned int* countArrTemp = new unsigned int[storageSize];
                long double *priceArrTemp = new long double[storageSize];

                FillArr(idArrTemp, idArr, storageSize - 1);
                FillArr(nameArrTemp, nameArr, storageSize - 1);
                FillArr(countArrTemp, countArr, storageSize - 1);
                FillArr(priceArrTemp, priceArr, storageSize - 1);

                idArrTemp[storageSize - 1] = storageSize;
                nameArrTemp[storageSize - 1] = newName;
                priceArrTemp[storageSize - 1] = price;
                countArrTemp[storageSize - 1] = count;


                std::swap(idArr, idArrTemp);
                std::swap(nameArr, nameArrTemp);
                std::swap(countArr, countArrTemp);
                std::swap(priceArr, priceArrTemp);

                delete[]idArrTemp, priceArrTemp, countArrTemp, nameArrTemp;

                std::cout << "Идет подготовка... ";
                Sleep(2000);
                std::cout << "Товар успешно добавлен!\n\n";
            }
            else if (choose == "2")
            {
                std::cout << "Отмена\n\n";
                Sleep(1500);
            }
            else
            {
                Err();
            }
        }
        
        if (exit == false)
        {
            break;
        }

         

    }

}

void ChangeName()
{
    std::string chooseId, newName, choose;
    unsigned int id = 0;

    while (true)
    {
        system("cls");
        ShowStorage(3);
        std::cout << "Введите ID товара или \"exit\" для выхода\n: ";
        Getline(chooseId);

        if (chooseId == "exit")
        {
            std::cout << "Операция смены названия прервана!\n\n";
            Sleep(1500);
            break;
        }

        std::cout << "Введите названние нового товара или \"exit\" для прекращения операции\n: ";
        Getline(newName);

        if (newName.size() <= 0 || newName.size() >= 70 || newName == "exit")
        {
            std::cout << "Максимальная длинная названия 70 символов\n";
            Sleep(1500);
        }

        else
        {
            id = std::stod(chooseId);
            std::cout << "\n" << std::left << std::setw(25)
                << nameArr[id] << "----> " << newName << "\n\n";
            std::cout << "Подтвердить?\n1 - Да\n2 - Нет\nВвод: ";
            Getline(choose);
        }

    }
}





bool IsNumber(const std::string& str)
{
    if (str.size() <= 0 || str.size() >= 999999999999)
    {
        std::cout << "Некорректный ввод\n";
        std::cout << "Ошибка размера числа. От 1 до 999.999.999.999 символов включительно\n\n";
        Sleep(1500);
        return false;
    }
    for (size_t i = 0; i < str.size(); i++)
    {
        if (!std::isdigit(str[i]))
        {
            std::cout << "Некорректный ввод\n";
            std::cout << "Введённые данные не являются числом\n\n";
            Sleep(1500);
            return false;
        }
    }
    return true;
}

inline void Getline(std::string& str)
{
    std::getline(std::cin, str, '\n');
}

inline void Err()
{
    Sleep(1500);
    system("cls");
    std::cout << "Некорректный ввод";
}

template<typename ArrType>
void FillArr(ArrType* dynamicArr, ArrType* staticArr, size_t arraySize)
{
    for (size_t i = 0; i < arraySize; i++)
    {
        dynamicArr[i] = staticArr[i];
    }
}