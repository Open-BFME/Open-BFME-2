// cl: /DNDEBUG /MD /EHsc
//
// EAStringC UTF-8 cursor workers on the 0x006D5F30 row, next to the rowed
// EAStringC::Mid bodies (EAStringCMid.cpp) they forward to. Flags match
// Rva006D5E70Cluster.cpp and EAStringCMid.cpp.

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

void *__cdecl rva006d4d40(void *pBuffer, int count);
int __cdecl rva006d4ca0(const char *pBuffer);

#include "../../../Apt/EAStringC.h"

extern char g_eaEmptyStringData[16];

// Retail inlines these lifetime members in this unit; the header keeps them out of line.

inline EAStringC::EAStringC()
{
	data = (EAStringC::StringDataC *)g_eaEmptyStringData;
	++((EAStringC::StringDataC *)g_eaEmptyStringData)->m_uRefCount;
}

inline EAStringC::~EAStringC()
{
	FreeData(data);
}

// ?rva006d5f30@EAStringC@@QBE?AV1@HH@Z @0x006D5F30 (174B). Codepoint substring:
// converts a codepoint start/count to byte offsets through rva006d4d40 and
// forwards to the byte-based Mid overloads, or the empty singleton. Donor is
// open-bfme-1 EAStringCUtf8Mid.cpp utf8Mid0089FBC0.
EAStringC EAStringC::rva006d5f30(int start, int count) const
{
	int effectiveStart = start;
	int adjustedCount = count;
	if (start < 0)
	{
		adjustedCount -= start;
		effectiveStart = 0;
	}
	if (adjustedCount <= 0)
		return EAStringC();
	const unsigned char *buffer = reinterpret_cast<const unsigned char *>(data) + 8;
	const unsigned char *first = (const unsigned char *)rva006d4d40((void *)buffer, effectiveStart);
	if (first == 0)
		return EAStringC();
	const unsigned char *last = (const unsigned char *)rva006d4d40((void *)first, adjustedCount);
	if (last == 0)
		return Mid((int)(first - buffer));
	return Mid((int)(first - buffer), (int)(last - first));
}
