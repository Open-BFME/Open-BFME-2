// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD
// ?Rva000B69EAGet@@YA?AVAsciiString@@ABV1@H@Z @0x000B69EA 125B free function returning AsciiString.
// Early return src when mode<0 else local copy plus switch 1/2 concat then copy out.
// Callees rowed 0x000365F0 copy plus 0x00005629 concat plus 0x00036410 release.
// Callers 0x000C2E3A twice prove signature. Prev 0x000B6971 Next 0x000B6A67 same dir.
#include "ascii_string.h"


AsciiString Rva000B69EAGet(const AsciiString &src, int mode)
{
	if (mode < 0)
		return src;
	AsciiString tmp(src);
	switch (mode) {
	case 1:
		((StringBase<char> *)&tmp)->concat("M");
		break;
	case 2:
		((StringBase<char> *)&tmp)->concat("L");
		break;
	}
	return tmp;
}
