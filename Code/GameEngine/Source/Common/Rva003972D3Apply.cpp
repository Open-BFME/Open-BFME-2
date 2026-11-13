// cl: /DNDEBUG /MD
//
// ?rva003972D3@Rva003972D3@@QAEXPAURva003972D3Range@@PBVUpgradeTemplate@@@Z, retail 0x003972D3, 132 bytes.
// Iterates an ObjectID range and re-applies an UpgradeTemplate to qualifying objects.
// Evidence: callers at 0x0039738F 0x0039739B pass [esi+0x50]/[esi+0x74] ranges with ebp upgrade;
// rowed ?findObjectByID@GameLogic@@QAEPAVObject@@W4ObjectID@@@Z via TheGameLogic,
// rowed ?rva00293003@Object@@QAEXPBX@Z, rowed ?rva0028BCF4@Object@@QBEPAXXZ with
// virtual slot 3 (+0x0C) and slot 6 (+0x18), rowed ?hasUpgrade@Object@@QBE_NPBVUpgradeTemplate@@@Z,
// rowed Object::affectedByUpgrade; prev/next share /O1 /DNDEBUG /MD.

#include "GameLogicObjectLookupView.h"

class Object;
class UpgradeTemplate;
class GameLogic;

struct Rva003972D3Range
{
	ObjectID *m_begin;
	ObjectID *m_end;
};

#include "../GameLogic/Object/object.h"


extern GameLogic *TheGameLogic;

class MidHelper003972D3
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual bool s03();
	virtual void s04();
	virtual void s05();
	virtual class Object *s06();
};

#include "../../Include/Common/Rva003972D3.h"

void Rva003972D3::rva003972D3(Rva003972D3Range *range, const UpgradeTemplate *upgrade)
{
	for (ObjectID *objectID = range->m_begin; objectID != range->m_end; ++objectID)
	{
		Object *obj = TheGameLogic->findObjectByID(*objectID);
		if (obj == 0)
			continue;
		obj->rva00293003(upgrade);
		MidHelper003972D3 *mid = (MidHelper003972D3 *)obj->rva0028BCF4();
		if (mid == 0)
			continue;
		if (!mid->s03())
			continue;
		Object *obj2 = mid->s06();
		if (obj2 == 0)
			continue;
		if (obj2->hasUpgrade(upgrade))
			continue;
		if (!obj2->affectedByUpgrade(upgrade))
			continue;
		obj2->rva00293003(upgrade);
	}
}
