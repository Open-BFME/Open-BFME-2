// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva0040B14EConstruct@@YAXPAVRva0040AEE3@@ABV1@@Z @ 0x0040B14E (45B). Construct Rva0040AEE3 via copy ctor.
// Evidence: calls rowed copy ctor 0x0040AEE3; EH prolog with state 0; null check on dst; callers 0x0040B1BB 0x0040B30B 0x0040B887 0x0040BA45.
#include <vector>
#include <new>

enum ScienceType
{
	SCIENCE_NONE = 0
};

class Rva0040AEE3
{
public:
	Rva0040AEE3(const Rva0040AEE3 &other);
	Rva0040AEE3 &operator=(const Rva0040AEE3 &other);
private:
	_STL::vector<ScienceType> m_0000;
	int m_000C;
};

void __cdecl Rva0040B14EConstruct(Rva0040AEE3 *p, const Rva0040AEE3 &src)
{
	new (p) Rva0040AEE3(src);
}

// Callers elsewhere reach this body through a spelling pinned to the same retail
// address with the same calling convention; bind it here.
#pragma comment(linker, "/alternatename:??$_Construct@VRva0040AEE3@@V1@@_STL@@YAXPAVRva0040AEE3@@ABV1@@Z=?Rva0040B14EConstruct@@YAXPAVRva0040AEE3@@ABV1@@Z")
