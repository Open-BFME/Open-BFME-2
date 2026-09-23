// ??0RadiateFearUpdateModuleData@@QAE@XZ
// partial score=0.97 date=2026-09-23
// cl: /O1 /arch:SSE /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0RadiateFearUpdateModuleData@@QAE@XZ, retail 0x0049C06C, 120 bytes.
// Radiate-fear data over own INI table 0x00C510B8 (InitiallyActive,
// WhichSpecialPower, GenerateTerror, GenerateFear,
// GenerateUncontrollableFear, EmotionPulseRadius, EmotionPulseInterval,
// VictimFilter; offsets read from the retail table; factory 0x24E6E8
// news 0x130). InitiallyActive at +8 is false; WhichSpecialPower at +0xC
// defaults to all via an inline or-minus-1 ctor; GenerateTerror at +0x10,
// GenerateFear at +0x11 and GenerateUncontrollableFear at +0x12 are
// false; EmotionPulseRadius at +0x14 nulls as float; EmotionPulseInterval
// at +0x18 nulls; VictimFilter at +0x1C builds in place through the
// pinned member ctor at 0x3623E5 while the +0x20 filter builds through
// the pinned member construct at 0x25342C plus a 28B FixedStorage temp
// from 0x00DFEFA4 applied through the pinned applyFilter at 0x362120.
// Row supersedes the ctor pin. Shape follows CallHelpOnDamageModuleData
// (or-first mask forces the vtable into the body). Both filters build
// through their pinned construct methods; the +0x20 member carries the
// sole EH state.
//
// WALL (4B, 116/120): the retail byte-1 EH state before the second
// construct has no clean source (same wall as CallHelpOnDamage 0.97:
// placement earns it with guard baggage, everything else earns nothing).
// t=45.

#include <cstring>

struct SpecialPowerMask
{
	SpecialPowerMask()
	{
		m_mask |= -1;
	}

	unsigned int m_mask;
};

class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other);
	~BfmeFixedStorage0004543D() {}

private:
	unsigned char m_bytes[28];
};

class Rva0025342CMember
{
public:
	Rva0025342CMember *construct();
	~Rva0025342CMember();

private:
	int m_x;
};

Rva0025342CMember::~Rva0025342CMember()
{
	m_x = 0;
}

class Rva003623E5Filter
{
public:
	Rva003623E5Filter *construct();
	void applyFilter(BfmeFixedStorage0004543D storage);

private:
	int m_handle;
};

class RadiateFearUpdateModuleData
{
public:
	RadiateFearUpdateModuleData();

private:
	void *m_vtable; // +0
	int m_gap04; // +4
	bool m_initiallyActive; // +8, InitiallyActive
	unsigned char m_pad09[3]; // +9
	SpecialPowerMask m_whichSpecialPower; // +0xC, WhichSpecialPower
	bool m_generateTerror; // +0x10, GenerateTerror
	bool m_generateFear; // +0x11, GenerateFear
	bool m_generateUncontrollableFear; // +0x12, GenerateUncontrollableFear
	unsigned char m_pad13; // +0x13
	float m_emotionPulseRadius; // +0x14, EmotionPulseRadius
	int m_emotionPulseInterval; // +0x18, EmotionPulseInterval
	Rva003623E5Filter m_victimFilter; // +0x1C, VictimFilter
	Rva0025342CMember m_secondFilter; // +0x20 (filter via pinned construct)
	unsigned char m_pad24[0x130 - 0x24]; // +0x24 (factory news 0x130)
};

// ??0RadiateFearUpdateModuleData@@QAE@XZ @0x0049C06C
RadiateFearUpdateModuleData::RadiateFearUpdateModuleData()
	: m_whichSpecialPower()
{
	m_vtable = reinterpret_cast<void *>(0x00C50FF0);
	m_initiallyActive = false;
	m_generateTerror = false;
	m_generateFear = false;
	m_generateUncontrollableFear = false;
	m_emotionPulseRadius = 0.0f;
	m_emotionPulseInterval = 0;
	m_victimFilter.construct();
	m_secondFilter.construct();
	m_victimFilter.applyFilter(
		BfmeFixedStorage0004543D(*reinterpret_cast<const BfmeFixedStorage0004543D *>(0x00DFEFA4)));
}
