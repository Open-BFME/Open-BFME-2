// ?rva003C24F0@ScriptActions@@QAEPAVObject@@PBUCoord3D@@PAVObjectTypes@@PAVPlayer@@_N@Z
// partial score=0.88 date=2026-10-04
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

// vftable 0x00C1FE10, allow 0x0026149C: +0x08 a flag.
class Rva0026149CFilter : public Rva000421C8
{
public:
	Rva0026149CFilter(bool match) : m_match(match) {}
	virtual bool allow(Object *obj);
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
		const ThingTemplate *templ = TheThingFactory->findTemplate(types->getNthInList(i));
		if (!templ)
			continue;
		Rva00261750Filter thing(templ, true);
		Rva0026137EFilter owned(player, true);
		Rva0026149CFilter third(false);
		if (player)
			thing.link(&owned);
		if (flag)
			thing.link(&third);
		Object *obj = ThePartitionManager->getClosestObject(pos, REALLY_FAR, 0, &thing);
		if (obj) {
			float dx = pos->x - obj->getPosition()->x;
			float dy = pos->y - obj->getPosition()->y;
			float dz = pos->z - obj->getPosition()->z;
			float distSqr = dx * dx + dy * dy + dz * dz;
			if (distSqr < bestDistSqr) {
				bestDistSqr = distSqr;
				bestObj = obj;
			}
		}
	}
	return bestObj;
}


