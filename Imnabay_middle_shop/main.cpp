#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <unordered_set>

// ----------------------------- Учётные записи -----------------------------------
size_t userSize = 2;
size_t staffCount = 1;
std::string userStatus[3]{ "Супер администратор","Администратор","Сотрудник" };
std::string* loginArr = new std::string[userSize]{ "admin","user" };
std::string* passArr = new std::string[userSize]{ "admin","user" };
std::string* statusArr = new std::string[userSize]{ userStatus[0], userStatus[2] };
double* salesArr = new double[userSize] {0.0, 0.0};
unsigned int* userIdArr = new unsigned int[userSize] {1, 2};
unsigned int currentId = 0;
std::string currentStatus;

void ChangeAccounts();
void ShowUsers(int mode = 0);
void AddNewUsers();
void ChangePass();
void DeleteUser();
// --------------------------------------------------------------------------------

// --------------------------------- Склад ----------------------------------------
size_t storageSize = 0;
size_t maxItemSize = 299;
unsigned int* idArr = nullptr;
std::string* nameArr = nullptr;
double* priceArr = nullptr;
unsigned int* countArr = nullptr;
bool isStorageCreated = false;

void CreateStorage();
void ShowStorage(int mode = 0);
void AddStorageItem();
void RemovesStorageItem();
void ChangePrice();

void ChangeStorage();
void AddNewItem();
void ChangeName();
void DeleteItem();

template<typename ArrType>
void FillArr(ArrType* dynamicArr, ArrType* staticArr, size_t arraySize);
// --------------------------------------------------------------------------------

// ---------------------------------- Продажи ------------------------------------
size_t checkSize = 0;
int* idArrCheck = nullptr;
std::string* nameArrCheck = nullptr;
unsigned int* quantityArrCheck = nullptr;
double* priceArrCheck = nullptr;
double* totalPriceArrCheck = nullptr;

double cashIncome = 0.0;
double bankIncome = 0.0;
double cash = 5000 + rand() % 7000;

// Функции для скидок
bool CheckVolumeDiscount(double& totalSum);
bool ApplyPromoCodeDiscount(double& totalSum);
void ApplyDiscount(double& totalSum, double discountPercent, const std::string& discountName);

void Selling();
void CheckArrPushback();
void PrintCheck(double& totalSum);
void StorageReturner();
// --------------------------------------------------------------------------------

// --------------------------------- Служебные -----------------------------------
std::unordered_set<char> specialSymbols;
std::unordered_set<char> passSymbols;
bool isPassSetCreated = false;
bool isSetCreated = false;

void Start();
bool Login();
bool Logout();
void ShowSuperAdminMenu();
void ShowAdminMenu();
void ShowUserMenu();
void ShowIncome();
void SetSpecialSymbols();
void SetPassSymbols();
bool CheckPass(const std::string& str);
bool CheckLogin(const std::string& str);
bool IsNumber(const std::string& str, bool allowDecimal = false);
inline void Getline(std::string& str);
inline void Err();
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
    delete[] salesArr;
    delete[] userIdArr;

    if (isStorageCreated)
    {
        delete[] idArr;
        delete[] nameArr;
        delete[] countArr;
        delete[] priceArr;
    }

    // Очистка чеков
    if (idArrCheck) delete[] idArrCheck;
    if (nameArrCheck) delete[] nameArrCheck;
    if (quantityArrCheck) delete[] quantityArrCheck;
    if (priceArrCheck) delete[] priceArrCheck;
    if (totalPriceArrCheck) delete[] totalPriceArrCheck;

    return 0;
}

// Функция проверки скидки за объем покупки
bool CheckVolumeDiscount(double& totalSum)
{
    for (size_t i = 0; i < checkSize; i++)
    {
        // Проверка условия: покупка более 4 штук одного товара ИЛИ общая стоимость товара более 150 млн
        if (quantityArrCheck[i] > 4 || totalPriceArrCheck[i] > 150000000.0)
        {
            std::cout << "\nТовар '" << nameArrCheck[i] << "' подходит для скидки за объем!\n";
            std::cout << "Количество: " << quantityArrCheck[i] << " шт., Сумма: " << totalPriceArrCheck[i] << " руб.\n";
            ApplyDiscount(totalSum, 15.0, "скидка за объем покупки (15%)");
            return true;
        }
    }
    return false;
}

// Функция применения промокода (теперь только при оплате)
bool ApplyPromoCodeDiscount(double& totalSum)
{
    std::string promoCode;
    std::cout << "Введите промокод или 'нет' для пропуска: ";
    Getline(promoCode);

    if (promoCode == "Далой")
    {
        std::cout << "\nПромокод применен!\n";
        std::cout << "Далой Израиль!\n";
        Sleep(2000);
        ApplyDiscount(totalSum, 10.0, "промокод 'Далой' (10%)");
        return true;
    }
    else if (promoCode != "нет")
    {
        std::cout << "Неверный промокод!\n";
        Sleep(1500);
    }

    return false;
}

// Функция применения скидки
void ApplyDiscount(double& totalSum, double discountPercent, const std::string& discountName)
{
    double discountAmount = totalSum * (discountPercent / 100.0);
    double newTotal = totalSum - discountAmount;

    std::cout << "\n????????????????????????????????????????\n";
    std::cout << "ПРИМЕНЕНА СКИДКА: " << discountName << "\n";
    std::cout << "Сумма скидки: " << discountAmount << " руб.\n";
    std::cout << "Старая сумма: " << totalSum << " руб.\n";
    std::cout << "Новая сумма: " << newTotal << " руб.\n";
    std::cout << "????????????????????????????????????????\n\n";
    Sleep(3000);

    totalSum = newTotal;
}

