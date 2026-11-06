// FILE: ObjectHelper.h ///////////////////////////////////////////////////////////////////////////
// Desc:   Canonical BFME2 ObjectHelper: the UpdateModule base of the helper modules every Object
//         builds (ObjectDefectionHelper, ObjectRecoveryHelper, ObjectRepulsorHelper,
//         ObjectWeaponStatusHelper, ObjectSMCHelper).
//
// Target facts (code addresses are RVAs, vftables VAs):
//  - ??0ObjectHelper 0x0028C8DF calls ??0UpdateModule 0x00253390, then installs 0x00BFBCF0 at +0,
//    UpdateModule's BehaviorModuleInterface table 0x00BEFF90 at +0x0C and UpdateModule's own
//    UpdateModuleInterface table 0x00BFBCE4 at +0x10, and calls setWakeFrame(UPDATE_SLEEP_FOREVER).
//    ObjectHelper therefore overrides nothing in either interface table.
//  - The destructor 0x004DF7C2 (rowed under the placeholder Rva004DF7C2) stores the same three
//    tables and tail-jumps to ~UpdateModule 0x0024A797. The first derived field sits at +0x20
//    (ObjectDefectionHelper's constructor 0x0028C955), so sizeof(ObjectHelper) is UpdateModule's.
//  - 0x00BFBCF0 has 13 slots and differs from UpdateModule's 0x00BF004C in slots 0-3 only: the
//    deleting destructor 0x0028C939, loadPostProcess 0x00497805 (`jmp 0x0058B03E`, UpdateModule's),
//    the name getter 0x0028C933 ("ObjectHelper") and xfer 0x004DF81B (version, then
//    UpdateModule::xfer). Slot 4, getModuleNameKey, stays __purecall.
//  - loadPostProcess 0x00497805 is the body many module tables fold onto (rowed as Rva00497805 and
//    as ICF twins); the helpers' own override 0x00483CEF is `jmp 0x00497805`, so it calls this one.
// Not declared here yet: GetSnapshotName and xfer. Their rows are placeholders (Rva0028C933Get,
// Rva004DF81B), and a derived class that does not override a slot would reference ObjectHelper's
// name there; until they carry ObjectHelper's name a view inherits UpdateModule's.
// Donor (Zero Hour ObjectHelper.h) facts: the class name and that it derives from UpdateModule.
// Zero Hour's ObjectHelper overrides getDisabledTypesToProcess; BFME2's (0x00BFBCE4 at +0x10) does not.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __BFME2_OBJECTHELPER_H_
#define __BFME2_OBJECTHELPER_H_

#include "UpdateModule.h"

class ObjectHelper : public UpdateModule
{
public:
	ObjectHelper( Thing *thing, const ModuleData *moduleData );
	virtual ~ObjectHelper();

protected:
	virtual void loadPostProcess();										// slot 1
};

#endif // __BFME2_OBJECTHELPER_H_
