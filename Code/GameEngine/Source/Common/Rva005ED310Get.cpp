// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// ?Rva005ED310Get@@YA?AVUnicodeString@@H@Z, retail 0x005ED310, 96 bytes.
// Formats int via 0x007C9260 when >=0 else empty; returns UnicodeString by value.
// Evidence: same format string and callees as Rva0043A568Get (format 0x006CB5D0 copy 0x00037050 release 0x00036E70); callers 0x005ED708 NumRegions 0x005ED76A NumUnits; prev 0x005ED2DE next 0x005ED5F3 same dir.
typedef unsigned short WideChar;

#include "unicode_string.h"


#define RankFmt ((const WideChar *)L"%d")

UnicodeString __cdecl Rva005ED310Get(int val)
{
	UnicodeString s;
	if (val >= 0)
		s.format(RankFmt, val);
	return s;
}