void Selling()
{
    std::string chooseId, chooseCount, chooseMoney, choose;
    unsigned int id = 0, count = 0, index = -1;
    double money = 0.0, totalSum = 0.0;
    bool isFirst = false;
    checkSize = 0;

    while (true)
    {
        ShowStorage();

        std::cout << "\nВведите ID товара для покупки или \"exit\" для завершения покупок: ";
        Getline(chooseId);
        if (chooseId == "exit")
        {
            system("cls");
            if (isFirst == false)
            {
                std::cout << "Выход без покупок\n";
                Sleep(1500);
                system("cls");
                break;
            }

            PrintCheck(totalSum);

            // ПРИМЕНЕНИЕ ТОЛЬКО СКИДКИ ЗА ОБЪЕМ (промокод только при оплате)
            bool discountApplied = false;

            // Скидка за объем (применяется сразу)
            discountApplied = CheckVolumeDiscount(totalSum);

            // Вывод итоговой суммы после применения скидок
            if (discountApplied)
            {
                system("cls");
                std::cout << "ИТОГОВЫЙ ЧЕК СО СКИДКОЙ:\n";
                PrintCheck(totalSum);
            }

            std::cout << "\nПодтвердите покупку?\n1- Да\n2 - Добавить ещё товар\n3 - Отмена\nВвод: ";
            Getline(choose);
            if (choose == "1")
            {
                bool promoApplied = false; // Флаг для промокода
                while (true)
                {
                    system("cls");
                    std::cout << "Выберите способ оплаты\n1 - Наличными\n2 - Безнал\n3 - Ввести промокод\nВвод: ";
                    Getline(choose);
                    if (choose == "1")
                    {
                        std::cout << "Введите кол-во наличных: ";
                        Getline(chooseMoney);
                        if (IsNumber(chooseMoney, true))
                        {
                            money = std::stod(chooseMoney);
                            if (money < totalSum)
                            {
                                std::cout << "Недостаточно средств!\n";
                                Sleep(1500);
                                continue;
                            }
                            else if (money - totalSum > cash)
                            {
                                std::cout << "Нет возможности дать сдачи. Повторите попытку!\n";
                                Sleep(1500);
                                continue;
                            }
                            else
                            {
                                std::cout << "Ваши: " << money << "\n";
                                Sleep(400);
                                std::cout << "Оплата прошла успешно. Сдача: " << money - totalSum << " рублей\n";
                                Sleep(2000);
                                cash += totalSum;
                                cash -= money - totalSum;
                                cashIncome += totalSum;
                                salesArr[currentId - 1] += totalSum;
                                system("cls");
                                break;
                            }
                        }
                    }
                    else if (choose == "2")
                    {
                        std::cout << "Приложить карту\n\n";
                        Sleep(1000);
                        if (rand() % 10 <= 2)
                        {
                            for (size_t i = 0; i < 5; i++)
                            {
                                std::cout << i + 1 << "\t";
                                Sleep(500);
                            }
                            std::cout << "\nСоединение не установлено. Повторите попытку\n";
                            Sleep(1500);
                        }
                        else
                        {
                            for (size_t i = 0; i < 5; i++)
                            {
                                std::cout << i + 1 << "\t";
                                Sleep(500);
                            }
                            std::cout << "\nОплата прошла успешно\n\nСпасибо за покупку!";
                            bankIncome += totalSum;
                            salesArr[currentId - 1] += totalSum;
                            Sleep(1500);
                            break;
                        }
                    }
                    else if (choose == "3")  // Ввод промокода при оплате
                    {
                        if (!promoApplied)
                        {
                            if (ApplyPromoCodeDiscount(totalSum))
                            {
                                promoApplied = true;
                                system("cls");
                                std::cout << "Обновленная сумма к оплате: " << totalSum << " руб.\n";
                                continue; // Вернуться к выбору оплаты
                            }
                        }
                        else
                        {
                            std::cout << "Промокод уже применен!\n";
                            Sleep(1500);
                        }
                    }
                    else if (choose == "Iman")
                    {
                        std::cout << "Иман оплатил вам чек. Всего доброго";
                        Sleep(1500);
                        system("cls");
                        break;
                    }
                    else
                    {
                        Err();
                    }
                }

                StorageReturner();
                system("cls");
                break;
            }
            else if (choose == "2")
            {
                continue;
            }
            else if (choose == "3")
            {
                std::cout << "Отмена покупки!\n";
                StorageReturner();
                Sleep(1500);
                system("cls");
                return;
            }
            else
            {
                Err();
                continue;
            }
        }

        if (IsNumber(chooseId, false))
        {
            id = std::stoi(chooseId) - 1;
            if (id >= storageSize)
            {
                std::cout << "Ошибка ID\n";
                Sleep(1500);
                continue;
            }
        }
        else
        {
            continue;
        }

        std::cout << "\nВведите кол-во товара или \"exit\" для выбора другого товара: ";
        Getline(chooseCount);
        if (chooseCount == "exit")
        {
            std::cout << "Отмена покупки товара: " << nameArr[id] << "\n\n";
            Sleep(1500);
            continue;
        }

        if (IsNumber(chooseCount, false))
        {
            count = std::stoi(chooseCount);
            if (count < 1 || count > countArr[id])
            {
                std::cout << "Ошибка кол-ва! Максимум: " << countArr[id] << "\n\n";
                Sleep(1500);
                continue;
            }
        }
        else
        {
            continue;
        }

        CheckArrPushback();
        if (isFirst == false)
        {
            isFirst = true;
        }
        index++;
        idArrCheck[index] = idArr[id];
        nameArrCheck[index] = nameArr[id];
        priceArrCheck[index] = priceArr[id];
        quantityArrCheck[index] = count;
        totalPriceArrCheck[index] = count * priceArr[id];
        countArr[id] -= count;
        totalSum += totalPriceArrCheck[index];

        std::cout << "\nТовар добавлен в чек\n\n";
        Sleep(1000);
    }
}

