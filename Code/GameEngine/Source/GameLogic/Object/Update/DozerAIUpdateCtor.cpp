// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// Identity: ModuleFactory registers this module as "ActivateModuleSpecialPower" (addModule pairs
// the name with its factories); formerly misnamed DozerAIUpdate.
// stlport
//
// ??0ActivateModuleSpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z at retail 0x004CDD02.
// Same opaque-base pattern as OCLUpdate: unidentified 0x88-byte
// UpdateModule-derived intermediate base 0x0044EF5E (pinned opaque as
// Rva0044EF5E); the derived body re-stores the inherited +0x0C/+0x10/+0x20
// slots. No trailing members (factory size 0x88). Factory stub order names
// it. Do NOT declare an explicit vptr member on the base.

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

// ??1Rva0044EF5E@@UAE@XZ defined by its owner; declared here for the base call.

enum NameKeyType;
class ActivateModuleSpecialPower : public Rva0044EF5E
{
public:
	ActivateModuleSpecialPower(Thing *thing, const ModuleData *moduleData);
	virtual ~ActivateModuleSpecialPower();
public:
	virtual enum NameKeyType getModuleNameKey() const;
public:
	virtual void triggerAbilityEffect();
};

ActivateModuleSpecialPower::ActivateModuleSpecialPower(Thing *thing, const ModuleData *moduleData)
	: Rva0044EF5E(thing, moduleData)
{
}

// ??1ActivateModuleSpecialPower@@UAE@XZ (retail 0x004CDD39) and its deleting
// destructor 0x004CDD9E are defined in ModuleUpdateDtors.cpp.
