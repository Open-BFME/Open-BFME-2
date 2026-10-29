// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX
//
// ScriptConditions::evaluateSkirmishSuppliesWithinDistancePerimeter, retail 0x003EA566, 510 bytes (caller
// 0x003EBAD9 in the condition dispatcher 0x003EA9AF). A BFME2 script
// condition: for each player of the parameter's player mask (TheScriptEngine
// 0x00357B82), whether some structure (KindOf bit 7) in the named trigger
// area's circle (its centre, its radius plus the radius parameter) that the
// 0x00261409 filter accepts for that player with flags 8 and that has a
// SupplyWarehouseDockUpdate module holds supplies (boxes at the module's
// +0x88 times the player's supply box value) worth more than the value
// parameter. The scan goes through BFME2's partition filter chain (the view
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

// vftable 0x00BFAD1C, allow 0x002611DD: no members of its own.
class Rva002611DDFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// vftable 0x00C004D8, allow 0x00261409: the player's relationship to the
// object's team against the +0x10 flags, +0x0C whether a hit allows.
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

// vftable 0x00BC2908, allow 0x002610DE: accept what has every kind of the
// first mask and none of the second.
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

#include "../../../../Libraries/Include/Lib/Coord3D.h"

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

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);	// 0x00148E1A
};
extern NameKeyGenerator *TheNameKeyGenerator;

// SupplyWarehouseDockUpdate as this condition reads it.
class Module
{
public:
	virtual void moduleSlot();
	char m_pad04[0x84];
	unsigned m_boxesStored; // +0x88 +0x88
};

class Object
{
	friend class ScriptConditions;
protected:
	Module *findModule(NameKeyType key) const;	// 0x0028B6D6
};

class Player
{
public:
	int getSupplyBoxValue();	// 0x002A9DAC
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(int &mask);	// 0x002A7BC9
};
extern PlayerList *ThePlayerList;

class Rva0030B719Shape
{
public:
	float getRadius() const;	// 0x0030B719
};

class PolygonTrigger
{
public:
	void getCenterPoint(Coord3D *pOutCoord) const;	// 0x002E38F3
	char m_pad00[0x08];
	Rva0030B719Shape m_shape;	// +0x08
};

class Parameter
{
public:
	unsigned char m_beforeInt[8];
	int m_int;
	float m_real;		// +0x0C
	AsciiString m_string;	// +0x10
};

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

#include "../../../Include/GameLogic/ScriptConditions.h"

bool ScriptConditions::evaluateSkirmishSuppliesWithinDistancePerimeter(Parameter *playerParm, Parameter *radiusParm, Parameter *areaParm,
	Parameter *valueParm)
{
	int mask = TheScriptEngine->rva00357B82(playerParm);
	while (mask) {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (!player)
			continue;
		PolygonTrigger *trigger = TheScriptEngine->getQualifiedTriggerAreaByName(areaParm->m_string);
		if (!trigger)
			continue;
		Coord3D center;
		trigger->getCenterPoint(&center);
		float extra = radiusParm->m_real;
		float radius = trigger->m_shape.getRadius() + extra;
		float value = valueParm->m_real;
		float best = 0.0f;
		BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(&center, radius, 0,
			Rva0004584D((const BfmeFixedStorage0004543D &)Rva00045411BitSet(0, 7), *(const BfmeFixedStorage0004543D *)&KINDOFMASK_NONE)
				.link(Rva00261409Filter(player, true, 8).link(&Rva002611DDFilter())), 0);
		Object *obj;
		while ((obj = hits.next()) != 0) {
			static NameKeyType key = TheNameKeyGenerator->nameToKey("SupplyWarehouseDockUpdate");
			Module *dock = obj->findModule(key);
			if (!dock)
				continue;
			unsigned boxes = dock->m_boxesStored;
			float supplies = (float)(boxes * player->getSupplyBoxValue());
			if (supplies > best)
				best = supplies;
		}
		if (best > value)
			return true;
	}
	return false;
}