void CheckArrPushback()
{
    checkSize++;
    int* idArrCheckTemp = new int[checkSize];
    std::string* nameArrCheckTemp = new std::string[checkSize];
    unsigned int* quantityArrCheckTemp = new unsigned int[checkSize];
    double* priceArrCheckTemp = new double[checkSize];
    double* totalPriceArrCheckTemp = new double[checkSize];

    // Копируем старые данные
    for (size_t i = 0; i < checkSize - 1; i++)
    {
        idArrCheckTemp[i] = idArrCheck ? idArrCheck[i] : 0;
        nameArrCheckTemp[i] = nameArrCheck ? nameArrCheck[i] : "";
        quantityArrCheckTemp[i] = quantityArrCheck ? quantityArrCheck[i] : 0;
        priceArrCheckTemp[i] = priceArrCheck ? priceArrCheck[i] : 0.0;
        totalPriceArrCheckTemp[i] = totalPriceArrCheck ? totalPriceArrCheck[i] : 0.0;
    }

    // Удаляем старые массивы
    delete[] idArrCheck;
    delete[] nameArrCheck;
    delete[] quantityArrCheck;
    delete[] priceArrCheck;
    delete[] totalPriceArrCheck;

    // Присваиваем новые
    idArrCheck = idArrCheckTemp;
    nameArrCheck = nameArrCheckTemp;
    quantityArrCheck = quantityArrCheckTemp;
    priceArrCheck = priceArrCheckTemp;
    totalPriceArrCheck = totalPriceArrCheckTemp;
}

void PrintCheck(double& totalSum)
{
    std::cout << "????????????????????????????????????????\n";
    std::cout << "               ЧЕК ПРОДАЖИ\n";
    std::cout << "????????????????????????????????????????\n";
    std::cout << "№\t" << "ID\t" << std::left << std::setw(25) << "Название товара\t"
        << "Цена за ед.\t" << "Кол-во\t" << "Сумма\n";

    for (size_t i = 0; i < checkSize; i++)
    {
        std::cout << i + 1 << "\t" << idArrCheck[i] << "\t" << std::left << std::setw(25)
            << nameArrCheck[i] << "\t" << priceArrCheck[i] << "\t\t" << quantityArrCheck[i]
            << "\t" << totalPriceArrCheck[i] << "\n";
    }
    std::cout << "????????????????????????????????????????\n";
    std::cout << "ОБЩАЯ СУММА: " << totalSum << " руб.\n";
    std::cout << "????????????????????????????????????????\n";
}

void StorageReturner()
{
    for (size_t i = 0; i < checkSize; i++)
    {
        countArr[idArrCheck[i] - 1] += quantityArrCheck[i];
    }

    delete[] idArrCheck;
    delete[] nameArrCheck;
    delete[] quantityArrCheck;
    delete[] priceArrCheck;
    delete[] totalPriceArrCheck;

    idArrCheck = nullptr;
    nameArrCheck = nullptr;
    quantityArrCheck = nullptr;
    priceArrCheck = nullptr;
    totalPriceArrCheck = nullptr;

    checkSize = 0;
}


void Start()
{
    std::string choose;
    while (true)
    {
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
                        if (isStorageCreated == false)
                        {
                            CreateStorage();
                        }
                        system("cls");
                        ShowSuperAdminMenu();
                        break;
                    }
                    else if (choose == "2")
                    {
                        if (isStorageCreated == false)
                        {
                            storageSize = 0;
                            idArr = new unsigned int[0];
                            nameArr = new std::string[0];
                            countArr = new unsigned int[0];
                            priceArr = new double[0];
                            isStorageCreated = true;
                        }
                        system("cls");
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
                if (isStorageCreated == false)
                {
                    CreateStorage();
                }
                ShowAdminMenu();
            }
            else if (currentStatus == userStatus[2])
            {
                if (isStorageCreated == false)
                {
                    CreateStorage();
                }
                ShowUserMenu();
            }
        }
        else
        {
            system("cls");
            std::cout << "Итоговая прибыль за смену: " << cashIncome + bankIncome;
            std::cout << "\n\n\tЗавершение работы\n";
            Sleep(2000);
            system("cls");
            break;
        }
    }
}

bool Login()
{
    std::string login, pass;

    while (true)
    {
        std::cout << "\n\n\n\t\t\tМагазин военной техники 'Счастливая смерть'\n\n\n";
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
                currentId = userIdArr[i];
                return true;
            }

        }
        Err();
    }
}

bool Logout()
{
    std::string choose;
    while (true)
    {
        system("cls");
        std::cout << "Для подтверждения выхода из пользователя введите ваш пароль или \"exit\" для возврата в меню: ";
        Getline(choose);
        if (choose == "exit")
        {
            system("cls");
            return false;
        }
        else if (choose == passArr[currentId - 1] || choose == passArr[0])
        {
            system("cls");
            return true;
        }
        else
        {
            Err();
        }
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
        if (choose == "1" && storageSize > 0)
        {
            Selling();
        }
        else if (choose == "2" && storageSize > 0)
        {
            ShowStorage();
        }
        else if (choose == "3" && storageSize > 0)
        {
            AddStorageItem();
        }
        else if (choose == "4" && storageSize > 0)
        {
            RemovesStorageItem();
        }
        else if (choose == "5" && storageSize > 0)
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
            ShowIncome();
        }
        else if (choose == "0")
        {
            if (Logout() == true)
            {
                break;
            }
        }
        else
        {
            Err();
        }
    }
}

