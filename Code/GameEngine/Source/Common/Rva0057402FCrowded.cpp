// cl: /MD /GX
//
// ?rva00573CFB@Rva00573F03@@UAEHPAVPlayer@@@Z, retail 0x0057402F, 316
// bytes: slot 4 of the derived build order Rva00573F03 (vftable 0x00C6E2F8,
// also in 0x00C70B68), overriding the base order's 0x00573CFB. State 9 when
// more than two alive objects allied (flags 4) to the player, of a kind
// among 3, 7 and 90 and of none of kind 205, stand within 300 of the
// order's position (slot 13, returned by value); else the base. The same
// crowding test as Rva00599AE3Crowded.cpp.
//
// The filters are BFME2's partition filter chain (the view
// AIStructureCreepTactic.cpp documents): a vptr, the +0x04 link to the next
// filter (PartitionFilter::link 0x00625790), then each filter's members;
// address-derived names after the out-of-line ctor, else after allow
// (slot 1).
#include <string.h>

class Object;
class Player;

#include "../../Include/GameLogic/PartitionFilter.h"

// A KindOfMaskType as the mask filters copy it (0x0004543D).
#include "../../Include/Common/BfmeFixedStorage0004543D.h"

// vftable 0x00C1A25C, allow 0x002610F2: accept what has any of the mask's kinds.
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
#include "../../Include/GameLogic/Rva0026119DFilter.h"

#include "../../../Libraries/Include/Lib/Coord3D.h"

// A KindOfMaskType view: 224 bits, zeroed then set bit by bit.
struct Rva0057402FMask
{
	Rva0057402FMask() { memset(this, 0, sizeof(*this)); }
	void set(int bit) { m_bits[bit >> 5] |= 1u << (bit & 31); }
	unsigned int m_bits[7];
};

#include "PartitionRangeQueryCallView.h"

extern PartitionManager *ThePartitionManager;

// LINK: the base check 0x00573CFB is rowed as AIBuildableStructure::canMake (AIBuildableStructure.cpp, UAEHPAVPlayer).
class AIBuildableStructure { public: virtual int canMake(Player *player); };

// The build-order object (Rva00573B23Dtor.cpp; 0x40 bytes) and the derived
// order whose slot 4 this is (Rva00573F03; vftable 0x00C6E2F8).
class Rva00573B23
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual int rva00573CFB(Player *player);		// slot 4; this class 0x00573CFB
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s0A();
	virtual void s0B();
	virtual void s0C();
	virtual Coord3D rva_slot13() const = 0;		// slot 13: the order position
};

class Rva00573F03 : public Rva00573B23
{
public:
	virtual int rva00573CFB(Player *player);
};

int Rva00573F03::rva00573CFB(Player *player)
{
	Rva0057402FMask kinds;
	kinds.set(3);
	kinds.set(90);
	kinds.set(7);
	Rva0057402FMask other;
	other.set(205);
	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(&(const Coord3D &)rva_slot13(), 300.0f, 0,
		Rva0026119DFilter().link(&Rva00261409Filter(player, true, 4))
			->link(Rva003959FA(*(BfmeFixedStorage0004543D *)&kinds)
				.link(&Rva0027231F(*(BfmeFixedStorage0004543D *)&other))), 0);
	unsigned int count = 0;
	while (hits.next() != 0)
		++count;
	if (count <= 2)
		return ((AIBuildableStructure *)this)->AIBuildableStructure::canMake(player);
	return 9;
}
