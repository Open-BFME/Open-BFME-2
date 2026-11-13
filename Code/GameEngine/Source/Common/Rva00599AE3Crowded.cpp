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

#include "../../../Libraries/Include/Lib/Coord3D.h"

class Object
{
public:
	char m_pad000[0x38];
	Coord3D m_pos;		// +0x38
};

#include "../../Include/GameLogic/PartitionFilter.h"

#include "../../Include/Common/BfmeFixedStorage0004543D.h"

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

// ??0Rva0027231F@@QAE@ABVBfmeFixedStorage0004543D@@@Z, retail 0x0027231F,
// 42 bytes: base clears the +0x04 link, vftable 0x00BFAF94, mask to +0x08
// through the rowed 0x0004543D copy ctor, ret 4.
Rva0027231F::Rva0027231F(const BfmeFixedStorage0004543D &mask)
	: m_08(mask)
{
}

// ?allow@Rva0027231F@@UAE_NPAVObject@@@Z, retail 0x00261176 (21 bytes), slot 1
// of vftable 0x00BFAF94: none of the mask's kinds (the rowed
// Thing::isAnyKindOf 0x0030ADC7 negated). The same bytes are rowed as
// Rva001DCD30::isNotAnyKindOf (ICF); defined here, where the vftable is
// emitted, so the slot resolves.
#include "../../Include/Common/BitFlagsTemplate.h"
#include "Thing/thing.h"

bool Rva0027231F::allow(Object *obj)
{
	return !((const Thing *)obj)->isAnyKindOf(*(const BitFlags<69> *)&m_08);
}

// vftable 0x00C004D8: the player's relationship to the object against flags.
#include "../../Include/GameLogic/Rva00261409Filter.h"

// vftable 0x00BFAD10: the object is alive.
#include "../../Include/GameLogic/Rva0026119DFilter.h"

#include "PartitionRangeQueryCallView.h"

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
