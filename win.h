#ifndef _WIN_H_
#define _WIN_H_

#include <windows.h>
#include "keygen.h"
#include "bitmap.h"
#include "resource.h"

#define ID_OFFICE95 1
#define ID_OFFICE97 2
#define ID_QUIT 3

/* Prototyp programu obslugi komunikatow */
LRESULT CALLBACK WndProc(HWND hWindow, UINT iMessage, 
						 WPARAM wParam, LPARAM lParam);

#endif