void ShowAdminMenu()
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
        if (choose == "1" && storageSize > 0)
        {
            Selling();
        }
        else if (choose == "2" && storageSize > 0)
        {
            ShowStorage();
        }
        else if (choose == "3" && storageSize > 0)
        {
            AddStorageItem();
        }
        else if (choose == "4" && storageSize > 0)
        {
            RemovesStorageItem();
        }
        else if (choose == "5" && storageSize > 0)
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
            ShowIncome();
        }
        else if (choose == "0")
        {
            if (Logout() == true)
            {
                break;
            }
        }
        else
        {
            Err();
        }
    }
}

void ShowUserMenu()
{
    std::string choose;
    while (true)
    {
        std::cout << "1 - Начать продажу\n";
        std::cout << "2 - Показать склад\n";
        std::cout << "3 - Отчёт о прибыли\n";
        std::cout << "0 - Закрыть смену\n";
        std::cout << "Ввод: ";
        Getline(choose);
        if (choose == "1" && storageSize > 0)
        {
            Selling();
        }
        else if (choose == "2" && storageSize > 0)
        {
            ShowStorage();
        }
        else if (choose == "3")
        {
            ShowIncome();
        }
        else if (choose == "0")
        {
            if (Logout() == true)
            {
                break;
            }
        }
        else
        {
            Err();
        }
    }
}

void ShowIncome()
{
    system("cls");
    std::cout << "Текущая прибыль\n\n";
    std::cout << "Наличный расчёт: " << cashIncome << "\n";
    std::cout << "Безналичный расчёт: " << bankIncome << "\n";
    std::cout << "Итого: " << bankIncome + cashIncome << "\n\n";
    std::cout << "Сумма ваших продаж: " << salesArr[currentId - 1] << "\n\n";

    system("pause");
    system("cls");
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

void SetPassSymbols()
{
    for (char i = '!'; i <= '&'; i++)
    {
        passSymbols.insert(i);
    }
    for (char i = '('; i <= '+'; i++)
    {
        passSymbols.insert(i);
    }
    for (char i = '.'; i <= '~'; i++)
    {
        passSymbols.insert(i);
    }
    isPassSetCreated = true;
}

bool CheckPass(const std::string& str)
{
    if (str.size() < 4 || str.size() > 30)
    {
        std::cout << "Ошибка длины пароля\n";
        Sleep(1500);
        return false;
    }

    int numCount = 0, symCount = 0;

    std::unordered_set<char> specialPassSym{ '!', '@', '#', '$', '%', '^', '&', '*',
        '(', ')', '-', '_', '=', '+', '/', '?', '|', '\\', '\"', '\'', ',', '.',
        '<', '>', '~', '`', ':', '{','}', '[',']', };

    for (char sym : str)
    {
        if (!passSymbols.count(sym))
        {
            std::cout << "Некорректный пароль\n";
            Sleep(1500);
            return false;
        }

        if (std::isdigit(sym))
        {
            numCount++;
        }
        if (specialPassSym.count(sym))
        {
            symCount++;
        }
    }

    if (numCount > 1 && symCount > 2)
    {
        return true;
    }
    else
    {
        std::cout << "Минимум 2 цифры и 3 символа\n";
        return false;
    }

}

bool CheckLogin(const std::string& str)
{
    if (str.size() < 5 || str.size() >= 20)
    {
        std::cout << "Недопустимая длина логина. От 5 до 20\n";
        Sleep(1500);
        return false;
    }

    for (char sym : str)
    {
        if (!specialSymbols.count(sym))
        {
            std::cout << "Некорректные символы в логине!\n\n";
            Sleep(1500);
            return false;
        }
    }

    for (size_t i = 0; i < userSize; i++)
    {
        if (str == loginArr[i])
        {
            std::cout << "Имя уже занято\n\n";
            Sleep(1500);
            return false;
        }
    }

    return true;
}

void ChangeAccounts()
{
    std::string choose;
    if (isSetCreated == false)
    {
        SetSpecialSymbols();
    }
    if (isPassSetCreated == false)
    {
        SetPassSymbols();
    }
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
            AddNewUsers();
        }
        else if (choose == "2" && userSize > 1)
        {
            ShowUsers();
        }
        else if (choose == "3" && userSize > 1)
        {
            ChangePass();
        }
        else if (choose == "4" && userSize > 1)
        {
            DeleteUser();
        }
        else if (choose == "0")
        {
            if (userSize < 1)
            {
                std::cout << "Нет доступных пользователей\n";
            }
            system("cls");
            break;
        }
        else
        {
            Err();
        }
    }
}

void ShowUsers(int mode)
{
    if (mode == 0)
    {
        system("cls");
        std::cout << "№\t" << std::left << std::setw(12) << "Логин\t\t" << "  Пароль\t\t\t" << "Роль\n";
        for (size_t i = 1; i < userSize; i++)
        {
            std::cout << i << "\t" << std::left << std::setw(8) << loginArr[i] << "\t\t" << passArr[i]
                << "\t\t\t" << statusArr[i] << "\n";
        }
        system("pause");
        system("cls");
    }
    else if (mode == 1)
    {
        system("cls");
        std::cout << "№\t" << std::left << std::setw(12) << "Логин\t\t" << "  Пароль\t\t\t" << "Роль\n";
        for (size_t i = 0; i < userSize; i++)
        {
            std::cout << i << "\t" << std::left << std::setw(8) << loginArr[i] << "\t\t" << passArr[i]
                << "\t\t\t" << statusArr[i] << "\n";
        }
        system("pause");
        system("cls");
    }
}

