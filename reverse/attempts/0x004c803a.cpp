// ??0PlayerHealSpecialPowerModuleData@@QAE@XZ
// partial score=0.98 date=2026-09-21
// cl: /O1 /MD /DNDEBUG /arch:SSE
// stlport

// ??0PlayerHealSpecialPowerModuleData@@QAE@XZ, retail 0x004C803A, 91 bytes.
// SpecialPower-side ModuleData for the PlayerHeal power. The rowed base-call
// buildFieldParse proc at 0x4C7E63 (on the rowed SpecialPower base 0x493207)
// owns the six-entry INI table at 0x00C5E298 (HealAmount at +0x7C,
// HealAsPercent at +0x80, HealRadius at +0x84, HealAffects at +0x88,
// HealFX at +0xA4, HealOCL at +0xA8), which sizes the class at 0xAC bytes
// over the pinned 0x7C-byte Rva004930A0 base. The rowed PlayerHealSpecialPower
// pool key plus the BFME1 PlayerHealSpecialPower files prove the name.
// Shape: empty (EBO) base plus init-listed vtable store and filter member, so
// the init call setups (lea edi plus mov ecx) hoist above the vtable store
// while the member call itself stays ordered after it, reproducing retail's
// base, setup, vtable, member-call sequence with no new pins. HealRadius
// defaults to the shared 100.0f constant at 0x00BC292C (CloudBreak precedent:
// TU-local extern float); the 0x1C memset over the filter reuses the CRT
// import thunk. Flat classes with no declared dtors keep the body frameless.

#include <string.h>

extern float g_healRadiusDefault; // 0x00BC292C, 100.0f

class Rva004930A0
{
public:
	Rva004930A0();
};

class Rva0024C7B3Member
{
public:
	Rva0024C7B3Member();

	unsigned char m_data[0x1C];
};

class PlayerHealSpecialPowerModuleData : public Rva004930A0
{
public:
	PlayerHealSpecialPowerModuleData();

private:
	const void *m_vtable;				// +0x00
	unsigned char m_pad04[0x7C - 4];	// +0x04
	float m_healAmount;					// +0x7C
	unsigned char m_healAsPercent;		// +0x80
	unsigned char m_pad81[3];			// +0x81
	float m_healRadius;					// +0x84
	Rva0024C7B3Member m_filter;			// +0x88
	void *m_healFX;						// +0xA4
	void *m_healOCL;					// +0xA8
};

// ??0PlayerHealSpecialPowerModuleData@@QAE@XZ @0x4C803A
PlayerHealSpecialPowerModuleData::PlayerHealSpecialPowerModuleData()
	: Rva004930A0()
	, m_vtable(reinterpret_cast<const void *>(0x00C5E7A8))
	, m_filter()
{
	m_healAmount = 0.0f;
	m_healRadius = g_healRadiusDefault;
	m_healAsPercent = 1;
	memset(&m_filter, 0, 0x1C);
	m_healFX = 0;
	m_healOCL = 0;
}
