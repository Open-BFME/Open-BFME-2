// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX /arch:SSE
//
// ScriptConditions::rva003EA764, retail 0x003EA764, 280 bytes (caller 0x003EC55A in the condition
// dispatcher 0x003EA9AF). A BFME2 script condition: the number of objects
// within the range of the named Eva event's position (Eva 0x00DFDC30:
// event id 0x001DE78E, position 0x001DD670) that pass the member-less
// 0x00261D01 filter and belong to the parameter's player mask
// (TheScriptEngine 0x00357B82), compared with the value (0 <, 1 <=, 2 ==,
// 3 >=, 4 >, 5 !=); zero when the event or its position or the mask is
// missing.
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

// vftable 0x00C35B28, allow 0x00261D01: no members of its own.
class Rva00261D01Filter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// vftable 0x00C1FDE0, allow 0x002613AF, slot 2 0x002613A3: +0x08 a player
// mask, +0x0C whether a match allows.
class Rva002613AFFilter : public Rva000421C8
{
public:
	Rva002613AFFilter(int playerMask, bool match) : m_playerMask(playerMask), m_match(match) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	int m_playerMask;
	bool m_match;
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Parameter;

class Eva
{
public:
	int rva001DE78E(const AsciiString *key);		// 0x001DE78E
	bool rva001DD670(int index, Coord3D *pos);		// 0x001DD670
};
extern Eva *TheEva;

struct BfmeWideHit
{
	Object *m_object;
	float m_distance;
};

struct BfmeWidePayload
{
	BfmeWideHit *m_begin;
	BfmeWideHit *m_end;
};

struct BfmeWideResult
{
	int size() const { return m_value->m_end - m_value->m_begin; }
	~BfmeWideResult();	// 0x0004AA28
	BfmeWidePayload *m_value;
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
	int rva00357B82(Parameter *playerParm);	// 0x00357B82
};
extern ScriptEngine *TheScriptEngine;

class ScriptConditions
{
public:
	bool rva003EA764(Parameter *playerParm, float range, const AsciiString *name, int comparison, int value);
};

bool ScriptConditions::rva003EA764(Parameter *playerParm, float range, const AsciiString *name, int comparison, int value)
{
	int count;
	int index = TheEva->rva001DE78E(name);
	Coord3D pos;
	int mask;
	if (index == -1)
		count = 0;
	else if (!TheEva->rva001DD670(index, &pos))
		count = 0;
	else if ((mask = TheScriptEngine->rva00357B82(playerParm)) == 0)
		count = 0;
	else {
		Rva00261D01Filter first;
		Rva002613AFFilter owned(mask, true);
		first.link(&owned);
		BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(&pos, range, 2, &first, 0);
		count = hits.size();
	}
	switch (comparison) {
	case 0: return count < value;
	case 1: return count <= value;
	case 2: return count == value;
	case 3: return count >= value;
	case 4: return count > value;
	case 5: return count != value;
	}
	return false;
}
