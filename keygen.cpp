#include "keygen.h"

int irand(int min, int max) 
{
    return ((double)rand() / ((double)RAND_MAX + 1.0)) * (max - min + 1) + min;
}

CKeygen::CKeygen()
{
	y_amount = 8;
	z_amount = 8;
}

CKeygen::~CKeygen(){}
void CKeygen::Generate(void){}

COffice95::COffice95(){}
COffice95::~COffice95(){}

COffice97::COffice97(){}
COffice97::~COffice97(){}

void COffice95::Generate(void)
{
	unsigned short x[3];
	unsigned short y[7];

	y[0] = 0;
	unsigned short y_amount = 8;


	/* 3 LOSOWE CYFRY */

	for(unsigned short i=0; i<3; i++)
	{
		x[i] = irand(0,9);
	}

	sprintf(buffer4, "%d%d%d", x[0],x[1],x[2]);


	/* SUMA CYFR PODZIELNA PRZEZ 7 */

	while((y_amount%7) != 0)
    {
        y_amount = 0;

        for(unsigned short i=0; i<7; i++)
        {
            y[i] = irand(0,9);
            y_amount += y[i];
        }
    }

	sprintf(buffer7, "%d%d%d%d%d%d%d", y[0],y[1],y[2],y[3],y[4],y[5],y[6]);
    
}

void COffice97::Generate(void)
{
	unsigned short x;
	unsigned short y;
	unsigned short fourth;
	unsigned short random_number;
	unsigned short z[7];

	z[0] = 0;
	unsigned short z_amount = 8;

	/* 3 LOSOWE CYFRY */

	x = irand(0, 99);
	y = irand(0, 9);

	/* 4 CYFRA */

	random_number = irand(1,2);
	
	if(y>=9)
		fourth = y+1;
	else
		fourth = y+random_number;

	switch(fourth)
	{
		case 10:
			fourth = 0;
			break;
		default:
			break;
	}

	if(x<10)
	{
		sprintf(buffer4, "%d%d%d%d", 0,x,y,fourth);
	}
	else
	{
		sprintf(buffer4, "%d%d%d", x,y,fourth);
	}

	/* SUMA CYFR PODZIELNA PRZEZ 7 */

	while((z_amount%7) != 0)
    {
        z_amount = 0;

        for(unsigned short i=0; i<7; i++)
        {
            z[i] = irand(0,9);
            z_amount += z[i];
        }
    }

	sprintf(buffer7, "%d%d%d%d%d%d%d", z[0],z[1],z[2],z[3],z[4],z[5],z[6]);
}

CKeygen *CObjectFactory::GetType(unsigned short Type)
{
	switch(Type)
	{
		case TOffice95:
			return new COffice95();
		break;

		case TOffice97:
			return new COffice97();
		break;

		default:
		break;
	}

	return NULL;
}