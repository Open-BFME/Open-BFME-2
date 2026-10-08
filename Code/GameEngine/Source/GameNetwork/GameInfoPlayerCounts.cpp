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
#include <map>
#include <stdlib.h>
#include <string.h>

// The parser reaches atoi, sscanf and strtol through msvcr71's import table
// while free and strdup are the game's direct bodies. /D_CRTIMP= gives the
// direct calls; <stdlib.h> already declares the plain forms, so the IAT forms
// live in their own scope to avoid C2375 (as MultiByteToWideCharSingleLine.cpp).
namespace CrtIAT
{
extern "C" __declspec(dllimport) int __cdecl atoi(const char *s);
extern "C" __declspec(dllimport) int __cdecl sscanf(const char *s, const char *fmt, ...);
extern "C" __declspec(dllimport) long __cdecl strtol(const char *s, char **end, int base);
}

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
	char c, char d);

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
	bool m_isMultiplayer;           // +0x24
	bool m_isScenarioMP;            // +0x25
	bool m_isOfficial;              // +0x26
};

bool operator<(const AsciiString &left, const AsciiString &right);

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left < right;
	}
};
}

class MapCache : public _STL::map<AsciiString, MapMetaData>
{
public:
	const MapMetaData *findMap(AsciiString mapName);
};

extern MapCache *TheMapCache;

class Image;

class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern ImageCollection *TheMappedImageCollection;

// The game's 16-byte digest test (Rva003FF1C2.cpp, rowed under its address
// name, as MpGameSetupSlots.cpp calls it).
class Rva003FF1C2
{
public:
	bool rva003FF1C2() const;
};

int __cdecl Rva00559EDCCompare(int *a, int *b);

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
	void setPlayerTemplate(Int playerTemplate);
	void setAccept() { m_isAccepted = true; }
	void unAccept() { if (isHuman()) m_isAccepted = false; }
	void setMapAvailability(bool hasMap) { if (isHuman()) m_hasMap = hasMap; }
	void setColor(Int color) { m_color = color; }
	void setStartPos(Int startPos) { m_startPos = startPos; }
	void setTeamNumber(Int teamNumber) { m_teamNumber = teamNumber; }
	void rva20Set(Int v) { m_20 = v; }
	void rva40Set(Int v) { m_40 = v; }
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
	virtual const Image *rva00401015(Int kind);
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
	void setMap(AsciiString mapName);
	void setMapCRC(unsigned int mapCRC);
	void setMapSize(unsigned int mapSize);
	void setMapContentsMask(Int mask) { m_mapMask = mask; }
	void setSeed(Int seed) { m_seed = seed; }
	void rva88Set(Int v) { m_88 = v; }
	void rva003FF1A7(int v);
	void rva58Set(Int v) { m_58 = v; }
	void rva60Set(const Int *rules) { memcpy(m_60, rules, sizeof(m_60)); }
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
AsciiString _Rva00621350GameInfoMapPath(const AsciiString &path, bool flag);
void Rva00559F11Parse(const char *text, int *rules);
char *strtok_r(char *str, const char *delim, char **pos);
_STL::wstring MultiByteToWideCharSingleLine(const char *orig);

// Zero Hour's MultiplayerSettings::getNumColors: the color count cached at
// +0x40 on first use from the +0x38 count.
class MultiplayerSettings
{
public:
	Int getNumColors()
	{
		if (m_numColors == 0)
			m_numColors = m_colorCount;
		return m_numColors;
	}
private:
	char m_pad00[0x38];
	Int m_colorCount;               // +0x38
	Int m_3c;
	Int m_numColors;                // +0x40
};

extern MultiplayerSettings *TheMultiplayerSettings;

// PlayerTemplateStore::getPlayerTemplateCount: the template vector's size,
// 0x1DC-byte elements between +0x0C and +0x10.
struct PlayerTemplateBody
{
	char m_bytes[0x1DC];
};

class PlayerTemplateStore
{
public:
	Int getPlayerTemplateCount() { return m_finish - m_start; }
private:
	char m_pad00[0x0C];
	PlayerTemplateBody *m_start;    // +0x0C
	PlayerTemplateBody *m_finish;   // +0x10
};

extern PlayerTemplateStore *ThePlayerTemplateStore;
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

