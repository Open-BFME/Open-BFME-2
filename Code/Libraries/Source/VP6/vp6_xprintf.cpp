// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001c4c90.md plus retail only.
// No decoder source was consulted.
// _vp6_xprintf retail 0x001C4C90..0x001C4EF1 (610 bytes) cdecl variadic
// (decoder instance / pixel offset into the post-process buffer at 0x25C /
// format) returning the text length or 0. Debug text overlay: formats into a
// 256-byte buffer through _vsnprintf (IAT 0x00BBA5E0) then draws it with GDI
// into a 1-bit bitmap of 8 x length by 8 pixels (8-pixel variable-pitch swiss
// font / text colour 1 / background 0 / transparent / BLACKNESS clear /
// clipped ExtTextOutA) and sets every lit pixel (GetPixel at x and 7 - y) to
// 255 in the luma plane stepping by the Y stride at 0x1B8. Retail selects the
// bitmap a second time where the spec says the font is selected and keeps
// that result as the font restore handle; any GDI failure skips to the
// cleanup ladder. Callers 0x001BB5F0 and 0x001BB6C0 (vp6_showinfo pair).
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

struct Vp6XprintfRect
{
	int left;
	int top;
	int right;
	int bottom;
};

extern "C" {
__declspec(dllimport) void *__stdcall CreateCompatibleDC(void *);
__declspec(dllimport) void *__stdcall CreateBitmap(int, int, unsigned int, unsigned int, const void *);
__declspec(dllimport) void *__stdcall SelectObject(void *, void *);
__declspec(dllimport) void *__stdcall CreateFontA(int, int, int, int, int, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, const char *);
__declspec(dllimport) unsigned long __stdcall SetTextColor(void *, unsigned long);
__declspec(dllimport) unsigned long __stdcall SetBkColor(void *, unsigned long);
__declspec(dllimport) int __stdcall SetBkMode(void *, int);
__declspec(dllimport) int __stdcall BitBlt(void *, int, int, int, int, void *, int, int, unsigned long);
__declspec(dllimport) int __stdcall ExtTextOutA(void *, int, int, unsigned int, const Vp6XprintfRect *, const char *, unsigned int, const int *);
__declspec(dllimport) unsigned long __stdcall GetPixel(void *, int, int);
__declspec(dllimport) int __stdcall DeleteObject(void *);
__declspec(dllimport) int __stdcall DeleteDC(void *);
}

struct Vp6XprintfInstance
{
	unsigned char pad000[0x1B8];
	int yStride;
	unsigned char pad1BC[0x25C - 0x1BC];
	unsigned char *postProcBuffer;
};

extern "C" int vp6_xprintf(Vp6XprintfInstance *pbi, int offset, const char *format, ...)
{
	int stride = pbi->yStride;
	char buffer[256] = "";
	unsigned char *dest = pbi->postProcBuffer + offset;
	int length = 0;
	va_list args;
	Vp6XprintfRect rect;
	void *dc;
	void *bitmap;
	void *oldBitmap;
	void *font;
	void *oldFont;
	int x, y;
	va_start(args, format);
	_vsnprintf(buffer, sizeof(buffer), format, args);
	va_end(args);
	rect.left = 0;
	rect.top = 0;
	rect.right = strlen(buffer) * 8;
	rect.bottom = 8;
	dc = CreateCompatibleDC(0);
	if (dc == 0)
		goto done;
	bitmap = CreateBitmap(rect.right, rect.bottom, 1, 1, 0);
	if (bitmap == 0)
		goto done;
	oldBitmap = SelectObject(dc, bitmap);
	if (oldBitmap == 0)
		goto freeBitmap;
	font = CreateFontA(8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x22, "");
	if (font == 0)
		goto restoreBitmap;
	oldFont = SelectObject(dc, bitmap);
	if (oldFont == 0)
		goto restoreBitmap;
	SelectObject(dc, font);
	SetTextColor(dc, 1);
	SetBkColor(dc, 0);
	SetBkMode(dc, 1);
	if (!BitBlt(dc, rect.left, rect.top, rect.right, rect.bottom, dc, rect.left, rect.top, 0x42))
		goto restoreBitmap;
	if (!ExtTextOutA(dc, 0, 0, 4, &rect, buffer, strlen(buffer), 0))
		goto restoreBitmap;
	for (y = rect.top; y < rect.bottom; y++) {
		for (x = rect.left; x < rect.right; x++) {
			if (GetPixel(dc, x, rect.bottom - y - 1))
				dest[x] = 255;
		}
		dest += stride;
	}
	length = strlen(buffer);
restoreBitmap:
	SelectObject(dc, oldBitmap);
freeBitmap:
	DeleteObject(bitmap);
done:
	if (font) {
		if (oldFont)
			SelectObject(dc, oldFont);
		DeleteObject(font);
	}
	if (dc)
		DeleteDC(dc);
	return length;
}
