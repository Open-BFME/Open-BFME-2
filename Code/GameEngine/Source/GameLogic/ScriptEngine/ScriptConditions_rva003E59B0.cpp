// cl: /G7 /O1 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /I. /ICode/GameEngine/Source/GameLogic/ScriptEngine /ICode
//
// ?rva003E59B0@ScriptConditions@@IAE_NPAVParameter@@00_N@Z
// retail 0x003E59B0 (313B, RET 0x10): unit form of the castle area test.
// Exact via W7-D3: the didEnter/didExit equal-arm must be spelled as a nested
// if/else, not a ternary, or cl emits cmp al,bl instead of test al,al.
// cl: /G7 /O1 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /I. /ICode/GameEngine/Source/GameLogic/ScriptEngine /ICode
// ?rva003E59B0@ScriptConditions@@IAE_NPAVParameter@@00_N@Z, retail 0x003E59B0
// (313 bytes, RET 0x10): the unit form of the castle area test in ScriptConditions_Rva003E6ED0.cpp
// -- the named unit against the named castle or, with no castle name and a player parameter naming
// no player, the closest KindOf-120 object to the unit through the same filter chain; the unit's
// didEnter / didExit against the castle's areas 1..7.
#include "ascii_string.h"

class Player;
class Object;

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next);	// 0x00625790
	Rva000421C8 *m_next;
};

// vftable 0x00BFAD28, allow 0x0026137E, slot 2 0x00261368: +0x08 a player, +0x0C whether a hit allows.
class Rva0026137EFilter : public Rva000421C8
{
public:
	Rva0026137EFilter(Player *player, bool match) : m_player(player), m_match(match) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	Player *m_player;
	bool m_match;
};

// The 224-bit KindOf mask; the (unused, bit) constructor is 0x00045411.
struct Rva00045411BitSet
{
public:
	Rva00045411BitSet(int unused, int bit) throw(); // 0x00045411
	unsigned m_bits[7]; // +0x00
};

class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};

// vftable 0x00BC2908, allow 0x002610DE: accept what has every kind of the first mask and none of the second.
class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b) throw();
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08; // +0x08
	BfmeFixedStorage0004543D m_24; // +0x24
};
template <int N> class BitFlags;
extern BitFlags<116> KINDOFMASK_NONE;

#include "Code/Libraries/Include/Lib/Coord3D.h"
#include "Code/GameEngine/Source/Common/PartitionRangeQueryCallView.h"
extern PartitionManager *ThePartitionManager;

#define REALLY_FAR (100000 * 10.0f)

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class PolygonTrigger;

#include "../../../Include/Common/Module.h"

class CastleBehavior
{
public:
	static NameKeyType rva0003955DA();	// 0x003955DA
};

// 0x00395E53, the castle area trigger for an index (row Rva00395E53Get.cpp).
class Rva00395E53
{
public:
	void *rva00395E53(unsigned int index);
};

enum ObjectStatusTypes { OBJECT_STATUS_NONE = 0 };
enum SpecialPowerType { SPECIAL_INVALID = 0 };
enum CellShroudStatus { CELLSHROUD_CLEAR, CELLSHROUD_FOGGED, CELLSHROUD_SHROUDED, CELLSHROUD_COUNT };
class Rva00261C89;
class Parameter;
class ContainModuleInterface;
class AsciiString;
class BodyModuleInterface;
class ThingTemplate;
class AIUpdateInterface;
class ExperienceTracker;
class Object
{
private:
	friend bool __stdcall Rva003E4B83Get(Parameter *);
public:
	friend class ScriptConditions;
	const Coord3D *getPosition() const { return &m_pos; }
	Rva00261C89 *getField04() const { return (Rva00261C89 *)m_template; }
	bool testStatus(ObjectStatusTypes status) const;
	float getVisionRange() const;
	bool hasSpecialPower(SpecialPowerType type) const;
	Player *getControllingPlayer() const;
protected:
	Module *findModule(NameKeyType key) const;
public:
	// Keep the native +0x250 load inline; omit the competing legacy getter.
	__declspec(dllimport) __forceinline ContainModuleInterface *getContain() const { return m_contain; }
	unsigned int getID() const { return m_id; }
	const AsciiString *rva00290E67() const;
	bool didEnter(PolygonTrigger *trigger); // 0x0028D718
	bool didExit(PolygonTrigger *trigger); // 0x0028D757
	BodyModuleInterface *getBodyModule() const { return m_body; }
	bool rva002943B2(const Player *player);
	CellShroudStatus getShroudStatusForPlayer(int playerIndex) const;
	const ThingTemplate *getTemplate() const { return m_template; }
	void *getContainedBy() const { return m_containedBy; }
	AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }
	char m_pad00[0x4];
	const ThingTemplate *m_template; // +0x04
	char m_pad08[0x30];
	Coord3D m_pos; // +0x38
	char m_pad44[0x30];
	unsigned int m_id; // +0x74
	char m_pad78[0x150];
	unsigned char m_disabledMask[4]; // +0x1C8
	char m_pad1CC[0x84];
	ContainModuleInterface *m_contain; // +0x250
