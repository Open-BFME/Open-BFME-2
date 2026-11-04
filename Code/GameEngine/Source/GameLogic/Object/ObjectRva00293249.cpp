// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva00293249@Rva00293249@@QAE_NW4ObjectID@@@Z, retail 0x00293249, 44 bytes.
// Free-standing ObjectID helper: findObjectByID via TheGameLogic then AI at
// +0x258 null-safe then virtual slot 0x248 bool result else false. Evidence:
// sole caller 0x00352C3C pushes ObjectID from [ebp-0x18] with this in edi;
// TheGameLogic global plus rowed findObjectByID 0x00049DC5; AI +0x258 per
// Object_isAbleToAttack; slot 0x248 from retail call; unblocks 0x00352BD0.
typedef bool Bool;

#include "../../Common/GameLogicObjectLookupView.h"

class Object;

extern GameLogic *TheGameLogic;

#include "../../../Include/GameLogic/Module/AIUpdate.h"

#include "object.h"

class Rva00293249
{
public:
	Bool rva00293249(ObjectID id);
};

Bool Rva00293249::rva00293249(ObjectID id)
{
	Object *obj = TheGameLogic->findObjectByID(id);
	if (!obj)
		return false;
	AIUpdateInterface *ai = obj->m_ai;
	if (!ai)
		return false;
	return ai->vslot146();
}