void AddNewUsers()
{
    std::string newLogin, newPass, newRole, choose;
    bool exit = true;
    while (true)
    {
        while (true)
        {
            system("cls");
            std::cout << "Введите логин нового пользователя или \"exit\" для выхода: ";
            Getline(newLogin);
            if (newLogin == "exit")
            {
                std::cout << "Отмена добавления нового пользователя!\n";
                Sleep(1500);
                exit = false;
                break;
            }
            if (CheckLogin(newLogin))
            {
                break;
            }
            else
            {
                std::cout << "Допустимые символы: a-z, A-Z, 0-9\n\n";
                Sleep(1500);
            }
        }

        while (exit)
        {
            system("cls");
            std::cout << "Введите пароль нового пользователя или \"exit\" для выхода: ";
            Getline(newPass);
            if (newPass == "exit")
            {
                std::cout << "Отмена добавления нового пользователя!\n";
                Sleep(1500);
                exit = false;
                break;
            }
            if (CheckPass(newPass))
            {
                break;
            }
            else
            {
                std::cout << "Допустимые символы: a-z, A-Z, 0-9 + символы\n\n";
                Sleep(1500);
            }
        }

        while (exit)
        {
            system("cls");
            std::cout << "Выберите роль для нового пользователя или \"exit\" для выхода: ";
            std::cout << "\n1 - Администратор\n2 - Сотрудник\nВвод: ";
            Getline(choose);
            if (choose == "exit")
            {
                std::cout << "Отмена добавления нового пользователя!\n";
                Sleep(1500);
                exit = false;
                break;
            }
            if (choose == "1")
            {
                newRole = userStatus[1];
                break;
            }
            else if (choose == "2")
            {
                newRole = userStatus[2];
                break;
            }
            else
            {
                Err();
            }
        }

        while (exit)
        {
            system("cls");
            std::cout << "Пользователь: " << newLogin << "\n";
            std::cout << "Пароль: " << newPass << "\n";
            std::cout << "Роль: " << newRole << "\n\n";

            std::cout << "Подтвердить?\n1 - Да\n2 - Нет\nВвод: ";
            Getline(choose);
            if (choose == "1")
            {
                userSize++;
                if (newRole == userStatus[2])
                {
                    staffCount++;
                }
                std::string* loginArrTemp = new std::string[userSize];
                std::string* passArrTemp = new std::string[userSize];
                std::string* statusArrTemp = new std::string[userSize];
                double* salesArrTemp = new double[userSize];
                unsigned int* userIdArrTemp = new unsigned int[userSize];

                for (size_t i = 0; i < userSize - 1; i++)
                {
                    loginArrTemp[i] = loginArr[i];
                    passArrTemp[i] = passArr[i];
                    statusArrTemp[i] = statusArr[i];
                    salesArrTemp[i] = salesArr[i];
                    userIdArrTemp[i] = userIdArr[i];
                }

                loginArrTemp[userSize - 1] = newLogin;
                passArrTemp[userSize - 1] = newPass;
                statusArrTemp[userSize - 1] = newRole;
                salesArrTemp[userSize - 1] = 0.0;
                userIdArrTemp[userSize - 1] = userSize;

                delete[] loginArr;
                delete[] passArr;
                delete[] statusArr;
                delete[] salesArr;
                delete[] userIdArr;

                loginArr = loginArrTemp;
                passArr = passArrTemp;
                statusArr = statusArrTemp;
                salesArr = salesArrTemp;
                userIdArr = userIdArrTemp;

                std::cout << "Идёт подготовка... ";
                Sleep(2000);
                std::cout << "Пользователь успешно добавлен!\n\n";
                exit = false;
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

        if (exit == false)
        {
            break;
        }
    }
}

void ChangePass()
{
    std::string newPass1, newPass2, choose;
    int userNumber = 0;
    int isAdmin = 0;
    while (true)
    {
        if (currentStatus == userStatus[0])
        {
            ShowUsers(1);
            isAdmin = 0;
        }
        else
        {
            ShowUsers();
            isAdmin = 1;
        }

        std::cout << "Выберите номер пользователя или \"exit\" для выхода: ";
        Getline(choose);
        if (choose == "exit")
        {
            std::cout << "Отмена изменения пароля!\n";
            Sleep(1500);
            break;
        }
        else if (IsNumber(choose, false))
        {
            userNumber = std::stoi(choose);
            if (userNumber < isAdmin || userNumber >= static_cast<int>(userSize))
            {
                std::cout << "Пользователя с таким номером не существует!\n";
                Sleep(1500);
                continue;
            }

            if (currentStatus == userStatus[1] && statusArr[userNumber] == userStatus[1])
            {
                std::cout << "Нельзя менять пароли Администраторам\n";
                Sleep(1500);
                continue;
            }

            system("cls");
            std::cout << "Введите новый пароль для пользователя " << loginArr[userNumber] << ": ";
            Getline(newPass1);
            std::cout << "Подтвердите пароль для пользователя " << loginArr[userNumber] << ": ";
            Getline(newPass2);
            if (CheckPass(newPass1) && CheckPass(newPass2) && newPass1 == newPass2)
            {
                passArr[userNumber] = newPass1;
                std::cout << "Успешно\n";
                Sleep(1500);
                break;
            }
            else
            {
                std::cout << "Повторите попытку\n";
                Sleep(1500);
            }
        }
        else
        {
            Err();
        }
    }
}

void DeleteUser()
{
    std::string chooseNumber, choose, checkPass;
    int userNumber = 0;
    int isAdmin = 0;
    while (true)
    {
        if (currentStatus == userStatus[0])
        {
            if (userSize < 2)
            {
                std::cout << "Нет доступных пользователей для удаления\n";
                Sleep(1500);
                return;
            }
        }
        else if (currentStatus == userStatus[1])
        {
            if (staffCount < 1)
            {
                std::cout << "Нет доступных пользователей для удаления\n";
                Sleep(1500);
                return;
            }
        }
        ShowUsers();
        isAdmin = 1;

        std::cout << "Выберите номер пользователя для удаления или \"exit\" для выхода: ";
        Getline(choose);
        if (choose == "exit")
        {
            std::cout << "Отмена удаления пользователя!\n";
            Sleep(1500);
            break;
        }
        else if (IsNumber(choose, false))
        {
            userNumber = std::stoi(choose);
            if (userNumber < isAdmin || userNumber >= static_cast<int>(userSize))
            {
                std::cout << "Пользователя с таким номером не существует!\n";
                Sleep(1500);
                continue;
            }

            system("cls");

            if (currentStatus == userStatus[1] && statusArr[userNumber] != userStatus[2])
            {
                std::cout << "Нельзя удалять администратора\n";
                Sleep(1500);
                continue;
            }

            std::cout << "Удаление пользователя: " << loginArr[userNumber] << "\n\n";
            std::cout << "Для подтверждения введите пароль супер администратора или \"exit\" для выхода: ";
            Getline(checkPass);
            if (checkPass == "exit")
            {
                std::cout << "Отмена удаления пользователя: " << loginArr[userNumber] << "\n\n";
                Sleep(1500);
                break;
            }
            else if (checkPass == passArr[0])
            {
                userSize--;
                if (statusArr[userNumber] == userStatus[2])
                {
                    staffCount--;
                }
                std::string* loginArrTemp = new std::string[userSize];
                std::string* passArrTemp = new std::string[userSize];
                std::string* statusArrTemp = new std::string[userSize];
                double* salesArrTemp = new double[userSize];
                unsigned int* userIdArrTemp = new unsigned int[userSize];

                for (size_t i = 0, c = 0; i < userSize; i++, c++)
                {
                    if (static_cast<int>(c) == userNumber)
                    {
                        c++;
                    }
                    loginArrTemp[i] = loginArr[c];
                    passArrTemp[i] = passArr[c];
                    statusArrTemp[i] = statusArr[c];
                    salesArrTemp[i] = salesArr[c];
                    userIdArrTemp[i] = userIdArr[c];
                }

                delete[] loginArr;
                delete[] passArr;
                delete[] statusArr;
                delete[] salesArr;
                delete[] userIdArr;

                loginArr = loginArrTemp;
                passArr = passArrTemp;
                statusArr = statusArrTemp;
                salesArr = salesArrTemp;
                userIdArr = userIdArrTemp;

                std::cout << "Идёт подготовка... ";
                Sleep(2000);
                std::cout << "Пользователь успешно удалён!\n\n";
                Sleep(1500);
                break;
            }
            else
            {
                std::cout << "Некорректный пароль\n";
                Sleep(1500);
            }
        }
        else
        {
            Err();
        }
    }
}

void CreateStorage()
{
    const unsigned int staticSize = 20;

    unsigned int id[staticSize]{ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20 };
    std::string name[staticSize]
    {
        "Разведывательный дрон Bayraktar TB3",
        "Ударный дрон Hermes-900X",
        "Многоцелевой Истребитель F-35X",
        "Тактический БПЛА MQ-9 Reaper Pro",
        "Тяжёлый танк M1A3 Abrams",
        "Самоходная артиллерия PzH 2000 Elite",
        "Ракетная система HIMARS-X",
        "Тактический ракетный комплекс ATACMS",
        "Штурмовой вертолёт AH-64E Guardian",
        "Космический спутник-разведчик",
        "Десантный корабль поддержки LPD-X",
        "Противокорабельный комплекс Harpoon",
        "Авианосец CVN-XX",
        "Баллистический комплекс TBM-Alpha",
        "Станция электронной войны EW-9000",
        "Беспилотный флот SkyFleet Pack",
        "Тактическая подводная лодка SSK-Pro",
        "Платформа ПВО S-400 Lite",
        "Мобильный ракетный комплекс MRLS Titan",
        "Гиперзвуковая пусковая установка MkI"
    };
    double price[staticSize]{
        25000000.00, 18000000.00, 120000000.00, 35000000.00, 95000000.00,
        15000000.00, 40000000.00, 80000000.00, 60000000.00, 500000000.00,
        1000000000.00, 45000000.00, 20000000000.00, 250000000.00, 30000000.00,
        120000000.00, 70000000.00, 90000000.00, 60000000.00, 1500000000.00
    };
    unsigned int count[staticSize]{ 5,8,2,6,3,4,6,2,5,1,1,10,1,1,3,2,2,2,4,1 };

    if (isStorageCreated)
    {
        delete[] idArr;
        delete[] nameArr;
        delete[] countArr;
        delete[] priceArr;
    }

    storageSize = staticSize;
    idArr = new unsigned int[storageSize];
    nameArr = new std::string[storageSize];
    countArr = new unsigned int[storageSize];
    priceArr = new double[storageSize];
    isStorageCreated = true;

    for (size_t i = 0; i < storageSize; i++)
    {
        idArr[i] = id[i];
        nameArr[i] = name[i];
        countArr[i] = count[i];
        priceArr[i] = price[i];
    }
}

void ShowStorage(int mode)
{
    if (mode == 0)
    {
        system("cls");
        std::cout << "ID\t" << std::left << std::setw(25) << "Название товара\t\t"
            << "Цена\t\t" << "Кол-во\n";
        for (size_t i = 0; i < storageSize; i++)
        {
            std::cout << idArr[i] << "\t" << std::left << std::setw(25) << nameArr[i] << "\t"
                << priceArr[i] << "\t\t" << countArr[i] << "\n";
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
                << countArr[i] << "\n";
        }
    }
    else if (mode == 2)
    {
        std::cout << "ID\t" << std::left << std::setw(25) << "Название товара\t\t"
            << "Цена\n";
        for (size_t i = 0; i < storageSize; i++)
        {
            std::cout << idArr[i] << "\t" << std::left << std::setw(25) << nameArr[i] << "\t"
                << priceArr[i] << "\n";
        }
    }
    else if (mode == 3)
    {
        std::cout << "ID\t" << std::left << std::setw(25) << "Название товара\t" << "\n";
        for (size_t i = 0; i < storageSize; i++)
        {
            std::cout << idArr[i] << "\t" << std::left << std::setw(25) << nameArr[i] << "\n";
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

        if (IsNumber(chooseId, false) && IsNumber(chooseCount, false))
        {
            id = std::stoi(chooseId) - 1;
            count = std::stoi(chooseCount);

            if (id >= storageSize || count < 0 || count > maxItemSize)
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
                    std::cout << "Отмена пополнения!\n";
                    Sleep(1500);
                }
                else
                {
                    Err();
                }
            }
        }
        else
        {
            Err();
        }
    }
}

void RemovesStorageItem()
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

        if (IsNumber(chooseId, false) && IsNumber(chooseCount, false))
        {
            id = std::stoi(chooseId) - 1;
            count = std::stoi(chooseCount);

            if (id >= storageSize || count < 0 || count > countArr[id])
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
                    std::cout << "Отмена списания!\n";
                    Sleep(1500);
                }
                else
                {
                    Err();
                }
            }
        }
        else
        {
            Err();
        }
    }
}

