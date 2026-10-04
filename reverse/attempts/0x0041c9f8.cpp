// ?rva0041C9F8@ActionManager@@QAE_NPBVObject@@PBUCoord3D@@PBVSpecialPowerTemplate@@@Z
// partial score=0.95 date=2026-10-04
// cl: /O1 /MD /GX /arch:SSE
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
};

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
	~BfmeWideResult();	// 0x0004AA28
	BfmeWidePayload *m_value;
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *pos, float maxDist, int dc,
		Rva000421C8 *filters);	// 0x00625360
	BfmeWideResult iterateObjectsInRange(const Coord3D *pos, float radius, int distCalc,
		Rva000421C8 *filters, int order);	// 0x00625610
};
extern PartitionManager *ThePartitionManager;

class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;	// 0x00288609
};

class SpecialPowerTemplate : public Overridable
{
public:
	const SpecialPowerTemplate *getFinalOverride() const
	{
		return (const SpecialPowerTemplate *)friend_getFinalOverride();
	}
	char m_pad00[0x18];
	bool flag2() const { return (m_flags >> 2) & 1; }
	bool flag4() const { return (m_flags >> 4) & 1; }
	unsigned int m_flags;	// +0x18
	char m_pad1C[0x54 - 0x1C];
	float m_54;		// +0x54
	char m_pad58[0x60 - 0x58];
	char m_60[4];		// +0x60
	char m_pad64[0x78 - 0x64];
	char m_78[4];		// +0x78
	float m_7C;		// +0x7C
};

class ActionManager
{
public:
	bool rva0041C9F8(const Object *obj, const Coord3D *pos, const SpecialPowerTemplate *sp);
	bool rva0041D4FA(const Object *obj, const Coord3D *pos, const SpecialPowerTemplate *sp);
};

bool ActionManager::rva0041C9F8(const Object *obj, const Coord3D *pos, const SpecialPowerTemplate *sp)
{
	if (!sp->getFinalOverride()->flag4())
		return true;
	Player *player = obj->getControllingPlayer();
	Rva002614ECFilter same(sp->getFinalOverride()->m_78, player, true);
	Rva0026119DFilter alive;
	float range = sp->getFinalOverride()->m_7C;
	return !ThePartitionManager->getClosestObject(pos, range, 1, alive.link(&same));
}

