#ifndef _BITMAP_H_
#define _BITMAP_H_

#include <windows.h>

HBITMAP createImageMask( HBITMAP bitmapHandle, const COLORREF transparencyColor);

#endif