// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX /arch:SSE
//
// ScriptActions::doTeamGarrisonNearestBuilding, retail 0x003C8CCD (350B; ret 4)
// Target identity: the action dispatcher 0x003CA4BE calls it at 0x003CC18B;
// Zero Hour's ScriptActions::doTeamGarrisonNearestBuilding is the donor for
// the name and flow. Target body: the team by name (getTeamNamed 0x003584E9),
// its first member (iterate_TeamMemberList 0x00263864) as the leader, then
// the objects near to far (iterateObjectsInRange 0x00625610, distance mode 3,
// order 1) passing the garrisonable-by-player filter for the team's
// controlling player (getControllingPlayer 0x0039D7CF) and the leader's
// same-map filter; each building with a contain module (+0x250) takes
// getContainMax (slot 28) - getContainCount(0) (slot 69) members that have an
// AI (+0x258) and are kind 72 and not kind 91 (the AI enter command
// 0x0026C347, from script). Running out of members ends the action.
// Target differences from the donor: no money-hacker internet-centre
// switch and the filter chain is BFME 2's linked one. Donor-carried: the
// infantry / no-garrison meaning of kinds 72 and 91.
// Shape: the kind test is STLport's bitset::test over 32-bit words with its
// range check (dead for constant kinds). A byte-mask view folds kind 72 to
// an int constant 1 that, with the in-loop CMD_FROM_SCRIPT push, takes EBX
// from retail's 0; without the range check the two tests share one dword
// load. DLINK_ITERATOR<Object>::advance and Team::iterate_TeamMemberList are
// inline over the virtual-inheritance Object layout of
// TeamIterateTeamMemberList.cpp, as in ScriptActions_doMoveTeamTowardsNearest.cpp.
#include "ascii_string.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../Common/PartitionRangeQueryCallView.h"

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

void __cdecl __stl_throw_out_of_range(const char *msg);

struct BfmeKindOfBits
{
	__forceinline static unsigned int whichword(unsigned int pos) { return pos / 32; }
	__forceinline static unsigned int whichbit(unsigned int pos) { return pos % 32; }
	__forceinline static unsigned long maskbit(unsigned int pos) { return ((unsigned long)1) << whichbit(pos); }
	__forceinline unsigned long getword(unsigned int pos) const { return m_w[whichword(pos)]; }
	__forceinline bool test(unsigned int pos) const
	{
		if (pos >= 224)
			__stl_throw_out_of_range("bitset");
		return (getword(pos) & maskbit(pos)) != (unsigned long)0;
	}
	unsigned long m_w[7];
};

struct ThingTemplate
{
	__forceinline bool isKindOf(int t) const { return m_kindOf.test(t); }
	char m_pad000[0x100];
	BfmeKindOfBits m_kindOf;	// +0x100
};

class Object;

class BfmeObjectVirtualTail { public: unsigned char m_vt[4]; };

class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

class BfmeObjectVtbl { public: virtual void bfmeObjectSlot0(); };

class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList() const;
};

class BfmeObjectDlinkPad
{
public:
	const ThingTemplate *m_template;	// +0x04
	unsigned char m_pad08[0x38 - 8];
	Coord3D m_pos;			// +0x38
	unsigned char m_pad44[0x24];
};

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	__forceinline bool isKindOf(int bit) const { return m_template->isKindOf(bit); }
	AIUpdateInterface *getAIUpdateInterface() { return m_ai; }
	ContainModuleInterface *getContain() const { return m_contain; }
	const Coord3D *getPosition() const { return &m_pos; }
private:
	unsigned char m_pad070[0x250 - 0x70];
	ContainModuleInterface *m_contain;	// +0x250
	unsigned char m_pad254[0x258 - 0x254];
	AIUpdateInterface *m_ai;	// +0x258
};

template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS *(OBJCLASS::*GetNextFunc)() const;
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc) : m_cur(cur), m_getNextFunc(getNextFunc) {}
	void advance() { if (m_cur) m_cur = ((*m_cur).*(m_getNextFunc))(); }
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;
};

class Team
{
public:
	Player *getControllingPlayer() const;			// 0x0039D7CF
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const { return DLINK_ITERATOR<Object>(m_head, &Object::dlink_next_TeamMemberList); }
private:
	unsigned char m_pad00[0x38];
	Object *m_head;
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

	for (Object *theBuilding = iter.next(); theBuilding; theBuilding = iter.next()) {
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
