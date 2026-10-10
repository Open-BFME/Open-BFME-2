// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// ?insert@?$vector@VW3DAnimationInfo@@V?$allocator@VW3DAnimationInfo@@@_STL@@@_STL@@QAEPAVW3DAnimationInfo@@PAV3@ABV3@@Z
// retail 0x00538944, 149 bytes: STLport 4.5.3 vector<W3DAnimationInfo>::insert.
//
// Ported from the Open-BFME-1 donor
// game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DAnimationInfoVectorInsert.cpp
// (reference/open-bfme-1 @ 6583b3c1). Compiled at /O1 it is a unique masked
// placement on unclaimed .text. Its callees are the pinned W3DAnimationInfo
// helpers: _Construct 0x00469C61, copy constructor 0x0004254E,
// __copy_backward_ptrs 0x005B2B1E and _M_insert_overflow 0x0047008E. The
// same addresses carry the ledger's BfmeFloat4Record00469C61 vector family.
// The donor's element model is kept: sixteen bytes with an out-of-line copy
// constructor and no destructor (a destructor adds a destroy loop retail lacks).
// The member is instantiated explicitly instead of through the donor's anchor.
#define _STLP_NO_EXCEPTIONS 1
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
class W3DAnimationInfo
{
public:
	W3DAnimationInfo(const W3DAnimationInfo &other);

private:
	char m_bfmeBody[0x10];
};

template _STL::vector<W3DAnimationInfo>::iterator
	_STL::vector<W3DAnimationInfo>::insert(_STL::vector<W3DAnimationInfo>::iterator, const W3DAnimationInfo &);
