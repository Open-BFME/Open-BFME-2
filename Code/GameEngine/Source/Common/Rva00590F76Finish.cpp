// cl: /Ireference/shims/bfme2_ascii /MD /GX-
// ?Rva00590F76Get@@YAHPBVRva004D6119@@@Z @0x00590F76 (47B):
// Free __cdecl size helper: copies the +0x1c UnicodeString via the rowed
// value-returning getter @0x004D6119 into the dead incoming argument home
// [ebp+8] (MSVC /O1 stack-slot reuse), reads the header length low byte at
// m_data+4, releases via the temporary's destructor -> rowed releaseBuffer
// @0x00036E70, then returns len*2+0x19.
// Sibling @0x00590F47 is the same body with +0x0D; caller 0x005929DE.
// The local field pointer is load-bearing: it makes the hidden-return
// temporary land in the dead argument home [ebp+8] instead of [ebp-4].
#include "unicode_string.h"

class Rva004D6119
{
public:
	UnicodeString rva004D6119() const;
};

int __cdecl Rva00590F76Get(const Rva004D6119 *obj)
{
	const Rva004D6119 *o = obj;
	unsigned char b = (unsigned char)o->rva004D6119().getLength();
	return b * 2 + 0x19;
}
