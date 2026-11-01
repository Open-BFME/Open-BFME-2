// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS -Ireference/open-bfme-1/game/GameEngine/Source/Common /Ireference/shims/bfme2_ascii -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/shims/bfmealloc
// stlport
// ??0Rva002186EB@@QAE@XZ, retail 0x002186EB, 61 bytes.
// Base count +4, reference +8 and map +0x0C (ctor 0x0033C432); caller 0x00218D61.
// Retail zeros +4 before vtable 0x7E5B10; EH states 0 then 1 precede the map call.

#include "ascii_string.h"


#include <map>
#include "../../../Include/Common/Rva0007DF07.h"

namespace _STL {
template <> map<int, void *, less<int>, allocator<pair<const int, void *> > >::map();
}

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);

class Rva002177CD
{
public:
	~Rva002177CD();
private:
	_STL::map<int, void *, _STL::less<int>, _STL::allocator<_STL::pair<const int, void *> > > m_records;
};

class Rva002186EBRef
{
public:
	Rva002186EBRef() : m_ref(0) {}
	~Rva002186EBRef()
	{
		if (m_ref)
			ReleaseTreeHintRef00217D4C(m_ref);
	}
	TargetRef00217D4C *m_ref;
};

class Rva002186EB : public Rva0007DF07
{
public:
	Rva002186EB();
	Rva002186EB(int tag);
	virtual ~Rva002186EB();
private:
	// +0x04 is Rva0007DF07::m_04 (canonical header).
	Rva002186EBRef defaults; // +0x08
	Rva002177CD sizes; // +0x0C
};

Rva002186EB::Rva002186EB()
{
}
