// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// stlport
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsPlayerMask.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus
// /O1). Compiled that way each body below places uniquely on unclaimed
// game.dat .text by masked whole-.text search, and ./build.sh reproduces it
// byte for byte: ScriptConditions::evaluatePlayerDestroyedNOrMoreBuildings
// 0x003E4810 (80B). Callee addresses are read off retail's call sites
// (reverse/symbols.csv). Only the placed bodies are carried; the donor's other
// definitions are omitted.

// Every ScriptConditions condition that resolves a player parameter to a mask
// of players and then asks each of them one question:
//
//   0x00322530  evaluatePlayerHasCredits                   money
//   0x00322780  evaluateNamedOwnedByPlayer                 a named unit's owner
//   0x003230C0  evaluatePlayerHasComparisonPercentPower    power supply ratio
//   0x003232D0  evaluatePlayerDestroyedNOrMoreBuildings    (never finished)
//   0x00323D50  evaluatePlayerCompareLightPoints           light points
//   0x00328590  evaluatePlayerHasNOrFewerFactionBuildings  faction buildings
//   0x00329160  evaluateSkirmishPlayerIsFaction            the player's side
//   0x003297F0  evaluatePlayerHasKilledKindOfUnits         kills of a KindOf
//
// All of them open the same way -- a mask out of the resolver at 0x0034DB40,
// then PlayerList::getEachPlayerFromMask consuming it one player at a time --
// and differ only in what they read off each player and how they compare it.
//
// They sat in five files, and the shared pair of callees appeared in them
// under four different names: the resolver as both unidentified_0034DB40 on
// ScriptEngine and bfmeNext1087 on a "BfmeP1087", the iterator as both
// getEachPlayerFromMask on PlayerList and bfmeLook1087 on a "BfmeD1087". The
// two Bfme classes were not other objects: g_bfmeP1087 is TheScriptEngine
// (0x00EF076C) and g_bfmeD1087 is ThePlayerList (0x00EED748), the same two
// globals under placeholder names. Named once, the family is visible.
//
// The Player they iterate had drifted the same way -- empty in two files, a
// "BfmeR1087" with a float at +0xA4 in a third, a 0x348 prefix before the
// kills in a fourth. One layout states all of it: the power supply at +0xA4
// and the kill counters at +0x348.
//
// The owner check and the faction check joined later, out of two more files,
// and brought two more spellings of the same things. Their Player was empty in
// one and a side string at +0x28 in the other; the side now sits in the one
// layout with the rest. Their Parameter disagreed outright: the owner file
// declared its string at +0x00 -- so that getString() would compile to nothing
// and the raw Parameter pointer would be what got pushed -- against +0x10
// everywhere else in ScriptConditions. The +0x10 layout is what retail has;
// the two call sites cast instead, and the body still byte-matches, which is
// how the +0x00 claim is shown to have been a fiction.
//
// unidentified_0034DB40 keeps its address-derived name: it forwards to
// TheScriptEngine's virtual at +0x4C and no identity has been proven for it.
// It appears here under both of its overloads on purpose, because they are not
// the same call: the AsciiString one is the ILT thunk at 0x000230B5, which is
// the route the owner check takes, while the Parameter one is the body at
// 0x0034DB40 that ScriptEngineGetPlayerMaskFromParameter.cpp defines. Spelling
// either call the other way moves the call target. The same is true of the
// light-point reader, which is still reached through the thunk at 0x00047D34
// rather than by name.

#include "ascii_string.h"
#include <bitset>

typedef bool Bool;
typedef unsigned short PlayerMaskType;
typedef unsigned int UnsignedInt;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
template <int NUMBITS>
class BitFlags
{
public:
	enum BogusInitType
	{
		kInit = 0
	};

	BitFlags(void) {}
	BitFlags(BogusInitType, int idx) { m_bits._Unchecked_set((size_t)idx); }
	BitFlags(BogusInitType, int idx1, int idx2)
	{
		m_bits._Unchecked_set(idx1);
		m_bits._Unchecked_set(idx2);
	}

