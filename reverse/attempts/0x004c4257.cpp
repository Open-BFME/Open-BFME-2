// ??0ScavengerSpecialPowerModuleData@@QAE@XZ
// partial score=0.6 date=2026-09-21
// cl: /O1 /MD /GX /Oy- /DNDEBUG /DWIN32 /D_WINDOWS
// stlport
//
// ??0ScavengerSpecialPowerModuleData@@QAE@XZ, retail 0x004C4257, 117 bytes.
// V1a: Devastate-V5 plus LevelGrant recipe — the pinned SpecialPower base
// (declared-only virtual dtor, the sole unwindable) arms the EH frame;
// the member bitset resets through the rowed bitset<128>::reset at
// 0x24CA24; the two strings clear through the rowed 0x36410 fold with no
// declared dtor (so no state 1); the derived vtable resolves through the
// ??_7 pin at 0xC5D1F0; memset clears the bitset word range.

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
	void clear();

private:
	char *m_text;
};

class ScavengerSpecialPowerModuleData : public Rva004930A0
{
public:
	ScavengerSpecialPowerModuleData();
	virtual ~ScavengerSpecialPowerModuleData();

private:
	unsigned long m_toggleBits[4]; // +0x7C
	int m_sleepFrameA; // +0x8C
	int m_sleepFrameB; // +0x90
	AsciiString m_nameA; // +0x94
	AsciiString m_nameB; // +0x98
};

// ??0ScavengerSpecialPowerModuleData@@QAE@XZ @0x4C4257
ScavengerSpecialPowerModuleData::ScavengerSpecialPowerModuleData()
{
	((_STL::bitset<128> *)m_toggleBits)->reset();
	m_sleepFrameA = 0;
	m_sleepFrameB = 0;
	memset(m_toggleBits, 0, 0x10);
	m_nameA.clear();
	m_nameB.clear();
}
