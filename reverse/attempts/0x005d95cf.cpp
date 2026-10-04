// ?rva005D95CF@Rva005EE816@@QAE_NPAVObject@@@Z
// partial score=0.9 date=2026-10-04
// cl: /O1 /MD /GX /arch:SSE
//
// A skirmish-AI special-power member of the AoE target picker's class (the
// class whose 0x005EE816 and 0x005EE8DD live in AISPecialPowerTargetAoE.cpp;
// this body sits in another unit at 0x005D95CF, retail file unknown):
// the nearest object allied to the target's controlling player within the
// picker's +0x10 radius; when it stands at least 0.8 of that radius away,
// try to place the AoE at it (0x005EE8DD).
class Player;

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct Rva005D95CFVec
{
	Rva005D95CFVec(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
	float lengthSqr() const { return x * x + y * y + z * z; }
	float lengthSqrRev() const { return z * z + y * y + x * x; }
	float x;
	float y;
	float z;
};

class Object
{
public:
	Player *getControllingPlayer() const;
	const Coord3D *getPosition() const { return &m_pos; }
	char m_pad000[0x38];
	Coord3D m_pos;		// +0x38
};

// BFME2's partition filters (the view AIStructureCreepTactic.cpp documents).
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

// vftable 0x00C004D8: the player's relationship to the object against flags.
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

// vftable 0x00BFAD10: the object is alive.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
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

class Rva005EE816
{
public:
	bool rva005EE8DD(const Coord3D *pos, Object *source);
	bool rva005D95CF(Object *target);
	float getRadius() const { return m_radius; }
private:
	char m_pad00[0x10];
	float m_radius;		// +0x10
};

bool Rva005EE816::rva005D95CF(Object *target)
{
	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(target->getPosition(), getRadius(), 0,
		Rva0026119DFilter().link(&Rva00261409Filter(target->getControllingPlayer(), true, 4)), 1);
	Object *other = hits.next();
	if (other != 0) {
		const Coord3D *pos = target->getPosition();
		const Coord3D *otherPos = other->getPosition();
		float r = getRadius() * 0.8f;
		float dx = otherPos->x - pos->x;
		float dy = otherPos->y - pos->y;
		float dz = otherPos->z - pos->z;
		if (dx * dx + dy * dy + dz * dz >= r * r)
			return rva005EE8DD(otherPos, target);
	}
	return false;
}

#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")
