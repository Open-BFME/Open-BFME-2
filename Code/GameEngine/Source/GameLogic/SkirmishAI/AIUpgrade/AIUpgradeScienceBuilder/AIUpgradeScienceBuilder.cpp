// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
//
// AIUpgradeScienceBuilder.cpp (the unit its random-value asserts name; the
// builder class itself is not established, hence the address name).
//
//   0x00597E30  at most once per g_00E063CC frames and while the AI manager's
//               record for the owner (0x002A8AB1) has +0x16C >= 1: pick a
//               random entry; unless already done (+0x2C) or owned (slot
//               16), build it (slot 6) when an object of kind 3 or 90 the
//               owner's relationship flag 4 accepts is alive within 400 of
//               the entry's slot-13 position (BFME2's partition filter
//               chain, the view AIStructureCreepTactic.cpp documents)
#include <string.h>

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

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead.
class Rva0026119DFilter : public Rva000421C8
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

// A KindOfMaskType as the mask filters copy it (0x0004543D).
class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};

// vftable 0x00C1A25C: any of the mask's kinds.
class Rva003959FA : public Rva000421C8
{
public:
	Rva003959FA(const BfmeFixedStorage0004543D &mask);	// 0x003959FA
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
};

#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

// A KindOfMaskType view: 224 bits, zeroed then set bit by bit.
struct Rva00597E30Mask
{
	Rva00597E30Mask() { memset(this, 0, sizeof(*this)); }
	void set(int bit) { m_bits[bit >> 5] |= 1u << (bit & 31); }
	unsigned int m_bits[7];
};

struct Coord3D
{
	float x;
	float y;
	float z;
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

class GameLogic
{
public:
	unsigned getFrame() const { return m_frame; }
	char m_pad00[0x40];
	unsigned m_frame;	// +0x40
};
extern GameLogic *TheGameLogic;

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);	// 0x00233FF4

struct Rva002A8AB1Record
{
	char m_pad00[0x16C];
	int get16C() const { return m_16C; }
	int m_16C;		// +0x16C
};

class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *owner);	// 0x002A8AB1
};
extern Rva002A8F24 *g_00DFEEF8;

extern unsigned g_00E063CC;	// frames between attempts

// One upgrade or science to build: slot 6 builds it, slot 13 is where,
// slot 16 whether the owner already has it, +0x2C whether it was done.
class Rva00597E30Entry
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void rva00597E30Slot6(Player *owner, int arg);
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual Coord3D rva00597E30Slot13();
	virtual void slot14();
	virtual void slot15();
	virtual int rva00597E30Slot16(Player *owner);
	char m_pad04[0x2C - 0x04];
	bool m_2C;		// +0x2C
};

class Rva00597E30
{
public:
	void rva00597E30();
private:
	char m_pad00[0x14];
	Player *m_14;			// +0x14 the owner
	char m_pad18[0x30 - 0x18];
	Rva00597E30Entry **m_30;	// +0x30 the entries
	Rva00597E30Entry **m_34;	// +0x34 their end
	char m_pad38[0x3C - 0x38];
	unsigned m_3C;			// +0x3C the last frame
};

void Rva00597E30::rva00597E30()
{
	if (m_30 == m_34)
		return;
	if (TheGameLogic->getFrame() - m_3C < g_00E063CC)
		return;
	if (g_00DFEEF8->rva002A8AB1(m_14)->get16C() < 1)
		return;
	Rva00597E30Entry *entry = m_30[GetGameLogicRandomValue(0, (m_34 - m_30) - 1,
		"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AIUpgrade\\AIUpgradeScienceBuilder\\AIUpgradeScienceBuilder.cpp", 0x1A1)];
	if (!entry || entry->m_2C)
		return;
	if (entry->rva00597E30Slot16(m_14))
		return;
	Rva00597E30Mask mask;
	mask.set(3);
	mask.set(90);
	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(&entry->rva00597E30Slot13(), 400.0f, 0,
		Rva0026119DFilter().link(&Rva00261409Filter(m_14, true, 4))->link(&Rva003959FA(*(BfmeFixedStorage0004543D *)&mask)), 0);
	if (hits.next()) {
		entry->rva00597E30Slot6(m_14, 0);
		entry->m_2C = true;
		m_3C = TheGameLogic->getFrame();
	}
}
