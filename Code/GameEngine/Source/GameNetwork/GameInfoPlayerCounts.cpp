// cl: /O1 /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport

// GameInfo player-count file-unit plus the two GameSlot predicates the
// counts call through. BFME1 GameNetwork/GameInfo.cpp donor shapes, with two
// BFME2 deltas proven by retail bytes: the human slot state moved 5 -> 6 for
// a new fifth state that rides with the AI states, and isOccupied() also
// requires the occupancy byte at +0x1A4. The predicates must live in this TU
// with the counters: same-TU visibility into isOccupied's definition is what
// lets the counters keep the slot pointer in EDX across the call with the
// count/limit in EDI/ESI (calling the pin as an opaque extern instead spills
// the pointer to ESI and the count to EBX).
//
// ?isHeroDataReadyForSlot@GameInfo@@QBE_NG@Z @0x003FF496 62B: false only when the slot
// at the given index is occupied, its +0x50 dword is set and the +0x64 block
// it guards with the +0x60 byte is absent; true otherwise (including an
// out-of-range index). The same same-TU visibility of isOccupied keeps the
// slot pointer in ECX across that call. The +0x50/+0x60/+0x64 fields are
// unidentified, hence the address name.

typedef int Int;

#include "ascii_string.h"
#include "unicode_string.h"
#include <string>

enum { MAX_SLOTS = 8 };

enum SlotState
{
	SLOT_OPEN = 0,
	SLOT_CLOSED = 1,
	SLOT_EASY_AI = 2,
	SLOT_MED_AI = 3,
	SLOT_BRUTAL_AI = 4,
	// Retail compares against state 5 alongside the AI states in both
	// isOccupied and isAI; ZH has no fifth state, so this BFME2 addition
	// keeps a mechanical name until its identity is proven.
	SLOT_AI_5 = 5,
	SLOT_PLAYER = 6
};

enum
{
	PLAYERTEMPLATE_RANDOM = -1,
	PLAYERTEMPLATE_OBSERVER = -2
};

unsigned char Rva0056BD91Pack(unsigned char a, unsigned char b,
	unsigned char c, unsigned char d);

void Rva0056BDA5Split(unsigned char a, unsigned char b, unsigned char c,
	unsigned char *out1, unsigned char *out2);

void __cdecl Rva00559FAC(int mode, void *rules);

class CreateAHeroData
{
public:
	unsigned char m_pad00[0x0C];
	int m_0c;
	int m_10;
};

class Rva0040A3F9
{
public:
	CreateAHeroData *rva0040A32F(int index);
};

struct OuterElem32
{
	char m_00[32];
};

struct Vec32
{
	OuterElem32 *m_start;
	OuterElem32 *m_finish;
	OuterElem32 *m_end;
};

class CreateAHeroManager
{
	char m_pad[0x14C];
public:
	Vec32 m_outer;
	int m_158;
public:
	Rva0040A3F9 *rva0021F797();
	int rva00219D52(unsigned int o);
};

extern CreateAHeroManager *TheCreateAHeroManager;

class MapMetaData
{
	char m_pad00[0x20];
public:
	Int m_numPlayers;               // +0x20
};

class MapCache
{
public:
	const MapMetaData *findMap(AsciiString mapName);
};

extern MapCache *TheMapCache;

// setState's connection record: the address dword and port word, both
// zeroed for a fresh slot.
struct GameSlotConnectInfo
{
	GameSlotConnectInfo() : m_ip(0), m_port(0) {}
	unsigned int m_ip;
	unsigned short m_port;
};

struct BfmeNetAddress
{
	bool Rva00248CBF(const BfmeNetAddress *other) const;
	unsigned int m_ip;
	unsigned short m_port;
};

