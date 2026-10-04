// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX /arch:SSE
//
// BFME2 script actions that name the object of a type nearest a team.
//
//   0x003C4625  (called from the action dispatcher 0x003CA4BE at
//               0x003CDD4D): the closest object to the team's centre that
//               the team's controlling player owns, of the given ObjectTypes
//               list (through the helper 0x003C24F0) or else the given
//               template; the script name then goes to it (0x00208968 and
//               0x0020A5FF, both TheScriptEngine members)
//   0x003C55A6  (called from the dispatcher 0x003CA4BE at 0x003CC7FF): the
//               same search from the team's centre for each player of the
//               named player mask in turn; the first hit goes to the named
//               apply 0x003C420A
//
// The filters are BFME2's partition filter chain (the view
// AIStructureCreepTactic.cpp documents): a vptr, the +0x04 link to the next
// filter (PartitionFilter::link 0x00625790), then each filter's members;
// address-derived names after allow (slot 1), the ctors being inline.
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

// The base filter's slot 2 is the trivial virtual retail shares across many
// vftable slots (0x0036CC7A); bind the declaration to that row.
#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

class ThingTemplate;

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

// vftable 0x00C1FDEC, allow 0x00261750: +0x08 a thing template, +0x0C
// whether a match allows (Zero Hour's PartitionFilterThing).
class Rva00261750Filter : public Rva000421C8
{
public:
	Rva00261750Filter(const ThingTemplate *tmpl, bool match) : m_template(tmpl), m_match(match) {}
	virtual bool allow(Object *obj);
	const ThingTemplate *m_template;
	bool m_match;
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object
{
public:
	const Coord3D *getPosition() const { return &m_pos; }
	char m_pad000[0x38];
	Coord3D m_pos;			// +0x38
};

class ObjectTypes
{
public:
	int getListSize() const { return m_end - m_begin; }
	AsciiString getNthInList(unsigned int index) const;	// 0x002041AC
private:
	char m_pad00[8];
	AsciiString *m_begin;	// +0x08
	AsciiString *m_end;	// +0x0C
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);	// 0x002D06CA
};
extern ThingFactory *TheThingFactory;

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *pos, float maxDist, int dc,
		Rva000421C8 *filters);	// 0x00625360
};
extern PartitionManager *ThePartitionManager;

#define REALLY_FAR (100000 * 10.0f)

class Parameter
{
public:
	const AsciiString &getString() const { return m_string; }
	unsigned char m_beforeInt[8];
	int m_int;
	float m_real;
	AsciiString m_string;	// +0x10
};

class Team
{
public:
	Player *getControllingPlayer() const;	// 0x0039D7CF
	void rva0039E5B9(Coord3D *center);	// 0x0039E5B9
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(int &mask);	// 0x002A7BC9
};
extern PlayerList *ThePlayerList;

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString name, bool exact);			// 0x003584E9
	ObjectTypes *getObjectTypes(const AsciiString &name);			// 0x00357651
	int rva00357475(const AsciiString &name, bool *found);			// 0x00357475
	void rva00208968(const AsciiString &name, Object *obj);			// 0x00208968
	void rva0020A5FF(Object *obj, const AsciiString &name);			// 0x0020A5FF
};
extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
public:
	Object *rva003C24F0(const Coord3D *pos, ObjectTypes *types, Player *player, bool flag);
	void rva003C4625(const AsciiString &objectType, Parameter *teamParm, const AsciiString &unitName);
	void rva003C420A(void *what, const AsciiString &name, Object *obj);	// 0x003C420A
	void rva003C55A6(void *what, const AsciiString &name, const AsciiString &objectType,
		const AsciiString &teamName, const AsciiString &playerName);
};

void ScriptActions::rva003C4625(const AsciiString &objectType, Parameter *teamParm, const AsciiString &unitName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamParm->getString(), false);
	if (!team)
		return;
	Coord3D pos;
	team->rva0039E5B9(&pos);
	Object *obj;
	ObjectTypes *types = TheScriptEngine->getObjectTypes(objectType);
	if (types) {
		obj = rva003C24F0(&pos, types, team->getControllingPlayer(), false);
	} else {
		const ThingTemplate *templ = TheThingFactory->findTemplate(objectType);
		if (!templ)
			return;
		obj = ThePartitionManager->getClosestObject(&pos, REALLY_FAR, 0,
			Rva00261750Filter(templ, true).link(&Rva0026137EFilter(team->getControllingPlayer(), true)));
	}
	if (obj) {
		TheScriptEngine->rva00208968(unitName, obj);
		TheScriptEngine->rva0020A5FF(obj, unitName);
	}
}

void ScriptActions::rva003C55A6(void *what, const AsciiString &name, const AsciiString &objectType,
	const AsciiString &teamName, const AsciiString &playerName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team)
		return;
	Coord3D pos;
	team->rva0039E5B9(&pos);
	int mask = TheScriptEngine->rva00357475(playerName, 0);
	if (!mask)
		return;
	do {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		Object *obj;
		ObjectTypes *types = TheScriptEngine->getObjectTypes(objectType);
		if (types) {
			obj = rva003C24F0(&pos, types, player, false);
		} else {
			const ThingTemplate *templ = TheThingFactory->findTemplate(objectType);
			if (!templ)
				continue;
			obj = ThePartitionManager->getClosestObject(&pos, REALLY_FAR, 0,
				Rva00261750Filter(templ, true).link(&Rva0026137EFilter(player, true)));
		}
		if (obj) {
			rva003C420A(what, name, obj);
			return;
		}
	} while (mask);
}
