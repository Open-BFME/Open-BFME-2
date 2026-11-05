// cl: /DNDEBUG /MD /D_CRTIMP= /EHsc
//
// EAStringC UTF-8 case-folding workers on the 0x006D6100 row, next to the
// rowed EAStringC::Mid bodies (EAStringCMid.cpp) and the UTF-8 cursor workers
// in Rva006D4CA0Cluster.cpp / Rva006D5F30Cluster.cpp. Both fold every codepoint
// through one case helper and re-encode it in place with the shared UTF-8
// encoder rva006d4dc0. Donor is open-bfme-1 EAStringCUtf8Normalize.cpp
// BfmeUtf8String008A00C0::map (tolower) / EAStringCUtf8NormalizeUpper.cpp
// (toupper), which inlined the decode/encode; retail calls the shared workers
// rva006d4280 and rva006d4dc0 instead.

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

#include <ctype.h>

const char *__cdecl rva006d4280(const char *pBuffer, int *pUnicode);
void __cdecl rva006d4dc0(char *pBuffer, int codepoint);

#include "../../../Apt/EAStringC.h"

// ?rva006D6100@EAStringC@@QAEAAV1@XZ @0x006D6100 (99B). Codepoint-lowercase
// fold: reserve a copy-on-write buffer, then walk the payload one UTF-8
// sequence at a time, lower each decoded codepoint and rewrite its bytes in
// place. Called by the rowed 0x006D7C80 normalizer.
EAStringC &EAStringC::rva006D6100()
{
	const unsigned int size = data->m_uSize;
	ChangeBuffer(size, 0, size, CB_PUSH_ZERO, size);

	unsigned char *p = (unsigned char *)(reinterpret_cast<char *>(data) + sizeof(StringDataC));
	for (;;)
	{
		int value;
		unsigned char *start = p;
		p = (unsigned char *)rva006d4280((const char *)p, &value);
		if (value == 0)
			break;
		rva006d4dc0((char *)start, tolower(value));
	}
	return *this;
}

// ?rva006D6170@EAStringC@@QAEAAV1@XZ @0x006D6170 (99B). Same fold with
// toupper; called by the rowed 0x006D7D00 string-value converter.
EAStringC &EAStringC::rva006D6170()
{
	const unsigned int size = data->m_uSize;
	ChangeBuffer(size, 0, size, CB_PUSH_ZERO, size);

	unsigned char *p = (unsigned char *)(reinterpret_cast<char *>(data) + sizeof(StringDataC));
	for (;;)
	{
		int value;
		unsigned char *start = p;
		p = (unsigned char *)rva006d4280((const char *)p, &value);
		if (value == 0)
			break;
		rva006d4dc0((char *)start, toupper(value));
	}
	return *this;
}
