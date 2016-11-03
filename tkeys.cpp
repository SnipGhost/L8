//-----------------------------------------------------------------------------
// File: tkeys.cpp
//-----------------------------------------------------------------------------
// Реализация методов структуры TKEYS
//-----------------------------------------------------------------------------
#include "tkeys.h"
//-----------------------------------------------------------------------------
// Конструирование объекта и генерация ключей
//-----------------------------------------------------------------------------
TKEYS::TKEYS(istream &input)
{
	if (DEBUG) cout << "Генерация ключей .. [ -- ]";
	size = STEPALLOC;
	const int len = 256;
	char str[len];
	char *token, *next_token;
	char delims[] = " .,!?/\\{}[]<>()'\":;|_#@*";
	key = new int[size];
	int w = 0;
	while (input.getline(str, len))
	{
		token = strtok_s(str, delims, &next_token);
		while (token != NULL)
		{
			if (w >= size) 
			{
				if (DEBUG) cout << "\nВыделение дополнительной памяти .. ";
				int *buf = new int[size+STEPALLOC];
				for (int i = 0; i < size; ++i) buf[i] = key[i];
				delete [] key;
				key = buf;
				buf = NULL;
				size += STEPALLOC;
				if (DEBUG) cout << "[ OK ]";
			}
			key[w] = 0;
			for (unsigned k = 0; k < strlen(token); ++k)
				key[w] += (256+token[k]);
			key[w] %= 256;
			w++;
			token = strtok_s(NULL, delims, &next_token);
		}
	}
	size = w;
	if (DEBUG) cout << "\nГенерация ключей .. [ OK ]\n";
}
//-----------------------------------------------------------------------------
// Очистка памяти
//-----------------------------------------------------------------------------
TKEYS::~TKEYS()
{
	if (DEBUG) cout << "Разрушение объекта .. ";
	delete [] key;
	if (DEBUG) cout << "[ OK ]" << endl;
}
//-----------------------------------------------------------------------------
// Печать ключей на экран
//-----------------------------------------------------------------------------
void TKEYS::print() 
{
	cout << "Ключей сгенерированно: " << size << endl;
	int k, a = 0;
	for (k = 0; k < size; ++k) 
		if (TERMINAL_COL > (size-k)*4) break;
	int width = (TERMINAL_COL-1) / (size-k);
	k = size - k;
	for (int h = 0; h < TERMINAL_COL-1; ++h) cout << "-";
	cout << endl;
	while (a < size) 
	{
		int ak = (a+k > size) ? size : (a+k);
		for (int i = a; i < ak; ++i) cout << setw(width) << key[i];
		cout << endl;
		a += k;
	}
	for (int h = 0; h < TERMINAL_COL-1; ++h) cout << "-";
	cout << endl;
}
//-----------------------------------------------------------------------------
//                                                      By SnipGhost 03.11.2016
//-----------------------------------------------------------------------------