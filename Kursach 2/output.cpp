#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include "functions.h"
#include "structures.h"
#include <vector>
#include <sstream>
#include <tchar.h>

using namespace std;

TCHAR* header()
{

	TCHAR str[MAX_PATH];
	swprintf_s(
		str,
		TEXT("%10s|%10s|%20s|%20s|%20s|%12s"),
		L"����",
		L"�������",
		L"������ ��������",
		L"������ ��������",
		L"������ ��������",
		L"�� ��������");
	return str;
}

TCHAR* entryToString(Entry entry)
{
	TCHAR str[MAX_PATH];
	swprintf_s(
		str,
		TEXT("%10s|%10i|%20s|%20s|%20s|%12s"),
		entry.key,
		entry.age,
		entry.firstAnimal,
		entry.secondAnimal,
		entry.thirdAnimal,
		(entry.toDelete ? L"��" : L"���"));
	return str;
}

TCHAR* animalToString(Animal animal)
{
	TCHAR str[120];
	swprintf_s(
		str,
		L"%i ��� ����������� \"%s\"",
		animal.amount,
		animal.animal);
	return str;
}

void readEntry(HANDLE hFile, TCHAR* key, Entry& entry)
{
	if (findKey(hFile, key)) {
		SetFilePointer(hFile, -(int)sizeof(Entry), NULL, FILE_CURRENT);
		ReadFile(hFile, (char*)(&entry), (int)sizeof(Entry), NULL, NULL);
	}
}

void readAll(HANDLE hFile, vector<Entry>* entriesList)
{
	int position = 0;
	Entry buffer = { 0 };
	DWORD size = GetFileSize(hFile, NULL);
	DWORD pointer;

	while (true) {
		pointer = SetFilePointer(hFile, position * sizeof(Entry), NULL, FILE_BEGIN);

		if (pointer == size) {
			break;
		}

		entriesList->push_back(buffer);
		ReadFile(hFile, (char*)(&(entriesList->at(entriesList->size() - 1))), sizeof(Entry), NULL, NULL);
		position++;
	}

	if (entriesList->size() == 0) {
		cout << "� ����� �����!" << endl;
	}
}