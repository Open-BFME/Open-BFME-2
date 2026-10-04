// cl: /O1 /MD /GX /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// AITargetHeuristicBaseDefense.cpp: the target heuristic whose slot 1
// 0x005737D6 passes "...\AITargetChooser\AITargetHeuristics\
// AITargetHeuristicBaseDefense.cpp" to GameLogicRandomValue. The class keeps
// its address-derived name Rva005737AF (ctor 0x0057379B, dtor 0x005737AF,
// vftable 0x00C6E1BC: slot 0 the deleting dtor 0x005737BA, slot 1 below).
//
// Slot 1: for each base-defense entry of the player's skirmish-AI record
// (TheSkirmishAIManager 0x002A8F24, record +0x10), the first alive object
// within the entry's radius of its position that is an enemy of the player
// (flags 1), has a kind among 3 and 90 and none of 54, 191, 205 and 206 is
// collected with the entry's count; one of them is picked at random
// (line 0x56) and handed to the choice with 200: count 1 sets the choice's
// +0x2C to 0 and goes on only 30% of the time (line 0x5F), count 2 sets 1,
// any other 2.
//
// The filters are BFME2's partition filter chain (the view
// AIStructureCreepTactic.cpp documents): a vptr, the +0x04 link to the next
// filter (PartitionFilter::link 0x00625790), then each filter's members;
// address-derived names after the out-of-line ctor, else after allow
// (slot 1).
#include <string.h>
#include <utility>
#include <vector>

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

// A KindOfMaskType as the mask filters copy it (0x0004543D).
class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};

// vftable 0x00C1A25C, allow 0x002610F2: accept what has any of the mask's kinds.
class Rva003959FA : public Rva000421C8
{
public:
	Rva003959FA(const BfmeFixedStorage0004543D &mask) throw();
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
};

// vftable 0x00BFAF94: the other one-mask filter.
class Rva0027231F : public Rva000421C8
{
public:
	Rva0027231F(const BfmeFixedStorage0004543D &mask) throw();
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
};

// vftable 0x00C6E1B0, allow 0x00260F1B, slot 2 0x00260EE0: +0x08 the
// player, +0x0C the relationship flags allowed (Zero Hour's
// PartitionFilterRelationship).
class Rva00260F1BFilter : public Rva000421C8
{
public:
	Rva00260F1BFilter(Player *player, int flags) : m_player(player), m_flags(flags) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	Player *m_player;
	int m_flags;
};

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead (status bit 0),
// ZH's PartitionFilterAlive.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

// A KindOfMaskType view: 224 bits, zeroed then set bit by bit.
struct Rva005737D6Mask
{
	Rva005737D6Mask() { memset(this, 0, sizeof(*this)); }
	void set(int bit) { m_bits[bit >> 5] |= 1u << (bit & 31); }
	unsigned int m_bits[7];
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

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);	// 0x00233FF4

// One base-defense entry: +0x04 its radius, +0x08 its position, +0x1C a
// vector whose element count is the entry's count.
struct Rva00049D20Entry
{
	void *m_00;
	float m_radius;		// +0x04
};

// The record's base-defense list: entries in the pointer vector at +0x10.
class Rva00049D20
{
public:
	void *rva00049D20(void *outPos, int index);	// 0x00049D20: entry's position
	int rva005D772D(int index);		// 0x005D772D: entry's count
	char m_pad00[0x10];
	Rva00049D20Entry **m_begin;	// +0x10
	Rva00049D20Entry **m_end;	// +0x14
};

struct Rva002A8F24Record
{
	char m_pad00[0x10];
	Rva00049D20 *m_10;		// +0x10
};

class Rva002A8F24
{
public:
	Rva002A8F24Record *rva002A8F24Record(void *owner);	// 0x002A8F24
};
extern Rva002A8F24 *g_00DFEEF8;

// What slot 1 hands the pick to: +0x2C the kind of pick.
class Rva002C5D8B
{
public:
	void rva002C5D8B(Object *obj, float value);	// 0x002C5D8B
	char m_pad00[0x2C];
	int m_2C;	// +0x2C
};

struct Rva005CB22A
{
	Rva005CB22A(void *held);
	virtual ~Rva005CB22A();
};

struct Rva005737AF : Rva005CB22A
{
	Rva005737AF();
	virtual ~Rva005737AF();
	virtual void rva005737D6(Rva002C5D8B *choice, Player *player, int unused);
};

void Rva005737AF::rva005737D6(Rva002C5D8B *choice, Player *player, int unused)
{
	Rva002A8F24Record *record = g_00DFEEF8->rva002A8F24Record(player);
	_STL::vector<_STL::pair<Object *, int> > found;
	Rva00049D20 *list = record->m_10;
	unsigned count = list->m_end - list->m_begin;
	for (unsigned i = 0; i < count; ++i) {
		Rva00049D20Entry *entry = list->m_begin[i];
		float radius = entry->m_radius;
		Coord3D pos;
		list->rva00049D20(&pos, i);
		Rva005737D6Mask kinds;
		Rva005737D6Mask other;
		other.set(205);
		kinds.set(3);
		kinds.set(90);
		other.set(54);
		other.set(191);
		other.set(206);
		Rva00260F1BFilter filterEnemies(player, 1);
		Rva003959FA filterKinds(*(BfmeFixedStorage0004543D *)&kinds);
		Rva0027231F filterOther(*(BfmeFixedStorage0004543D *)&other);
		Rva0026119DFilter filterAlive;
		filterEnemies.link(&filterKinds);
		filterEnemies.link(&filterOther);
		filterEnemies.link(&filterAlive);
		BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(&pos, radius, 0,
			&filterEnemies, 0);
		Object *obj = hits.next();
		if (obj) {
			_STL::pair<Object *, int> hit;
			hit.first = obj;
			hit.second = list->rva005D772D(i);
			found.push_back(hit);
		}
	}
	if (!found.empty()) {
		int index = GetGameLogicRandomValue(0, found.size() - 1,
			"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AITacticalAI\\AITargetChooser\\AITargetHeuristics\\AITargetHeuristicBaseDefense.cpp",
			0x56);
		_STL::pair<Object *, int> &pick = found[index];
		bool go = true;
		switch (pick.second) {
		case 1:
			choice->m_2C = 0;
			go = GetGameLogicRandomValue(0, 100,
				"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AITacticalAI\\AITargetChooser\\AITargetHeuristics\\AITargetHeuristicBaseDefense.cpp",
				0x5F) < 30;
			break;
		case 2:
			choice->m_2C = 1;
			break;
		default:
			choice->m_2C = 2;
			break;
		}
		if (go)
			choice->rva002C5D8B(pick.first, 200.0f);
	}
}
