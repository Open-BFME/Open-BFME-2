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
// DieModule::loadPostProcess and DieModule::xfer below make Zero Hour's base
// calls; select the BehaviorModule declarations they need (BehaviorModule.h).
// Every table this unit emits derives from DieModule, which overrides both.
#define BFME_BEHAVIORMODULE_LOADPOSTPROCESS
#define BFME_BEHAVIORMODULE_XFER
#include "../../../../Include/GameLogic/Module/DieModule.h"
#include "../../../../Include/GameLogic/Module/DieMuxData.h"
#include "../../../../Include/Common/NameKeyGenerator.h"

extern NameKeyGenerator *TheNameKeyGenerator;

#include "../../../../../../reference/open-bfme-1/game/GameEngine/Include/Common/ObjectID.h"

// DieModule::xfer calls Xfer::Version1; keep its operand types beside the include.
class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
class Coord3DBase;
struct ICoord3D;
struct Region3D;
struct IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../../../Include/Common/BfmeXfer.h"

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
// DieModule's Snapshot overrides, slots 1 and 3 of its primary table 0x00C41E78.
// Both are bodies retail folds with other modules' identical overrides:
//  - loadPostProcess 0x0058B03E: the tail jump to BehaviorModule::loadPostProcess
//    (UpdateModule's, DamageModule's and CollideModule's rows share it);
//  - xfer 0x004CE56D: Version1, then BehaviorModule::xfer 0x004C9C7D
//    (DamageModule's and CollideModule's rows share it).
// Donor: Zero Hour DieModule.cpp defines these two (and crc, which BFME2's
// Snapshot has no slot for), with these bodies.
void DieModule::loadPostProcess()
{
	BehaviorModule::loadPostProcess();
}

void DieModule::xfer( Xfer *xfer )
{
	xfer->Version1();
	BehaviorModule::xfer( xfer );
}

//-------------------------------------------------------------------------------------------------
class Xfer;
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
protected:
	virtual void xfer(class Xfer *);
};

//-------------------------------------------------------------------------------------------------
SpecialPowerCompletionDie::SpecialPowerCompletionDie( Thing *thing, const ModuleData* moduleData ) : DieModule( thing, moduleData )
{
	m_creatorID = INVALID_ID;
	m_creatorSet = false;
}

//-------------------------------------------------------------------------------------------------
// Retail 0x004869FC (fold rows ??1SpecialPowerCompletionDie@@MAE@XZ and
// ??_GSpecialPowerCompletionDie@@MAEPAXI@Z): the class's three tables, then a
// tail jump to ~DieModule 0x0045CE54.
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