// ?rva003FF1A7@GameInfo@@QAEXH@Z @0x003FF1A7 27B: mode setter at +0x5C with
// rules reset at +0x60 via pinned Rva00559FAC 0x00559FAC. Early-out when the
// stored mode already equals the new value. A GameInfo member, not GameSlot
// (the earlier spelling): ParseAsciiStringToGameInfo 0x00401EF0 calls it on
// its GameInfo argument with the parsed "GT=" value, between the inline
// GSID and "SI=" stores and before copying the parsed "GR=" ten-int rules
// block (the one Rva00559FAC fills) over +0x60. 8 callers.
void GameInfo::rva003FF1A7(int v)
{
	if (m_5c == v)
		return;
	m_5c = v;
	Rva00559FAC(v, m_60);
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

// StringBase<unsigned short>::isEmpty expanded in place, as AsciiString's
// in ascii_string.h: no buffer, or a zero length in its header.
static inline bool wideIsEmpty(const UnicodeString &s)
{
	const char *data = *(const char *const *)&s;
	return data == 0 || *(const unsigned short *)(data + 4) == 0;
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

// ?rva00401015@GameInfo@@UAEPBVImage@@H@Z @0x00401015 (342B), vtable slot 6
// (+0x18): the lobby icon for the game. Kind 1 is the non-default rules icon
// (the +0x60 rules against the defaults Rva00559FAC gives for the +0x5C mode);
// kind 0 is, in mode 0, the user-map icon for a map the cache lacks or does
// not mark official (+0x26), and in mode 1 the resumed-save icon when the
// +0xCC digest is set. The unused UnicodeString is retail's (constructed and
// destroyed, state 1). The compare count goes through a local: tested in place
// it becomes test eax,eax where retail compares against the zero in EBX.
const Image *GameInfo::rva00401015(Int kind)
{
	const Image *image = NULL;
	switch (kind)
	{
	case 1:
	{
		Int defaults[10];
		Rva00559FAC(m_5c, defaults);
		Int numDiffs = Rva00559EDCCompare(defaults, m_60);
		if (numDiffs != 0)
			image = TheMappedImageCollection->findImageByName(AsciiString("AptLobbyNonDefaultSettings"));
		break;
	}
	case 0:
	{
		UnicodeString tooltip;
		switch (m_5c)
		{
		case 0:
		{
			AsciiString map = getMap();
			map.toLower();
			MapCache::iterator it = TheMapCache->find(map);
			if (it == TheMapCache->end() || !(*it).second.m_isOfficial)
				image = TheMappedImageCollection->findImageByName(AsciiString("AptUserMapNotConquered"));
			break;
		}
		case 1:
			if (((const Rva003FF1C2 *)this)->rva003FF1C2())
				image = TheMappedImageCollection->findImageByName(AsciiString("AptLobbyResumeSavedGame"));
			break;
		}
		break;
	}
	}
	return image;
}

// The "M=" value's first three characters are the map contents mask in hex.
static Int grabHexInt(const char *s)
{
	char tmp[6] = "0xfff";
	tmp[2] = s[0];
	tmp[3] = s[1];
	tmp[4] = s[2];
	Int b = CrtIAT::strtol(tmp, NULL, 16);
	return b;
}

// ?ParseAsciiStringToGameInfo@@YA_NPAVGameInfo@@VAsciiString@@_N@Z @0x0040116B
// (3595B): BFME1/ZH ParseAsciiStringToGameInfo, the inverse of
// GameInfoToAsciiString above. BFME2 keys: M (three hex digits of mask, the
// map path through 0x00400898), MC, MS, SD, GR (ten ints through 0x00559F11),
// GSID, GT, SI and the S slot list. Human records add the +0x20 (-100..0) and
// +0x40 (0..256) fields and the hero byte, AI records +0x20, a fourth letter
// 'B' (state 5) and the hero byte; start positions lose their upper bound.
// The hero byte is applied after copying +0x5C from the game's current slot.
// The new flag keeps the game's current names when a record's name is empty.
bool ParseAsciiStringToGameInfo(GameInfo *game, AsciiString options, bool withNames)
{
	char *buf = strdup(options.str());
	char *bufPtr = buf;
	char *strPos, *keyValPair;
	GameSlot newSlot[MAX_SLOTS];
	bool optionsOk = true;
	AsciiString mapName;
	Int si = -1;
	Int mapContentsMask = 0;
	unsigned int mapCRC = 0;
	unsigned int mapSize = 0;
	Int seed = 0;
	Int gsid = 0;
	Int gt = 0;
	Int gameRules[10];
	Rva00559FAC(-1, gameRules);

	bool sawMap, sawMapCRC, sawMapSize, sawSeed, sawSlotlist, sawGR, sawGSID, sawGT, sawSI;
	sawMap = sawMapCRC = sawMapSize = sawSeed = sawSlotlist = sawGR = sawGSID = sawGT = sawSI = false;
	UnicodeString oldNames[MAX_SLOTS];

	if (!withNames)
	{
		for (unsigned int i = 0; i < MAX_SLOTS; ++i)
			oldNames[i] = game->getConstSlot(i)->getName();
	}

	while ((keyValPair = strtok_r(bufPtr, ";", &strPos)) != NULL)
	{
		bufPtr = NULL;

		AsciiString key, val;
		char *pos = NULL;
		char *keyPtr, *valPtr;
		keyPtr = strtok_r(keyValPair, "=", &pos);
		valPtr = strtok_r(NULL, "\n", &pos);
		if (keyPtr)
			key = keyPtr;
		if (valPtr)
			val = valPtr;

		if (val.isEmpty())
		{
			optionsOk = false;
			break;
		}

		if (key.compare("M") == 0)
		{
			if (val.getLength() < 3)
			{
				optionsOk = false;
				break;
			}
			mapContentsMask = grabHexInt(val.str());
			mapName = _Rva00621350GameInfoMapPath(AsciiString(val.str() + 3), false);
			sawMap = true;
		}
		else if (key.compare("MC") == 0)
		{
			mapCRC = 0;
			CrtIAT::sscanf(val.str(), "%X", &mapCRC);
			sawMapCRC = true;
		}
		else if (key.compare("MS") == 0)
		{
			mapSize = CrtIAT::atoi(val.str());
			sawMapSize = true;
		}
		else if (key.compare("SD") == 0)
		{
			seed = CrtIAT::atoi(val.str());
			sawSeed = true;
		}
		else if (key.compare("GR") == 0)
		{
			Rva00559F11Parse(val.str(), gameRules);
			sawGR = true;
		}
		else if (key.compare("GSID") == 0)
		{
			gsid = 0;
			CrtIAT::sscanf(val.str(), "%X", &gsid);
			sawGSID = true;
		}
		else if (key.compare("GT") == 0)
		{
			gt = CrtIAT::atoi(val.str());
			sawGT = true;
		}
		else if (key.compare("SI") == 0)
		{
			si = CrtIAT::atoi(val.str());
			sawSI = true;
		}
		else if (key.getLength() == 1 && *key.str() == 'S')
		{
			sawSlotlist = true;
			char *rawSlotBuf = strdup(val.str());
			char *freeMe = NULL;
			AsciiString rawSlot;
			for (int i = 0; i < MAX_SLOTS; ++i)
			{
				rawSlot = strtok_r(rawSlotBuf, ":", &pos);
				if (rawSlotBuf)
					freeMe = rawSlotBuf;
				rawSlotBuf = NULL;
				// The slot pointer lives in ESI across the switch, and the AI
				// record's tokenizer position has its own frame slot (it does not
				// share the human record's): both are declared out here.
				GameSlot *slot = &newSlot[i];
				char *aiSlotPos;
				switch (*baseStr(rawSlot))
				{
					case 'H':
					{
						char *slotPos = NULL;
						AsciiString slotValue(strtok_r((char *)baseStr(rawSlot), ",", &slotPos));
						if (slotValue.isEmpty())
						{
							optionsOk = false;
							break;
						}
						UnicodeString name;
						name.set(MultiByteToWideCharSingleLine(slotValue.str() + 1).c_str());
						if (!withNames && wideIsEmpty(name))
							name = oldNames[i];

						slotValue = strtok_r(NULL, ",", &slotPos);
						if (slotValue.isEmpty())
						{
							optionsOk = false;
							break;
						}
						unsigned int playerIP = 0;
						CrtIAT::sscanf(slotValue.str(), "%x", &playerIP);

						slotValue = strtok_r(NULL, ",", &slotPos);
						if (slotValue.isEmpty())
						{
							optionsOk = false;
							break;
						}
						unsigned int playerPort = 0;
						CrtIAT::sscanf(slotValue.str(), "%d", &playerPort);

						GameSlotConnectInfo connectInfo;
						connectInfo.m_ip = playerIP;
						connectInfo.m_port = playerPort;
						slot->setState(SLOT_PLAYER, name, &connectInfo);

						slotValue = strtok_r(NULL, ",", &slotPos);
						if (slotValue.getLength() != 2)
						{
							optionsOk = false;
							break;
						}
						const char *svs = slotValue.str();
						if (*svs == 'T')
							slot->setAccept();
						else if (*svs == 'F')
							slot->unAccept();
						++svs;
						if (*svs == 'T')
							slot->setMapAvailability(true);
						else
							slot->setMapAvailability(false);

						slotValue = strtok_r(NULL, ",", &slotPos);
						if (slotValue.isEmpty())
						{
							optionsOk = false;
							break;
						}
						Int color = CrtIAT::atoi(slotValue.str());
						if (color < -1 || color >= TheMultiplayerSettings->getNumColors())
						{
							optionsOk = false;
							break;
						}
						slot->setColor(color);

						slotValue = strtok_r(NULL, ",", &slotPos);
						if (slotValue.isEmpty())
						{
							optionsOk = false;
							break;
						}
						Int playerTemplate = CrtIAT::atoi(slotValue.str());
						if (playerTemplate < PLAYERTEMPLATE_OBSERVER || playerTemplate >= ThePlayerTemplateStore->getPlayerTemplateCount())
						{
							optionsOk = false;
							break;
						}
						slot->setPlayerTemplate(playerTemplate);

						slotValue = strtok_r(NULL, ",", &slotPos);
						if (slotValue.isEmpty())
						{
							optionsOk = false;
							break;
						}
						Int startPos = CrtIAT::atoi(slotValue.str());
						if (startPos < -1)
						{
							optionsOk = false;
							break;
						}
						slot->setStartPos(startPos);

						slotValue = strtok_r(NULL, ",", &slotPos);
						if (slotValue.isEmpty())
						{
							optionsOk = false;
							break;
						}
						Int team = CrtIAT::atoi(slotValue.str());
						if (team < -1 || team >= MAX_SLOTS / 2)
						{
							optionsOk = false;
							break;
						}
						slot->setTeamNumber(team);

						slotValue = strtok_r(NULL, ",", &slotPos);
						if (slotValue.isEmpty())
						{
							optionsOk = false;
							break;
						}
						Int v20 = CrtIAT::atoi(slotValue.str());
						if (v20 < -100 || v20 > 0)
						{
							optionsOk = false;
							break;
						}
						slot->rva20Set(v20);

						slotValue = strtok_r(NULL, ",", &slotPos);
						if (slotValue.isEmpty())
						{
							optionsOk = false;
							break;
						}
						Int v40 = CrtIAT::atoi(slotValue.str());
						if (v40 < 0 || v40 > 0x100)
						{
							optionsOk = false;
							break;
						}
						slot->rva40Set(v40);

						slotValue = strtok_r(NULL, ",", &slotPos);
						if (slotValue.isEmpty())
						{
							optionsOk = false;
							break;
						}
						Int hero = CrtIAT::atoi(slotValue.str());
						slot->m_5c = game->getSlot(i)->m_5c;
						slot->decodeHero(hero);
					}
					break;
					case 'C':
					{
						aiSlotPos = NULL;
						AsciiString slotValue(strtok_r((char *)baseStr(rawSlot), ",", &aiSlotPos));
						if (slotValue.isEmpty())
						{
							optionsOk = false;
							break;
						}
						switch (*(slotValue.str() + 1))
						{
							case 'E':
							{
								GameSlotConnectInfo connectInfo;
								slot->setState(SLOT_EASY_AI, UnicodeString::TheEmptyString, &connectInfo);
							}
							break;
							case 'M':
							{
								GameSlotConnectInfo connectInfo;
								slot->setState(SLOT_MED_AI, UnicodeString::TheEmptyString, &connectInfo);
							}
							break;
							case 'H':
							{
								GameSlotConnectInfo connectInfo;
								slot->setState(SLOT_BRUTAL_AI, UnicodeString::TheEmptyString, &connectInfo);
							}
							break;
							case 'B':
							{
								GameSlotConnectInfo connectInfo;
								slot->setState(SLOT_AI_5, UnicodeString::TheEmptyString, &connectInfo);
							}
							break;
							default:
							{
								optionsOk = false;
							}
							break;
						}

						slotValue = strtok_r(NULL, ",", &aiSlotPos);
						if (slotValue.isEmpty())
						{
							optionsOk = false;
							break;
						}
						Int color = CrtIAT::atoi(slotValue.str());
						if (color < -1 || color >= TheMultiplayerSettings->getNumColors())
						{
							optionsOk = false;
							break;
						}
						slot->setColor(color);

						slotValue = strtok_r(NULL, ",", &aiSlotPos);
						if (slotValue.isEmpty())
						{
							optionsOk = false;
							break;
						}
						Int playerTemplate = CrtIAT::atoi(slotValue.str());
						if (playerTemplate < PLAYERTEMPLATE_OBSERVER || playerTemplate >= ThePlayerTemplateStore->getPlayerTemplateCount())
						{
							optionsOk = false;
							break;
						}
						slot->setPlayerTemplate(playerTemplate);

						slotValue = strtok_r(NULL, ",", &aiSlotPos);
						if (slotValue.isEmpty())
						{
							optionsOk = false;
							break;
						}
						Int startPos = CrtIAT::atoi(slotValue.str());
						bool isStartPosBad = false;
						if (startPos < -1)
							isStartPosBad = true;
						for (Int j = 0; j < i; ++j)
						{
							if (startPos >= 0 && startPos == slot->getStartPos())
								isStartPosBad = true;
						}
						if (isStartPosBad)
						{
							optionsOk = false;
							break;
						}
						slot->setStartPos(startPos);

						slotValue = strtok_r(NULL, ",", &aiSlotPos);
						if (slotValue.isEmpty())
						{
							optionsOk = false;
							break;
						}
						Int team = CrtIAT::atoi(slotValue.str());
						if (team < -1 || team >= MAX_SLOTS / 2)
						{
							optionsOk = false;
							break;
						}
						slot->setTeamNumber(team);

						slotValue = strtok_r(NULL, ",", &aiSlotPos);
						if (slotValue.isEmpty())
						{
							optionsOk = false;
							break;
						}
						Int v20 = CrtIAT::atoi(slotValue.str());
						if (v20 < -100 || v20 > 0)
						{
							optionsOk = false;
							break;
						}
						slot->rva20Set(v20);

						slotValue = strtok_r(NULL, ",", &aiSlotPos);
						if (slotValue.isEmpty())
						{
							optionsOk = false;
							break;
						}
						Int hero = CrtIAT::atoi(slotValue.str());
						slot->m_5c = game->getSlot(i)->m_5c;
						slot->decodeHero(hero);
					}
					break;
					case 'O':
					{
						GameSlotConnectInfo connectInfo;
						slot->setState(SLOT_OPEN, UnicodeString::TheEmptyString, &connectInfo);
					}
					break;
					case 'X':
					{
						GameSlotConnectInfo connectInfo;
						slot->setState(SLOT_CLOSED, UnicodeString::TheEmptyString, &connectInfo);
					}
					break;
					default:
					{
						optionsOk = false;
					}
					break;
				}
			}
			if (freeMe)
				free(freeMe);
		}
		else
		{
			optionsOk = false;
			break;
		}
	}
	if (buf)
		free(buf);

	if (optionsOk && sawMap && sawMapCRC && sawMapSize && sawSeed && sawSlotlist && sawGR && sawGSID && sawGT && sawSI)
	{
		if (!game)
			return true;

		for (Int i = 0; i < MAX_SLOTS; i++)
			game->setSlot(i, newSlot[i]);

		game->setMap(mapName);
		game->setMapCRC(mapCRC);
		game->setMapSize(mapSize);
		game->setMapContentsMask(mapContentsMask);
		game->setSeed(seed);
		game->rva88Set(gsid);
		game->rva003FF1A7(gt);
		game->rva58Set(si);
		game->rva60Set(gameRules);
		return true;
	}

	return false;
}
