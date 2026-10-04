// ?Rva0040B99FCopy@@YAXPAVRva0040B707@@ABV1@@Z
// partial score=0.93 date=2026-10-04
// cl: /O1 /EHsc /Ireference/shims/bfme2_ascii
// stlport
// ?Rva0040B99FCopy@@YAXPAVRva0040B707@@ABV1@@Z @0x0040B99F 45B chain null-checked placement copy via callers 0x0040B9DA 0x0040BA05
#include <vector>
#include "ascii_string.h"

enum ScienceType
{
	ScienceType_0
};
struct BfmeRecord0040B61A
{
	char m_bytes[1];
};

class Rva0040B707
{
public:
	Rva0040B707(const Rva0040B707 &o);
private:
	int m_00;
	_STL::vector<ScienceType> m_04;
	AsciiString m_10;
	AsciiString m_14;
	AsciiString m_18;
	_STL::vector<BfmeRecord0040B61A> m_1C;
};

// ?Rva0040B99FCopy@@YAXPAVRva0040B707@@ABV1@@Z present-unmatched
void __cdecl Rva0040B99FCopy(Rva0040B707 *dst, const Rva0040B707 &src)
{
	if (dst != 0)
		new(dst) Rva0040B707(src);
}
