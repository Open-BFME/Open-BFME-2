// cl: /O1 /MD /GX /Oy- /DNDEBUG /DWIN32 /D_WINDOWS
// Identity: ModuleFactory registers this data class under "WeaponChangeSpecialPowerModule" (addModule
// pairs the name with this factory); formerly misnamed ScavengerSpecialPowerModuleData.
// stlport
//
// ??0WeaponChangeSpecialPowerModuleData@@QAE@XZ, retail 0x004C4257 (123 bytes).
// SpecialPower-side ModuleData for the Scavenger (toggle) power. The table
// at 0x00C5D0F0 (FlagsUsedForToggle at +0x7C plus ToggleOnSleepFrames at
// +0x8C plus ToggleOffSleepFrames at +0x90 plus ToggleOnAttributeModifier at
// +0x94 plus ToggleOffAttributeModifier at +0x98) sizes the class at 0x9C
// bytes over the 0x7C-byte SpecialPower base built by the out-of-line
// 0x004930A0 constructor (pinned as Rva004930A0). The Scavenger pool key at
// 0x4C4387 plus the name getter at 0x4C4381 sit in the same cluster and the
// factory at 0x251D40 is rowed. The toggle words live in a TU-local member
// type whose inline construction runs the rowed bitset<128>::reset at
// 0x24CA24 over them. That reset call sits inside init so its setup hoists
// above the compiler-emitted vtable store (Devastate precedent) which is
// what orders the head as xor plus lea plus state plus vtable plus call.
// Every member init lives in the init-list in retail order (toggle plus
// sleep zeros plus inline string zeros) so the body holds only the memset
// through the CRT import plus the two clears through the rowed 0x36410
// fold. The base declared-only dtor arms state 0 and the two string
// declared-only dtors advance the second store to state 2 with state 1
// folded away. The nameA zero reuses the ebx zero through edi while the
// nameB zero is the direct and-imm idiom.

#include <bitset>
#include <string.h>

namespace _STL {
template<> bitset<128> &bitset<128>::reset();
}

class Rva004930A0
{
public:
	Rva004930A0();
	virtual ~Rva004930A0();

private:
	unsigned char m_pad[0x7C - 4];
};

class AsciiString
{
public:
	AsciiString() : m_text(0) {}
	~AsciiString();
	void clear();

	char *m_text;
};

struct ToggleFlags
{
	unsigned long m_words[4];
	ToggleFlags() { ((_STL::bitset<128> *)m_words)->reset(); }
};

class WeaponChangeSpecialPowerModuleData : public Rva004930A0
{
public:
	WeaponChangeSpecialPowerModuleData();
	virtual ~WeaponChangeSpecialPowerModuleData();

private:
	ToggleFlags m_toggle; // +0x7C
	int m_sleepFrameA; // +0x8C
	int m_sleepFrameB; // +0x90
	AsciiString m_nameA; // +0x94
	AsciiString m_nameB; // +0x98
};

// ??0WeaponChangeSpecialPowerModuleData@@QAE@XZ @0x4C4257
WeaponChangeSpecialPowerModuleData::WeaponChangeSpecialPowerModuleData()
	: m_toggle(), m_sleepFrameA(0), m_sleepFrameB(0), m_nameA(), m_nameB()
{
	memset(m_toggle.m_words, 0, 0x10);
	m_nameA.clear();
	m_nameB.clear();
}
