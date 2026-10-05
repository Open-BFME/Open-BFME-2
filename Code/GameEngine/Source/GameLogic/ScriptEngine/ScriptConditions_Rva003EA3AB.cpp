// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX /arch:SSE
//
// ScriptConditions::rva003EA3AB, retail 0x003EA3AB, 443 bytes (caller
// 0x003EAEDD in the condition dispatcher 0x003EA9AF). Zero Hour's
// evaluateTypeSighted made BFME2: for each player of the parameter's player
// mask (TheScriptEngine 0x00357B82, ThePlayerList::getEachPlayerFromMask),
// whether any object that player owns, alive, of the parsed ObjectTypes
// (0x00566E6C into an ObjectTypesTemp) lies within the named unit's vision
// range through BFME2's partition filter chain (the view
// AIStructureCreepTactic.cpp documents).
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

struct Coord3D
{
	float x;
	float y;
	float z;
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

class ThingTemplate
{
public:
	const AsciiString &getName() const { return m_name; }
	char m_pad00[0x64];
	AsciiString m_name;	// +0x64
};

class Object
{
public:
	float getVisionRange() const;	// 0x0028DDE0
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_pos; }
	char m_pad000[0x04];
	const ThingTemplate *m_template;	// +0x04
	char m_pad008[0x38 - 0x08];
	Coord3D m_pos;		// +0x38
};

class ObjectTypes
{
public:
	virtual ~ObjectTypes();
	bool isInSet(const AsciiString &name) const;	// 0x00376A62
};

class ObjectTypesTemp
{
public:
	ObjectTypesTemp();	// 0x003BA7FF
	~ObjectTypesTemp() { ::delete m_types; }
	ObjectTypes *m_types;
};

class Parameter
{
public:
	unsigned char m_beforeInt[8];
	int m_int;
	float m_real;
	AsciiString m_string;	// +0x10
};

void Rva00566E6CParse(Parameter *typeParm, ObjectTypes *types);	// 0x00566E6C

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
	bool rva003EA3AB(const AsciiString &unitName, Parameter *typeParm, Parameter *playerParm);
};

bool ScriptConditions::rva003EA3AB(const AsciiString &unitName, Parameter *typeParm, Parameter *playerParm)
{
	Object *theObj = TheScriptEngine->getUnitNamed(unitName);
	if (!theObj)
		return false;
	int mask = TheScriptEngine->rva00357B82(playerParm);
	while (mask) {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		ObjectTypesTemp types;
		Rva00566E6CParse(typeParm, types.m_types);
		BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(theObj->getPosition(),
			theObj->getVisionRange(), 0,
			Rva0026137EFilter(player, true).link(Rva0026119DFilter().link(Rva00261058(theObj, false).link(
				Rva00261513Filter(theObj, true, -1.0f).link(&Rva002611BFFilter(theObj))))), 0);
		Object *obj;
		while ((obj = hits.next()) != 0)
			if (types.m_types->isInSet(obj->getTemplate()->getName()))
				return true;
	}
	return false;
}
