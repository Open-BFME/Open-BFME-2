// cl: /O2 /DNDEBUG /MD
// Donor: BFME1 EAStringCAssign.cpp at 0x008A0480.
// Target: 0x006D6250 calls ChangeBuffer and SetSize; uses length/hash at +2/+6
// and payload at +8. Preserve the donor copy operation with that SetSize call.

#include <string.h>

int __cdecl utf8EncodedLength(int c);

#include "../../../Apt/EAStringC.h"

extern char g_eaEmptyStringData[16];

EAStringC &EAStringC::Assign(const EAStringC &other)
{
	unsigned otherSize = other.data->m_uSize;
	unsigned n = data->m_uSize;
	if (n > otherSize)
		n = otherSize;
	ChangeBuffer(otherSize, 0, n, CB_PUSH_ZERO, n);
	char *dst = (reinterpret_cast<char *>(data) + sizeof(StringDataC));
	memcpy(dst, (reinterpret_cast<char *>(other.data) + sizeof(StringDataC)), otherSize);
	dst[otherSize] = 0;
	SetSize(otherSize);
	data->m_uHash = other.data->m_uHash;
	return *this;
}
EAStringC &EAStringC::rva006D61E0(int c)
{
	FreeData(data);
	data = (EAStringC::StringDataC *)g_eaEmptyStringData;
	++((EAStringC::StringDataC *)g_eaEmptyStringData)->m_uRefCount;
	int len = utf8EncodedLength(c);
	unsigned int n = data->m_uSize;
	if (n > (unsigned int)len)
		n = len;
	ChangeBuffer(len, 0, n, CB_PUSH_ZERO, n);
	rva006D4190(c);
	return *this;
}
