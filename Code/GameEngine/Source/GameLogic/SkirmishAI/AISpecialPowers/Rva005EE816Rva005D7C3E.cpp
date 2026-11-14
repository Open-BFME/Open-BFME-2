// cl: /MD /GX /Op
//
// ?rva005D7C3E@Rva005EE816@@QAE_NPAVObject@@@Z, retail 0x005d7c3e, 312 bytes. Banked partial (score 0.97) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
#include <string.h>

class Object;
class Player;

#include "../../../../Include/GameLogic/PartitionFilter.h"

// A KindOfMaskType as the mask filters copy it (0x0004543D).
#include "../../../../Include/Common/BfmeFixedStorage0004543D.h"

// vftable 0x00C1A25C, allow 0x002610F2: accept what has any of the mask's kinds.
class Rva003959FA : public Rva000421C8
{
public:
	Rva003959FA(const BfmeFixedStorage0004543D &mask);
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
};

// vftable 0x00C004D8, allow 0x00261409: the player's relationship to the
// object's team against the +0x10 flags (ZH's PartitionFilterRelationship
// analogue), +0x0C whether a hit allows.
#include "../../../../Include/GameLogic/Rva00261409Filter.h"

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead (status bit 0),
// ZH's PartitionFilterAlive.
#include "../../../../Include/GameLogic/Rva0026119DFilter.h"

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

// A KindOfMaskType view: 224 bits, zeroed then set bit by bit.
struct Rva005D75BEMask
{
	Rva005D75BEMask() { memset(this, 0, sizeof(*this)); }
	__declspec(dllimport) __forceinline void set(int bit) { m_bits[bit >> 5] |= 1u << (bit & 31); }
	unsigned int m_bits[7];
};

#include "../../Object/object.h"

#include "../../../Common/PartitionRangeQueryCallView.h"

extern PartitionManager *ThePartitionManager;

#include "../../../../Include/GameLogic/Rva005EEA20.h"

// The AoE special-power target picker (AISPecialPowerTargetAoE.cpp holds
// 0x005EE816 and 0x005EE8DD).
#include "../../../../Include/GameLogic/AISpellBookStructureBreaker.h"

class Rva005EE816
{
public:
	bool rva005EE8DD(const Coord3D *pos, Object *source);	// 0x005EE8DD
	bool rva005D7558(Object *source);			// 0x005D7558
	bool rva005D7D93(Object *source);			// 0x005D7D93
	bool rva005D75BE(Object *source);
	bool rva005D7C3E(Object *source);
private:
	char m_pad00[0x28];
	Rva005EEA20 m_finder;	// +0x28
};

bool Rva005EE816::rva005D7C3E(Object *source)
{
	Object *target = m_finder.findUnitInCombat(source->getControllingPlayer(), true, true);
	if (target) {
		Rva005D75BEMask mask;
		mask.set(60);
		mask.set(150);
		mask.set(61);
		mask.set(189);
		mask.set(156);
		BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(target->getPosition(), 500.0f, 0,
			Rva0026119DFilter().link(Rva00261409Filter(source->getControllingPlayer(), true, 4)
				.link(&Rva003959FA(*(BfmeFixedStorage0004543D *)&mask))), 1);
		Object *hit = hits.next();
		if (hit)
			return rva005EE8DD(hit->getPosition(), source);
	}
	return ((AISpellBookStructureBreaker *)this)->shouldActivate(source);
}
