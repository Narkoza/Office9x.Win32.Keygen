#include "bitmap.h"

HBITMAP createImageMask( HBITMAP bitmapHandle, const COLORREF transparencyColor) 
{
    
    BITMAP bitmap;

    
    HDC bitmapGraphicsDeviceContext = CreateCompatibleDC(NULL);
    HDC bitmapMaskGraphicsDeviceContext = CreateCompatibleDC(NULL);

    
    HBITMAP bitmapMaskHandle;

    
    GetObject(bitmapHandle, sizeof(BITMAP), &bitmap);
    bitmapMaskHandle = CreateBitmap(bitmap.bmWidth, bitmap.bmHeight, 1, 1, NULL);

    
    SelectObject(bitmapGraphicsDeviceContext, bitmapHandle);
    SelectObject(bitmapMaskGraphicsDeviceContext, bitmapMaskHandle);

    
    SetBkColor(bitmapGraphicsDeviceContext, transparencyColor);

    
    BitBlt(bitmapMaskGraphicsDeviceContext, 0, 0, bitmap.bmWidth, bitmap.bmHeight, bitmapGraphicsDeviceContext, 0, 0, SRCCOPY);
    BitBlt(bitmapGraphicsDeviceContext, 0, 0, bitmap.bmWidth, bitmap.bmHeight, bitmapMaskGraphicsDeviceContext, 0, 0, SRCINVERT);

    
    DeleteDC(bitmapGraphicsDeviceContext);
    DeleteDC(bitmapMaskGraphicsDeviceContext);

    
    return bitmapMaskHandle;
}