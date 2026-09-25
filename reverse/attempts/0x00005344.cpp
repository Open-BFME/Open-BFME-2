// ?compareNoCase@WideCharCompare@@QBEHPBG0H@Z
// partial score=0.85 date=2026-09-25
// Probe V4: register fnptr, direct params.
#include <string.h>

extern int (__cdecl *g_wideFold)(int);

struct WideCharCompare
{
	char m_unused;

	int compareNoCase(const wchar_t *a, const wchar_t *b, int len) const;
};

int WideCharCompare::compareNoCase(const wchar_t *a, const wchar_t *b, int len) const
{
	register int (__cdecl *fold)(int) = g_wideFold;
	while (len > 0) {
		wchar_t fa = (wchar_t)fold(*a);
		wchar_t fb = (wchar_t)fold(*b);
		if (fa != fb)
			return (int)(unsigned short)fa - (int)(unsigned short)fb;
		++a;
		++b;
		--len;
	}
	return 0;
}
