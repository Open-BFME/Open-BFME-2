// cl: /Ireference/shims/bfme2_ascii /O1 /GX /arch:SSE /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// Rva0044ECCE is an address-derived base stand-in; its target class name is unproven.
// stlport
//
// ??1ToggleMountedSpecialAbilityUpdateModuleData@@UAE@XZ, retail 0x004AE10B, 74 bytes.
// Dtor over ctor TU layout (vtable 0x00855220, base SpecialAbilityUpdateModuleData 0xC8 opaque,
// OpacityTarget@C8 TriggerInstantly@CC CancelDisguise@CD MountedTemplate@D0
// SynchronizeTimer@D4; factory 0x24F6C5 news 0xE0 table 0x00BEF770). Destroys
// vector<AsciiString> at +0xD4 via rowed 0x0002CC70 (state 1) then
// AsciiString at +0xD0 via pinned 0x00036410 (state 0, releaseBuffer fold;
// AsciiString/StringBase pins share the address) then base
// Rva0044ECCE via pinned 0x0044ECCE (state -1). Shape follows
// GiveOrRestoreUpgradeSpecialPowerModuleDataDtor (74B strings plus
// Rva0044ECCE) with StealthUpdateModuleDataDtor vector precedent
// (novtable derived plus virtual base, empty body, no entry store).
// Caller is slot-0 ??_G at 0x004AE0EF (vtable 0x00855220).
// Uses the shared ascii_string.h so the emitted ??_GAsciiString copy calls
// releaseBuffer like the kept WOLBuddyOverlay copy (LINK-COMDAT).
#include <vector>

class Rva0044ECCE
{
public:
	virtual ~Rva0044ECCE();

private:
	unsigned char m_pad[0xC8 - 4];
};

#include "ascii_string.h"

class __declspec(novtable) ToggleMountedSpecialAbilityUpdateModuleData : public Rva0044ECCE
{
public:
	virtual ~ToggleMountedSpecialAbilityUpdateModuleData();

private:
	float m_opacityTarget;
	bool m_triggerInstantlyOnCreate;
	bool m_cancelDisguiseWhenDismounting;
	unsigned char m_padCE[2];
	AsciiString m_mountedTemplate;
	_STL::vector<AsciiString> m_synchronizeTimer;
};

ToggleMountedSpecialAbilityUpdateModuleData::~ToggleMountedSpecialAbilityUpdateModuleData()
{
}
