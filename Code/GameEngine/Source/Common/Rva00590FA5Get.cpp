// cl: /Ireference/shims/bfme2_ascii /MD /GX-
// ?Rva00590FA5Get@@YAHPBVRva0023E928@@@Z @0x00590FA5 47B leaf: free __cdecl size helper like siblings @0x00590F47/@0x00590F76 but via getter @0x0023E928 and returns len*2+0x1D
// evidence: same rowed value-returning getter @0x0023E928 into dead arg home [ebp+8], same header length low byte at m_data+4, same releaseBuffer @0x00036E70, same lea eax,[eax+eax+0x1d]; caller 0x00592A25; prev/next same ascii /O1 flags
#include "unicode_string.h"

class Rva0023E928
{
public:
	UnicodeString rva0023E928() const;
};

int __cdecl Rva00590FA5Get(const Rva0023E928 *obj)
{
	const Rva0023E928 *o = obj;
	unsigned char b = (unsigned char)o->rva0023E928().getLength();
	return b * 2 + 0x1D;
}
