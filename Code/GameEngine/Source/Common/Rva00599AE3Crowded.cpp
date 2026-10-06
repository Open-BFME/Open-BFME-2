// cl: /MD /GX
//
// ?rva00599AE3@AIDozerManager@@QAE_NPAVObject@@@Z, retail 0x00599AE3, 281 bytes.
// A member of the skirmish-AI owner record's +0x140 object list (AIDozerManager,
// Rva00599825ListAdd.cpp: +0x0C the owner player): whether at most two alive
// objects allied (flags 4) to that player, of a kind among 3, 7 and 90 and of
// none of kind 205, stand within 300 of the object. The filters are BFME2's
// PartitionFilter chain (the view AIStructureCreepTactic.cpp documents); the
// kind-157 one is the one-mask filter 0x0027231F (vftable 0x00BFAF94).
#include <string.h>

class Player;

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object
{
public:
	char m_pad000[0x38];
	Coord3D m_pos;		// +0x38
};

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

class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};

// A KindOfMaskType view: 224 bits, zeroed then set bit by bit.
struct Rva00599AE3Mask
{
	Rva00599AE3Mask() { memset(this, 0, sizeof(*this)); }
	void set(int bit) { m_bits[bit >> 5] |= 1u << (bit & 31); }
	unsigned int m_bits[7];
};

// vftable 0x00C1A25C: any of the mask's kinds.
class Rva003959FA : public Rva000421C8
{
public:
	Rva003959FA(const BfmeFixedStorage0004543D &mask);
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
};

// vftable 0x00BFAF94: the other one-mask filter.
class Rva0027231F : public Rva000421C8
{
public:
	Rva0027231F(const BfmeFixedStorage0004543D &mask);
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
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

class AIDozerManager
{
public:
	bool rva00599AE3(Object *obj);
private:
	char m_pad00[0x0C];
	Player *m_player;	// +0x0C
};

bool AIDozerManager::rva00599AE3(Object *obj)
{
	Rva00599AE3Mask kinds;
	kinds.set(3);
	kinds.set(90);
	kinds.set(7);
	Rva00599AE3Mask other;
	other.set(205);
	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(&obj->m_pos, 300.0f, 0,
		Rva0026119DFilter().link(&Rva00261409Filter(m_player, true, 4))
			->link(Rva003959FA(*(BfmeFixedStorage0004543D *)&kinds)
				.link(&Rva0027231F(*(BfmeFixedStorage0004543D *)&other))), 0);
	unsigned int count = 0;
	while (hits.next() != 0)
		++count;
	return count <= 2;
}

#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")
