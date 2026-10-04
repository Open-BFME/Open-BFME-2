// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX /arch:SSE
//
// ScriptConditions::rva003E56C5, retail 0x003E56C5, 422 bytes (caller
// 0x003EAE77 in the condition dispatcher 0x003EA9AF). Zero Hour's
// evaluateEnemySighted made BFME2: for each player of the parameter's player
// mask (0x00357B82), whether anything that player owns, in the alliance
// relationship (0x003E40AF) to the named unit, alive, not of KindOf bits 89
// or 134, lies within the unit's vision range through BFME2's partition
// filter chain (the view AIStructureCreepTactic.cpp documents).
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

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// vftable 0x00BF8FE4, allow 0x0026109D; the out-of-line ctor 0x00261058.
class Rva00261058 : public Rva000421C8
{
public:
	Rva00261058(Object *obj, bool flag);	// 0x00261058
	virtual bool allow(Object *obj);
	Player *m_player;
	bool m_flag;
};

// vftable 0x00C0719C, allow 0x00261513: +0x08 an object, +0x0C a flag,
// +0x10 a float.
class Rva00261513Filter : public Rva000421C8
{
public:
	Rva00261513Filter(const Object *obj, bool flag, float value)
		: m_obj(obj), m_flag(flag), m_value(value) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
	bool m_flag;
	float m_value;
};

// vftable 0x00BF91BC, allow 0x002611BF.
class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

// vftable 0x00BFBC90, allow 0x00260EB1: +0x08 the object, +0x0C
// relationship flags, +0x10 whether a hit allows.
class Rva00260EB1Filter : public Rva000421C8
{
public:
	Rva00260EB1Filter(const Object *obj, int flags, bool match)
		: m_obj(obj), m_flags(flags), m_match(match) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	const Object *m_obj;
	int m_flags;
	bool m_match;
};

// The 224-bit KindOf mask; the (unused, bit, bit) constructor is 0x0006EE7A.
class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(int unused, int bit1, int bit2) throw();	// 0x0006EE7A
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};

// vftable 0x00BC2908, allow 0x002610DE: accept what has every kind of the
// first mask and none of the second.
class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b) throw();
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};
extern unsigned char g_00DFEFA4StoragePrototype[28];

struct Coord3D
{
	float x;
	float y;
	float z;
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *pos, float maxDist, int dc,
		Rva000421C8 *filters);	// 0x00625360
};
extern PartitionManager *ThePartitionManager;

class Object
{
public:
	float getVisionRange() const;	// 0x0028DDE0
	const Coord3D *getPosition() const { return &m_pos; }
	char m_pad000[0x38];
	Coord3D m_pos;		// +0x38
};

class Parameter
{
public:
	int getInt() const { return m_int; }
	unsigned char m_beforeInt[8];
	int m_int;		// +0x08
	float m_real;
	AsciiString m_string;	// +0x10
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
	Object *getUnitNamed(const AsciiString &name);	// 0x003588E7
	int rva00357B82(Parameter *playerParm);		// 0x00357B82
};
extern ScriptEngine *TheScriptEngine;

class ScriptConditions
{
public:
	int rva003E40AF(int alliance);	// 0x003E40AF
	bool rva003E56C5(const AsciiString &unitName, Parameter *allianceParm, Parameter *playerParm);
};

bool ScriptConditions::rva003E56C5(const AsciiString &unitName, Parameter *allianceParm, Parameter *playerParm)
{
	Object *theObj = TheScriptEngine->getUnitNamed(unitName);
	if (!theObj)
		return false;
	int relationDescriber = rva003E40AF(allianceParm->getInt());
	int mask = TheScriptEngine->rva00357B82(playerParm);
	if (!mask)
		return false;
	do {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (ThePartitionManager->getClosestObject(theObj->getPosition(), theObj->getVisionRange(), 0,
				Rva0026137EFilter(player, true).link(Rva00260EB1Filter(theObj, relationDescriber, false).link(
					Rva0026119DFilter().link(Rva00261058(theObj, false).link(Rva002611BFFilter(theObj).link(
						Rva00261513Filter(theObj, true, -1.0f).link(
							&Rva0004584D(*(const BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype,
								BfmeFixedStorage0004543D(0, 0x59, 0x86))))))))) != 0)
			return true;
	} while (mask);
	return false;
}