private:
	BodyModuleInterface *m_body; // +0x254
	AIUpdateInterface *m_ai; // +0x258 (retail-proven by the kept ScriptActions_doTeamFaceWaypoint row)
	char m_pad25C[0x8];
public:
	ExperienceTracker *m_experienceTracker; // +0x264
	char m_pad268[0xC];
private:
	void *m_containedBy; // +0x274
	char m_pad278[0x1D4];
public:
	int m_44c; // +0x44C
};

class PlayerList
{
public:
	Player *getPlayerFromMask(int mask);
	Player *getEachPlayerFromMask(int &mask);
	int rva002A7C0B(bool flag);
	Player *getNeutralPlayer() const { return m_neutralPlayer; }
	char m_pad00[0x18];
private:
	Player *m_neutralPlayer; // +0x18
};
extern PlayerList *ThePlayerList;

class Parameter
{
public:
	enum { LESS_THAN = 0, LESS_EQUAL, EQUAL, GREATER_EQUAL, GREATER, NOT_EQUAL };
private:
	friend class ScriptConditions; // Native conditions read the +0x08 word inline.
public:
	float getReal() const { return m_real; }
	const AsciiString &getString() const { return m_string; }
	void setCachedFrame(int value) { m_cachedFrame = value; }
	__declspec(dllimport) __forceinline int getInt() const { return m_int; }
	int bfme_getInt_58502() const { return m_int; }
	int bfme_int_ena() const { return m_int; }
	int bfme_int_exa() const { return m_int; }
	int bfme_int_hos() const { return m_int; }
	// LINK: same-body helper under a TU-unique name (identical inlined bytes); the getInt copy loses to the first-in-order copy. No flags touched.
	int bfme_getInt_f996b() const { return m_int; }
	char m_pad00[0x8];
	int m_int; // +0x08
	float m_real; // +0x0C
	AsciiString m_string; // +0x10
	unsigned char m_afterString[8]; // +0x14
	unsigned int m_objectId; // +0x1C
	int m_cachedFrame; // +0x20
};

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

#include "../../../Include/GameLogic/ScriptConditions.h"

bool ScriptConditions::rva003E59B0(Parameter *pUnitParm, Parameter *pCastleParm,
	Parameter *playerParm, bool entered)
{
	Object *obj = TheScriptEngine->getUnitNamed(pUnitParm);
	if (!obj)
		return false;
	Object *castle;
	if (pCastleParm) {
		castle = (entered ? (TheScriptEngine->getUnitNamed(pCastleParm)) : (TheScriptEngine->getUnitNamed(pCastleParm)));
	} else {
		if (!playerParm)
			return false;
		Player *player = ThePlayerList->getPlayerFromMask(TheScriptEngine->rva00357475(playerParm->getString(), 0));
		if (player)
			return false;
		castle = ThePartitionManager->getClosestObject(obj->getPosition(), REALLY_FAR, 0,
			Rva0004584D((const BfmeFixedStorage0004543D &)Rva00045411BitSet(0, 0x78), *(const BfmeFixedStorage0004543D *)&KINDOFMASK_NONE)
				.link(&Rva0026137EFilter(player, true)));
	}
	if (!castle)
		return false;
	CastleBehavior *behavior = (CastleBehavior *)castle->findModule(CastleBehavior::rva0003955DA());
	if (!behavior)
		return false;
	int i = 0;
	do {
		++i;
		PolygonTrigger *area = (PolygonTrigger *)((Rva00395E53 *)behavior)->rva00395E53(i);
		if (!area)
			return false;
		if (entered)
		{
			if (obj->didEnter(area))
				return true;
		}
		else
		{
			if (obj->didExit(area))
				return true;
		}
	} while (i < 7);
	return false;
}
