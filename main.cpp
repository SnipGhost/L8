//-----------------------------------------------------------------------------
// File: main.cpp
//-----------------------------------------------------------------------------
#include <direct.h>
#include "tkeys.h"
#include "functions.h"
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
int main() 
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// НЕ РАБОТАЕТ ДЛЯ РЕЖИМА ОТЛАДКИ
	char curdir[1024];                // Временные переменные
	_getcwd(curdir, sizeof(curdir));  // Получаем текущую директорию
	string path = curdir;             // Копируем в наш путь
	path += "\\Data\\";               // Добавляем имя директории
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	TKEYS *keys = NULL;
	string in = "", out = "", res = "";
	int button;
	while (true) 
	{
		system("chcp 1251 > nul");
		system("cls");
		cout << "----------= Шифрование файлов =----------" << endl;
		cout << " 1. Сгенерировать ключи из файла \n";
		cout << " 2. Распечатать массив ключей \n";
		cout << " 3. Зашифровать/расшифровать файл \n";
		cout << " 4. Протестировать \n";
		cout << " 5. Вывести статистику по символу \n";
		cout << " 6. Выход \n";
		cout << "-----------------------------------------" << endl;
		cin >> button;
		switch (button)
		{
			case 1: // Генерация ключей из указанного файла
			{
				if (keys != NULL) delete keys;
				if (DEFAULT) in = "key.txt";
				else {
					cout << "Введите имя файла: ";
					cin >> in;
				}
				ifstream fkey;
				fkey.open(path + in);
				if (fkey.fail()) {
					cout << "Ошибка чтения файла\n";
				} else {
					keys = new TKEYS(fkey);
					fkey.close();
				}
				system("pause");
				break;
			}
			case 2: // Вывод массива ключей на экран
			{
				if (keys != NULL) keys->print();
				else cout << "Ключи еще не сгенерированы!\n";
				system("pause");
				break;
			}
			case 3: // Шифрование/дешифровка указанного файла
			{
				if (keys != NULL) {
					if (DEFAULT) {
						in = "in.txt";
						out = "out.txt";
						res = "res.txt";
					} else {
						cout << "Введите имя исходного файла: ";
						cin >> in;
						cout << "Введите имя выходного файла: ";
						cin >> out;
						cout << "Введите имя проверочного файла: ";
						cin >> res;
					}
					encryptFile(path + in, path + out, keys);
					encryptFile(path + out, path + res, keys);
				} else {
					cout << "Ключи еще не сгенерированы!\n";
				}
				system("pause");
				break;
			}
			case 4: // Тестирование
			{
				cout << "Еще не готово\n";
				system("pause");
				break;
			}
			case 5: // Вывод статистики по указанному символу
			{
				if (DEFAULT) {
					in = "in.txt";
					out = "out.txt";
				} else {
					cout << "Введите имя исходного файла: ";
					cin >> in;
					cout << "Введите имя выходного файла: ";
					cin >> out;
				}
				char c;
				if (DEFAULT) {
					c = 'b';
				} else {
					cout << "Введите символ ASCII: ";
					cin.ignore(7777, '\n');
					cin.get(c);
				}
				printStat(path + in, path + out, c);
				system("pause");
				break;
			}
			case 6: // Выход и завершение работы
			{
				if (keys != NULL) delete keys;
				exit(0);
				break;
			}
			default:
				cout << "Нет такой операции\n";
				system("pause");
		}
	}
	return 0;
}
//-----------------------------------------------------------------------------
//                                                      By SnipGhost 03.11.2016
//-----------------------------------------------------------------------------