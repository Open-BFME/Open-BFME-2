// cl: /O1 /arch:SSE /MD /DNDEBUG
//
// ??0GiantBirdSlowDeathBehaviorModuleData@@QAE@XZ, retail 0x00461F7F,
// 110 bytes. Derived ModuleData ctor over table 0xC42D08 (FXHitGround@?,
// OCLHitGround@?, DelayFromGroundToFinalDeath@?, CrashAvoidKindOfs@?).
// Identity is the rowed poolkey 0x461EA0 (GiantBirdSlowDeathBehavior) just
// past the behavior ctor, plus factory 0x24B5D1 (news 0x1C4, sole caller)
// plus chained proc 0x461E3D (SlowDeath base 0x45E93F plus own table).
// Shape: opaque EMPTY SlowDeath base (EBO, declared-only ctor resolving to
// the pin at 0x45E386, contributes no size) plus flat derived members with
// explicit void*m_vtable (no virtuals, no vtable emission). Init-list holds
// only the vtable store so it lands between the implicit base call and the
// implicit member call; body assignments follow retail order (ands, zero,
// memset, floats, flag). The +0x19C member is constructed through the shared
// 0x1C helper pinned at 0x24C7B3 and then explicitly memcoded again, exactly
// as retail does; memset resolves to the rowed CRT import.

#include <string.h>

class SlowDeathBehaviorModuleData
{
public:
	SlowDeathBehaviorModuleData();
};

class Rva0024C7B3Member
{
public:
	Rva0024C7B3Member();
	unsigned char m_data[0x1C];
};

class GiantBirdSlowDeathBehaviorModuleData : public SlowDeathBehaviorModuleData
{
public:
	GiantBirdSlowDeathBehaviorModuleData();

private:
	const void *m_vtable; // +0 (EBO: base contributes no size)
	unsigned char m_pad[0x190 - 4]; // +4
	int m_unk190; // +0x190
	int m_unk194; // +0x194
	float m_unk198; // +0x198
	Rva0024C7B3Member m_unk19C; // +0x19C
	float m_unk1B8; // +0x1B8
	float m_unk1BC; // +0x1BC
	bool m_unk1C0; // +0x1C0
};

// ??0GiantBirdSlowDeathBehaviorModuleData@@QAE@XZ @0x461F7F
GiantBirdSlowDeathBehaviorModuleData::GiantBirdSlowDeathBehaviorModuleData()
	: m_vtable(reinterpret_cast<const void *>(0x00C42E98))
{
	m_unk190 = 0;
	m_unk194 = 0;
	m_unk198 = 0.0f;
	memset(&m_unk19C, 0, 0x1C);
	m_unk1B8 = 800.0f;
	m_unk1BC = 0.1f;
	m_unk1C0 = false;
}
