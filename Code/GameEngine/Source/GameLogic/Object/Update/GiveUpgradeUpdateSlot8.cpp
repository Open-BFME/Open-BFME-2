// cl: /DNDEBUG /MD
//
// GiveUpgradeUpdate slot 8 of its +0x20 interface table 0x00C511F0 (installed
// by the ctors 0x0049C3D3 and 0x0049C410), retail 0x0049C553 (63 bytes), so
// `this` is that subobject: the SpecialAbilityUpdate +0x20 slot-8 base
// 0x0044EDA6 first (its false stands), then true unless the Object named by
// +0x40 still exists without bit 0 of its +0x438 byte. Named by the base's
// address, like ToggleDeploySpecialAbilityUpdateSlot8.cpp.
typedef bool Bool;
#include "../../../Common/GameLogicObjectLookupView.h"
#include "../object.h"
extern GameLogic *TheGameLogic;
class ModuleData;
#include "../../../../Include/GameLogic/Module/UpdateModule.h"
class SpecialPowerUpdateInterface
{
public:
	virtual void u0(); virtual void u1(); virtual void u2(); virtual void u3();
	virtual void u4(); virtual void u5(); virtual void u6(); virtual void u7();
	virtual Bool rva0044EDA6(int value);
};
class SpecialAbilityUpdate : public UpdateModule, public SpecialPowerUpdateInterface
{
public:
	virtual Bool rva0044EDA6(int value);
};
class GiveUpgradeUpdate : public SpecialAbilityUpdate
{
public:
	virtual Bool rva0044EDA6(int value);
private:
	unsigned char m_pad24[0x40 - 0x24];
	ObjectID m_40; // +0x40
};
Bool GiveUpgradeUpdate::rva0044EDA6(int value)
{
	if (!SpecialAbilityUpdate::rva0044EDA6(value))
		return false;
	if (m_40 == INVALID_OBJECT_ID)
		return true;
	Object *obj = TheGameLogic->findObjectByID(m_40);
	return obj == 0 || (obj->m_privateStatus & 1) != 0;
}
