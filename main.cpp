#include "keygen.h"
#include "bitmap.h"
#include "win.h"
#include "resource.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst,
				   LPSTR lpCmdLine, int nShowCmd)
{
	srand(GetTickCount());

	/* "Klasa Okna" */
	WNDCLASS	kWndClass;

	/* Wlasciwosci wyswietlania */
	kWndClass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	kWndClass.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON) );
	kWndClass.hbrBackground = GetSysColorBrush(COLOR_3DFACE);

	/* Wlasciwosci systemowe */
	kWndClass.hInstance		= hInstance;
	kWndClass.lpfnWndProc	= WndProc;
	kWndClass.lpszClassName = "WindowsApp";

	/* Wlasciwosci dodatkowe */
	kWndClass.lpszMenuName = NULL;

	kWndClass.cbClsExtra = NULL;
	kWndClass.cbWndExtra = NULL;
	kWndClass.style = NULL;

	/* Proba rejestracji klasy */
	if(!RegisterClass(&kWndClass))
		return -1;

	/* "Okno" */
	HWND hWindow;

	/* Tworzenie okna */
	hWindow = CreateWindowEx(0, "WindowsApp", "Office9x KeyGen", 
							WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | 
							WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 370, 240, 
							HWND_DESKTOP, NULL, hInstance, NULL);
	
	ShowWindow(hWindow, nShowCmd);

	/* Petla komunikatow w czasie rzeczywistym */
	MSG kMessage;

	/* Wejscie do petli czasu rzeczywistego */
	while(1)
	{
		/* Zapytanie czy nie ma w kolejce oczekujacych komunikatow */
		if(PeekMessage(&kMessage, hWindow, 0, 0, PM_REMOVE))
		{
			/* Jezeli jest to WM_QUIT, opusc petle */
			if(WM_QUIT == kMessage.message)
			{
				break;
			}
			/* Normalne przetwarzanie komunikatow */
			else
			{
				TranslateMessage(&kMessage);
				DispatchMessage(&kMessage);
			}
		}
		/* Brak komunikatow, wykonuj nasz kod */
		else
		{
			/* Nic nie rob... */
		}
	}

	return 0L;
}

