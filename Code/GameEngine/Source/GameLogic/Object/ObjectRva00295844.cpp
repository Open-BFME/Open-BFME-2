// cl: /MD /GX
//
// ?rva00295844@Object@@QAEXM@Z, retail 0x00295844, 227 bytes (caller
// 0x002972CF in 0x002972B1). Sums the template +0x51C value of every enemy
// (relationship 1) alive object sharing this object's map status within
// the range, stores it at +0x444 and sets the 5000 ms timer through the
// rowed 0x0028C0F2. That setter is a leaf that cannot throw; retail drops
// the hit list from the unwind map accordingly, so it is declared throw().
//
// The filters are BFME2's partition filter chain (the view
// AIStructureCreepTactic.cpp documents): a vptr, the +0x04 link to the next
// filter (PartitionFilter::link 0x00625790), then each filter's members;
// address-derived names after allow (slot 1), the ctors being inline.
class Object;
class Player;

#include "../../../Include/GameLogic/PartitionFilter.h"

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead (status bit 0),
// ZH's PartitionFilterAlive.
#include "../../../Include/GameLogic/Rva0026119DFilter.h"

// vftable 0x00BFBC90, allow 0x00260EB1, getPlayerMask 0x00260E6A: the object,
// relationship flags and whether a hit allows.
#include "../../../Include/GameLogic/Rva00260EB1Filter.h"

// vftable 0x00BF91BC, allow 0x002611BF.
#include "../../../Include/GameLogic/Rva002611BFFilter.h"

#include "../../../../Libraries/Include/Lib/Coord3D.h"

#include "../../../Include/Common/ThingTemplate.h"

#include "../../Common/PartitionRangeQueryCallView.h"

extern PartitionManager *ThePartitionManager;

class Object
{
public:
	void rva00295844(float range);
	void rva0028C0F2(unsigned int ms) throw();	// 0x0028C0F2
	char m_pad000[4];
	const ThingTemplate *m_template;	// +0x04
	char m_pad008[0x38 - 8];
	Coord3D m_pos;			// +0x38
	char m_pad044[0x444 - 0x44];
	float m_444;			// +0x444
};

void Object::rva00295844(float range)
{
	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(&m_pos, range, 0,
		Rva00260EB1Filter(this, 1, false).link(Rva0026119DFilter().link(&Rva002611BFFilter(this))), 0);
	float total = 0.0f;
	Object *obj;
	while ((obj = hits.next()) != 0)
		total += obj->m_template->m_threatLevel;
	m_444 = total;
	rva0028C0F2(5000);
}