class GameSlot
{
public:
	GameSlot();
	GameSlot(const GameSlot &);
	virtual ~GameSlot();
	virtual void reset();
	void setState(SlotState state, UnicodeString name, const GameSlotConnectInfo *connectInfo);
	bool isHuman() const { return m_state == SLOT_PLAYER; }
	bool isOccupied() const;
	bool isAI() const;
	Int rva003FF145(const BfmeNetAddress *other) const;
	bool isObserver() const;
	unsigned char encodeHero() const;
	bool decodeHero(unsigned char v);
	void rva003FF1A7(int v);
	bool isOpen() const { return m_state == SLOT_OPEN; }
	Int getState() const { return m_state; }
	bool isAccepted() const { return m_isAccepted; }
	bool hasMap() const { return m_hasMap; }
	Int getColor() const { return m_color; }
	Int getStartPos() const { return m_startPos; }
	Int getPlayerTemplate() const { return m_playerTemplate; }
	Int getTeamNumber() const { return m_teamNumber; }
	const UnicodeString &getName() const { return m_name; }
	Int rva20() const { return m_20; }
	Int rva40() const { return m_40; }

private:
	Int m_state;                    // +0x04
	bool m_isAccepted;              // +0x08
	bool m_hasMap;                  // +0x09
	bool m_isMuted;                 // +0x0A
	Int m_color;                    // +0x0C
	Int m_startPos;                 // +0x10
	Int m_14;                       // +0x14
	Int m_playerTemplate;           // +0x18
	Int m_teamNumber;               // +0x1C
	Int m_20;                       // +0x20
	Int m_origTriple[3];            // +0x24..+0x2F
	UnicodeString m_name;           // +0x30
	AsciiString m_34;               // +0x34
public:
	BfmeNetAddress m_addr38;        // +0x38
private:
	Int m_40;                       // +0x40
	char m_pad44[0x0C];             // +0x44
public:
	Int m_50;                       // +0x50
	Int m_54;                       // +0x54
	Int m_58;                       // +0x58
	Int m_5c;                       // +0x5C
public:
	// Retail loads these whole and narrows at the byte-wide call; reading
	// the fields directly lets the compiler narrow the loads instead.
	Int rva54() const { return m_54; }
	Int rva58() const { return m_58; }
	Int rva5C() const { return m_5c; }
	unsigned char m_60;             // +0x60
	char m_pad61[3];
	Int m_64;                       // +0x64
	const Int *rva64() const { return m_60 ? &m_64 : 0; }
private:
	char m_pad68[0x1A4 - 0x68];     // +0x68..+0x1A3
	unsigned char m_occupancy;      // +0x1A4
	char m_pad1A5[0x1AC - 0x1A5];   // +0x1A5..+0x1AB (AsciiString at +0x1A8)
};

class GameInfo
{
public:
	// Vtable 0x008193C8: getLocalSlotNum is slot 13 (+0x34), isSandbox slot
	// 20 (+0x50). The other slots are not reconstructed in this TU.
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual Int getLocalSlotNum() const = 0;
	virtual void slot38() = 0;
	virtual void slot3c() = 0;
	virtual void adjustSlotsForMap();
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4c() = 0;
	virtual bool isSandbox();

	Int getNumPlayers() const;
	Int getNumNonObserverPlayers() const;
	Int getNumOpenOrOccupiedSlots() const;
	GameSlot *getSlot(Int slotNum);
	const GameSlot *getConstSlot(Int slotNum) const;
	void setSlot(Int slotNum, GameSlot slotInfo);
	bool rva003FF457() const;
	bool isHeroDataReadyForSlot(unsigned short slotNum) const;
	AsciiString getMap() const;
	unsigned int getMapCRC() const { return m_mapCRC; }
	unsigned int getMapSize() const { return m_mapSize; }
	Int getMapContentsMask() const { return m_mapMask; }
	Int getSeed() const { return m_seed; }
	Int rva58() const { return m_58; }
	Int rva5C() const { return m_5c; }
	Int rva88() const { return m_88; }
private:
	char m_pad[0x14];
	GameSlot *m_slot[MAX_SLOTS];    // +0x18
	char m_pad38[0x08];
	AsciiString m_mapName;          // +0x40
	unsigned int m_mapCRC;          // +0x44
	unsigned int m_mapSize;         // +0x48
	Int m_mapMask;                  // +0x4C
	Int m_seed;                     // +0x50
	Int m_54;                       // +0x54
public:
	Int m_58;                       // +0x58
	Int m_5c;                       // +0x5C
	Int m_60[10];                   // +0x60, the "GR=" list
	Int m_88;                       // +0x88, the "GSID=" value
};

