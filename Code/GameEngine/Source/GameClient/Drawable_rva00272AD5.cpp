// cl: /O1 /MD /GX /arch:SSE
//
// ?rva00272AD5@Drawable@@QAEPAVObject@@XZ, retail 0x00272AD5, 214 bytes.
// A Drawable member (callers at 0x00278A38, 0x00278B6C and 0x00278BFA in
// Drawable::rva0027893E): the closest object to the drawable's position
// (+0x38) within the +0x80 float of the global at 0x00DFDC30 that has kind
// 0x7A or 0x9E and passes alive, the member-less 0x002611DD filter, the
// player filter over ThePlayerList's +0x10 player, and the 0x00261790
// near-position filter.
//
// The filters are BFME2's partition filter chain (the view
// AIStructureCreepTactic.cpp documents): a vptr, the +0x04 link to the next
// filter (PartitionFilter::link 0x00625790), then each filter's members;
// address-derived names after the out-of-line ctor, else after allow
// (slot 1). Retail updates the unwind state only after the kind filter is
// built, so the bitset and kind-filter ctors are declared throw() here.
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

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead (status bit 0),
// ZH's PartitionFilterAlive.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// vftable 0x00BFAF94: the other one-mask filter.
class Rva0027231F : public Rva000421C8
{
public:
	Rva0027231F(const BfmeFixedStorage0004543D &mask) throw();
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
};

// The base filter's slot 2 is the trivial virtual retail shares across many
// vftable slots (0x0036CC7A); bind the declaration to that row.
#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

// A KindOfMaskType with two kinds set (0x0006EE7A).
struct Rva0006EE7A
{
	Rva0006EE7A(int unused, int bit1, int bit2) throw();
	unsigned int m_bits[7];
};

// vftable 0x00BFAD1C, allow 0x002611DD: no members of its own.
class Rva002611DDFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

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

class Drawable;

// vftable 0x00BF9000, allow 0x002617E8 (ctor 0x00261790): the thing's
// position and its radius scaled by a GlobalData factor, and a flag.
class Rva00261790 : public Rva000421C8
{
public:
	Rva00261790(Drawable *thing, bool flag);
	virtual bool allow(Object *obj);
	float m_pos[3];
	float m_radius;
	bool m_flag;
};

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

class PlayerList
{
public:
	char m_pad00[0x10];
	Player *m_10;		// +0x10
};
extern PlayerList *ThePlayerList;

struct Rva00DFDC30
{
	char m_pad00[0x80];
	float m_80;		// +0x80
};
extern Rva00DFDC30 *g_Va00DFDC30;

class Drawable
{
public:
	Object *rva00272AD5();
	char m_pad000[0x38];
	Coord3D m_pos;		// +0x38
};

Object *Drawable::rva00272AD5()
{
	Rva0026119DFilter alive;
	Rva002611DDFilter second;
	Rva0026137EFilter player(ThePlayerList->m_10, true);
	Rva0027231F kinds(*(BfmeFixedStorage0004543D *)&Rva0006EE7A(0, 0x7a, 0x9e));
	Rva00261790 near(this, true);
	kinds.link(&alive)->link(&second)->link(&player)->link(&near);
	return ThePartitionManager->getClosestObject(&m_pos, g_Va00DFDC30->m_80, 0, &kinds);
}
