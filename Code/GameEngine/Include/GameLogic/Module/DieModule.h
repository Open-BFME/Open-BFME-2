// FILE: DieModule.h /////////////////////////////////////////////////////////////////////////////
// Desc:   Canonical BFME2 DieModuleInterface and DieModule.
//
// Target facts:
//  - ??0DieModule (0x0045CEBD) calls ??0BehaviorModule, then stores the interface's
//    own table 0x00C1C780 at +0x10, the primary 0x00C41E78 at +0 and the
//    behavior-interface table 0x00C4A650 at +0x0C: sizeof 0x14.
//  - 0x00C1C780 holds one __purecall slot; every die module's own +0x10 table
//    (e.g. CrushDie's 0x00C4AC30) fills it with its onDie.
//  - 0x00C4A650 differs from BehaviorModule's 0x00BEE9C0 only at slot 7,
//    0x002533D3, which returns the DieModuleInterface at this+4 (NULL for NULL).
//  - ??1DieModule@@MAE@XZ (0x0045CE54) and ??_GDieModule@@MAEPAXI@Z are rowed:
//    a protected virtual destructor.
// Donor (Zero Hour DieModule.h) facts: onDie(const DamageInfo *), getDie()
// returning this, the protected isDieApplicable.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __BFME2_DIEMODULE_H_
#define __BFME2_DIEMODULE_H_

#include "BehaviorModule.h"

class DamageInfo;

//-------------------------------------------------------------------------------------------------
class DieModuleInterface
{
public:
	virtual void onDie( const DamageInfo *damageInfo ) = 0;
};

//-------------------------------------------------------------------------------------------------
class DieModule : public BehaviorModule, public DieModuleInterface
{
public:
	DieModule( Thing *thing, const ModuleData *moduleData );

	virtual DieModuleInterface *getDie() { return this; }

protected:
	virtual ~DieModule();
	bool isDieApplicable( const DamageInfo *damageInfo ) const;
};

#endif // __BFME2_DIEMODULE_H_
