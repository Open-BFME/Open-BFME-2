// ?doTeamGarrisonNearestBuilding@ScriptActions@@IAEXABVAsciiString@@@Z
// partial score=0.85 date=2026-10-04
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX /arch:SSE
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

// vftable 0x00BF91BC, allow 0x002611BF.
class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

// The base filter's slot 2 is the trivial virtual retail shares across many
// vftable slots (0x0036CC7A); bind the declaration to that row.
#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

// vftable 0x00C1FE1C, allow 0x00261478: +0x08 a player, +0x0C whether a
// match allows, +0x10 the command source (Zero Hour's
// PartitionFilterGarrisonableByPlayer).
class Rva00261478Filter : public Rva000421C8
{
public:
	Rva00261478Filter(Player *player, bool match, int source)
		: m_player(player), m_match(match), m_source(source) {}
	virtual bool allow(Object *obj);
	Player *m_player;
	bool m_match;
	int m_source;
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum CommandSourceType
{
	CMD_FROM_SCRIPT = 1
};

// The +0x250 contain module interface; only the slots this action calls.
class ContainModuleInterface
{
public:
	virtual void v00() = 0;
	virtual void v01() = 0;
	virtual void v02() = 0;
	virtual void v03() = 0;
	virtual void v04() = 0;
	virtual void v05() = 0;
	virtual void v06() = 0;
	virtual void v07() = 0;
	virtual void v08() = 0;
	virtual void v09() = 0;
	virtual void v0A() = 0;
	virtual void v0B() = 0;
	virtual void v0C() = 0;
	virtual void v0D() = 0;
	virtual void v0E() = 0;
	virtual void v0F() = 0;
	virtual void v10() = 0;
	virtual void v11() = 0;
	virtual void v12() = 0;
	virtual void v13() = 0;
	virtual void v14() = 0;
	virtual void v15() = 0;
	virtual void v16() = 0;
	virtual void v17() = 0;
	virtual void v18() = 0;
	virtual void v19() = 0;
	virtual void v1A() = 0;
	virtual void v1B() = 0;
	virtual int getContainMax() const = 0;	// slot 28 (+0x70)
	virtual void v1D() = 0;
	virtual void v1E() = 0;
	virtual void v1F() = 0;
	virtual void v20() = 0;
	virtual void v21() = 0;
	virtual void v22() = 0;
	virtual void v23() = 0;
	virtual void v24() = 0;
	virtual void v25() = 0;
	virtual void v26() = 0;
	virtual void v27() = 0;
	virtual void v28() = 0;
	virtual void v29() = 0;
	virtual void v2A() = 0;
	virtual void v2B() = 0;
	virtual void v2C() = 0;
	virtual void v2D() = 0;
	virtual void v2E() = 0;
	virtual void v2F() = 0;
	virtual void v30() = 0;
	virtual void v31() = 0;
	virtual void v32() = 0;
	virtual void v33() = 0;
	virtual void v34() = 0;
	virtual void v35() = 0;
	virtual void v36() = 0;
	virtual void v37() = 0;
	virtual void v38() = 0;
	virtual void v39() = 0;
	virtual void v3A() = 0;
	virtual void v3B() = 0;
	virtual void v3C() = 0;
	virtual void v3D() = 0;
	virtual void v3E() = 0;
	virtual void v3F() = 0;
	virtual void v40() = 0;
	virtual void v41() = 0;
	virtual void v42() = 0;
	virtual void v43() = 0;
	virtual void v44() = 0;
	virtual int getContainCount(int flags) const = 0;	// slot 69 (+0x114)
};

class AICommandInterface
{
public:
	void rva0026C347(Object *obj, CommandSourceType source);	// 0x0026C347
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
	char m_pad000[0x100];
	unsigned char m_kindOf[28];	// +0x100
};

class Object
{
public:
	bool isKindOf(int bit) const { return m_template->isKindOf(bit); }
	AIUpdateInterface *getAIUpdateInterface() { return m_ai; }
	ContainModuleInterface *getContain() const { return m_contain; }
	const Coord3D *getPosition() const { return &m_pos; }
	char m_pad000[4];
	const ThingTemplate *m_template;	// +0x04
	char m_pad008[0x38 - 8];
	Coord3D m_pos;			// +0x38
	char m_pad044[0x250 - 0x44];
	ContainModuleInterface *m_contain;	// +0x250
	char m_pad254[0x258 - 0x254];
	AIUpdateInterface *m_ai;	// +0x258
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

class Team
{
public:
	Player *getControllingPlayer() const;			// 0x0039D7CF
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;	// 0x00263864
};

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

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString name, bool exact);	// 0x003584E9
};
extern ScriptEngine *TheScriptEngine;

#define REALLY_FAR (100000 * 10.0f)

class ScriptActions
{
protected:
	void doTeamGarrisonNearestBuilding(const AsciiString &teamName);
};

void ScriptActions::doTeamGarrisonNearestBuilding(const AsciiString &teamName)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName, false);
	if (!theTeam)
		return;

	DLINK_ITERATOR<Object> diter = theTeam->iterate_TeamMemberList();
	Object *leader = diter.cur();
	if (!leader)
		return;

	BfmeWideResult iter = ThePartitionManager->iterateObjectsInRange(leader->getPosition(), REALLY_FAR, 3,
		Rva00261478Filter(theTeam->getControllingPlayer(), true, CMD_FROM_SCRIPT).link(&Rva002611BFFilter(leader)), 1);

	Object *theBuilding;
	while ((theBuilding = iter.next()) != 0) {
		ContainModuleInterface *cmi = theBuilding->getContain();
		if (!cmi)
			continue;

		int slotsAvailable = cmi->getContainMax() - cmi->getContainCount(0);
		for (int i = 0; i < slotsAvailable; ) {
			Object *obj = diter.cur();
			if (diter.done() || !obj)
				return;

			AIUpdateInterface *ai = obj->getAIUpdateInterface();
			if (ai && obj->isKindOf(72) && !obj->isKindOf(91)) {
				ai->m_commands.rva0026C347(theBuilding, CMD_FROM_SCRIPT);
				++i;
			}
			diter.advance();
		}
	}
}

