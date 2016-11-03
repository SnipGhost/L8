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
	// �� �������� ��� ������ �������
	char curdir[1024];                // ��������� ����������
	_getcwd(curdir, sizeof(curdir));  // �������� ������� ����������
	string path = curdir;             // �������� � ��� ����
	path += "\\Data\\";               // ��������� ��� ����������
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	TKEYS *keys = NULL;
	string in = "", out = "", res = "";
	int button;
	while (true) 
	{
		system("chcp 1251 > nul");
		system("cls");
		cout << "----------= ���������� ������ =----------" << endl;
		cout << " 1. ������������� ����� �� ����� \n";
		cout << " 2. ����������� ������ ������ \n";
		cout << " 3. �����������/������������ ���� \n";
		cout << " 4. �������������� \n";
		cout << " 5. ������� ���������� �� ������� \n";
		cout << " 6. ����� \n";
		cout << "-----------------------------------------" << endl;
		cin >> button;
		switch (button)
		{
			case 1: // ��������� ������ �� ���������� �����
			{
				if (keys != NULL) delete keys;
				if (DEFAULT) in = "key.txt";
				else {
					cout << "������� ��� �����: ";
					cin >> in;
				}
				ifstream fkey;
				fkey.open(path + in);
				if (fkey.fail()) {
					cout << "������ ������ �����\n";
				} else {
					keys = new TKEYS(fkey);
				}
				system("pause");
				break;
			}
			case 2: // ����� ������� ������ �� �����
			{
				if (keys != NULL) keys->print();
				else cout << "����� ��� �� �������������!\n";
				system("pause");
				break;
			}
			case 3: // ����������/���������� ���������� �����
			{
				if (keys != NULL) {
					if (DEFAULT) {
						in = "in.txt";
						out = "out.txt";
						res = "res.txt";
					} else {
						cout << "������� ��� ��������� �����: ";
						cin >> in;
						cout << "������� ��� ��������� �����: ";
						cin >> out;
						cout << "������� ��� ������������ �����: ";
						cin >> res;
					}
					encryptFile(path + in, path + out, keys);
					encryptFile(path + out, path + res, keys);
				} else {
					cout << "����� ��� �� �������������!\n";
				}
				system("pause");
				break;
			}
			case 4: // ������������
			{
				cout << "��� �� ������\n";
				system("pause");
				break;
			}
			case 5: // ����� ���������� �� ���������� �������
			{
				if (DEFAULT) {
					in = "in.txt";
					out = "out.txt";
				} else {
					cout << "������� ��� ��������� �����: ";
					cin >> in;
					cout << "������� ��� ��������� �����: ";
					cin >> out;
				}
				char c;
				if (DEFAULT) {
					c = 'b';
				} else {
					cout << "������� ������ ASCII: ";
					cin.get(c);
				}
				printStat(path + in, path + out, c);
				system("pause");
				break;
			}
			case 6: // ����� � ���������� ������
			{
				if (keys != NULL) delete keys;
				exit(0);
				break;
			}
			default:
				cout << "��� ����� ��������\n";
				system("pause");
		}
	}
	return 0;
}
//-----------------------------------------------------------------------------
//                                                      By SnipGhost 03.11.2016
//-----------------------------------------------------------------------------