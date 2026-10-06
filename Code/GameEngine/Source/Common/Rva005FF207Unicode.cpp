// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?Rva005FF207Format@@YA?AVUnicodeString@@H@Z @ 0x005FF207 (96B).
// Conditional Unicode format into temp then return by value (hidden pointer).
// Evidence: format row 0x006CB5D0; StringBase wide copy 0x00037050;
// releaseBuffer 0x00036E70; format string 0x007C9260 (g_Va007C9260);
// caller 0x005FF4F8 pushes (val,out) hidden-pointer style and passes
// return to 0x005FF450.
#include "ascii_string.h"

#include "unicode_string.h"

extern const unsigned short g_Va007C9260[];

UnicodeString __cdecl Rva005FF207Format(int val)
{
	UnicodeString tmp;
	if (val >= 0)
		tmp.format(g_Va007C9260, val);
	return tmp;
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?g_Va007C9260@@3QBGB=??_C@_15KNBIKKIN@?$AA?$CF?$AAd?$AA?$AA@")
