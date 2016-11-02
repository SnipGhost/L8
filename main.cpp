//-----------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <string>
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
const string path = "”кажи свой путь!";
#define TERMINAL_COL 80
#define STEPALLOC 20
//-----------------------------------------------------------------------------
struct TKEYS
{
	int *key;
	unsigned size;
	TKEYS(istream &input);
	~TKEYS();
	void print();
};
//-----------------------------------------------------------------------------
void TKEYS::print()
{
	int k = TERMINAL_COL / 4;
	int a = 0;
	while (a < size)
	{
		int ak = (a+k > size) ? size : (a+k);
		for (int i = a; i < ak; ++i) cout << key[i] << " ";
		cout << endl;
		a += k;
	}
	
}
//-----------------------------------------------------------------------------
TKEYS::TKEYS(istream &input)
{
	size = STEPALLOC;
	const int len = 256;
	char str[len];
	char *token;
	char delims[] = " .,!?/\\{}[]<>()'\":;|_#@*";
	key = new int[size];
	int w = 0;
	while (input.getline(str, len))
	{
		token = strtok(str, delims);
		//cout << token << endl;
		while (token != NULL)
		{
			//cout << w << endl;
			if (w >= size)
			{
				int *buf = new int[size+STEPALLOC];
				for (unsigned i = 0; i < size; ++i) buf[i] = key[i];
				delete [] key;
				key = buf;
				buf = NULL;
				size += STEPALLOC;
			}
			key[w] = 0;
			for (unsigned k = 0; k < strlen(token); ++k)
				key[w] += (int)token[k];
			key[w] %= 256;
			w++;
			token = strtok(NULL, delims);
			//if (token != NULL) cout << token << endl << endl;
		}
	}
	size = w;
}
//-----------------------------------------------------------------------------
TKEYS::~TKEYS()
{
	delete [] key;
	cout << "Destruction complete" << endl;
}
//-----------------------------------------------------------------------------
void encrypt(istream &input, ostream &output, const TKEYS &keys)
{
	input.clear();
	input.seekg(0);
	string str;
	while (getline(input, str)) 
	{
		for (unsigned i = 0; i < str.length(); ++i)
			str[i] = (str[i] ^ (keys.key[i % keys.size]));
		output << str << endl;	
	}
}
//-----------------------------------------------------------------------------
void printStat(istream &source, istream &result, char c)
{
	source.clear();
	source.seekg(0);
	result.clear();
	result.seekg(0);
	string ss, sr;
	int stat[256];
	while (getline(source, ss) && getline(result,sr))
	{
		
	}
}
//-----------------------------------------------------------------------------
int main() 
{
	ifstream fin, fkey;
	ofstream fout;

	fin.open(path + "in.txt");
	fout.open(path + "out.txt");
	fkey.open(path + "key.txt");

	TKEYS k(fkey);
	k.print();

	encrypt(fin, fout, k);

	fin.close();
	fout.close();

	fin.open(path + "out.txt");
	fout.open(path + "res.txt");

	encrypt(fin, fout, k);

	return 0;
}
//-----------------------------------------------------------------------------
// By SnipGhost & Roman B.                                           02.11.2016
//-----------------------------------------------------------------------------