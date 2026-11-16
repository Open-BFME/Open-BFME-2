// Rva0020E89C: canonical declarations for the members units call through private views of it;
// rowed 0x0020E89C reads the AsciiString at +0x38, rowed 0x0020E90F compares the int key at +0x12C,
// rowed 0x004FB600 and 0x003F7198 read the int at +0x13C; the remaining storage stays opaque.
#ifndef CANONICAL_RVA0020E89C_H
#define CANONICAL_RVA0020E89C_H

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

class UnicodeString;

class Rva0020E89C
{
public:
	UnicodeString rva0020E89C();
	UnicodeString rva003F15D1();

	char m_00[0x38];
	AsciiString m_38;
	char m_3C[0x12C - 0x3C];
	int m_12C;
	char m_130[0x13C - 0x130];
	int m_13C;
};

#endif // CANONICAL_RVA0020E89C_H
