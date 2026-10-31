// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX
//
// ?rva003C9D0D@ScriptActions@@QAEXABVAsciiString@@M@Z, retail 0x003C9D0D,
// 321 bytes (called from the action dispatcher 0x003CA4BE at 0x003CE56A).
// A BFME2 script action: walking the kind-7 objects that relate to the
// team's controlling player by flags 2 within the range of the team's
// centre (0x0039DA2A) from near to far, at the first whose body reports
// below 1 (body slot 5), every team member of kind 78 with an AI gets the
// AI command 0x0036F19B on it.
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
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b);
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};

// vftable 0x00C004D8, allow 0x00261409: the player's relationship to the
// object's team against the +0x10 flags (ZH's PartitionFilterRelationship
// analogue), +0x0C whether a hit allows.
class Rva00261409Filter : public Rva000421C8
{
public:
	Rva00261409Filter(Player *player, bool match, int flags)
		: m_player(player), m_match(match), m_flags(flags) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	Player *m_player;
	bool m_match;
	int m_flags;
};

struct Rva00045411BitSet
{
	Rva00045411BitSet(int unused, int bit);	// 0x00045411
	unsigned int m_bits[7];
};
template<int N> class BitFlags;
extern BitFlags<116> KINDOFMASK_NONE;

#include "../../../../Libraries/Include/Lib/Coord3D.h"

enum CommandSourceType
{
	CMD_FROM_SCRIPT = 1
};

// The +0x254 body module interface; only the slot this action calls.
class BodyModuleInterface
{
public:
	virtual void v00() = 0;
	virtual void v01() = 0;
	virtual void v02() = 0;
	virtual void v03() = 0;
	virtual void v04() = 0;
	virtual float getHealthRatio() const = 0;	// slot 5 (+0x14), compared with 1
};

class AICommandInterface
{
public:
	void rva0036F19B(Object *obj, CommandSourceType source);	// 0x0036F19B
};

class AIUpdateInterface
{
public:
	char m_pad00[0x20];
	AICommandInterface m_commands;	// +0x20
};

struct ThingTemplate
{
	bool isKindOf(int bit) const { return (m_kindOf[bit >> 3] >> (bit & 7)) & 1; }
	// LINK: same-body helper under a TU-unique name (identical inlined bytes); the isKindOf copy loses to the first-in-order copy. No flags touched.
	bool bfme_isKindOf_72c56(int bit) const { return (m_kindOf[bit >> 3] >> (bit & 7)) & 1; }
	char m_pad000[0x100];
	unsigned char m_kindOf[28];	// +0x100
};

class Object
{
public:
	bool isKindOf(int bit) const { return m_template->isKindOf(bit); }
	// LINK: same-body helper under a TU-unique name (identical inlined bytes); the Object::isKindOf copy loses to the first-in-order copy. No flags touched.
	bool bfme_isKindOfObj_5d2a1(int bit) const { return m_template->bfme_isKindOf_72c56(bit); }
	AIUpdateInterface *getAIUpdateInterface() { return m_ai; }
	// LINK: same-body helper under a TU-unique name (identical inlined bytes); the getAIUpdateInterface copy loses to the first-in-order copy. No flags touched.
	AIUpdateInterface *bfme_getAIUpdateInterface_de3c5() { return m_ai; }
	BodyModuleInterface *getBodyModule() const { return m_body; }
	char m_pad000[4];
	const ThingTemplate *m_template;	// +0x04
	char m_pad008[0x254 - 8];
	BodyModuleInterface *m_body;		// +0x254
	AIUpdateInterface *m_ai;		// +0x258
};

template<class OBJ> class DLINK_ITERATOR
{
public:
	void advance();						// 0x00263526
	bool done() const { return m_cur == 0; }
	OBJ *cur() const { return m_cur; }
private:
	OBJ *m_cur;
	char m_pad[20];
};

#include "../../../Include/Common/TeamBFME2.h"

struct BfmeWideResult
{
	Object *next() throw();	// 0x00045623
	~BfmeWideResult();	// 0x0004AA28
	void *m_value;
};

class PartitionManager
{
public:
	BfmeWideResult iterateObjectsInRange(const Coord3D *pos, float radius, int distCalc,
		Rva000421C8 *filters, int order);	// 0x00625610
};
extern PartitionManager *ThePartitionManager;

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
public:
	void rva003C9D0D(const AsciiString &teamName, float range);
};

void ScriptActions::rva003C9D0D(const AsciiString &teamName, float range)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team)
		return;

	Coord3D center;
	BfmeWideResult iter = ThePartitionManager->iterateObjectsInRange(team->rva0039DA2A(&center), range, 0,
		Rva00261409Filter(team->getControllingPlayer(), true, 2)
			.link(&Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 7),
				*(BfmeFixedStorage0004543D *)&KINDOFMASK_NONE)), 1);

	Object *building;
	while ((building = iter.next()) != 0) {
		BodyModuleInterface *body = building->getBodyModule();
		if (body && body->getHealthRatio() < 1.0f) {
			for (DLINK_ITERATOR<Object> it = team->iterate_TeamMemberList(); !it.done(); it.advance()) {
				Object *member = it.cur();
				if (member->bfme_isKindOfObj_5d2a1(78) && member->bfme_getAIUpdateInterface_de3c5())
					member->bfme_getAIUpdateInterface_de3c5()->m_commands.rva0036F19B(building, CMD_FROM_SCRIPT);
			}
			break;
		}
	}
}
