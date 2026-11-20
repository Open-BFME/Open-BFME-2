// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// Identity: ModuleFactory registers this module as "EvacuateGarrisonSpecialPower" (addModule pairs
// the name with its factories); formerly misnamed SupplyCenterDockUpdate.
// stlport
//
// ??0EvacuateGarrisonSpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z at
// retail 0x004CDBFC (47B). Same opaque-base pattern as MissileLauncherBuildingUpdate:
// unidentified 0x88-byte UpdateModule-derived intermediate base 0x0044EF5E
// (pinned opaque as Rva0044EF5E); the derived body re-stores the inherited
// +0x0C/+0x10/+0x20 pointer slots (address-of TU-local dummies,
// DIR32-patched). No trailing members (factory size 0x88). Do NOT declare an
// explicit vptr member on the base: the compiler's hidden vptr already sits
// at +0 and a declared one shifts every slot by 4.

#include "../../../../Include/GameLogic/Module/SpecialAbilityUpdate.h"

class Thing;
class ModuleData;

// Rva0044EF5E only spells the base constructor call: the ledger rows SpecialAbilityUpdate's constructor
// under that name. It adds nothing to SpecialAbilityUpdate.
class Rva0044EF5E : public SpecialAbilityUpdate
{
public:
	Rva0044EF5E(Thing *thing, const ModuleData *moduleData);
	virtual ~Rva0044EF5E();
};

enum NameKeyType;
class EvacuateGarrisonSpecialPower : public Rva0044EF5E
{
public:
	EvacuateGarrisonSpecialPower(Thing *thing, const ModuleData *moduleData);
	virtual ~EvacuateGarrisonSpecialPower();
public:
	virtual enum NameKeyType getModuleNameKey() const;
public:
	virtual void finishAbility();
};

EvacuateGarrisonSpecialPower::EvacuateGarrisonSpecialPower(Thing *thing, const ModuleData *moduleData)
	: Rva0044EF5E(thing, moduleData)
{
}

