// cl: /O1 /G7 /arch:SSE /DNDEBUG /DWIN32 /MD /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep -ICode/Libraries/Source/WWVegas/WW3D2
//
// ?Render@WaterRenderObjClass@@UAEXAAVRenderInfoClass@@@Z, retail 0x001017E7
// (113 bytes, RET 4): the RenderObjClass Render slot of the water render
// object's +4 table 0x00BC7138 (Snapshot primary at +0, as in Zero Hour's
// WaterRenderObjClass), so `this` is the RenderObjClass subobject. Zero
// Hour's WaterRenderObjClass::Render reduced to BFME 2's gates: nothing while
// only emissive draws run (dx8wrapper's 0x00DEC3D8), before the terrain has a
// map (TheTerrainRenderObject +0x37C0), when the water is off (+0x25C), under
// the camera projection override (0x00DEDA05) or while the shadow map is drawn
// (WW3D 0x00DEC404). Water types 0..2 draw through the full object's
// 0x001014A9 (with a false flag); the DX8 render states are then applied and
// invalidated and the water tracks system (+0x100) is flushed.
class RenderInfoClass;

extern bool bfmeOnlyEmissiveDraws;
extern bool bfmeCameraProjectionOverride;

#include "../../../../../Libraries/Source/WWVegas/WW3D2/WW3DClass.h"

#include "../../../../../Libraries/Source/WWVegas/WW3D2/DX8WrapperClass.h"

class WorldHeightMap;
class BaseHeightMapRenderObjClass
{
public:
	// Inline like retail, without emitting a competing getMap copy.
	__declspec(dllimport) __forceinline WorldHeightMap *getMap() { return m_map; }
private:
	unsigned char m_unknown0000[0x37C0];
	WorldHeightMap *m_map; // +0x37C0
};
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

#include "../../../../Include/W3DDevice/GameClient/WaterTracksRenderSystem.h"

class WaterRenderObjSnapshotView
{
public:
	virtual void crc();
};

class RenderObjClass
{
public:
	virtual void Render(RenderInfoClass &rinfo);
};

class WaterRenderObjClass : public WaterRenderObjSnapshotView, public RenderObjClass
{
public:
	virtual void Render(RenderInfoClass &rinfo);
protected:
	void rva001014A9(RenderInfoClass &rinfo, bool flag);
private:
	unsigned char m_pad008[0xF4 - 0x08];
	int m_waterType;				// +0xF4
	unsigned char m_padF8[0x100 - 0xF8];
	WaterTracksRenderSystem *m_waterTrackSystem;	// +0x100
	unsigned char m_pad104[0x25C - 0x104];
	bool m_doWaterRender;				// +0x25C
};

void WaterRenderObjClass::Render(RenderInfoClass &rinfo)
{
	if (bfmeOnlyEmissiveDraws)
		return;
	if (TheTerrainRenderObject && !TheTerrainRenderObject->getMap())
		return;	//no map has been loaded yet.
	if (!m_doWaterRender)
		return;
	if (bfmeCameraProjectionOverride)
		return;
	if (WW3D::Is_Currently_Rendering_Shadow_Map())
		return;

	switch (m_waterType)
	{
	case 0:
	case 1:
	case 2:
		rva001014A9(rinfo, false);
		break;
	}

	DX8Wrapper::Apply_Render_State_Changes();
	DX8Wrapper::Invalidate_Cached_Render_States();

	if (m_waterTrackSystem)
		m_waterTrackSystem->flush(rinfo);
}
