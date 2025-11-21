#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <unordered_set>

// ----------------------------- Учётные записи -----------------------------------
size_t userSize = 2;
std::string userStatus[3]{ "Супер администратор", "Администратор", "Сотрудник" };
std::string* loginArr = new std::string[userSize]{ "admin", "user" };
std::string* passArr = new std::string[userSize]{ "admin", "user" };
std::string* statusArr = new std::string[userSize]{ userStatus[0], userStatus[2] };
std::string currentStatus;

// Глобальное множество для проверки символов
std::unordered_set<char> specialSymbols;
bool isSetCreated = false;

void ChangeAccounts();
void ShowUsers();
void AddNewUser();
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
void DeleteItem();

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
bool CheckLogin(const std::string& str);

void SetSpecialSymbols();
// --------------------------------------------------------------------------------

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(static_cast<unsigned int>(time(NULL)));
    Start();

    delete[] loginArr;
    delete[] passArr;
    delete[] statusArr;
    if (isStorageCreated)
    {
        delete[] idArr;
        delete[] nameArr;
        delete[] countArr;
        delete[] priceArr;
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
            ChangeAccounts();
        }
        else if (choose == "8")
        {
        }
        else if (choose == "0")
        {
            break;
        }
        else
        {
            Err();
        }
    }
}

void ChangeAccounts()
{
    if (!isSetCreated)
    {
        SetSpecialSymbols();
    }

    std::string choose;

    while (true)
    {
        system("cls");

        std::cout << "1 - Добавить нового пользователя\n";
        std::cout << "2 - Показать пользователей\n";
        std::cout << "3 - Изменить пароль пользователя\n";
        std::cout << "4 - Удалить пользователя\n";
        std::cout << "0 - Выход из редактора аккаунтов\n";
        std::cout << "Ввод: ";

        Getline(choose);

        if (choose == "1")
        {
            AddNewUser();
        }
        else if (choose == "2")
        {
            ShowUsers();
        }
        else if (choose == "3")
        {
            // Реализовать изменение пароля
        }
        else if (choose == "4")
        {
            // Реализовать удаление пользователя
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

void ShowUsers()
{
    system("cls");
    std::cout << "\t" << std::left << std::setw(12) << "Логин\t\t " << "Пароль\t\t\t" << "Роль\n";

    for (size_t i = 0; i < userSize; i++)
    {
        std::cout << i + 1 << "\t" << std::left << std::setw(8) << loginArr[i] << "\t\t" << passArr[i]
            << "\t\t\t" << statusArr[i] << "\n";
    }
    system("pause");
}

void AddNewUser()
{
    // Реализовать добавление нового пользователя
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

    if (isStorageCreated)
    {
        delete[] idArr;
        delete[] nameArr;
        delete[] priceArr;
        delete[] countArr;
    }

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
    if (storageSize == 0)
    {
        std::cout << "Склад пуст!\n";
        system("pause");
        return;
    }

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
            std::cout << idArr[i] << "\t" << std::left << std::setw(25) << nameArr[i] << "\n";
        }
    }
}

void AddStorageItem()
{
    if (storageSize == 0)
    {
        std::cout << "Склад пуст! Сначала создайте склад.\n";
        Sleep(1500);
        return;
    }

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
            id = std::stoi(chooseId) - 1;
            count = std::stoi(chooseCount);
            if (id >= storageSize || count == 0 || count > maxItemSize)
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
                    std::cout << "Товар успешно пополнен\n\n";
                    Sleep(1500);
                    system("cls");
                    break;
                }
                else if (choose == "2")
                {
                    std::cout << "Отмена пополнения!";
                    Sleep(1500);
                }
            }
        }
    }
}