AsciiString __cdecl Rva00400783Get(const AsciiString &path, bool flag);
void __cdecl Rva0055A087Format(int *vals, AsciiString *out);
_STL::string WideCharStringToMultiByte(const unsigned short *orig);

// ?isOccupied@GameSlot@@QBE_NXZ
bool GameSlot::isOccupied() const
{
	return (m_state == SLOT_PLAYER || m_state == SLOT_EASY_AI || m_state == SLOT_MED_AI
		|| m_state == SLOT_BRUTAL_AI || m_state == SLOT_AI_5) && m_occupancy;
}

// ?isAI@GameSlot@@QBE_NXZ
bool GameSlot::isAI() const
{
	return m_state == SLOT_EASY_AI || m_state == SLOT_MED_AI
		|| m_state == SLOT_BRUTAL_AI || m_state == SLOT_AI_5;
}

Int GameSlot::rva003FF145(const BfmeNetAddress *other) const
{
	if (m_state == SLOT_PLAYER && m_addr38.Rva00248CBF(other))
		return 1;
	return 0;
}

// ?isObserver@GameSlot@@QBE_NXZ
// No BFME1 donor: the observer template (-2) read as a predicate. Fifteen
// direct callers, mostly lobby UI.
bool GameSlot::isObserver() const
{
	return m_playerTemplate == PLAYERTEMPLATE_OBSERVER;
}

// ?encodeHero@GameSlot@@QBEEXZ
// No donor: the byte the LAN lobby's hero setter 0x004456B8 sends as
// "Hero=%d". Kind 1 is a plain yes, kinds 2 and 3 pack the +0x5C or the
// +0x54/+0x58 pair through the rowed Rva0056BD91Pack 0x0056BD91; the kind
// field +0x50 and the packed fields are unidentified, hence the address name.
unsigned char GameSlot::encodeHero() const
{
	switch (m_50)
	{
	case 0:
		return 0;
	case 1:
		return 1;
	case 3:
		return Rva0056BD91Pack(rva54() + 2, rva58(), 0, 0);
	case 2:
		return Rva0056BD91Pack(1, rva5C(), 0, 0);
	}
	return 0;
}

// ?getNumPlayers@GameInfo@@QBEHXZ
Int GameInfo::getNumPlayers() const
{
	Int numPlayers = 0;
	for (int i = 0; i < MAX_SLOTS; ++i)
	{
		if (m_slot[i] && m_slot[i]->isOccupied())
			numPlayers++;
	}
	return numPlayers;
}

// ?getConstSlot@GameInfo@@QBEPBVGameSlot@@H@Z
// Unrowed second definition: the row lives in GameSlotApparent.cpp, but this
// file-unit's counters need same-TU visibility into the body (it preserves
// EDX: only EAX is written) so their index loops stay in EDX across the call
// instead of spilling to a third callee-saved register.
const GameSlot *GameInfo::getConstSlot(Int slotNum) const
{
	if (slotNum < 0 || slotNum >= MAX_SLOTS)
		return 0;
	return m_slot[slotNum];
}

// ?getSlot@GameInfo@@QAEPAVGameSlot@@H@Z
// Unrowed second definition, as getConstSlot above: the row lives in
// GameInfoGetSlot.cpp, but adjustSlotsForMap needs same-TU visibility into
// it (it writes only EAX) to keep its first loop's index in EDX.
GameSlot *GameInfo::getSlot(Int slotNum)
{
	if (m_slot == 0)
		return 0;
	return (slotNum < 0 || slotNum >= MAX_SLOTS) ? 0 : m_slot[slotNum];
}

// ?getNumNonObserverPlayers@GameInfo@@QBEHXZ
Int GameInfo::getNumNonObserverPlayers() const
{
	Int numPlayers = 0;
	for (int i = 0; i < MAX_SLOTS; ++i)
	{
		if (m_slot[i] && m_slot[i]->isOccupied()
			&& m_slot[i]->getPlayerTemplate() != PLAYERTEMPLATE_OBSERVER)
			numPlayers++;
	}
	return numPlayers;
}

