// cl: /O1 /MD /GX /arch:SSE
//
// EntEnragedUpdate members that ask the partition manager whether anything
// qualifying is near (+0x04 the module data, +0x08 the object; both called
// from the unrowed 0x004B2761, at 0x004B2847 and 0x004B2857). Each is true
// when an object within the module data's +0x14 range (2D centre) passes:
//
//   0x004B25C9  the 0x002614EC filter over the module data's +0x18 and the
//               object's controlling player, the 0x002611AF one and the
//               allied (relationship 4) one
//   0x004B266D  the 0x00261058 player filter, the 0x002614EC one over the
//               module data's +0x1C, and alive
//
// The filters are BFME2's partition filter chain (the view
// AIStructureCreepTactic.cpp documents): a vptr, the +0x04 link to the next
// filter (PartitionFilter::link 0x00625790), then each filter's members;
// address-derived names after the out-of-line ctor, else after allow
// (slot 1).
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

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead (status bit 0),
// ZH's PartitionFilterAlive.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// vftable 0x00BF8FE4, allow 0x0026109D: +0x08 the object's controlling player
// (or none), +0x0C a flag.
class Rva00261058 : public Rva000421C8
{
public:
	Rva00261058(Object *obj, bool flag);
	virtual bool allow(Object *obj);
	Player *m_player;
	bool m_flag;
};

// vftable 0x00BFBC90, allow 0x00260EB1, getPlayerMask 0x00260E6A: the object,
// relationship flags and whether a hit allows.
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

// vftable 0x00C56930, allow 0x002611AF: no members of its own.
class Rva002611AFFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
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

struct EntEnragedUpdateModuleData
{
	char m_pad00[0x14];
	float m_range;		// +0x14
	char m_18[4];		// +0x18
	char m_1C[4];		// +0x1C
};

class EntEnragedUpdate
{
public:
	bool rva004B25C9();
	bool rva004B266D();
private:
	const void *m_vtable;
	const EntEnragedUpdateModuleData *m_moduleData;	// +0x04
	Object *m_object;				// +0x08
};

bool EntEnragedUpdate::rva004B25C9()
{
	Object *obj = m_object;
	const EntEnragedUpdateModuleData *md = m_moduleData;
	Rva002614ECFilter same(md->m_18, obj->getControllingPlayer(), true);
	Rva00260EB1Filter allies(obj, 4, false);
	Rva002611AFFilter third;
	same.link(&third);
	same.link(&allies);
	return ThePartitionManager->getClosestObject(&obj->m_pos, md->m_range, 1, &same) != 0;
}

bool EntEnragedUpdate::rva004B266D()
{
	const EntEnragedUpdateModuleData *md = m_moduleData;
	Object *obj = m_object;
	Rva00261058 player(obj, false);
	Rva002614ECFilter same(md->m_1C, obj->getControllingPlayer(), true);
	Rva0026119DFilter alive;
	player.link(&same);
	player.link(&alive);
	return ThePartitionManager->getClosestObject(&obj->m_pos, md->m_range, 1, &player) != 0;
}
