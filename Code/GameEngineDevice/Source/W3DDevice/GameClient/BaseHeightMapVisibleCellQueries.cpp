// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// Native boundaries 6C6A3..6C6E2 and6C6E2..6C721 are separate RET8 bodies,
// after Cast_Ray's terminal true branch at6C69F. WorldBuilder's saved extent
// incorrectly merges these into Cast_Ray. The reference showAsVisibleCliff
// (BF1 a7c38d3b BaseHeightMap.cpp) guides the bounds/index operation only:
// native adds four coordinate checks and reads bit-vectors at37EC/3800.
// Native data/callee evidence proves the layouts; original getter names are
// not asserted. The const bool subscript provider is rowed at0006BE55.
// always.h defines array placement-new itself.
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include "../../../Include/W3DDevice/GameClient/WorldHeightMap.h"

// Use the canonical RefCountClass instead of the donor refcount.h.
#define REFCOUNT_H

#include "../../../Include/W3DDevice/GameClient/BaseHeightMap.h"

// The canonical header leaves the two bit-vectors at +0x37EC/+0x3800 untyped;
// these readers give this TU the std::vector<bool> views the bodies index.
static __forceinline const std::vector<bool> &visibleCliffBits(const BaseHeightMapRenderObjClass *self)
{
 return self->unknown37EC;
}
static __forceinline const std::vector<bool> &visibleImpassableBits(const BaseHeightMapRenderObjClass *self)
{
 return self->unknown3800;
}
bool BaseHeightMapRenderObjClass::showAsVisibleCliff(int xIndex,int yIndex) const {
 int width=m_map->m_width;
 if(xIndex<0 || yIndex<0 || yIndex>=m_map->m_height || xIndex>=width)return false;
 return visibleCliffBits(this)[xIndex+yIndex*width];
}
bool BaseHeightMapRenderObjClass::showAsVisibleImpassable(int xIndex,int yIndex) const {
 int width=m_map->m_width;
 if(xIndex<0 || yIndex<0 || yIndex>=m_map->m_height || xIndex>=width)return false;
 return visibleImpassableBits(this)[xIndex+yIndex*width];
}
