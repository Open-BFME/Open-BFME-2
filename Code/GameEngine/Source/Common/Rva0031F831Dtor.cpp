// cl: /MD /Ireference/shims/bfme2_ascii
// stlport
// ??1Rva0031F831@@QAE@XZ @0x0031F831 9B dtor zeroes +8 then releases StringBase.
// Retail and [ecx+8],0 then jmp releaseBuffer 0x00036410. Evidence: unlock lane;
// caller 0x0031F856 is deleting dtor calling this as ??1; rowed releaseBuffer
// ?releaseBuffer@?$StringBase@D@@AAEXXZ; and-mem-zero idiom needs /O1.
// The canonical frozen StringBase replaces the private copy; its switch
// declares the narrow teardown out of line, rowed at 0x00036410
// (StringBaseWideReleaseBuffer.cpp).
#define BFME_STRINGBASE_PUBLIC_DTOR
#include "string_base.h"

class Rva0031F831 {
public: ~Rva0031F831();
private: StringBase<char> m_str;
         char m_pad[4];
         int m_8; };
Rva0031F831::~Rva0031F831()
{
	m_8 = 0;
}
