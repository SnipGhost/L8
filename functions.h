//-----------------------------------------------------------------------------
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
//-----------------------------------------------------------------------------
#include "tkeys.h"
//-----------------------------------------------------------------------------
// ����������/���������� �����
int encryptFile(string inputfile, string outputfile, const TKEYS *keys);
//-----------------------------------------------------------------------------
// ������ ���������� �� �������
int printStat(string sourcefile, string resultfile, char c);
//-----------------------------------------------------------------------------
#endif /* FUNCTIONS_H */                             // By SnipGhost 03.11.2016
//-----------------------------------------------------------------------------