void ChangePrice()
{
    std::string chooseId, choosePrice, choose;
    unsigned int id = 0;
    double newPrice;

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
        std::cout << "Введите новую цену для товара: ";
        Getline(choosePrice);

        if (IsNumber(chooseId, false) && IsNumber(choosePrice, true))
        {
            id = std::stoi(chooseId) - 1;
            newPrice = std::stod(choosePrice);

            if (id >= storageSize || newPrice < 0 || newPrice > 999999999999)
            {
                std::cout << "Некорректный id или цена\nМаксимальная цена - " << 999999999999 << "\n\n";
                Sleep(1500);
            }
            else
            {
                std::cout << "\n" << std::left << std::setw(25) << nameArr[id] << "\t"
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
                    std::cout << "Отмена изменения цены!\n";
                    Sleep(1500);
                }
                else
                {
                    Err();
                }
            }
        }
        else
        {
            Err();
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
        else if (choose == "2" && storageSize > 0)
        {
            ChangeName();
        }
        else if (choose == "3" && storageSize > 0)
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
    double price = 0.0;
    unsigned int count = 0;
    bool exit = true;

    while (true)
    {
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
                exit = false;
                break;
            }

            if (newName.size() <= 0 || newName.size() >= 60)
            {
                std::cout << "Ошибка. Максимальная длина названия 60 символов\n";
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
            std::cout << "\tДобавление нового товара!\n\nВведите \"exit\" для прекращения операции\n\n";
            std::cout << "Введите кол-во нового товара: ";
            Getline(newCount);

            if (newCount == "exit")
            {
                std::cout << "Операция добавления товара прервана!\n\n";
                Sleep(1500);
                exit = false;
                break;
            }

            if (IsNumber(newCount, false))
            {
                count = std::stoi(newCount);
                if (count > maxItemSize)
                {
                    std::cout << "Ошибка максимального размера товара. Не более " << maxItemSize << "ед.\n\n";
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
            system("cls");
            std::cout << "\tДобавление нового товара!\n\nВведите \"exit\" для прекращения операции\n\n";
            std::cout << "Введите цену нового товара: ";
            Getline(newPrice);

            if (newPrice == "exit")
            {
                std::cout << "Операция добавления цены нового товара прервана!\n\n";
                Sleep(1500);
                exit = false;
                break;
            }

            if (IsNumber(newPrice, true))
            {
                price = std::stod(newPrice);
                if (price > 999999999999)
                {
                    std::cout << "Ошибка максимальной цены. Не более " << 999999999999 << "ед.\n\n";
                    Sleep(1500);
                }
                else
                {
                    break;
                }
            }
        }

        system("cls");

        if (exit)
        {
            std::cout << "Новый товар: " << newName << "\nКол-во: " << count << "\nЦена: " << price << "\n\n";
            std::cout << "Подтвердить?\n1 - Да\n2 - Нет\nВвод: ";
            Getline(choose);

            if (choose == "1")
            {
                storageSize++;
                unsigned int* idArrTemp = new unsigned int[storageSize];
                std::string* nameArrTemp = new std::string[storageSize];
                unsigned int* countArrTemp = new unsigned int[storageSize];
                double* priceArrTemp = new double[storageSize];

                for (size_t i = 0; i < storageSize - 1; i++)
                {
                    idArrTemp[i] = idArr[i];
                    nameArrTemp[i] = nameArr[i];
                    countArrTemp[i] = countArr[i];
                    priceArrTemp[i] = priceArr[i];
                }

                idArrTemp[storageSize - 1] = storageSize;
                nameArrTemp[storageSize - 1] = newName;
                priceArrTemp[storageSize - 1] = price;
                countArrTemp[storageSize - 1] = count;

                delete[] idArr;
                delete[] nameArr;
                delete[] countArr;
                delete[] priceArr;

                idArr = idArrTemp;
                nameArr = nameArrTemp;
                countArr = countArrTemp;
                priceArr = priceArrTemp;

                std::cout << "Идёт подготовка... ";
                Sleep(2000);
                std::cout << "Товар успешно добавлен!\n\n";
                Sleep(1500);
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
        std::cout << "\nВведите ID товара или \"exit\" для выхода: ";
        Getline(chooseId);

        if (chooseId == "exit")
        {
            std::cout << "Операция смены названия прервана!\n\n";
            Sleep(1500);
            break;
        }

        std::cout << "Введите название нового товара: ";
        Getline(newName);

        if (newName.size() <= 0 || newName.size() >= 60 || newName == "exit")
        {
            std::cout << "Ошибка имени. Максимальная длина названия 60 символов\n";
            Sleep(1500);
        }
        else if (IsNumber(chooseId, false))
        {
            id = std::stoi(chooseId) - 1;

            if (id >= storageSize)
            {
                std::cout << "Ошибка ID!\n";
                Sleep(1500);
            }
            else
            {
                std::cout << "\n" << std::left << std::setw(25)
                    << nameArr[id] << " ---> " << newName << "\n\n";
                std::cout << "Подтвердить?\n1 - Да\n2 - Нет\nВвод: ";
                Getline(choose);
                if (choose == "1")
                {
                    nameArr[id] = newName;
                    std::cout << "Изменение названия успешно завершено\n";
                    Sleep(1500);
                    break;
                }
                else if (choose == "2")
                {
                    std::cout << "Отмена\n";
                    Sleep(1500);

                }
                else
                {
                    Err();
                }
            }
        }
    }
}

void DeleteItem()
{
    std::string chooseId, choose;
    unsigned int id = 0;

    while (true)
    {
        system("cls");
        ShowStorage(3);
        std::cout << "\nВведите ID товара для удаления или \"exit\" для выхода: ";
        Getline(chooseId);
        if (chooseId == "exit")
        {
            std::cout << "Операция удаления товара прервана!\n\n";
            Sleep(1500);
            break;
        }

        if (IsNumber(chooseId, false))
        {
            id = std::stoi(chooseId) - 1;
            if (id >= storageSize)
            {
                std::cout << "Ошибка ID\n";
                Sleep(1500);
            }
            else
            {
                std::cout << "Удаляемый товар: " << nameArr[id] << "\n\n";
                std::cout << "Подтвердить?\n1 - Да\n2 - Нет\nВвод: ";
                Getline(choose);

                if (choose == "1")
                {
                    storageSize--;
                    unsigned int* idArrTemp = new unsigned int[storageSize];
                    std::string* nameArrTemp = new std::string[storageSize];
                    unsigned int* countArrTemp = new unsigned int[storageSize];
                    double* priceArrTemp = new double[storageSize];

                    for (size_t i = 0, c = 0; i < storageSize; i++, c++)
                    {
                        if (id == c)
                        {
                            c++;
                        }
                        idArrTemp[i] = i + 1;
                        nameArrTemp[i] = nameArr[c];
                        countArrTemp[i] = countArr[c];
                        priceArrTemp[i] = priceArr[c];
                    }

                    delete[] idArr;
                    delete[] nameArr;
                    delete[] countArr;
                    delete[] priceArr;

                    idArr = idArrTemp;
                    nameArr = nameArrTemp;
                    countArr = countArrTemp;
                    priceArr = priceArrTemp;

                    std::cout << "Идёт подготовка... ";
                    Sleep(2000);
                    std::cout << "Товар успешно удалён!\n\n";
                    Sleep(1500);
                    break;
                }
                else if (choose == "2")
                {
                    std::cout << "Отмена удаления товара!\n";
                    Sleep(1500);
                }
                else
                {
                    Err();
                }
            }
        }
    }
}

bool IsNumber(const std::string& str, bool allowDecimal)
{
    if (str.empty() || str.size() > 20)
    {
        std::cout << "Некорректный ввод\n";
        std::cout << "Ошибка размера числа.\n\n";
        Sleep(1500);
        return false;
    }

    bool hasDecimalPoint = false;
    for (size_t i = 0; i < str.size(); i++)
    {
        if (str[i] == '.' && allowDecimal)
        {
            if (hasDecimalPoint || i == 0 || i == str.size() - 1)
            {
                std::cout << "Некорректный ввод\n";
                std::cout << "Введённые данные не являются числом\n\n";
                Sleep(1500);
                return false;
            }
            hasDecimalPoint = true;
        }
        else if (!std::isdigit(str[i]))
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
    std::cout << "Некорректный ввод\n";
    Sleep(1500);
    system("cls");
}

template<typename ArrType>
void FillArr(ArrType* dynamicArr, ArrType* staticArr, size_t arraySize)
{
    for (size_t i = 0; i < arraySize; i++)
    {
        dynamicArr[i] = staticArr[i];
    }
}