// cl: /Ireference/shims/bfme2_ascii /O1 /MD /GX /arch:SSE
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
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b);
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};

// The base filter's slot 2 is the trivial virtual retail shares across many
// vftable slots (0x0036CC7A); bind the declaration to that row.
#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

struct Rva00045411BitSet
{
	Rva00045411BitSet(int unused, int bit);	// 0x00045411
	unsigned int m_bits[7];
};
extern unsigned char g_00DFEFA4StoragePrototype[28];

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

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object
{
public:
	char m_pad000[0x38];
	Coord3D m_pos;		// +0x38
};

class Parameter
{
public:
	unsigned char m_beforeInt[8];
	int m_int;
	float m_real;
	AsciiString m_string;	// +0x10
};

class Team
{
public:
	Object *rva0039E8EB();			// 0x0039E8EB
	void rva0039E5B9(Coord3D *center);	// 0x0039E5B9
};

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString name, bool exact);			// 0x003584E9
	Object *getUnitNamed(Parameter *parameter);				// 0x003588E7
	int rva00357475(const AsciiString &name, bool *found);			// 0x00357475
};
extern ScriptEngine *TheScriptEngine;

class PlayerList
{
public:
	Player *getPlayerFromMask(int mask);	// 0x002A7B91
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
	bool rva002F477E(Object *obj, const Coord3D *from, const Coord3D *to, int flags);
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }
	char m_pad00[0x10];
	Pathfinder *m_pathfinder;	// +0x10
};
extern AI *TheAI;

class ScriptConditions
{
public:
	bool rva003E5CB1(Parameter *unitParm, Parameter *playerParm);
	bool rva003E83AF(Parameter *teamParm, Parameter *playerParm);
};

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
			*(BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype).link(&Rva0026137EFilter(player, true)));
	if (found == 0)
		return false;
	return TheAI->pathfinder()->rva002F477E(obj, &obj->m_pos, &found->m_pos, 0);
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
			*(BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype).link(&Rva0026137EFilter(player, true)));
	if (found == 0)
		return false;
	return TheAI->pathfinder()->rva002F477E(obj, &obj->m_pos, &found->m_pos, 0);
}
