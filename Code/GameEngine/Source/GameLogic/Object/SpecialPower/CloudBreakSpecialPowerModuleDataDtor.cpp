// cl: /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS /Ireference/shims/bfme2_ascii
//
// ??1CloudBreakSpecialPowerModuleData@@UAE@XZ, retail 0x004C47F3, 56 bytes.
// CloudBreakSpecialPower ModuleData dtor (ctor rowed at 0x004C479A in
// CloudBreakSpecialPowerModuleDataCtor.cpp, vtable 0x00C5D468 with slot 0
// ??_G at 0x004C47D7). Destroys the AsciiString member at +0x84 through the
// pinned 0x00036410 body, then the SpecialPowerModuleData base through the rowed
// 0x0049334F body. Layout follows the ctor TU (0x7C base plus float at
// +0x7C plus CloudBreakFX at +0x80 plus SunbeamObject string at +0x84 plus
// float at +0x88, total 0x8C matching the factory news). novtable suppresses
// the derived vtable store retail lacks (Invisibility precedent); the base
// call restores the base table.

// The canonical frozen StringBase replaces the private copy; the switch
// declares the narrow destructor, which resolves to the rowed teardown.
#define BFME_STRINGBASE_PUBLIC_DTOR
#include "string_base.h"

class SpecialPowerModuleData
{
public:
	virtual ~SpecialPowerModuleData();

private:
	unsigned char m_pad[0x7C - 4];
};

class __declspec(novtable) CloudBreakSpecialPowerModuleData : public SpecialPowerModuleData
{
public:
	virtual ~CloudBreakSpecialPowerModuleData();

private:
	float m_cloudBreakRadius; // +0x7C
	void *m_cloudBreakFX; // +0x80
	StringBase<char> m_sunbeamObject; // +0x84
	float m_objectSpacing; // +0x88
};

CloudBreakSpecialPowerModuleData::~CloudBreakSpecialPowerModuleData()
{
}