// ?getNumOpenOrOccupiedSlots@GameInfo@@QBEHXZ
// No BFME1 donor: counts slots that are open for joining plus slots already
// taken (state OPEN read inline, the rest via the in-TU isOccupied). Both
// callers pair it with getNumPlayers, so the difference is the open count.
Int GameInfo::getNumOpenOrOccupiedSlots() const
{
	Int numSlots = 0;
	for (int i = 0; i < MAX_SLOTS; ++i)
	{
		const GameSlot *slot = getConstSlot(i);
		if (slot->isOpen() || slot->isOccupied())
			numSlots++;
	}
	return numSlots;
}

// ?isSandbox@GameInfo@@UAE_NXZ @0x003FF3E3 (116B): vtable slot 20, after
// isSkirmish (18) and isMultiPlayer (19) as in BFME1/ZH GameInfo.cpp. ZH body
// (every other occupied slot on the local team), plus a BFME2 observer path:
// with no local slot the first occupied slot's team stands in. The team
// number is the +0x1C dword after the player template.
bool GameInfo::isSandbox()
{
	Int localSlotNum = getLocalSlotNum();
	Int localTeam = -1;
	if (localSlotNum < 0)
	{
		for (Int i = 0; i < MAX_SLOTS; ++i)
		{
			const GameSlot *slot = getConstSlot(i);
			if (slot->isOccupied())
			{
				localTeam = slot->getTeamNumber();
				break;
			}
		}
	}
	else
	{
		localTeam = getConstSlot(localSlotNum)->getTeamNumber();
	}
	for (Int i = 0; i < MAX_SLOTS; ++i)
	{
		if (i == localSlotNum)
			continue;

		const GameSlot *slot = getConstSlot(i);
		if (slot->isOccupied() && (slot->getTeamNumber() < 0 || slot->getTeamNumber() != localTeam))
			return false;
	}
	return true;
}

// ?rva003FF457@GameInfo@@QBE_NXZ @0x003FF457 (63B): the all-slots form of
// isHeroDataReadyForSlot below, scanning the slot array directly: false when any
// occupied slot has the +0x50 kind set but no +0x64 block. One caller,
// 0x0044C285.
bool GameInfo::rva003FF457() const
{
	if (!m_slot)
		return true;
	for (int i = 0; i < MAX_SLOTS; ++i) {
		const GameSlot *slot = m_slot[i];
		if (slot->isOccupied() && slot->m_50 != 0 && !slot->rva64())
			return false;
	}
	return true;
}

bool GameInfo::isHeroDataReadyForSlot(unsigned short slotNum) const
{
	if (m_slot && slotNum < MAX_SLOTS) {
		const GameSlot *slot = m_slot[slotNum];
		if (slot->isOccupied() && slot->m_50 != 0 && !slot->rva64())
			return false;
	}
	return true;
}

