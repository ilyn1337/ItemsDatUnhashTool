#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdint>
#include <cstring>
#include <vector>
#include <stdint.h>
#include <string>
#include <fstream>
#include <utility>
#include <sstream>
#include <limits.h>
#pragma warning(disable:4996)
#ifndef _UNISTD_H
#define _UNISTD_H    1
#include <stdlib.h>
#include <io.h>
#include <getopt.h>
#include <process.h>
#include <direct.h>
#define srandom srand
#define random rand
#define R_OK    4    
#define W_OK    2  
#define F_OK    0 
#define access _access
#define dup2 _dup2
#define execve _execve
#define ftruncate _chsize
#define unlink _unlink
#define fileno _fileno
#define getcwd _getcwd
#define chdir _chdir
#define isatty _isatty
#define lseek _lseek
#ifdef _WIN64
#define ssize_t __int64
#else
#define ssize_t long
#endif
#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2
typedef __int16           int16_t;
typedef __int32           int32_t;
typedef __int64           int64_t;
typedef unsigned __int8   uint8_t;
typedef unsigned __int16  uint16_t;
typedef unsigned __int32  uint32_t;
typedef unsigned __int64  uint64_t;

#endif _UNISTD_H

using namespace std;

std::ifstream::pos_type filesize(const char* filename)
{
	std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
	return in.tellg();
}

uint32_t HashString(unsigned char* str, int len)
{
	if (!str) return 0;

	unsigned char* n = (unsigned char*)str;
	uint32_t acc = 0x55555555;

	if (len == 0)
	{
		while (*n)
			acc = (acc >> 27) + (acc << 5) + *n++;
	}
	else
	{
		for (int i = 0; i < len; i++)
		{
			acc = (acc >> 27) + (acc << 5) + *n++;
		}
	}
	return acc;

}

unsigned char* getA(string fileName, int* pSizeOut, bool bAddBasePath, bool bAutoDecompress)
{
	unsigned char* pData = NULL;
	FILE* fp = fopen(fileName.c_str(), "rb");
	if (!fp)
	{
		cout << "File not found" << endl;
		if (!fp) return NULL;
	}

	fseek(fp, 0, SEEK_END);
	*pSizeOut = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	pData = (unsigned char*)new unsigned char[((*pSizeOut) + 1)];
	if (!pData)
	{
		printf("Out of memory opening %s?", fileName.c_str());
		return 0;
	}
	pData[*pSizeOut] = 0;
	fread(pData, *pSizeOut, 1, fp);
	fclose(fp);

	return pData;
}

int main() {
	cout << "Created By ColdChip, Windows Optimization by noob" << endl;
	uint8_t* pData;
	int size = 0;
	const char filename[] = "items.dat";
	size = filesize(filename);
	pData = getA((string)filename, &size, false, false);

	printf("Hash found: %i\n", HashString((unsigned char*)pData, size));
	system("PAUSE");
}