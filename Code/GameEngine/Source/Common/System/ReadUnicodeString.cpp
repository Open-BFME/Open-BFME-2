// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?readUnicodeString@@YA?AVUnicodeString@@PAU_iobuf@@@Z @0x0037B648 194B.
// Ported from BFME 1 donor game/GameEngine/Source/Common/System/
// ReadUnicodeString.cpp at Open-BFME-1 6583b3c1ff (ZH GameText.cpp's file-scope
// reader); the donor recompiled /O1 places uniquely here with every
// non-relocation byte equal (tools/donor_sweep.py). Target facts: the IAT
// fgetwc import, the 2048-byte zero-filled wide buffer and the rowed
// StringBase<wchar> ctor 0x00037E30, copy 0x00037050 and release 0x00036E70.
// The name is carried from the donor; retail keeps no symbol for it.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;

#include "unicode_string.h"

#define EOF (-1)

struct _iobuf
{
};

extern "C" __declspec(dllimport) unsigned short __cdecl fgetwc(_iobuf *stream);

UnicodeString readUnicodeString(_iobuf *file)
{
	unsigned short str[1024] = L"";
	int index = 0;

	int c = fgetwc(file);
	if (c == EOF) {
		str[index] = 0;
	}
	str[index] = c;

	while (index < 1023 && str[index] != 0) {
		++index;
		int c = fgetwc(file);
		if (c == 0xffff) {
			str[index] = 0;
			break;
		}
		str[index] = c;
	}
	str[1023] = L'\0';

	UnicodeString retval(str);
	return retval;
}
