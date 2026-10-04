// cl: /O1 /MD /GX /arch:SSE
//
// AISpecialPowerSelfAoEHealHeros.cpp (the unit retail's random-range assert
// names, 0x00C76340).
//
//   0x005D9A45  slot 6 of vftable 0x00C76324 (Rva005D9A1E): draw a health
//               threshold of 0.5 +- 0.1; true when the caster's health ratio
//               (+0x254 slot 4 over slot 6) is below it, or when some other
//               alive object allied (flags 2) to the caster within the +0x14
//               radius, of template kind bit 0x04 at +0x113, is
//
// The filters are BFME2's partition filter chain (the view
// AIStructureCreepTactic.cpp documents).

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

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

struct Coord3D
{
	float x;
	float y;
	float z;
};

// The module at Object +0x254: slots 4 and 6 return the health and its
// maximum (inferred from the unit's name and the ratio taken).
class Rva005D9A45Body
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual float getHealth() const;	// slot 4
	virtual void v5();
	virtual float getMaxHealth() const;	// slot 6
};

// What Object +0x04 points at: 0x005D9A45 tests bit 0x04 of +0x113.
struct Rva005D9A45Template
{
	char m_pad000[0x113];
	unsigned char m_113;	// +0x113
};

class Object
{
public:
	Player *getControllingPlayer() const;	// 0x0028AFA9
	const Coord3D *getPosition() const { return &m_pos; }
	char m_pad000[0x04];
	Rva005D9A45Template *m_04;	// +0x04
	char m_pad008[0x38 - 0x08];
	Coord3D m_pos;		// +0x38
	char m_pad044[0x254 - 0x44];
	Rva005D9A45Body *m_254;	// +0x254
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

float GetGameLogicRandomValueReal(float lo, float hi, char *file, int line);

// The self-AoE heal picker (vftable 0x00C76324): +0x14 a radius.
class Rva005D9A1E
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual bool rva005D9A45(Object *source);
	float getRadius() const { return m_14; }
private:
	char m_pad04[0x10];
	float m_14;		// +0x14
};

bool Rva005D9A1E::rva005D9A45(Object *source)
{
	bool result = false;
	float threshold = GetGameLogicRandomValueReal(-0.1f, 0.1f,
		"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AISpecialPowers\\AISpecialPowerInstances\\AISpecialPowerSelfAoEHealHeros.cpp", 36) + 0.5f;
	Rva005D9A45Body *body = source->m_254;
	if (body->getHealth() / body->getMaxHealth() < threshold) {
		result = true;
	} else {
		BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(source->getPosition(), getRadius(), 0,
			Rva0026119DFilter().link(&Rva00261409Filter(source->getControllingPlayer(), true, 2)), 1);
		for (Object *obj = hits.next(); obj; obj = hits.next()) {
			if (source == obj)
				continue;
			if (!(obj->m_04->m_113 & 0x04))
				continue;
			Rva005D9A45Body *other = obj->m_254;
			float ratio = other->getHealth() / other->getMaxHealth();
			if (ratio < threshold) {
				result = true;
				break;
			}
		}
	}
	return result;
}
