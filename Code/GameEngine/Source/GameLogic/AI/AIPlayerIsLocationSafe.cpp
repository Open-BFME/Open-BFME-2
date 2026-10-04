// cl: /O1 /MD /GX /arch:SSE
//
// AIPlayer::isLocationSafe, retail 0x004F08A8, 295 bytes (caller 0x004F2C0B,
// beside the matched checkForSupplyCenter 0x004F29E9 in AIPlayer.cpp, which
// is built without /arch:SSE). Zero Hour's body over BFME2's linked filters
// (built inner first): no enemy within the AI data's supply-centre safe
// radius (+0x84) plus the template's bounding radius (+0xB0) that is not an
// ally or neutral (relationship flags 10), alive, passes the player filter
// in place of Zero Hour's stealth one, is significant, and is neither a
// kind-14 (harvester) nor a kind-16 (dozer) object.
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

// A KindOfMaskType as the mask filters copy it (0x0004543D).
class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};

// vftable 0x00C1A268, allow 0x0026115D: reject what has any of the first
// mask's kinds (ZH's PartitionFilterRejectByKindOf).
class Rva00395A35 : public Rva000421C8
{
public:
	Rva00395A35(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b);
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};

// vftable 0x00C004D8, allow 0x00261409: the player's relationship to the
// object's team against the +0x10 flags (ZH's PartitionFilterRelationship
// analogue), +0x0C whether a hit allows.
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
	Rva00261058(Player *player, bool flag) : m_player(player), m_flag(flag) {}
	virtual bool allow(Object *obj);
	Player *m_player;
	bool m_flag;
};

// The base filter's slot 2 is the trivial virtual retail shares across many
// vftable slots (0x0036CC7A); bind the declaration to that row.
#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

struct Rva00045411BitSet
{
	Rva00045411BitSet(int unused, int bit);	// 0x00045411
	unsigned int m_bits[7];
};
extern unsigned char g_00DFEFA4StoragePrototype[28];

// vftable 0x00C07160, allow 0x00261246: two flags (Zero Hour's
// PartitionFilterInsignificantBuildings(allowNonBuildings, allowInsignificant)).
class Rva00261246Filter : public Rva000421C8
{
public:
	Rva00261246Filter(bool a, bool b) : m_a(a), m_b(b) {}
	virtual bool allow(Object *obj);
	bool m_a;
	bool m_b;
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class ThingTemplate
{
public:
	float getBoundingCircleRadius() const { return m_boundingRadius; }
	char m_pad000[0xB0];
	float m_boundingRadius;		// +0xB0
};

struct TAiData
{
	char m_pad000[0x84];
	float m_supplyCenterSafeRadius;	// +0x84
};

class AI
{
public:
	TAiData *getAiData() const { return m_aiData; }
	char m_pad00[0x18];
	TAiData *m_aiData;		// +0x18
};
extern AI *TheAI;

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *pos, float maxDist, int dc,
		Rva000421C8 *filters);	// 0x00625360
};
extern PartitionManager *ThePartitionManager;

enum DistanceCalculationType
{
	FROM_BOUNDINGSPHERE_2D = 3
};

class AIPlayer
{
public:
	bool isLocationSafe(const Coord3D *pos, const ThingTemplate *tthing);
private:
	char m_pad00[0x0C];
	Player *m_player;		// +0x0C
};

bool AIPlayer::isLocationSafe(const Coord3D *pos, const ThingTemplate *tthing)
{
	if (tthing == 0)
		return false;

	float radius = TheAI->getAiData()->m_supplyCenterSafeRadius;
	radius += tthing->getBoundingCircleRadius();

	Object *enemy = ThePartitionManager->getClosestObject(pos, radius, FROM_BOUNDINGSPHERE_2D,
		Rva00261409Filter(m_player, false, 10)
			.link(Rva0026119DFilter()
			.link(Rva00261058(m_player, false)
			.link(Rva00261246Filter(true, false)
			.link(Rva00395A35(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 16),
				*(BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype)
			.link(&Rva00395A35(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 14),
				*(BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype)))))));
	if (enemy != 0)
		return false;
	return true;
}
