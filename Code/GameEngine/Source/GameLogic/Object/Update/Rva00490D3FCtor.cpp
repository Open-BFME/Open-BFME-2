// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva00490D3F@@QAE@PAVThing@@PBVModuleData@@@Z at
// retail 0x00490D3F (47B). Opaque-base pattern (unidentified 0x88-byte
// UpdateModule-derived intermediate base 0x0044EF5E, pinned opaque as
// Rva0044EF5E); the derived body re-stores the inherited +0x0C/+0x10/+0x20
// pointer slots (address-of TU-local dummies, DIR32-patched: 0xC4D640 /
// 0xC4DEE8 / 0xC552A4). No trailing members (factory stub news 0x88).
// Identity unproven (opaque Rva name); serves the 0x24D67B factory stub.

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

class Rva00490D3F : public Rva0044EF5E
{
public:
	Rva00490D3F(Thing *thing, const ModuleData *moduleData);
	virtual ~Rva00490D3F();
};

Rva00490D3F::Rva00490D3F(Thing *thing, const ModuleData *moduleData)
	: Rva0044EF5E(thing, moduleData)
{
}

// ~Rva00490D3F (retail 0x00490D76) and its deleting destructor are defined in
// ModuleUpdateDtors.cpp.
