#include "win.h"

HICON hIcon1;
HICON hIcon2;

HBITMAP g_bmp;
HBITMAP g_bmpMask;

HWND hwndEdit1;
HWND hwndEdit2;
HWND hwndButton1;
HWND hwndButton2;
HWND hwndQuitButton;

CKeygen *oWin95oem;
CKeygen *oWin95cd;
CKeygen *oOffice95;
CKeygen *oOffice97;

/* "Program obslugi komunikatow" */
LRESULT CALLBACK WndProc(HWND hWindow, UINT iMessage, 
						 WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
    PAINTSTRUCT ps;
	HFONT hFont, holdFont;
	DWORD color;

	HDC hdcScr;
	HDC hdcBmp;
	HBITMAP hbmOld;
	HDC hdcMask;
	HBITMAP hbmOldMask;

	static wchar_t *credits1 = L"-= {  Office9x Keygen by Narkoza  } =-";
	static wchar_t *credits2 = L"(C) 2022";
	static wchar_t *dash = L"-";
	static wchar_t *KEY = L"YOUR OFFICE KEY: ";


	switch(iMessage)
	{
		case WM_INITDIALOG:

			hIcon1 = (HICON)LoadImageW(GetModuleHandleW(NULL), MAKEINTRESOURCEW(IDI_ICON), IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE);
			SendMessage(hWindow, WM_SETICON, ICON_BIG, (LPARAM)hIcon1);

		break;

		case WM_PAINT:

			hdcScr = GetDC(NULL);
			hdcBmp = CreateCompatibleDC(hdcScr);
			hbmOld = (HBITMAP)SelectObject(hdcBmp, g_bmp);
			hdcMask = CreateCompatibleDC(hdcScr);
			hbmOldMask = (HBITMAP) SelectObject(hdcMask, g_bmpMask );

			hdc = BeginPaint(hWindow, &ps); // POCZATEK RYSOWANIA
				
				/* TEKST */
					color = GetSysColor(COLOR_BTNFACE);
					SetBkColor(hdc, color);

					hFont = CreateFontW(15, 0, 0, 0, FW_MEDIUM, 0, 0, 0, 0,
                                0, 0, 0, 0, L"MS Sans Serif");
					holdFont = (HFONT)SelectObject(hdc, hFont);

					TextOutW(hdc, 144, 20,  credits1,  lstrlenW(credits1));
					TextOutW(hdc, 209, 40,  credits2,  lstrlenW(credits2));
					TextOutW(hdc, 77, 115,  KEY,  lstrlenW(KEY));

					hFont = CreateFontW(23, 0, 0, 0, FW_MEDIUM, 0, 0, 0, 0,
                                0, 0, 0, 0, L"MS Sans Serif");
					holdFont = (HFONT)SelectObject(hdc, hFont);
					TextOutW(hdc, 222, 111,  dash,  lstrlenW(dash));

				/* BITMAPA */
					
					BitBlt(hdc, 35, 10, 64, 64, hdcMask, 0, 0, SRCAND);
					BitBlt(hdc, 35, 10, 184, 184, hdcBmp, 0, 0, SRCPAINT);
					
					
					SelectObject(hdcMask, hbmOldMask);
					DeleteDC(hdcMask);

					SelectObject(hdcBmp, hbmOld);
					DeleteDC(hdcBmp);
					ReleaseDC(NULL, hdcScr); 


			EndPaint(hWindow, &ps); // KONIEC RYSOWANIA
        break;

		case WM_CREATE:

			oOffice95 = (CObjectFactory::GetType(TOffice95));
			oOffice97 = (CObjectFactory::GetType(TOffice97));

			hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT); // Czcionka
			
			/* Pole 1 */
			hwndEdit1 = CreateWindowEx(WS_EX_CLIENTEDGE, "Edit", "",
						WS_VISIBLE | WS_CHILD,
						187, 112, 30, 20,
						hWindow, NULL, NULL, NULL
			);

				SendMessage(hwndEdit1, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0)); // Ustawia czcionke w polu tekstowym
				SendMessage(hwndEdit1, EM_SETREADONLY, TRUE, TRUE); // Usuwa mozliwosc edycji w polu tekstowym

			/* Pole 2 */
			hwndEdit2 = CreateWindowEx(WS_EX_CLIENTEDGE, "Edit", "",
						WS_VISIBLE | WS_CHILD,
						234, 112, 48, 20,
						hWindow, (HMENU) NULL, NULL, NULL
			);

				SendMessage(hwndEdit2, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
				SendMessage(hwndEdit2, EM_SETREADONLY, TRUE, TRUE);


			/* RAMKI */
			CreateWindow(TEXT("BUTTON"), TEXT(""),
						WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
						17, 75, 330, 84,
						hWindow, (HMENU) NULL, NULL, NULL
			);

			CreateWindow(TEXT("BUTTON"), TEXT(""),
						WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
						120, 50, 227, 10,
						hWindow, (HMENU) NULL, NULL, NULL
			);

			/* PRZYCISK 1 */
			hwndButton1 = CreateWindow(TEXT("BUTTON"), TEXT("Office95"),
				WS_CHILD | WS_VISIBLE,
				12, 170, 100, 30,
				hWindow, (HMENU) ID_OFFICE95, NULL, NULL
			);
				SendMessage(hwndButton1, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0)); // Ustaw czcionke


			/* PRZYCISK 2 */
			hwndButton2 = CreateWindow(TEXT("BUTTON"), TEXT("Office97"),
				WS_CHILD | WS_VISIBLE,
				132, 170, 100, 30,
				hWindow, (HMENU) ID_OFFICE97, NULL, NULL
			);
				SendMessage(hwndButton2, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0)); // Ustaw czcionke

			/* PRZYCISK 3 */
			hwndQuitButton = CreateWindow(TEXT("BUTTON"), TEXT("Quit"),
				WS_CHILD | WS_VISIBLE,
				252, 170, 100, 30,
				hWindow, (HMENU) ID_QUIT, NULL, NULL
			);
				SendMessage(hwndQuitButton, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0)); // Ustaw czcionke

			/* BITMAPA */ 

				g_bmp = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_CLIPPY));
					if(g_bmp == NULL)
						MessageBox(hWindow, "Failed to load image!", "Error", MB_OK | MB_ICONEXCLAMATION);

				g_bmpMask = createImageMask(g_bmp, RGB(0, 0, 0));
					if(g_bmpMask == NULL)
						MessageBox(hWindow, "Could not create mask!", "Error", MB_OK | MB_ICONEXCLAMATION);
		break;

		case WM_COMMAND:

			if(LOWORD(wParam) == ID_OFFICE95)
			{
				oOffice95->Generate();
				SetWindowText(hwndEdit1, oOffice95->buffer4);
				SetWindowText(hwndEdit2, oOffice95->buffer7);
			}

			if(LOWORD(wParam) == ID_OFFICE97)
			{
				oOffice97->Generate();
				SetWindowText(hwndEdit1, oOffice97->buffer4);
				SetWindowText(hwndEdit2, oOffice97->buffer7);
			}
			

			if(LOWORD(wParam) == ID_QUIT)
			{
				delete oOffice95;
				delete oOffice97;
				exit(0);
			}
		break;

		case WM_CLOSE:
			delete oOffice95;
			delete oOffice97;
			exit(0);
        break;

		default:
			return DefWindowProc(hWindow, iMessage, wParam, lParam);
	}

	return 0;
}
