/* Shity code to spam desktop with an image - by zapan */

#include <windows.h>
#include <stdio.h>

int main (int argc, char *argv[]) {

	HWND hwndDesktop;
	HDC hdcDesktop, hdcCompatibleDesktop;
	DWORD dwWidth, dwHeight, i;
	HBITMAP hbitmapImg;
	HINSTANCE hInstance;
	BITMAP bitmap;
	RECT rectDesktop;

	/* Get misc. values */
	hdcDesktop  = GetDC (NULL); /* Handle of desktop screen */
	hInstance  = GetModuleHandle (NULL);
	dwHeight   = GetDeviceCaps (hdcDesktop, VERTRES);
	dwWidth    = GetDeviceCaps (hdcDesktop, HORZRES);
	hbitmapImg = LoadBitmap (hInstance, "IMGpwned");
	GetObject (hbitmapImg, sizeof (BITMAP), &bitmap);
	hwndDesktop = GetDesktopWindow ();
	GetWindowRect (hwndDesktop, &rectDesktop);

	if (NULL == hbitmapImg) 
		exit (EXIT_FAILURE);

	hdcCompatibleDesktop = CreateCompatibleDC (hdcDesktop);
	SelectObject (hdcCompatibleDesktop, hbitmapImg);

	/* Stretch mad image to the desktop and blit it forever <3 */
	while (TRUE) {
		StretchBlt (hdcDesktop, 0, 0, 
		            rectDesktop.right, rectDesktop.bottom,
			    hdcCompatibleDesktop, 0, 0, 
			    bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
		Sleep (1);
	}

	/* Release... but never reached */
	/*
	DeleteDC (hdcCompatibleDesktop);
	ReleaseDC (NULL, hdcDesktop);
	DeleteObject (hbitmapImg);

	exit (EXIT_FAILURE);
	*/
}
