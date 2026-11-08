// cl: /O1 /DNDEBUG /MD
//
// ??0DamageModule@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004B9704, 47 bytes: the base
// constructor of the damage behaviors. The compiler's own order gives retail's four stores:
// DamageModuleInterface's implicit constructor at +0x10, then the class's +0, +0x0C and +0x10.

// As CreateModule.cpp: this unit emits BehaviorModule's own tables (slot 1 is its loadPostProcess).
#define BFME_BEHAVIORMODULE_LOADPOSTPROCESS
#include "../../../../Include/GameLogic/Module/DamageModuleClass.h"

// ??0DamageModule@@QAE@PAVThing@@PBVModuleData@@@Z @0x004B9704
inline DamageModule::DamageModule(Thing *thing, const ModuleData *moduleData) :
	BehaviorModule(thing, moduleData)
{
}

// ~BehaviorModule inline here gives retail's store order (+0x10, then the inlined +0 and +0x0C) and
// the tail jump to ~ObjectModule.
inline BehaviorModule::~BehaviorModule()
{
}

// ??1DamageModule@@UAE@XZ @0x004B96CC
DamageModule::~DamageModule()
{
}

// DamageModule ctor is a header inline elsewhere: other units emit select-any
// copies, so a strong definition here was a duplicate in the linked build.
// This anchor only makes this unit emit its copy for the ledger row; it is
// not retail code.
#pragma inline_depth(0)
// ?bfmeEmitDamageModuleCtor@@YAXPAVDamageModule@@PAVThing@@PBVModuleData@@@Z present-unmatched
void bfmeEmitDamageModuleCtor(DamageModule *damageModule, Thing *thing, const ModuleData *moduleData)
{
	damageModule->DamageModule::DamageModule(thing, moduleData);
}
#pragma inline_depth()
