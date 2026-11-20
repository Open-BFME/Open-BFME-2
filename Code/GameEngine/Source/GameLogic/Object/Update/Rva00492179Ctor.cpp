// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva00492179@@QAE@PAVThing@@PBVModuleData@@@Z at
// retail 0x00492179 (47B). Opaque-base pattern (unidentified 0x88-byte
// UpdateModule-derived intermediate base 0x0044EF5E, pinned opaque as
// Rva0044EF5E); the derived body re-stores the inherited +0x0C/+0x10/+0x20
// pointer slots (address-of TU-local dummies, DIR32-patched: 0xC4D640 /
// 0xC4DEE8 / 0xC552A4). No trailing members (factory stub news 0x88).
// Identity unproven (opaque Rva name); serves the 0x24D9D2 factory stub.
// The paired dtor (0x004921B0, ModuleUpdateDtors.cpp) is already rowed (same consts).

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

class Rva00492179 : public Rva0044EF5E
{
public:
	Rva00492179(Thing *thing, const ModuleData *moduleData);
	virtual ~Rva00492179();
public:
	virtual void triggerAbilityEffect();
public:
	virtual void startUnpacking();
};

Rva00492179::Rva00492179(Thing *thing, const ModuleData *moduleData)
	: Rva0044EF5E(thing, moduleData)
{
}

// ~Rva00492179 (retail 0x004921B0) and its deleting destructor are defined in
// ModuleUpdateDtors.cpp.