	void clear(void) { m_bits.reset(); }
	void set(int idx) { m_bits._Unchecked_set((size_t)idx); }

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<192> KindOfMaskType;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Parameter
{
public:
	int getInt(void) const { return m_int; }
	const AsciiString &getString(void) const { return m_string; }

private:
	unsigned char m_beforeInt[8];
	int m_int;						// this+0x08
	float m_real;
	AsciiString m_string;					// this+0x10
};

// The power supply ratio at retail 0x000C7DE0; still an address-derived name.
class Gen_000C7DE0
{
public:
	float bfmeRatio(void) const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class PlayerKills
{
public:
	int getKillsOfKindOf(KindOfMaskType setMask, KindOfMaskType clearMask);	// retail 0x00036D72
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Money.h
class Money
{
public:
	virtual void unused();

	UnsignedInt countMoney() const { return m_money; }

private:
	UnsignedInt m_money;
	int m_playerIndex;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	int countObjects(KindOfMaskType setMask, KindOfMaskType clearMask);	// retail 0x0001FF1E
	int rva000D4730CountObjects( UnsignedInt bitIndex, int limit ) const;
	Money *getMoney() { return &m_money; }
	const AsciiString &getSide() const { return m_side; }

	unsigned char m_beforeSide[0x28];
	AsciiString m_side;					// this+0x28
	unsigned char m_beforeMoney[0x48 - 0x28 - sizeof(AsciiString)];
	Money m_money;						// this+0x48
	unsigned char m_beforeEnergy[0xA4 - 0x48 - sizeof(Money)];
	Gen_000C7DE0 m_energy;					// this+0xA4
	unsigned char m_beforeKills[0x348 - 0xA4 - sizeof(Gen_000C7DE0)];
	PlayerKills m_kills;					// this+0x348
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerList.h
class PlayerList
{
public:
	Player *getEachPlayerFromMask(PlayerMaskType &mask);	// retail 0x000DF4A0 via ILT 0x0002EE60
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Player *getControllingPlayer(void) const;		///< ILT thunk at 0x00020824
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual Object *getUnitNamed(const AsciiString &name) = 0;	// slot 26, vtable+0x68

	PlayerMaskType unidentified_0034DB40(Parameter *playerParm);	///< body at 0x0034DB40
	PlayerMaskType unidentified_0034DB40(const AsciiString &name);	///< ILT thunk at 0x000230B5
};

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;
extern const KindOfMaskType KINDOFMASK_NONE;
extern void j_00047d34();
int bfmeLookup_001c62b0( void *name );

class BfmeP1087
{
public:
	PlayerMaskType bfmeNext1087( Parameter *parameter );
};

// Retail spells the singleton at 0x012F076C TheScriptEngine (declared above);
// BfmeP1087 is this TU's view of the reviewed player-mask thunk, so it is cast
// at the use instead of being a second name for the global.

// The per-player light-point reader is only known as the thunk at 0x00047D34,
// so it is called through the thunk's address rather than by name.
class PlayerLightPoints
{
};


// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptConditions.h
class ScriptConditions
{
protected:
	Bool evaluatePlayerHasCredits(Parameter *, Parameter *, Parameter *);
	Bool evaluatePlayerHasComparisonPercentPower(Parameter *, Parameter *, Parameter *);
	Bool evaluatePlayerDestroyedNOrMoreBuildings(Parameter *, Parameter *, Parameter *);
	Bool evaluatePlayerCompareLightPoints(Parameter *, Parameter *, Parameter *);
	Bool evaluatePlayerHasNOrFewerFactionBuildings(Parameter *, Parameter *);
	Bool evaluatePlayerHasKilledKindOfUnits(Parameter *, Parameter *, Parameter *);
	Bool evaluatePlayerHasNumberObjectsWithModelCondition(
		Parameter *, Parameter *, Parameter *, Parameter *);
	Bool evaluateNamedOwnedByPlayer(Parameter *, Parameter *);
	Bool evaluateSkirmishPlayerIsFaction(Parameter *, Parameter *);
};


// ?evaluatePlayerDestroyedNOrMoreBuildings@ScriptConditions@@IAE_NPAVParameter@@00@Z
Bool ScriptConditions::evaluatePlayerDestroyedNOrMoreBuildings(
	Parameter *playerParm, Parameter *, Parameter *opponentParm)
{
	PlayerMaskType playerMask = TheScriptEngine->unidentified_0034DB40(playerParm);
	Player *player = ThePlayerList->getEachPlayerFromMask(playerMask);
	PlayerMaskType opponentMask = TheScriptEngine->unidentified_0034DB40(opponentParm);
	Player *opponent = ThePlayerList->getEachPlayerFromMask(opponentMask);
	if (!player || !opponent) {
		return false;
	}

	return false;
}


