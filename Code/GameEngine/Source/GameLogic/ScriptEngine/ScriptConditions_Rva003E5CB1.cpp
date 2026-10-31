// cl: /Ireference/shims/bfme2_ascii /MD /GX
//
// ?rva003E5CB1@ScriptConditions@@QAE_NPAVParameter@@0@Z, retail 0x003E5CB1,
// 228 bytes (caller 0x003EB385 in the condition dispatcher 0x003EA9AF). A
// BFME2 script condition: false unless the named unit exists and the
// player parameter resolves to no player; then whether a path exists from
// the unit to the closest kind-120 object (within 1000000) that passes the
// player filter for that (null) player.
//
// 0x003E83AF (caller 0x003EB3AB) is the team twin: the team's first member
// (0x0039E8EB) and the closest such object to the team's centre
// (0x0039E5B9).
//
// The filters are BFME2's partition filter chain (the view
// AIStructureCreepTactic.cpp documents): a vptr, the +0x04 link to the next
// filter (PartitionFilter::link 0x00625790), then each filter's members;
// address-derived names after the out-of-line ctor, else after allow
// (slot 1).
#include "ascii_string.h"

class Object;
class Player;

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

// A KindOfMaskType as the mask filters copy it (0x0004543D).
class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};

// vftable 0x00BC2908, allow 0x002610DE: accept what has every kind of the
// first mask and none of the second (ZH's PartitionFilterAcceptByKindOf).
class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b) throw();
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08; // +0x08
	BfmeFixedStorage0004543D m_24; // +0x24
};

struct Rva00045411BitSet
{
public:
	Rva00045411BitSet(int unused, int bit) throw(); // 0x00045411
	unsigned m_bits[7]; // +0x00
};
template <int N> class BitFlags;
extern BitFlags<116> KINDOFMASK_NONE;

// vftable 0x00BFAD28, allow 0x0026137E, slot 2 0x00261368: +0x08 a
// player, +0x0C whether a hit allows.
class Rva0026137EFilter : public Rva000421C8
{
public:
	Rva0026137EFilter(Player *player, bool match) : m_player(player), m_match(match) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	Player *m_player;
	bool m_match;
};

#include "../../../../Libraries/Include/Lib/Coord3D.h"

enum ObjectStatusTypes { OBJECT_STATUS_NONE = 0 };
enum SpecialPowerType { SPECIAL_INVALID = 0 };
enum NameKeyType
{
    NAMEKEY_INVALID = 0
};
enum CellShroudStatus { CELLSHROUD_CLEAR, CELLSHROUD_FOGGED, CELLSHROUD_SHROUDED, CELLSHROUD_COUNT };
class Rva00261C89;
class Parameter;
class Module;
class ContainModuleInterface;
class ScriptConditions;
class AsciiString;
class PolygonTrigger;
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

#include "../../../Include/Common/TeamBFME2.h"

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

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

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *pos, float maxDist, int dc,
		Rva000421C8 *filters);	// 0x00625360
};
extern PartitionManager *ThePartitionManager;

class Pathfinder
{
public:
	bool QuickDoesPathExist(Object *obj, const Coord3D *from, const Coord3D *to, int x);
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_10; }
	char m_pad[0x10]; // +0x00
	Pathfinder *m_10; // +0x10
};
extern AI *TheAI;

#include "../../../Include/GameLogic/ScriptConditions.h"

bool ScriptConditions::rva003E5CB1(Parameter *unitParm, Parameter *playerParm)
{
	Object *obj = TheScriptEngine->getUnitNamed(unitParm);
	if (obj == 0)
		return false;
	Player *player = ThePlayerList->getPlayerFromMask(TheScriptEngine->rva00357475(playerParm->m_string, 0));
	if (player != 0)
		return false;
	Object *found = ThePartitionManager->getClosestObject(&obj->m_pos, 1000000.0f, 0,
		Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 120),
			*(BfmeFixedStorage0004543D *)&KINDOFMASK_NONE).link(&Rva0026137EFilter(player, true)));
	if (found == 0)
		return false;
	return TheAI->pathfinder()->QuickDoesPathExist(obj, &obj->m_pos, &found->m_pos, 0);
}

bool ScriptConditions::rva003E83AF(Parameter *teamParm, Parameter *playerParm)
{
	Team *team = TheScriptEngine->getTeamNamed(teamParm->m_string, false);
	if (team == 0)
		return false;
	Object *obj = team->rva0039E8EB();
	if (obj == 0)
		return false;
	Player *player = ThePlayerList->getPlayerFromMask(TheScriptEngine->rva00357475(playerParm->m_string, 0));
	if (player != 0)
		return false;
	Coord3D center;
	team->rva0039E5B9(&center);
	Object *found = ThePartitionManager->getClosestObject(&center, 1000000.0f, 0,
		Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 120),
			*(BfmeFixedStorage0004543D *)&KINDOFMASK_NONE).link(&Rva0026137EFilter(player, true)));
	if (found == 0)
		return false;
	return TheAI->pathfinder()->QuickDoesPathExist(obj, &obj->m_pos, &found->m_pos, 0);
}
