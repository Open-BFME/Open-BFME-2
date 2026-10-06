// cl: /Ireference/shims/bfme2_ascii /MD /Oi
// ?rva0037EACC@Rva0037EACC@@QAEXPAX@Z @0x0037EACC 81B. Copy-to method: AsciiString
// at +0xD4 to dest +0x4 via pin-only operator= 0x000366F0, dwords +0x8 +0xC,
// Rva001EAFC1 at +0xB0 to dest +0x94 via rowed operator= 0x001EAFC1, 128B block
// +0x14 to dest +0x10 via rep movsd, flag +0x90 set to 1. Evidence: two
// operator= calls plus rep movsd plus flag store, ret 4, callers 0x001EC4C8
// 0x0037EB26, neighbours Rva0037E421Accessor and VTableInstalls.
#include <string.h>
#include "ascii_string.h"
class Rva001EAFC1
{
public:
	Rva001EAFC1 &operator=(const Rva001EAFC1 &other);
};
struct Rva0037EACCSrc;
struct Rva0037EACCDest;
struct Rva0037EACC
{
	void rva0037EACC(void *dest);
};
void Rva0037EACC::rva0037EACC(void *destPtr)
{
	char *dest = (char *)destPtr;
	char *src = (char *)this;
	*(AsciiString *)(dest + 0x4) = *(AsciiString *)(src + 0xD4);
	*(int *)(dest + 8) = *(int *)(src + 8);
	*(int *)(dest + 0xC) = *(int *)(src + 0xC);
	*(Rva001EAFC1 *)(dest + 0x94) = *(Rva001EAFC1 *)(src + 0xB0);
	memcpy(dest + 0x10, src + 0x14, 128);
	*(int *)(dest + 0x90) = 1;
}
