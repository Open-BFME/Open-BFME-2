// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?rva005EBDBF@Rva005EB8D6@@QAE_NPAX@Z @0x005EBDBF 600B (thiscall ret 4).
// WorldBuilder 0x015E8FD0 StrategicConflictResults::Impl::SetCurrentBattle
// (StrategicConflictResults.cpp:347 assert compiled out); the pinned
// address-derived spelling keeps the constructor's class name (ctor
// 0x005EB9F2 in StrategicConflictResultsImplCtor.cpp and dtor 0x005EB8D6).
// Stores the battle at +0x0C and runs the rowed CalcPlayerRemap 0x005EBCCE
// then for every army of every side (side count from the battle's 28-byte
// side vector +0x18/+0x1C; per-side army count rowed 0x003F4DAE) reads the
// army's result record (rowed 0x003F46F2: player +0 then veterancy lost
// destroyed and heroes-lost counts) and the remapped player index from the
// +0x44 int map (key side*10000+army) and publishes the player's name (or
// L"Unknown") the four counts (L"%d") through the Apt window manager's
// rowed bfmeSetText 0x00225301 and the player's faction name (+0x40 then
// +0x20) into the +0x28 list (rowed 0x00524767). Literals copied from
// retail including its "Destoyed" spelling.
#include "ascii_string.h"
#include "unicode_string.h"

namespace _STL
{
template <class T> struct less;
template <class T> class allocator;
template <class T1, class T2> struct pair;
template <class K, class V, class C = less<K>, class A = allocator<pair<const K, V> > >
class map
{
public:
	V &operator[](const K &key);
private:
	char m_impl[0xC];
};
}

class StrategicConflictResults
{
public:
	class Impl;
};
class StrategicConflictResults::Impl
{
public:
	void CalcPlayerRemap();
};

class Rva003F468D
{
public:
	int rva003F4DAE(int side);
};

struct StrategicBattleSideView
{
	char m_bytes[0x1C];
};

struct StrategicBattleSideVector
{
	int size() const { return m_end - m_begin; }
	StrategicBattleSideView *m_begin;
	StrategicBattleSideView *m_end;
	StrategicBattleSideView *m_capacity;
};

class LivingWorldBattle
{
public:
	int *rva003F46F2(int side, int army);
	int getSideCount() const { return m_sides.size(); }
private:
	char m_pad00[0x18];
	StrategicBattleSideVector m_sides; // +0x18
};

struct StrategicFactionView
{
	char m_pad00[0x20];
	AsciiString m_name; // +0x20
};

struct StrategicPlayerView
{
	char m_pad00[0x1C];
	UnicodeString m_displayName;     // +0x1C
	char m_pad20[0x40 - 0x20];
	StrategicFactionView *m_faction; // +0x40
};

// The army result record answered by 0x003F46F2.
struct StrategicArmyResultView
{
	StrategicPlayerView *m_player; // +0
	int m_veterancy;               // +4
	int m_lost;                    // +8
	int m_destroyed;               // +0xC
	int m_heroesLost;              // +0x10
};

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &name, const UnicodeString &text, bool number);
};
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class Rva00524306
{
public:
	void rva00524767(const AsciiString &name, const AsciiString &value);
};

class Rva005EB8D6
{
public:
	bool rva005EBDBF(void *battle);
private:
	static int getPlayerKey(int side, int army) { return side * 10000 + army; }

	char m_pad00[0x0C];
	LivingWorldBattle *m_battle;         // +0x0C
	char m_pad10[0x28 - 0x10];
	Rva00524306 m_factions;              // +0x28
	char m_pad29[0x44 - 0x29];
	_STL::map<int, int> m_playerRemap;   // +0x44
};

bool Rva005EB8D6::rva005EBDBF(void *battle)
{
	m_battle = (LivingWorldBattle *)battle;
	reinterpret_cast<StrategicConflictResults::Impl *>(this)->CalcPlayerRemap();

	AsciiString label;
	for (int side = 0; side < m_battle->getSideCount(); ++side)
	{
		int count = reinterpret_cast<Rva003F468D *>(m_battle)->rva003F4DAE(side);
		for (int army = 0; army < count; ++army)
		{
			StrategicArmyResultView *result = (StrategicArmyResultView *)m_battle->rva003F46F2(side, army);
			int player = m_playerRemap[getPlayerKey(side, army)];
			UnicodeString text;

			label.format("APT:Player_%d_Name_String", player);
			if (result->m_player)
				g_bfmeAptWindowManager->bfmeSetText(label, result->m_player->m_displayName, false);
			else
				g_bfmeAptWindowManager->bfmeSetText(label, UnicodeString(L"Unknown"), false);

			label.format("APT:Player_%d_Destoyed_String", player);
			text.format(L"%d", result->m_destroyed);
			g_bfmeAptWindowManager->bfmeSetText(label, text, true);

			label.format("APT:Player_%d_HeroLost_String", player);
			text.format(L"%d", result->m_heroesLost);
			g_bfmeAptWindowManager->bfmeSetText(label, text, true);

			label.format("APT:Player_%d_Lost_String", player);
			text.format(L"%d", result->m_lost);
			g_bfmeAptWindowManager->bfmeSetText(label, text, true);

			label.format("APT:Player_%d_Veterancy_String", player);
			text.format(L"%d", result->m_veterancy);
			g_bfmeAptWindowManager->bfmeSetText(label, text, true);

			StrategicFactionView *faction = result->m_player->m_faction;
			label.format("StrategicConflictResults::PlayerFaction_%d", player);
			m_factions.rva00524767(label, faction->m_name);
		}
	}
	return true;
}
