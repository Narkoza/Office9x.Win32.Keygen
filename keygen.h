#ifndef _KEYGEN_H_
#define _KEYGEN_H_

#include <iostream>
#include <time.h>
#include <windows.h>
#include "win.h"

int irand(int min, int max);

enum ObjectTypes
{
	TOffice95,
	TOffice97
}; 

class CKeygen
{
public:
	unsigned short y_amount;
	unsigned short z_amount;
	char buffer4[64];
	char buffer7[64];

	CKeygen();
	virtual ~CKeygen();

	virtual void Generate(void);
};

class COffice95 : public CKeygen
{
	unsigned short x[3];
	unsigned short y[7];

public:
	COffice95();
	virtual ~COffice95();

	virtual void Generate(void);
};

class COffice97 : public CKeygen
{
	unsigned short x;
	unsigned short y;
	unsigned short fourth;
	unsigned short random_number;
	unsigned short z[7];

public:
	COffice97();
	virtual ~COffice97();

	virtual void Generate(void);
};

class CObjectFactory
{
public:
	static CKeygen *GetType(unsigned short Type);
};

#endif
