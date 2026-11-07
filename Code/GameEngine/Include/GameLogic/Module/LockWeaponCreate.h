// FILE: LockWeaponCreate.h ///////////////////////////////////////////////////////////////////////
// Desc:   BFME2 LockWeaponCreate and its module data, on the canonical CreateModule.
//
// Target facts:
//  - ??0LockWeaponCreate (0x004B8C0E) calls ??0CreateModule (0x004B8CF7), then stores the
//    primary table 0x00C592FC at +0, the shared behavior-interface table 0x00BEF9C0 at
//    +0x0C and the create-interface table 0x00C592EC at +0x10. The destructor 0x004B8C3E
//    stores the same three and jumps to ~CreateModule 0x004B8CDE.
//  - 0x00C592EC: onCreate is the shared empty `ret` 0x000B3FD0; onBuildComplete is
//    0x004B8CC9 (clears +0x14, then Object::setWeaponLock(module data +8, 2)).
//  - 0x00C592FC: slot 2 is 0x004B8C38, returning "LockWeaponCreate"; slot 3 is
//    0x004851E3 (Version1, then CreateModule's xfer); slot 4 is 0x004B8C57, the
//    rowed static ?rva004B8C57@LockWeaponCreate (left undeclared as a virtual here).
//  - ??0LockWeaponCreateModuleData (0x00254C8E) clears +8 and stores its table.
// Donor (Zero Hour LockWeaponCreate.h) facts: the class names, m_slotToLock,
// onCreate and onBuildComplete.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __BFME2_LOCKWEAPONCREATE_H_
#define __BFME2_LOCKWEAPONCREATE_H_

#include "CreateModuleClass.h"
#include "../../Common/ModuleData.h"

enum WeaponSlotType;
class MultiIniFieldParse;

//-------------------------------------------------------------------------------------------------
class LockWeaponCreateModuleData : public ModuleData
{
public:
	WeaponSlotType m_slotToLock;			// +0x08

	LockWeaponCreateModuleData();
	static void buildFieldParse( MultiIniFieldParse &p );
};

//-------------------------------------------------------------------------------------------------
class LockWeaponCreate : public CreateModule
{
public:
	LockWeaponCreate( Thing *thing, const ModuleData *moduleData );
	virtual ~LockWeaponCreate();

	virtual void onCreate( void ) { }
	virtual void onBuildComplete();

protected:
	virtual const char *GetSnapshotName() const;
	virtual void xfer( Xfer *xfer );

private:
	const LockWeaponCreateModuleData *getLockWeaponCreateModuleData() const
	{
		return (const LockWeaponCreateModuleData *)getModuleData();
	}
};

#endif // __BFME2_LOCKWEAPONCREATE_H_
