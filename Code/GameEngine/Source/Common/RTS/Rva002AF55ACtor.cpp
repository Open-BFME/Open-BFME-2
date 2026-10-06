// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva002AF55A@@QAE@XZ @0x002AF55A (39B): argless ctor clearing +0 then Vector_base at +8 and +0x14 via rowed 0x00211E58.
// Evidence: and [esi],0 then lea [ebp-1] allocator temp plus ecx esi+8/si+14 calls to rowed Vector_base BfmeE16; mov eax esi ret; neighbours FamilyDeletingDtors /O1 and PlayerRva002AF614 /O1.
#include <vector>

struct BfmeE16 { float x, y, z, w; };

class Rva002AF55A
{
public:
	Rva002AF55A();
private:
	int m_00;
	int m_04;
	_STL::vector<BfmeE16> m_08;
	_STL::vector<BfmeE16> m_14;
};

Rva002AF55A::Rva002AF55A()
	: m_00(0), m_08(_STL::allocator<BfmeE16>()), m_14(_STL::allocator<BfmeE16>())
{
}