void RemoveStorageItem()
{
    if (storageSize == 0)
    {
        std::cout << "Склад пуст! Сначала создайте склад.\n";
        Sleep(1500);
        return;
    }

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
            id = std::stoi(chooseId) - 1;
            count = std::stoi(chooseCount);
            if (id >= storageSize || count == 0 || count > countArr[id])
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
                    std::cout << "Товар успешно списан\n\n";
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
    if (storageSize == 0)
    {
        std::cout << "Склад пуст! Сначала создайте склад.\n";
        Sleep(1500);
        return;
    }

    std::string chooseId, choosePrice, choose;
    unsigned int id = 0;
    long double newPrice;

    while (true)
    {
        system("cls");
        ShowStorage(2);
        std::cout << "Введите ID товара или \"exit\" для выхода: ";
        Getline(chooseId);
        if (chooseId == "exit")
        {
            std::cout << "Отмена операции изменения цены!\n";
            Sleep(1500);
            system("cls");
            break;
        }
        std::cout << "Введите новую цену товара: ";
        Getline(choosePrice);
        if (IsNumber(chooseId) && IsNumber(choosePrice))
        {
            id = std::stoi(chooseId) - 1;
            newPrice = std::stold(choosePrice);
            if (id >= storageSize || newPrice < 0 || newPrice > 999999999999)
            {
                std::cout << "Некорректный id или цена\nМаксимальная цена - 999999999999\n\n";
                Sleep(1500);
            }
            else
            {
                std::cout << std::left << std::setw(25) << nameArr[id] << "\t"
                    << priceArr[id] << " ---> " << newPrice << "\n\n";
                std::cout << "Подтвердить?\n1 - Да\n2 - Нет\nВвод: ";
                Getline(choose);

                if (choose == "1")
                {
                    priceArr[id] = newPrice;
                    std::cout << "Цена успешно изменена\n\n";
                    Sleep(1500);
                    system("cls");
                    break;
                }
                else if (choose == "2")
                {
                    std::cout << "Отмена изменения!";
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
            DeleteItem();
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
    long double price = 0.0;
    unsigned int count = 0;
    bool exit = true;

    while (true)
    {
        system("cls");
        std::cout << "\tДобавление нового товара!\n\nВведите \"exit\" для прекращения операции\n\n";

        std::cout << "Введите название нового товара: ";
        Getline(newName);

        if (newName == "exit")
        {
            std::cout << "Операция добавления товара прервана!\n\n";
            Sleep(1500);
            break;
        }

        if (newName.empty() || newName.size() >= 70)
        {
            std::cout << "Максимальная длина названия товара 70 символов\n";
            Sleep(1500);
            continue;
        }

        std::cout << "Введите кол-во нового товара: ";
        Getline(newCount);

        if (newCount == "exit")
        {
            std::cout << "Операция добавления товара прервана!\n\n";
            Sleep(1500);
            break;
        }

        if (!IsNumber(newCount) || (count = std::stoi(newCount)) > maxItemSize)
        {
            std::cout << "Ошибка максимального размера товара. Не более " << maxItemSize << " ед.\n\n";
            Sleep(1500);
            continue;
        }

        std::cout << "Введите цену нового товара: ";
        Getline(newPrice);

        if (newPrice == "exit")
        {
            std::cout << "Операция добавления товара прервана!\n\n";
            Sleep(1500);
            break;
        }

        if (!IsNumber(newPrice) || (price = std::stold(newPrice)) > 999999999999)
        {
            std::cout << "Ошибка максимальной цены товара. Не более 999999999999\n\n";
            Sleep(1500);
            continue;
        }

        std::cout << "Новый товар: " << newName << "\nКол-во: " << count << "\nЦена: " << price << "\n\n";
        std::cout << "Подтвердить?\n1- Да\n2 - Нет\nВвод: ";
        Getline(choose);

        if (choose == "1")
        {
            size_t newStorageSize = storageSize + 1;
            unsigned int* idArrTemp = new unsigned int[newStorageSize];
            std::string* nameArrTemp = new std::string[newStorageSize];
            unsigned int* countArrTemp = new unsigned int[newStorageSize];
            long double* priceArrTemp = new long double[newStorageSize];

            for (size_t i = 0; i < storageSize; i++)
            {
                idArrTemp[i] = idArr[i];
                nameArrTemp[i] = nameArr[i];
                countArrTemp[i] = countArr[i];
                priceArrTemp[i] = priceArr[i];
            }

            idArrTemp[storageSize] = static_cast<unsigned int>(storageSize + 1);
            nameArrTemp[storageSize] = newName;
            priceArrTemp[storageSize] = price;
            countArrTemp[storageSize] = count;

            delete[] idArr;
            delete[] nameArr;
            delete[] countArr;
            delete[] priceArr;

            idArr = idArrTemp;
            nameArr = nameArrTemp;
            countArr = countArrTemp;
            priceArr = priceArrTemp;
            storageSize = newStorageSize;

            std::cout << "Идет подготовка... ";
            Sleep(2000);
            std::cout << "Товар успешно добавлен!\n\n";
            break;
        }
        else if (choose == "2")
        {
            std::cout << "Отмена\n\n";
            Sleep(1500);
            break;
        }
        else
        {
            Err();
        }
    }
}

void ChangeName()
{
    if (storageSize == 0)
    {
        std::cout << "Склад пуст! Сначала создайте склад.\n";
        Sleep(1500);
        return;
    }

    std::string chooseId, newName, choose;
    size_t id = 0;

    while (true)
    {
        system("cls");
        ShowStorage(3);
        std::cout << "Введите ID товара или \"exit\" для выхода: ";
        Getline(chooseId);

        if (chooseId == "exit")
        {
            std::cout << "Операция смены названия прервана!\n\n";
            Sleep(1500);
            break;
        }

        if (!IsNumber(chooseId))
        {
            continue;
        }

        id = std::stoi(chooseId) - 1;

        if (id >= storageSize)
        {
            std::cout << "Некорректный ID\n";
            Sleep(1500);
            continue;
        }

        std::cout << "Введите новое название товара: ";
        Getline(newName);

        if (newName.empty() || newName.size() >= 70)
        {
            std::cout << "Максимальная длина названия 70 символов\n";
            Sleep(1500);
            continue;
        }

        std::cout << "\n" << std::left << std::setw(25)
            << nameArr[id] << " ---> " << newName << "\n\n";
        std::cout << "Подтвердить?\n1 - Да\n2 - Нет\nВвод: ";
        Getline(choose);

        if (choose == "1")
        {
            nameArr[id] = newName;
            std::cout << "Изменение названия успешно завершено";
            Sleep(1500);
            break;
        }
        else if (choose == "2")
        {
            std::cout << "Отмена\n";
            Sleep(1500);
            break;
        }
        else
        {
            Err();
        }
    }
}

void DeleteItem()
{
    if (storageSize == 0)
    {
        std::cout << "Склад пуст! Сначала создайте склад.\n";
        Sleep(1500);
        return;
    }

    std::string chooseId, choose;
    size_t id = 0;

    while (true)
    {
        system("cls");
        ShowStorage(3);
        std::cout << "\nВведите ID товара для удаления или \"exit\" для выхода: ";
        Getline(chooseId);

        if (chooseId == "exit")
        {
            std::cout << "Операция удаления прервана!\n\n";
            Sleep(1500);
            break;
        }

        if (!IsNumber(chooseId))
        {
            continue;
        }

        id = std::stoi(chooseId) - 1;

        if (id >= storageSize)
        {
            std::cout << "Ошибка ID\n";
            Sleep(1500);
            continue;
        }

        std::cout << "Удаляемый товар: " << nameArr[id] << "\n\n";
        std::cout << "Подтвердить?\n1 - Да\n2 - Нет\nВвод: ";
        Getline(choose);

        if (choose == "1")
        {
            if (storageSize == 1)
            {
                delete[] idArr;
                delete[] nameArr;
                delete[] countArr;
                delete[] priceArr;

                idArr = nullptr;
                nameArr = nullptr;
                countArr = nullptr;
                priceArr = nullptr;
                storageSize = 0;
                isStorageCreated = false;
            }
            else
            {
                size_t newStorageSize = storageSize - 1;
                unsigned int* idArrTemp = new unsigned int[newStorageSize];
                std::string* nameArrTemp = new std::string[newStorageSize];
                unsigned int* countArrTemp = new unsigned int[newStorageSize];
                long double* priceArrTemp = new long double[newStorageSize];

                for (size_t i = 0, j = 0; i < storageSize; i++)
                {
                    if (i == id) continue;

                    idArrTemp[j] = j + 1;
                    nameArrTemp[j] = nameArr[i];
                    countArrTemp[j] = countArr[i];
                    priceArrTemp[j] = priceArr[i];
                    j++;
                }

                delete[] idArr;
                delete[] nameArr;
                delete[] countArr;
                delete[] priceArr;

                idArr = idArrTemp;
                nameArr = nameArrTemp;
                countArr = countArrTemp;
                priceArr = priceArrTemp;
                storageSize = newStorageSize;
            }

            std::cout << "Идет подготовка... ";
            Sleep(2000);
            std::cout << "Товар успешно удален!\n\n";
            break;
        }
        else if (choose == "2")
        {
            std::cout << "Отмена\n\n";
            Sleep(1500);
            break;
        }
        else
        {
            Err();
        }
    }
}

bool IsNumber(const std::string& str)
{
    if (str.empty())
    {
        std::cout << "Некорректный ввод\n";
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
    std::cout << "Некорректный ввод";
    Sleep(1500);
    system("cls");
}

bool CheckLogin(const std::string& str)
{
    if (str.size() < 5 || str.size() > 20)
    {
        std::cout << "Недопустимая длина логина. От 5 до 20\n";
        Sleep(1500);
        return false;
    }

    for (char sym : str)
    {
        if (specialSymbols.find(sym) == specialSymbols.end())
        {
            std::cout << "Некорректные символы в логине!\n\n";
            Sleep(1500);
            return false;
        }
    }

    return true;
}

void SetSpecialSymbols()
{
    for (char i = '0'; i <= '9'; i++)
    {
        specialSymbols.insert(i);
    }
    for (char i = 'A'; i <= 'Z'; i++)
    {
        specialSymbols.insert(i);
    }
    for (char i = 'a'; i <= 'z'; i++)
    {
        specialSymbols.insert(i);
    }
    isSetCreated = true;
}

template<typename ArrType>
void FillArr(ArrType* dynamicArr, ArrType* staticArr, size_t arraySize)
{
    for (size_t i = 0; i < arraySize; i++)
    {
        dynamicArr[i] = staticArr[i];
    }
}