// ?decodeHero@GameSlot@@QAE_NE@Z @0x003FF8B0 215B. GameSlot hero-kind setter,
// inverse of encodeHero: kind 0 clears, 1 sets plain, hi==1 stores hero index
// +0x5C and resolves +0x54/+0x58 via TheCreateAHeroManager 0x00DFE344, else
// kind 3 stores hi-2/lo. Evidence: +0x50/+0x54/+0x58/+0x5C layout, rowed
// Rva0056BDA5Split 0x0056BDA5, pinned rva0021F797/rva0040A32F, rowed
// rva00219D52, callers 0x0024A6C6 0x00401A5D 0x00401D6C 0x00448BF0 0x005A431B.
bool GameSlot::decodeHero(unsigned char v)
{
	m_50 = 0;
	m_54 = 0;
	m_58 = 0;
	if (v == 0) {
		m_50 = 0;
		return true;
	}
	if (v == 1) {
		m_50 = 1;
		return true;
	}
	unsigned char hi;
	unsigned char lo;
	Rva0056BDA5Split(v, 0, 0, &hi, &lo);
	if (hi == 1) {
		m_50 = 2;
		unsigned int idx = lo;
		if (idx >= (unsigned int)TheCreateAHeroManager->m_158)
			return false;
		m_5c = (int)idx;
		Rva0040A3F9 *heroes = TheCreateAHeroManager->rva0021F797();
		CreateAHeroData *data = heroes->rva0040A32F(m_5c);
		if (data == 0)
			return true;
		m_54 = data->m_0c;
		m_58 = data->m_10;
		return true;
	}
	unsigned int hi2 = hi;
	--hi2;
	--hi2;
	Vec32 *outer = &TheCreateAHeroManager->m_outer;
	unsigned int outerCount = (unsigned int)(((char *)outer->m_finish - (char *)outer->m_start) >> 5);
	if (hi2 >= outerCount)
		return false;
	unsigned int lo2 = lo;
	int inner = TheCreateAHeroManager->rva00219D52(hi2);
	if (lo2 >= (unsigned int)inner)
		return false;
	m_50 = 3;
	m_54 = (int)hi2;
	m_58 = (int)lo2;
	return true;
}

// ?rva003FF1A7@GameSlot@@QAEXH@Z @0x003FF1A7 27B: mode setter at +0x5C with
// rules reset at +0x60 via pinned Rva00559FAC 0x00559FAC. Early-out when the
// stored mode already equals the new value. Evidence: +0x5C/+0x60 layout
// matches GameSlot m_5c/m_60, pin-only callee YAXHPAX, 8 callers.
void GameSlot::rva003FF1A7(int v)
{
	if (m_5c == v)
		return;
	m_5c = v;
	Rva00559FAC(v, &m_60);
}

// ?adjustSlotsForMap@GameInfo@@UAEXXZ @0x0040052C (599B): vtable slot 16
// (+0x40). BFME1/ZH GameInfo.cpp adjustSlotsForMap: count the occupied
// slots, then open free slots while the map (+0x20 player count of the
// MapCache entry for the +0x40 map name) has room and close the rest. BFME2
// also counts the human slots among the occupied ones and, when the +0x5C
// mode is 1, opens free slots only while fewer than two are human (counting
// each opened slot as one) and closes the others.
void GameInfo::adjustSlotsForMap()
{
	const MapMetaData *md = TheMapCache->findMap(m_mapName);
	if (md != 0)
	{
		Int numPlayers = md->m_numPlayers;
		Int numPlayerSlots = 0;
		Int numHumanSlots = 0;
		Int i;

		for (i = 0; i < MAX_SLOTS; ++i)
		{
			GameSlot *tempSlot = getSlot(i);
			if (tempSlot->isOccupied())
			{
				++numPlayerSlots;
				if (tempSlot->isHuman())
					++numHumanSlots;
			}
		}

		for (i = 0; i < MAX_SLOTS; ++i)
		{
			GameSlot *slot = getSlot(i);
			if (numPlayers > numPlayerSlots)
			{
				if (!(slot->isOccupied()))
				{
					if (m_5c == 1)
					{
						if (numHumanSlots < 2)
						{
							GameSlot newSlot;
							GameSlotConnectInfo connectInfo;
							newSlot.setState(SLOT_OPEN, UnicodeString::TheEmptyString, &connectInfo);
							setSlot(i, newSlot);
							++numHumanSlots;
						}
						else
						{
							GameSlot newSlot;
							GameSlotConnectInfo connectInfo;
							newSlot.setState(SLOT_CLOSED, UnicodeString::TheEmptyString, &connectInfo);
							setSlot(i, newSlot);
						}
					}
					else
					{
						GameSlot newSlot;
						GameSlotConnectInfo connectInfo;
						newSlot.setState(SLOT_OPEN, UnicodeString::TheEmptyString, &connectInfo);
						setSlot(i, newSlot);
						++numPlayerSlots;
					}
				}
			}
			else
			{
				if (!(slot->isOccupied()))
				{
					GameSlot newSlot;
					GameSlotConnectInfo connectInfo;
					newSlot.setState(SLOT_CLOSED, UnicodeString::TheEmptyString, &connectInfo);
					setSlot(i, newSlot);
				}
			}
		}
	}
}

