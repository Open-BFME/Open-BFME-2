// cl: /O1 /arch:SSE /G7 /MD /DNDEBUG /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// ?rva0004353C@Rva00043511@@QAEXXZ, retail 0x0004353C, 593 bytes.
// Time-of-day lighting fade step on the Rva00043511 record (mode, start frame,
// duration in seconds, source colour): progress = frames elapsed * the logic
// step / duration; past 1.0 the duration is cleared (fade over), otherwise the
// source colour is blended with each of the three lighting rows of the current
// time of day (stride 0x24, rows at +0x140 / +0x3C8 / +0x650 of the global
// data, 0x6C per time of day), the first two pushed to the display lights
// through vtable slots 0xC4 / 0xC8 and the 0x140 blend stored at +0x8FC.
// Mode 1 swaps the two weights. The terrain render object is told afterwards.
// Evidence (target): Display slots 0xC4/0xC8 are the rowed Rva0004443E
// 4450E/44545 setDiffuse pair (W3DDisplayLightingScale.cpp, RET 0x10 = index
// plus three floats, so they are declared with float arguments: the call site
// pushes them through fld/fstp like retail); the game-client slot 0x7C is
// getFrame (Win32Mouse.cpp); 0x009BA508 is the rowed logic step float. Donor
// (structure only): WorldBuilder 0x00966810 debug twin (names unavailable).
// Codegen: the three blends are computed in z, x, y order into struct locals
// before the calls; the loop condition is spelled 3 > i (found by mutation
// walk; it moves the object z load past the argument store).
struct Rva0004353CColor
{
	float x, y, z;
};

#include "../../../../GameEngine/Include/Common/GlobalData.h"

class Display
{
public:
	virtual void v00(void);
	virtual void v01(void);
	virtual void v02(void);
	virtual void v03(void);
	virtual void v04(void);
	virtual void v05(void);
	virtual void v06(void);
	virtual void v07(void);
	virtual void v08(void);
	virtual void v09(void);
	virtual void v0a(void);
	virtual void v0b(void);
	virtual void v0c(void);
	virtual void v0d(void);
	virtual void v0e(void);
	virtual void v0f(void);
	virtual void v10(void);
	virtual void v11(void);
	virtual void v12(void);
	virtual void v13(void);
	virtual void v14(void);
	virtual void v15(void);
	virtual void v16(void);
	virtual void v17(void);
	virtual void v18(void);
	virtual void v19(void);
	virtual void v1a(void);
	virtual void v1b(void);
	virtual void v1c(void);
	virtual void v1d(void);
	virtual void v1e(void);
	virtual void v1f(void);
	virtual void v20(void);
	virtual void v21(void);
	virtual void v22(void);
	virtual void v23(void);
	virtual void v24(void);
	virtual void v25(void);
	virtual void v26(void);
	virtual void v27(void);
	virtual void v28(void);
	virtual void v29(void);
	virtual void v2a(void);
	virtual void v2b(void);
	virtual void v2c(void);
	virtual void v2d(void);
	virtual void v2e(void);
	virtual void v2f(void);
	virtual void v30(void);
	virtual void setTerrainDiffuse(int index, float red, float green, float blue);	// slot 0xC4
	virtual void setObjectDiffuse(int index, float red, float green, float blue);	// slot 0xC8
};

#include "../../../../GameEngine/Include/GameClient/GameClientClass.h"

#include "../../../Include/W3DDevice/GameClient/BaseHeightMap.h"

extern GlobalData *TheWritableGlobalData;
extern GameClient *TheGameClient;
extern Display *TheDisplay;
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;
extern float opacityLogicStepSeconds;

class Rva00043511
{
public:
	void rva0004353C();
private:
	int m_mode;
	unsigned int m_startFrame;
	float m_duration;
	float m_color[3];
};

void Rva00043511::rva0004353C()
{
	if (m_duration == 0.0f)
		return;
	float toWeight = ((float)(TheGameClient->getFrame() - m_startFrame) * opacityLogicStepSeconds) / m_duration;
	if (toWeight > 1.0f)
	{
		m_duration = 0.0f;
		return;
	}
	float fromWeight = 1.0f - toWeight;
	if (m_mode == 1)
	{
		float swap = fromWeight;
		fromWeight = toWeight;
		toWeight = swap;
	}
	int tod = TheWritableGlobalData->m_timeOfDay;
	const GlobalData::TerrainLighting *fade = TheWritableGlobalData->m_terrainLighting[tod];
	const GlobalData::TerrainLighting *terrain = TheWritableGlobalData->m_terrainObjectsLighting[tod];
	const GlobalData::TerrainLighting *object = TheWritableGlobalData->field0650[tod];
	for (int i = 0; 3 > i; ++i)
	{
		RGBColor blended;
		blended.blue = toWeight * fade[i].diffuse.blue + fromWeight * m_color[2];
		blended.red = toWeight * fade[i].diffuse.red + fromWeight * m_color[0];
		blended.green = toWeight * fade[i].diffuse.green + fromWeight * m_color[1];
		Rva0004353CColor terrainColor;
		terrainColor.z = toWeight * terrain[i].diffuse.blue + fromWeight * m_color[2];
		terrainColor.x = toWeight * terrain[i].diffuse.red + fromWeight * m_color[0];
		terrainColor.y = toWeight * terrain[i].diffuse.green + fromWeight * m_color[1];
		Rva0004353CColor objectColor;
		objectColor.z = toWeight * object[i].diffuse.blue + fromWeight * m_color[2];
		objectColor.x = toWeight * object[i].diffuse.red + fromWeight * m_color[0];
		objectColor.y = toWeight * object[i].diffuse.green + fromWeight * m_color[1];
		TheDisplay->setTerrainDiffuse(i, terrainColor.x, terrainColor.y, terrainColor.z);
		TheDisplay->setObjectDiffuse(i, objectColor.x, objectColor.y, objectColor.z);
		TheWritableGlobalData->m_terrainDiffuse[i] = blended;
	}
	if (TheTerrainRenderObject)
		TheTerrainRenderObject->rva0006846A(tod);
}
