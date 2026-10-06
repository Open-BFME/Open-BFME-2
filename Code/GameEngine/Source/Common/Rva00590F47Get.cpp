// cl: /Ireference/shims/bfme2_ascii /MD /GX-
// ?Rva00590F47Get@@YAHPBVRva004D6119@@@Z @0x00590F47 47B leaf: free __cdecl size helper like sibling @0x00590F76 but returns len*2+0x0D
// evidence: same rowed value-returning getter @0x004D6119 into dead arg home [ebp+8], same header length low byte at m_data+4, same releaseBuffer @0x00036E70, same lea eax,[eax+eax+0xd]; caller 0x005929D6; prev/next same ascii /O1 flags
#include "unicode_string.h"

class Rva004D6119
{
public:
	UnicodeString rva004D6119() const;
};

int __cdecl Rva00590F47Get(const Rva004D6119 *obj)
{
	const Rva004D6119 *o = obj;
	unsigned char b = (unsigned char)o->rva004D6119().getLength();
	return b * 2 + 0x0D;
}
