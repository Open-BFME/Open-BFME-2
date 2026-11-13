// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /arch:SSE /D_STLP_USE_STATIC_LIB
// stlport
// ?rva003C24F0@ScriptActions@@QAEPAVObject@@PBUCoord3D@@PAVObjectTypes@@PAVPlayer@@_N@Z, retail
// 0x003C24F0 (370 bytes, EH, RET 16): BFME 2's ScriptActions::findClosestObject
// (Open-BFME-1 ScriptActions_findClosestObject.cpp, 0x002F5D50, is the donor;
// the BFME 2 body adds a third filter, flag-gated). Over an ObjectTypes list:
// each entry's template gets a thing filter, linked to the player filter when a
// player is given and to a fixed filter when the flag is set, and the closest
// hit to the position wins by squared distance. Called by the nearest-object
// team actions (0x003C2662 0x003C276A 0x003C33C9 0x003C42B9 0x003C449C ...).
// Honest address name: the WorldBuilder name is not proven.
#include "../../../Include/GameLogic/ObjectTypesClass.h"

class Object;
class Player;

#include "../../../Include/GameLogic/PartitionFilter.h"

// The base filter's slot 2 is the trivial virtual retail shares across many
// vftable slots (0x0036CC7A); bind the declaration to that row.

class ThingTemplate;

// vftable 0x00BFAD28, allow 0x0026137E, slot 2 0x00261368: +0x08 a
// player, +0x0C whether a hit allows.
#include "../../../Include/GameLogic/Rva0026137EFilter.h"

// vftable 0x00C1FDEC, allow 0x00261750: +0x08 a thing template, +0x0C
// whether a match allows (Zero Hour's PartitionFilterThing).
class Rva00261750Filter : public Rva000421C8
{
public:
	Rva00261750Filter(const ThingTemplate *tmpl, bool match) : m_template(tmpl), m_match(match) {}
	virtual bool allow(Object *obj);
	const ThingTemplate *m_template; // +0x08
	bool m_match; // +0x0C
	char m_pad0D[0x3];
};

// vftable 0x00C1FE10, allow 0x0026149C: +0x08 a flag.
class Rva0026149CFilter : public Rva000421C8
{
public:
	Rva0026149CFilter(bool match) : m_match(match) {}
	virtual bool allow(Object *obj);
	bool m_match;
};

#include "../../../../Libraries/Include/Lib/Coord3D.h"

// Copy of the position, subtracted in place (Open-BFME-1's findClosestObject
// delta: Coord3D delta = *position; delta.sub(obj position); delta.lengthSqr()).
struct Rva003C24F0Delta
{
	Rva003C24F0Delta(const Coord3D &position) : x(position.x), y(position.y), z(position.z) {}
	void sub(const Coord3D *o) { x -= o->x; y -= o->y; z -= o->z; }
	float lengthSqr() const { return x * x + y * y + z * z; }
	float x;
	float y;
	float z;
};

#include "../Object/object.h"


#include "../../../Include/Common/ThingFactory.h"
extern ThingFactory *TheThingFactory;

#include "../../Common/PartitionRangeQueryCallView.h"
extern PartitionManager *ThePartitionManager;

#define REALLY_FAR (100000 * 10.0f)
#define HUGE_DIST 3.4028234663852886e+38f

class ScriptActions
{
public:
	Object *rva003C24F0(const Coord3D *pos, ObjectTypes *types, Player *player, bool flag);
};

Object *ScriptActions::rva003C24F0(const Coord3D *pos, ObjectTypes *types, Player *player, bool flag)
{
	Object *bestObj = 0;
	float bestDistSqr = HUGE_DIST;
	int count = types->getListSize();
	for (int i = 0; i < count; ++i) {
		const ThingTemplate *thingTemplate = TheThingFactory->findTemplate(types->getNthInList(i));
		if (!thingTemplate)
			continue;
		Rva00261750Filter thing(thingTemplate, true);
		Rva0026137EFilter owned(player, true);
		Rva0026149CFilter third(false);
		if (player)
			thing.link(&owned);
		if (flag)
			thing.link(&third);
		Object *obj = ThePartitionManager->getClosestObject(pos, 100000 * 10.0f, 0, &thing);
		if (obj) {
			Rva003C24F0Delta delta(*pos);
			delta.sub(obj->getPosition());
			float distSqr = delta.lengthSqr();
			if (distSqr < bestDistSqr) {
				bestDistSqr = distSqr;
				bestObj = obj;
			}
		}
	}
	return bestObj;
}


