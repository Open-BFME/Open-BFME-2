// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// GetTickCount-based seconds counter. The indirect call reaches the IAT slot at
// 0x00BBA294, which reverse/symbols.csv pins as kernel32.dll!GetTickCount, and
// the reciprocal multiply (0x10624DD3, shr edx,6) is the unsigned divide-by-1000
// idiom. Free function; identity is this image's address.

extern "C" __declspec(dllimport) unsigned int __stdcall GetTickCount(void);

// ?Rva006C1790@@YAIXZ @ 0x006C1790 (21B)
unsigned int Rva006C1790(void)
{
	return GetTickCount() / 1000;
}

// ?Rva006C1FE0@@YGIPADHPAPAD@Z @ 0x006C1FE0 (45B)
// Trailing 16-bit length reader: the size lives in the last two bytes of the
// run, the body is that length plus the two-byte field, and the optional out
// pointer receives where the body starts. stdcall (ret 0xC). Address-derived.
unsigned int __stdcall Rva006C1FE0(char *base, int length, char **bodyOut)
{
	unsigned short bodySize = *reinterpret_cast<unsigned short *>(base + length - 2);

	if (bodyOut)
		*bodyOut = base + length - 2 - bodySize;

	return bodySize + 2;
}
