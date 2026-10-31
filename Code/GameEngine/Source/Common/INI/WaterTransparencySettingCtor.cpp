// cl: /Ireference/shims/bfme2_ascii /ICode/Libraries/Include /O1 /DNDEBUG /MD /EHsc /arch:SSE
//
// ??0WaterTransparencySetting@@QAE@XZ, retail 0x00200D80, 249 bytes.
// Zero Hour / BFME 1 Water.h WaterTransparencySetting constructor (donor
// semantics) over BFME 2's measured layout: the Overridable base (vtable
// 0x00BDDC48, -1 third word as in the rowed Overridable ctor 0x001E35CA), the
// rowed registration base at +0x10 (0x00200D38) named "WaterTransparency",
// and the texture "TWWater01.tga" set through StringBase<char>::set 0x000055F5.
// Field names past the donor's are address-derived.
#include "ascii_string.h"
#include "Lib/RGBColor.h"

typedef float Real;
typedef bool Bool;
typedef int Int;

#include "../../../Include/Common/Overridable.h"



#include "../../../Include/GameClient/Water.h"

WaterTransparencySetting::WaterTransparencySetting() : Rva00200D38(AsciiString("WaterTransparency"))
{
	m_transparentWaterDepth = 3.0f;
	m_minWaterOpacity = 1.0f;
	m_standingWaterColor.red = 1.0f;
	m_standingWaterColor.green = 1.0f;
	m_standingWaterColor.blue = 1.0f;
	m_radarColor.red = 140;
	m_radarColor.green = 140;
	m_radarColor.blue = 255;
	m_standingWaterTexture.set("TWWater01.tga");
	m_riverTransparencyMultiplier = 1.0f;
	m_unk4C = 50.0f;
	m_additiveBlend = false;
	m_unk50 = false;
	m_unk54 = 0.0f;
	m_unk58 = 0.0f;
}

// Slot 1 of the setting table is the shared empty return at 0x000B3FD0.
// ?WaterTransparencySetting::slot1 present-unmatched
void WaterTransparencySetting::slot1()
{
}
