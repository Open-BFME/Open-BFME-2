// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /ICode/Libraries/Include
// Bodies follow the Generals Zero Hour reference
// (GameEngine/Source/GameLogic/Object/Die/SpecialPowerCompletionDie.cpp).
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
// FILE: SpecialPowerCompletionDie.cpp ////////////////////////////////////////////////////////////
// Author: Matthew D. Campbell, May 2002
// Desc:   Die method responsible for telling TheScriptEngine that a special power has been completed
///////////////////////////////////////////////////////////////////////////////////////////////////
class Thing;
class ModuleData;
class Object;
#include "../../../../Include/GameLogic/Module/DieModule.h"
#include "../../../../Include/GameLogic/Module/DieMuxData.h"
#include "../../../../Include/Common/NameKeyGenerator.h"

extern NameKeyGenerator *TheNameKeyGenerator;

enum ObjectID { INVALID_ID = 0 };

// BFME2 has no crc: the canonical DieModule's Snapshot slot 2 is GetSnapshotName,
// so this unit's tables no longer name the Zero Hour ?crc@BehaviorModule.
//-------------------------------------------------------------------------------------------------
// The die-module data (0x0045CE4C) forwards to its DieMuxData at +8
// (`add ecx, 8; jmp 0x004CE588`).
class DieModuleData
{
public:
	bool isDieApplicable( const Object *obj, const DamageInfo *damageInfo ) const;
private:
	char m_moduleData[8];
	DieMuxData m_dieMuxData;
};

bool DieModuleData::isDieApplicable( const Object *obj, const DamageInfo *damageInfo ) const
{
	return m_dieMuxData.isDieApplicable( obj, damageInfo );
}

//-------------------------------------------------------------------------------------------------
// ??0DieModule (0x0045CEBD) calls ??0BehaviorModule, then the inline
// DieModuleInterface constructor and DieModule's own three tables. Inline: the
// other die units emit the same COMDAT, so a strong copy here would be a duplicate.
inline DieModule::DieModule( Thing *thing, const ModuleData *moduleData ) : BehaviorModule( thing, moduleData )
{
}

//-------------------------------------------------------------------------------------------------
class SpecialPowerCompletionDie : public DieModule
{
public:
	SpecialPowerCompletionDie( Thing *thing, const ModuleData* moduleData );
	virtual NameKeyType getModuleNameKey() const;
	virtual void onDie( const DamageInfo *damageInfo );
	void setCreator( ObjectID creatorID );
	void notifyScriptEngine();
protected:
	virtual ~SpecialPowerCompletionDie();
private:
	ObjectID m_creatorID;				// +0x14
	bool m_creatorSet;					// +0x18
};

//-------------------------------------------------------------------------------------------------
SpecialPowerCompletionDie::SpecialPowerCompletionDie( Thing *thing, const ModuleData* moduleData ) : DieModule( thing, moduleData )
{
	m_creatorID = INVALID_ID;
	m_creatorSet = false;
}

//-------------------------------------------------------------------------------------------------
// Retail 0x004869FC (rowed as the opaque ??1Rva004869FC): the class's three tables,
// then a tail jump to ~DieModule 0x0045CE54.
SpecialPowerCompletionDie::~SpecialPowerCompletionDie( void )
{
}

//-------------------------------------------------------------------------------------------------
NameKeyType SpecialPowerCompletionDie::getModuleNameKey() const
{
	static NameKeyType nameKey = TheNameKeyGenerator->nameToKey( "SpecialPowerCompletionDie" );
	return nameKey;
}

//-------------------------------------------------------------------------------------------------
void SpecialPowerCompletionDie::onDie( const DamageInfo *damageInfo )
{
	if (!isDieApplicable(damageInfo))
		return;

	notifyScriptEngine();
}

// SpecialPowerCompletionDie::notifyScriptEngine is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Die/SpecialPowerCompletionDieNotify.cpp (0x00486B01).

//-------------------------------------------------------------------------------------------------
void SpecialPowerCompletionDie::setCreator( ObjectID creatorID )
{
	if (!m_creatorSet)
	{
		m_creatorSet = true;
		m_creatorID = creatorID;
	}
}

// SpecialPowerCompletionDie::xfer: defined in SpecialPowerCompletionDieXfer.cpp (its row's unit).
