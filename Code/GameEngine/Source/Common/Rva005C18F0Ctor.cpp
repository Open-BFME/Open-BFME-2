// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs
#include "unicode_string.h"

// ??0Rva005C18F0@@QAE@XZ, RVA 0x005C1896, 62B. Unlock lane: default ctor
// storing g_00E06034 at +4 via the base, constructing the member at +8
// through rowed ??0StrategicStatsPreferences@@QAE@ABVUnicodeString@@@Z at
// 0x00537DBC with UnicodeString::TheEmptyString, storing vtable 0x008743C4
// under EH state 0. Base carries the scalar so its store lands before the
// derived EH state and vtable. Caller at 0x005C19FD in 0x005C19B6. Flags
// copy Rva005C18F0Dtor.cpp with the shared ascii shim first.
// The two rank-point tables (RankPointValue.cpp's Rva00559AC1, int m_vals[11], 44 bytes each).
// g_00E06034 at VA 0x00E06034 is the strategic one, built by the initializer 0x007B3DD2
// (0x00559A76 with 1); the real-time one at VA 0x00E06060 is Rva007ABEF3ArgCtorInits.cpp's
// g_rva005C1A8DDefault (P132). A 100-byte char array here once spanned both.
class Rva00559AC1
{
public:
	Rva00559AC1 *rva00559A76(int a);
private:
	int m_vals[11];
};
Rva00559AC1 g_00E06034;
extern Rva00559AC1 g_rva005C1A8DDefault;

class StrategicStatsPreferences
{
public:
	StrategicStatsPreferences(const UnicodeString &);
private:
	char m_pad[4];
};

class Rva005DDE01;
class UserPreferences;

// Retail table 0x008743B8 (3 slots): the deleting destructor 0x005C1879 and two
// pure slots (__purecall 0x0003B810) that both derived tables fill.
class Rva005C1860
{
public:
	Rva005C1860(char *tag=(char *)&g_00E06034) : m_04(tag) {}
	virtual ~Rva005C1860() {}
	virtual void slot1(Rva005DDE01 *table) = 0;
	virtual UserPreferences *slot2() = 0;
protected:
	char *m_04;
};

// Retail table 0x008743C4: [0x005C18D4, 0x005C2603, 0x005C4AD5].
class Rva005C18F0 : public Rva005C1860
{
public:
	Rva005C18F0();
	virtual ~Rva005C18F0();
	virtual void slot1(Rva005DDE01 *table);
	virtual UserPreferences *slot2();
private:
	StrategicStatsPreferences m_08;
};

Rva005C18F0::Rva005C18F0()
	: m_08(UnicodeString::TheEmptyString)
{
}

// Slot 2 returns the embedded preferences (+8); retail folds this 4-byte body
// (lea eax,[ecx+8]; ret) with its sibling's at 0x005C4AD5. This unit's
// preferences view is opaque, so the UserPreferences base (at offset 0 of the
// ProfilePreferences-derived member) is reached by a view cast.
UserPreferences *Rva005C18F0::slot2()
{
	return reinterpret_cast<UserPreferences *>(&m_08);
}

// Native5C1926..5C1964: constructor used by Rva005C1A36 at5C19FD.
// Its rowed destructor5C1980 and scalar5C1964 own vtableC743D0;
// +4 points at the real-time rank table, VA 0x00E06060 (retail 0x009C1937 stores it).
class RealTimeStatsPreferences { public: RealTimeStatsPreferences(const UnicodeString &); private: char m_storage[4]; };
// Retail table 0x008743D0: [0x005C1964, 0x005C1BDE, 0x005C4AD5].
class Rva005C1980 : public Rva005C1860 { public: Rva005C1980(); virtual ~Rva005C1980(); virtual void slot1(Rva005DDE01 *table); virtual UserPreferences *slot2(); private: RealTimeStatsPreferences m_08; };
Rva005C1980::Rva005C1980() : Rva005C1860((char *)&g_rva005C1A8DDefault), m_08(UnicodeString::TheEmptyString) { }

// Same folded 4-byte body as Rva005C18F0::slot2 (0x005C4AD5).
UserPreferences *Rva005C1980::slot2()
{
	return reinterpret_cast<UserPreferences *>(&m_08);
}
