// cl: /DNDEBUG /MD /EHsc
//
// ??0Made002CCB04@@QAE@XZ retail 0x0050B59B 43B
// Evidence: leaf lane; pin ??0Made002CCB04; callee base Rva00507823 0x0050775B; caller parseEmotionWeaponNugget 0x002CCB29; prev Made002CCB04Parse same /O1 DNDEBUG MD; vtable 0x00864D10 plus members 0x128 -1 plus 0x12C float0 plus 0x130 0.
//
// Retail table 0x00864D10 is the base's 14 slots (Rva00507823.h) with slots
// 5..7 overridden: 0x0050B4E2 (forward then, with a positive range, slot 6 at
// the object's +0x38 position), 0x0050B519 (range query forwarding every
// object) and 0x0050B5C6 (the shared `mov al,1; ret`). Each is rowed under
// another name, so the overrides here are byte-identical bodies admitted as
// ICF folds; the forward helper 0x0050B479 stays declared only.
#include "../../../Include/GameLogic/Module/Rva00507823.h"

class PartitionManager;
extern PartitionManager *ThePartitionManager;
#include "../../Common/PartitionRangeQueryCallView.h"

class Made002CCB04 : public Rva00507823
{
public:
	Made002CCB04();
	virtual void vslot05(const void *a, void *obj);
	virtual void vslot06(const void *a, void *position);
	virtual bool vslot07() { return true; }
	void rva0050B479(void *a, Object *obj);	// 0x0050B479, Made002CCB04.cpp
private:
	int m_128;
	float m_12C;
	int m_130;
};
Made002CCB04::Made002CCB04()
{
	m_128 = -1;
	m_130 = 0;
	m_12C = 0.0f;
}

void Made002CCB04::vslot05(const void *a, void *obj)
{
	rva0050B479((void *)a, (Object *)obj);
	if (m_12C > 0.0f)
		vslot06(a, (char *)obj + 0x38);
}

void Made002CCB04::vslot06(const void *a, void *position)
{
	float range = (m_12C > 1.0f) ? m_12C : 1.0f;
	BfmeWideResult iterator = ThePartitionManager->rva006255D0((const Coord3D *)position, range, 3, 0);
	for (void *other = iterator.next(); other; other = iterator.next())
		rva0050B479((void *)a, (Object *)other);
}
