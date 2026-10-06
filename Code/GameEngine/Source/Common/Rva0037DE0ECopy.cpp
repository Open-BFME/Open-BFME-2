// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /Oi
// ?rva0037DE0E@Rva0037DE0E@@QAEEPAX@Z @0x0037DE0E 85B. Copy-to via rowed
// 0x0037E3D9 plus dwords +8 +C, 128B block +0x10 to dest +0x14 via rep movsd,
// Rva001EAFC1 +0x94 to dest +0xB0 via rowed operator= 0x001EAFC1, zero +0xB4
// and byte +0xC4, return 1. Evidence: two rowed calls, ret 4, test al in
// caller 0x0040C4D9, neighbours Rva0037DCA5Get and Rva0037DF2CCtor.
#include <string.h>
#include "ascii_string.h"
class UnitRevivalEntry
{
public:
	void setThingTemplateName(const AsciiString &arg);
};
class Rva001EAFC1
{
public:
	Rva001EAFC1 &operator=(const Rva001EAFC1 &other);
};
class Rva0037DE0E
{
	char m_pad00[4];
	AsciiString m_s04;
	int m_08;
	int m_0C;
	char m_block10[128];
	char m_pad90[4];
	Rva001EAFC1 m_94;
public:
	unsigned char rva0037DE0E(void *dest);
};
unsigned char Rva0037DE0E::rva0037DE0E(void *destPtr)
{
	char *dest = (char *)destPtr;
	char *src = (char *)this;
	((UnitRevivalEntry *)dest)->setThingTemplateName(*(const AsciiString *)(src + 4));
	*(int *)(dest + 8) = *(int *)(src + 8);
	*(int *)(dest + 0xC) = *(int *)(src + 0xC);
	memcpy(dest + 0x14, src + 0x10, 128);
	*(Rva001EAFC1 *)(dest + 0xB0) = *(Rva001EAFC1 *)(src + 0x94);
	*(int *)(dest + 0xB4) = 0;
	*(unsigned char *)(dest + 0xC4) = 0;
	return 1;
}
