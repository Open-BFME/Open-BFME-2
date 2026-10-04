// cl: /O1 /MD /GX /arch:SSE
//
// ?rva004AF1CE@RespawnUpdate@@QAEPAVObject@@XZ, retail 0x004AF1CE, 143 bytes.
// A RespawnUpdate member (layout as RespawnUpdateCtor.cpp: +0x04 the module
// data, +0x08 the object; caller 0x004AFA17 in the unrowed 0x004AF92F): the
// closest object within 1000000 of ours that passes the 0x00260E2A filter
// (its controlling player) and the 0x002614EC one (the module data's +0x08,
// that player, true), or our own object when there is none.
//
// The filters are BFME2's partition filter chain (the view
// AIStructureCreepTactic.cpp documents): a vptr, the +0x04 link to the next
// filter (PartitionFilter::link 0x00625790), then each filter's members;
// address-derived names after allow (slot 1), the ctors being inline. The
// inline destructors only restore the base vftable, which cl drops here.
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

// vftable 0x00BFAD04, allow 0x00260E2A, slot 2 0x00260E1E: +0x08 a player.
class Rva00260E2AFilter : public Rva000421C8
{
public:
	Rva00260E2AFilter(Player *player) : m_player(player) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	Player *m_player;
};

// vftable 0x00BCECF0, allow 0x002614EC: +0x08 what to compare, +0x0C a
// player, +0x10 whether a hit allows.
class Rva002614ECFilter : public Rva000421C8
{
public:
	Rva002614ECFilter(const void *what, Player *player, bool match)
		: m_what(what), m_player(player), m_match(match) {}
	virtual bool allow(Object *obj);
	const void *m_what;
	Player *m_player;
	bool m_match;
};

// The base filter's slot 2 is the trivial virtual retail shares across many
// vftable slots (0x0036CC7A); bind the declaration to that row.
#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object
{
public:
	Player *getControllingPlayer() const;	// 0x0028AFA9
	char m_pad000[0x38];
	Coord3D m_pos;		// +0x38
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *pos, float maxDist, int dc,
		Rva000421C8 *filters);	// 0x00625360
};
extern PartitionManager *ThePartitionManager;

struct RespawnUpdateModuleData
{
	char m_pad00[8];
	char m_08[4];		// +0x08
};

class RespawnUpdate
{
public:
	Object *rva004AF1CE();

private:
	const void *m_vtable;
	const RespawnUpdateModuleData *m_moduleData;	// +0x04
	Object *m_object;				// +0x08
};

Object *RespawnUpdate::rva004AF1CE()
{
	Object *obj = m_object;
	const RespawnUpdateModuleData *md = m_moduleData;
	Rva00260E2AFilter player(obj->getControllingPlayer());
	Rva002614ECFilter same(md->m_08, obj->getControllingPlayer(), true);
	player.link(&same);
	Object *found = ThePartitionManager->getClosestObject(&obj->m_pos, 1000000.0f, 0, &player);
	if (found == 0)
		found = obj;
	return found;
}
