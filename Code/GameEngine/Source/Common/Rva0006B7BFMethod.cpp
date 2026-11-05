// cl: /MD /EHsc /Ireference/shims/bfme2_ascii /DNDEBUG /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// ?rva0006B7BF@BaseHeightMapRenderObjClass@@QAEXPBVRva0055A88BDwordField@@V?$StringBase@D@@M@Z @0x0006B7BF 69B
// Wrapper over rowed 0x000E6135: loads Rva000E6135* from this+0x3860 and forwards
// (id, by-value AsciiString name, float value) if non-null. By-value name gives
// the EH prolog with state 0 guard and the releaseBuffer teardown. Caller at
// 0x000CF40E passes TheTerrainRenderObject as this, id from [ecx+8], name copy
// from ([ecx+4]+8), float from ([ecx+4]+0x20).
// The canonical frozen StringBase replaces the private copy; its switch makes
// the member dtor reachable and keeps the teardown an out-of-line call to the
// rowed releaseBuffer (0x00036410 narrow, 0x00036E70 wide).
#define BFME_STRINGBASE_PUBLIC_DTOR
#include "string_base.h"



class Rva0055A88BDwordField;

class Rva000E6135
{
public:
	void rva000E6135(const Rva0055A88BDwordField *idSrc, const StringBase<char> &name, float value);
};

#include "../../../../GameEngineDevice/Include/W3DDevice/GameClient/WorldHeightMap.h"

// Use the canonical RefCountClass instead of the donor refcount.h.
#define REFCOUNT_H

#include "../../../../GameEngineDevice/Include/W3DDevice/GameClient/BaseHeightMap.h"

void BaseHeightMapRenderObjClass::rva0006B7BF(const Rva0055A88BDwordField *id, StringBase<char> name, float value)
{
	if (field3860 != 0)
		static_cast<Rva000E6135 *>(field3860)->rva000E6135(id, name, value);
}
