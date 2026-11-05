// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// GiveUpgradeUpdate slot 8 of its +0x20 interface table 0x00C511F0 (installed
// by the ctors 0x0049C3D3 and 0x0049C410), retail 0x0049C553 (63 bytes), so
// `this` is that subobject: the SpecialAbilityUpdate +0x20 slot-8 base
// 0x0044EDA6 first (its false stands), then true unless the Object named by
// +0x40 still exists without bit 0 of its +0x438 byte. Named vslot08 after
// the canonical SpecialPowerUpdateInterface slot 8 (no donor name).
typedef bool Bool;
#include "../../../Common/GameLogicObjectLookupView.h"
#include "../object.h"
extern GameLogic *TheGameLogic;
class ModuleData;
#include "../../../../Include/GameLogic/Module/UpdateModule.h"
#include "../../../../Include/GameLogic/Module/SpecialPowerUpdateInterface.h"
#include "../../../../Include/GameLogic/Module/SpecialAbilityUpdate.h"
class GiveUpgradeUpdate : public SpecialAbilityUpdate
{
public:
	virtual Bool vslot08(int value);
};
Bool GiveUpgradeUpdate::vslot08(int value)
{
	if (!SpecialAbilityUpdate::vslot08(value))
		return false;
	if (m_targetID == INVALID_OBJECT_ID)
		return true;
	Object *obj = TheGameLogic->findObjectByID(m_targetID);
	return obj == 0 || (obj->m_privateStatus & 1) != 0;
}
