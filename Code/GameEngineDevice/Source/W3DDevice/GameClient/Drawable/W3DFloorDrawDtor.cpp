// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// ??1W3DFloorDraw@@UAE@XZ @0x000CF1A6 102B
// Dtor over W3DFloorDraw: restores both vptrs (+0 via Rva000CEB6F line and
// +0x10 second base) then if moduleData (+4) and drawable (+8) are non-null
// forwards (drawable, AsciiString copy of moduleData+8) through
// TheTerrainRenderObject->rva0006B76C (rowed 0x0006B76C) and calls the base
// dtor rowed 0x000CEB6F. Donor is BFME1
// game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DFloorDrawDestructor.cpp
// (same if-if shape with moduleData+8 string through a global). BFME2 deltas:
// two vptrs (second base trivial inline) and the terrain-render global.
// Shape lever: AsciiString with inline forwarding copy/dtor to the base so
// the by-value copy keeps retail mov ebp-0x14 esp then mov ecx esp order.
// Callers: 0x000CF495 deleting dtor. Vtables patched as DIR32 by the gate.
#include "ascii_string.h"


struct FloorDrawModuleData
{
	char m_pad[8];
	AsciiString m_name;
};

class Rva0055A88BDwordField;

#include "../../../../Include/W3DDevice/GameClient/BaseHeightMap.h"

extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;
// TheTerrainRenderObject: matched references place it at VA 0xde1eac (zero-filled .bss).
BaseHeightMapRenderObjClass * TheTerrainRenderObject;

class Rva000CEB6F
{
public:
	virtual ~Rva000CEB6F();
protected:
	FloorDrawModuleData *m_moduleData;
	Rva0055A88BDwordField *m_drawable;
private:
	char m_pad0C[0x10 - 0x0C];
};

class W3DFloorDrawSecondBase
{
public:
	virtual void secondBaseAnchor() {}
};

class W3DFloorDraw : public Rva000CEB6F, public W3DFloorDrawSecondBase
{
public:
	virtual ~W3DFloorDraw();
};

W3DFloorDraw::~W3DFloorDraw()
{
	if (m_moduleData != 0)
	{
		Rva0055A88BDwordField *drawable = m_drawable;
		if (drawable != 0)
			TheTerrainRenderObject->rva0006B76C(drawable, m_moduleData->m_name);
	}
}