// StringBase<char>::concat(char) expanded in place, as in the sibling
// GameInfoSetMap.cpp: the byte goes to a stack slot and into concat(text, 1)
// at 0x000369A0.
static inline void concatChar(AsciiString &s, char c)
{
	((StringBase<char> *)&s)->concat(&c, 1);
}

// StringBase<char>::str(): an empty string reads the function-local
// TheNullChr (0x00BBAC1C) rather than the shared header's "" literal.
static inline const char *baseStr(const AsciiString &s)
{
	return ((const StringBase<char> *)&s)->str();
}

// ?GameInfoToAsciiString@@YA?AVAsciiString@@PBVGameInfo@@_N@Z @0x00400AF8
// (827B): BFME1/ZH GameInfoToAsciiString, the lobby's slot-list string.
// BFME2 rewrites the header ("M=%3.3x%s;MC=%X;MS=%d;SD=%d;GSID=%X;GT=%d;SI=%d;"
// then a "GR=" list of ten ints from +0x60 through 0x0055A087), drops the
// name-length budget, appends +0x20, +0x40 and the hero byte (0x003FF16F) to
// the slot records, adds a fourth AI letter 'B' for state 5 and takes a flag
// that blanks the human names. The flag's callers pass 1 or a register.
// Retail's argument scheduling separates getters from plain member reads:
// getter results are loaded before the hero-byte call (and the header's
// before the str() branch), the connection record's ip/port after it.
AsciiString GameInfoToAsciiString(const GameInfo *game, bool withNames)
{
	if (!game)
		return AsciiString::TheEmptyString;

	AsciiString mapName = Rva00400783Get(game->getMap(), false);

	AsciiString optionsString;
	optionsString.format("M=%3.3x%s;MC=%X;MS=%d;SD=%d;GSID=%X;GT=%d;SI=%d;",
		game->getMapContentsMask(), baseStr(mapName), game->getMapCRC(), game->getMapSize(),
		game->getSeed(), game->rva88(), game->rva5C(), game->rva58());

	{
		AsciiString rules("GR=");
		Rva0055A087Format(const_cast<Int *>(game->m_60), &rules);
		rules.concat(";");
		optionsString.concat(rules);
	}

	concatChar(optionsString, 'S');
	concatChar(optionsString, '=');
	for (Int i = 0; i < MAX_SLOTS; ++i)
	{
		const GameSlot *slot = game->getConstSlot(i);

		AsciiString str;
		if (slot && slot->isHuman())
		{
			AsciiString name = WideCharStringToMultiByte(slot->getName().str()).c_str();
			str.format("H%s,%X,%d,%c%c,%d,%d,%d,%d,%d,%d,%d:",
				withNames ? baseStr(name) : "",
				slot->m_addr38.m_ip, slot->m_addr38.m_port,
				slot->isAccepted() ? 'T' : 'F',
				slot->hasMap() ? 'T' : 'F',
				slot->getColor(), slot->getPlayerTemplate(),
				slot->getStartPos(), slot->getTeamNumber(),
				slot->rva20(), slot->rva40(), slot->encodeHero());
		}
		else if (slot && slot->isAI())
		{
			char c;
			if (slot->getState() == SLOT_EASY_AI)
				c = 'E';
			else if (slot->getState() == SLOT_MED_AI)
				c = 'M';
			else if (slot->getState() == SLOT_BRUTAL_AI)
				c = 'H';
			else
				c = 'B';
			str.format("C%c,%d,%d,%d,%d,%d,%d:", c,
				slot->getColor(), slot->getPlayerTemplate(),
				slot->getStartPos(), slot->getTeamNumber(),
				slot->rva20(), slot->encodeHero());
		}
		else if (slot && slot->getState() == SLOT_OPEN)
		{
			str = "O:";
		}
		else
		{
			str = "X:";
		}
		optionsString.concat(str);
	}
	concatChar(optionsString, ';');

	return optionsString;
}
