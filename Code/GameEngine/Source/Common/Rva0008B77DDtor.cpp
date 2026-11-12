// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
// ??1Rva008B77D@@UAE@XZ @0x0008B77D 54B
// Opaque dtor called by the rowed ??_G 0x0008B7B3. Target facts: stores its
// vtable 0x00BC7514 { ??_G 0x0008B7B3, 0x00312EDA, 0x003114A7 }, destroys the
// STLport vector<BfmeStringHeadRecord184> at +0x2C through its rowed dtor
// 0x0008B64A (sole caller) under EH state 0 for the base subobject, then the
// inline base dtor resets to the base vtable 0x00BC745C, the shared
// Rva000851F3 interface (whose 0x2C-byte prefix puts the vector at +0x2C).
// Identity unproven; address-derived names.
#include <vector>
#include "../../Include/GameClient/Rva0008990CArrayOwner.h"

#include "../../../Libraries/Source/WWVegas/WWLib/BfmeStringHeadRecord184.h"

// Out of line in retail (rowed 0x0008B64A, StlportVectorDtorFamily.cpp).
template <>
_STL::vector<BfmeStringHeadRecord184, _STL::allocator<BfmeStringHeadRecord184> >::~vector();

class Rva008B77D : public Rva000851F3
{
public:
	virtual ~Rva008B77D();
	virtual void rva00047A69C(int);
	virtual void rva00086B2C(int, int, Real, Real, int, int);

private:
	_STL::vector<BfmeStringHeadRecord184> m_records; // +0x2C
};

Rva008B77D::~Rva008B77D()
{
}

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?rva00047A69C@Rva008B77D@@UAEXH@Z=?rva00312EDA@Rva008B77D@@UAEXPBURva00311431Arg@@@Z")
