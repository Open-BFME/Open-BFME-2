// Copied from reference/shims/diemodule_link/GameLogic/Module/DieModule.h; each change is marked "BFME 2:".
// BFME2 scoped view of the ZH DieModule header at BFME1 f36a4db066aa61ed.
// Retail deleting wrapper 0x0045CEF4 calls the out-of-line destructor and global delete.
// Preserve the donor class and constructor; adjust only these two proven operations.
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: DieModule.h /////////////////////////////////////////////////////////////////////////////////
// Author: Colin Day, September 2001
// Desc:
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __DieModule_H_
#define __DieModule_H_

#include "Common/Module.h"
#include "GameLogic/Damage.h"
#include "GameLogic/Module/BehaviorModule.h"
#include "Common/ObjectStatusTypes.h"

//-------------------------------------------------------------------------------------------------
/** OBJECT DIE MODULE base class */
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
class DieModuleInterface
{
public:
	virtual void onDie( const DamageInfo *damageInfo ) = 0;
};

//-------------------------------------------------------------------------------------------------
class DieMuxData	// does NOT inherit from ModuleData.
{
public:
	DeathTypeFlags				m_deathTypes;
	VeterancyLevelFlags		m_veterancyLevels;
	ObjectStatusMaskType	m_exemptStatus;						///< die module is ignored if any of these status bits are set
	ObjectStatusMaskType	m_requiredStatus;					///< die module is ignored if any of these status bits are clear

	DieMuxData();
	static const FieldParse* getFieldParse();

	Bool isDieApplicable(const Object* obj, const DamageInfo *damageInfo) const;
};

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
class DieModuleData : public BehaviorModuleData
{
public:
	DieMuxData			m_dieMuxData;

	static void buildFieldParse(MultiIniFieldParse& p)
	{
		BehaviorModuleData::buildFieldParse(p);
		p.add(DieMuxData::getFieldParse(), offsetof( DieModuleData, m_dieMuxData ));
	}

	inline Bool isDieApplicable(const Object* obj, const DamageInfo *damageInfo) const { return m_dieMuxData.isDieApplicable(obj, damageInfo); }
};

//-------------------------------------------------------------------------------------------------
class DieModule : public BehaviorModule, public DieModuleInterface
{

protected:
	virtual ~DieModule();
public:
	enum DieModuleMagicEnum { DieModule_GLUE_NOT_IMPLEMENTED = 0 };
protected:
	inline void *operator new(size_t s, DieModuleMagicEnum e DECLARE_LITERALSTRING_ARG2)
	{
		DEBUG_CRASH(("this should be impossible to call (abstract base class)"));
		DEBUG_ASSERTCRASH(s == sizeof(DieModule), ("The wrong operator new is being called; ensure all objects in the hierarchy have MemoryPoolGlue set up correctly"));
		throw ERROR_BUG;
		return 0;
	}
protected:
	inline void operator delete(void *p, DieModuleMagicEnum e DECLARE_LITERALSTRING_ARG2)
	{
		DEBUG_CRASH(("this should be impossible to call (abstract base class)"));
	}
protected:
	inline void *operator new(size_t s)
	{
		DEBUG_CRASH(("this should be impossible to call (abstract base class)"));
		DEBUG_ASSERTCRASH(s == sizeof(DieModule), ("The wrong operator new is being called; ensure all objects in the hierarchy have MemoryPoolGlue set up correctly"));
		throw ERROR_BUG;
		return 0;
	}
	inline void operator delete(void *p)
	{
		::operator delete(p);
	}
private:
	virtual MemoryPool *getObjectMemoryPool()
	{
		throw ERROR_BUG;
		return 0;
	}
public: /* include this line at the end to reset visibility to 'public' */
	MAKE_STANDARD_MODULE_MACRO_ABC( DieModule )
	MAKE_STANDARD_MODULE_DATA_MACRO_ABC(DieModule, DieModuleData)

public:

	DieModule( Thing *thing, const ModuleData* moduleData );
	// virtual destructor prototype defined by MemoryPoolObject

	static Int getInterfaceMask() { return MODULEINTERFACE_DIE; }

	// BehaviorModule
	virtual DieModuleInterface* getDie() { return this; }

	void onDie( const DamageInfo *damageInfo ) = 0;

protected:
	// BFME 2: out of line, row ?isDieApplicable@DieModule@@IBE_NPBVDamageInfo@@@Z 0x0045CEA7, called at 0x00485C93.
	Bool isDieApplicable(const DamageInfo *damageInfo) const;

};
inline DieModule::DieModule( Thing *thing, const ModuleData* moduleData ) : BehaviorModule( thing, moduleData ) { }
// Destructor is owned by FXListDie.cpp (RVA 0x0045CE54).

#endif
