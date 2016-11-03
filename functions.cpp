//-----------------------------------------------------------------------------
#include "functions.h"
//-----------------------------------------------------------------------------
// Шифрование/дешифровка файла
//-----------------------------------------------------------------------------
int encryptFile(string inputfile, string outputfile, const TKEYS *keys)
{
	if (DEBUG) cout << "Открытие файлов .. ";
	int len, pos = 0;
	FILE *fs, *fr;
	errno_t err;
	err = fopen_s(&fs, inputfile.c_str(), "rb");
	if (err != 0) { cout << "Ошибка чтения файла\n"; return -1; }
	fopen_s(&fr, outputfile.c_str(), "wb");
	fseek(fs, 0, SEEK_END);
	len = ftell(fs);
	rewind(fs); 
	if (DEBUG) cout << "[ OK ]\n" << "Бинарное шифрование .. ";
	unsigned char c1, c2;
	fread(&c1, sizeof(char), 1, fs);
	while (pos < len)
	{
		pos++;
		c2 = c1 ^ (keys->key[pos % keys->size]);
		fwrite(&c2, sizeof(char), 1, fr);
		fread(&c1, sizeof(char), 1, fs);
	}
	if (DEBUG) cout << "[ OK ]\n" << "Закрытие файлов .. ";
	fclose(fs);
	fclose(fr);
	if (DEBUG) cout << "[ OK ]\n";
	return 1;
}
//-----------------------------------------------------------------------------
// Печать статистики по символу
//-----------------------------------------------------------------------------
int printStat(string sourcefile, string resultfile, char c)
{
	if (DEBUG) cout << "Открытие файлов .. ";
	FILE *fs, *fr;
	errno_t err;
	err = fopen_s(&fs, sourcefile.c_str(), "rb");
	if (err != 0) { cout << "Ошибка чтения файла\n"; return -1; }
	err = fopen_s(&fr, resultfile.c_str(), "rb");
	if (err != 0) { cout << "Ошибка чтения файла\n"; return -1; }
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	fseek(fs, 0, SEEK_END);
	int len = ftell(fs);
	rewind(fs); 
	if (DEBUG) cout << "[ OK ]\n" << "Считывание данных .. ";
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	int stat[16][16] = { 0 };
	unsigned char c1, c2;
	int pos = 0, max = 0;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Посимвольно читаем коды из бинарников, записываем стату
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	fread(&c1, sizeof(char), 1, fs);
	fread(&c2, sizeof(char), 1, fr);
	while (pos < len)
	{
		pos++;
		if (c1 == c) 
		{
			int r = ++stat[c2 % 16][int(c2 / 16)];
			if (r > max) max = r;
		}
		fread(&c1, sizeof(char), 1, fs);
		fread(&c2, sizeof(char), 1, fr);
	} 
	if (DEBUG) cout << "[ OK ]\n" << "Формирование таблицы .. [ -- ]\n";
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Печать шапки таблицы
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	system("chcp 866 > nul");
	len = 0;
	if (max == 0) len = 1;
	while (max > 0) { len++; max /= 10; }
	cout << char(218);
	for (int h = 0; h < len; ++h) cout << char(196);
	cout << char(194);
	for (int k = 0; k < 15; ++k)
	{
		for (int h = 0; h < len; ++h) cout << char(196);
		cout << char(194);
	}
	for (int h = 0; h < len; ++h) cout << char(196);
	cout << char(191) << endl;
	cout << char(179) << setw(len) << ' ' << char(179);
	for (int k = 0; k < 16; ++k) 
		cout << hex << setw(len) << k << char(179);
	cout << endl;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Печать строк 0-F в каждой по 0-F элементов
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	for (int i = 0; i < 16; ++i)
	{
		cout << char(195);
		for (int k = 0; k < 16; ++k)
		{
			for (int h = 0; h < len; ++h) cout << char(196);
			cout << char(197);
		}
		for (int h = 0; h < len; ++h) cout << char(196);
		cout << char(180) << endl;
		cout << char(179) << hex << setw(len) << i;
		for (int j = 0; j < 16; ++j)
		{
			cout << dec << char(179);
			cout << setw(len);
			if (stat[i][j] == 0) cout << char('.');
			else cout << stat[i][j];
		}
		cout << char(179) << endl;
	}
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Завершаем таблицу
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	cout << char(192);
	for (int h = 0; h < len; ++h) cout << char(196);
	for (int k = 0; k < 16; ++k) 
	{
		cout << char(193);
		for (int h = 0; h < len; ++h) cout << char(196);
	}
	cout << char(217) << endl;
	system("chcp 1251 > nul");
	if (DEBUG) cout << "Формирование таблицы .. [ OK ]\n" << "Закрытие файлов .. ";
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	fclose(fs);
	fclose(fr);
	if (DEBUG) cout << "[ OK ]\n";
	return 1;
}
//-----------------------------------------------------------------------------
//                                                      By SnipGhost 03.11.2016
//-----------------------------------------------------------------------------