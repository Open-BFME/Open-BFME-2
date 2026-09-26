// cl: /O1 /GX /arch:SSE /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??1ToggleMountedSpecialAbilityUpdateModuleData@@UAE@XZ, retail 0x004AE10B, 74 bytes.
// Dtor over ctor TU layout (vtable 0x00855220, base Rva0044EB54 0xC8 opaque,
// OpacityTarget@C8 TriggerInstantly@CC CancelDisguise@CD MountedTemplate@D0
// SynchronizeTimer@D4; factory 0x24F6C5 news 0xE0 table 0x00BEF770). Destroys
// vector<AsciiString> at +0xD4 via rowed 0x0002CC70 (state 1) then
// StringBase<char> at +0xD0 via pinned 0x00036410 (state 0) then base
// DamageModuleBase via pinned 0x0044ECCE (state -1). Shape follows
// GiveOrRestoreUpgradeSpecialPowerModuleDataDtor (74B strings plus
// DamageModuleBase) with StealthUpdateModuleDataDtor vector precedent
// (novtable derived plus virtual base, empty body, no entry store).
// Caller is slot-0 ??_G at 0x004AE0EF (vtable 0x00855220).
#include <vector>

template<typename T> class StringBase
{
public:
	~StringBase();

private:
	void *m_data;
};

class DamageModuleBase
{
public:
	virtual ~DamageModuleBase();

private:
	unsigned char m_pad[0xC8 - 4];
};

class AsciiString
{
public:
	~AsciiString();

private:
	void *m_data;
};

class __declspec(novtable) ToggleMountedSpecialAbilityUpdateModuleData : public DamageModuleBase
{
public:
	virtual ~ToggleMountedSpecialAbilityUpdateModuleData();

private:
	float m_opacityTarget;
	bool m_triggerInstantlyOnCreate;
	bool m_cancelDisguiseWhenDismounting;
	unsigned char m_padCE[2];
	StringBase<char> m_mountedTemplate;
	_STL::vector<AsciiString> m_synchronizeTimer;
};

ToggleMountedSpecialAbilityUpdateModuleData::~ToggleMountedSpecialAbilityUpdateModuleData()
{
}
