// cl: /O1 /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// Target 0x4613EB destroys 12B Link elements through the clearer at
// 0x003F29F8 (stride 0xC, per-element destruction through 0x0007FAB3),
// then frees the vector storage. Target 0x003F29F8 is the element
// clearer loop; target 0x0007FAB3 is the element dtor itself (null-checked
// free of the owned pointer at +0). Link elements are therefore 12B owner
// records; interiors are positional (the dtor proves +0 is an owned
// pointer, the rest is unproven). StlportAsciiStringVectorDtor precedent
// (explicit instantiation emits the foldable family).
#include <vector>

extern "C" void _free(void *ptr);

struct DynamicPortalLink
{
	void *m_owned;
	int m_second;
	int m_third;
	~DynamicPortalLink();
};

template _STL::vector<DynamicPortalLink>::~vector();

// ?rva0032E7E2@Rva0032E7E2@@QAEXXZ — RVA 0x0032E7E2, 30B.
// Vector storage teardown: destroy range [start finish) via the rowed
// _Destroy at 0x003F29F8, then free start via the rowed _free at 0x00030830.
// Evidence: retail push [esi+4] push [esi] plus call 0x003F29F8,
// mov esi [esi] plus test, push esi plus call 0x00030830;
// prev 0x0032E7A3 same TU and flags, same Link Destroy callee.
#include <stdlib.h>

class Rva0032E7E2
{
public:
	void rva0032E7E2();
	DynamicPortalLink *m_start;
	DynamicPortalLink *m_finish;
};

void Rva0032E7E2::rva0032E7E2()
{
	_STL::_Destroy(m_start, m_finish);
	if (m_start != 0)
		free(m_start);
}

// ??1Rva001FFE93@@UAE@XZ, retail 0x001FFE93..0x001FFEE9 (86 bytes, EH): the
// destructor its rowed scalar deleting destructor 0x001FFE77 calls (vtable
// 0x00BE25EC). Members go in reverse: the +0x1C Link vector (retail's call
// lands on the duplicate vector destructor 0x001FFD2C, the copy this object's
// unit got: its scopetable differs from the one at 0x0032E7A3, so it was not
// folded and the shared vector symbol cannot name it; the member is viewed
// through a class whose destructor is pinned there), the wide strings at
// +0x18 and +0x14 (rowed releaseBuffer 0x00036E70), then the rowed base
// destructor 0x001E3624.
// The canonical frozen StringBase replaces the private copy; its switch makes
// the member dtor reachable and keeps the teardown an out-of-line call to the
// rowed releaseBuffer (0x00036410 narrow, 0x00036E70 wide).
#define BFME_STRINGBASE_PUBLIC_DTOR
#include "string_base.h"

class Overridable
{
public:
	virtual ~Overridable();
private:
	void *m_04;
};

// Native1FFD2C has a distinct EH handler from the vector copy at4613EB.
// Its complete63B body destroys [start,finish) then frees storage through
// the same STLport base cleanup, including cleanup when element teardown throws.
// The application type remains unknown; this is the existing member ABI view.
class DynamicPortalLinkVectorCopy1FFD2C
 : public _STL::_Vector_base<DynamicPortalLink, _STL::allocator<DynamicPortalLink> >
{
public:
 ~DynamicPortalLinkVectorCopy1FFD2C();
};
typedef char DynamicPortalLinkVectorCopyWidth[sizeof(DynamicPortalLinkVectorCopy1FFD2C)==12 ? 1 : -1];
DynamicPortalLinkVectorCopy1FFD2C::~DynamicPortalLinkVectorCopy1FFD2C()
{
 _STL::_Destroy(this->_M_start, this->_M_finish);
}

// Native3F30D1 is another separate63B copy of the same vector teardown.
// LivingWorldRegionConstructor.cpp's +0x180/+0x18C members and their EH
// funclets reach it as ??1Gen_uwm_003f30d1; this view defines that name.
// The application type remains unknown, as for the 1FFD2C copy above.
class Gen_uwm_003f30d1
 : public _STL::_Vector_base<DynamicPortalLink, _STL::allocator<DynamicPortalLink> >
{
public:
 ~Gen_uwm_003f30d1();
};
typedef char Gen_uwm_003f30d1Width[sizeof(Gen_uwm_003f30d1)==12 ? 1 : -1];
Gen_uwm_003f30d1::~Gen_uwm_003f30d1()
{
 _STL::_Destroy(this->_M_start, this->_M_finish);
}

class Rva001FFE93 : public Overridable
{
public:
	virtual ~Rva001FFE93();
private:
	unsigned char m_pad08[0x14 - 0x08];
	StringBase<unsigned short> m_str14;
	StringBase<unsigned short> m_str18;
	DynamicPortalLinkVectorCopy1FFD2C m_links1C;
};

Rva001FFE93::~Rva001FFE93()
{
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1DynamicPortalLinkVec@@QAE@XZ=??1?$vector@UDynamicPortalLink@@V?$allocator@UDynamicPortalLink@@@_STL@@@_STL@@QAE@XZ")
