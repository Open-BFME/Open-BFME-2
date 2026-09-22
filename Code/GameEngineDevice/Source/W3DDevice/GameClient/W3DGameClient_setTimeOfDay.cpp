// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /arch:SSE /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
//
// ?setTimeOfDay@W3DGameClient@@UAEXW4TimeOfDay@@@Z @ 0x0004C884 (56B).
// Dedicated TU: BFME1 donor shape verbatim, adapted to BFME2 retail (measured):
// water/shadow/display globals at 0x00DE2000/0x00DE5DFC/0x00DFE9D8 (DIR32,
// address-derived placeholder names per the R2Data precedent) and the display
// call at virtual slot 0xB4 (45 pads, AddFrameEntry idiom). The Bool twins
// (EnableLoginControls/enableControls) are refuted by the dword push.

enum TimeOfDay
{
	TIME_OF_DAY_MORNING = 0,
	TIME_OF_DAY_AFTERNOON = 1,
	TIME_OF_DAY_EVENING = 2,
	TIME_OF_DAY_NIGHT = 3
};

extern void *W3DGCData00DE2000;
extern void *W3DGCData00DE5DFC;
extern void *W3DGCData00DFE9D8;

#include "vector3.h"

class W3DGameClientWaterShim
{
public:
	void setTimeOfDay(TimeOfDay tod);
};

class W3DGameClientShadowShim
{
public:
	void setTimeOfDay(TimeOfDay tod);
	void setLightPosition(int lightIndex, float x, float y, float z);
};

class W3DGameClientDisplayShim
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void slot44() = 0;
	virtual void setTimeOfDay(TimeOfDay tod) = 0;
};

class W3DGameClient
{
public:
	virtual void setTimeOfDay(TimeOfDay tod);
};

// ?setTimeOfDay@W3DGameClient@@UAEXW4TimeOfDay@@@Z
void W3DGameClient::setTimeOfDay(TimeOfDay tod)
{
	void *water = W3DGCData00DE2000;
	if (water)
		((W3DGameClientWaterShim *)water)->setTimeOfDay(tod);
	void *shadow = W3DGCData00DE5DFC;
	if (shadow)
		((W3DGameClientShadowShim *)shadow)->setTimeOfDay(tod);
	void *display = W3DGCData00DFE9D8;
	((W3DGameClientDisplayShim *)display)->setTimeOfDay(tod);
}

// One 0x6C-stride time-of-day lighting entry. The direction lives at +0x18
// (ambient + diffuse RGBColor pairs ahead of it, BFME1 TerrainLighting:
// ambient@0 diffuse@0xC lightPos@0x18). Retail indexes base+0x3C8+0x6C*tod.
struct ShadowTerrainLightEntry
{
	char m_pad00[0x18];
	float m_lightX;
	float m_lightY;
	float m_lightZ;
	char m_pad24[0x6C - 0x24];
};

extern void *W3DGCData00DFE758;

// Sun distance (BFME1 SUN_DISTANCE_FROM_GROUND was 10000.0f; retail pools
// 10000000.0f in .rdata, so BFME2 keeps it a literal with a new value).
#define SHADOW_SUN_DISTANCE_FROM_GROUND 10000000.0f

// ?setTimeOfDay@W3DGameClientShadowShim@@QAEXW4TimeOfDay@@@Z @ 0x0009A64D (195B).
// BFME1 W3DShadowManager::setTimeOfDay donor verbatim (ray to light source,
// negate, normalize, scale by the sun distance, install at slot 0).
void W3DGameClientShadowShim::setTimeOfDay(TimeOfDay tod)
{
	const ShadowTerrainLightEntry *entry =
		(const ShadowTerrainLightEntry *)((const char *)W3DGCData00DFE758 + 0x3C8 + tod * 0x6C);
	Vector3 lightRay(-entry->m_lightX, -entry->m_lightY, -entry->m_lightZ);
	lightRay.Normalize();
	lightRay *= SHADOW_SUN_DISTANCE_FROM_GROUND;
	setLightPosition(0, lightRay.X, lightRay.Y, lightRay.Z);
}
