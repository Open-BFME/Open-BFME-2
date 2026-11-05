// cl: /DNDEBUG /MD
// TU-local declarations for the six rowed HijackerUpdate methods.
// UpdateModule's canonical base is 0x20 bytes; the rowed setters and lookup
// methods access the target ID at +0x20 and flags at +0x30/+0x31.
#include "../../../../Include/GameLogic/Module/UpdateModule.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

class Object
{
public:
    ObjectID getID() const { return m_id; }
private:
    char m_pad[0x74];
    ObjectID m_id;
};

class HijackerUpdate : public UpdateModule
{
public:
    HijackerUpdate(Thing *thing, const ModuleData *moduleData);
    virtual UpdateSleepTime update();
    static NameKeyType rva0004A4010();
    void setTargetObject(const Object *object);
    Object *getTargetObject() const;
    void setUpdate(bool update) { m_update = update; }
    void setIsInVehicle(bool inVehicle) { m_isInVehicle = inVehicle; }
protected:
    virtual void loadPostProcess();
private:
    ObjectID m_targetID;
    Coord3D m_ejectPos;
    bool m_update;
    bool m_isInVehicle;
    bool m_wasTargetAirborne;
};

#define BFME_SNAPSHOT_NAME_GETTER(NAME, TEXT) \
	class NAME \
	{ \
	protected: \
		virtual const char *GetSnapshotName() const; \
	}; \
	const char *NAME::GetSnapshotName() const \
	{ \
		return TEXT; \
	}
#define BFME_LITERAL_NAME_GETTER(NAME, TEXT) \
	class NAME \
	{ \
	public: \
		const char *name() const; \
	}; \
	const char *NAME::name() const \
	{ \
		return TEXT; \
	}

BFME_LITERAL_NAME_GETTER(Rva004A3FA4Named, "HijackerUpdate")

// ---- from Code/GameEngine/Source/GameLogic/Object/Update/HijackerUpdate.cpp

// Ported verbatim from the Generals Zero Hour reference (GameEngine/Source/GameLogic/Object/Update/HijackerUpdate.cpp); this unit had no counterpart under Code/.

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

///////////////////////////////////////////////////////////////////////////////////////////////////
//
// FILE: HijackerUpdate.cpp 
// Author: Mark Lorenzen, July 2002
// Desc:   Allows hijacker to kepp with his hijacked vehicle (though hidden) until it dies, then 
// to become a hijacker once more
//
/////////////////////////////////////////////////////////////////////////////////////////////////

// USER INCLUDES //////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// Unverified donor definition banked in reverse/attempt_support/link-seat-20261021/HijackerUpdate-unmatched.cpp.txt

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// HijackerUpdate::update (0x004A40DB) is rowed in HijackerUpdateUpdate.cpp;
// a second definition here would not link.

// The header setters setIsInVehicle (0x004A3F81) and setUpdate (0x0066CA90)
// are rowed in this unit; the anchor keeps their out-of-line bodies emitted.
// ?bfmeAnchorHijackerUpdateSetters absent-from-retail
void bfmeAnchorHijackerUpdateSetters(HijackerUpdate *hijackerUpdate)
{
	hijackerUpdate->setIsInVehicle(false);
	hijackerUpdate->setUpdate(false);
}

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline void HijackerUpdate::setTargetObject( const Object *object )
{
  if( object )
  {
    m_targetID = object->getID();

		// here we also test the target to see whether it ejects pilots
		// when it dies... if so, stores a pointer to that diemoduleinterface
		// NULL if not...

//		BehaviorModule **dmi = NULL;
//		for( dmi = object->getBehaviorModules(); *dmi; ++dmi )
//		{
//			m_ejectPilotDMI = (*dmi)->getEjectPilotDieInterface();
//			if( m_ejectPilotDMI )
//				return;
//		}  // end for dmi
  }
	else
	{
		m_targetID = INVALID_OBJECT_ID;
//		m_ejectPilotDMI = NULL;
	}

}

// ?bfmeAnchorHijackerUpdatesetTargetObject absent-from-retail
void bfmeAnchorHijackerUpdatesetTargetObject(HijackerUpdate *hijackerUpdate, const Object *object)
{
	hijackerUpdate->setTargetObject(object);
}

Object* HijackerUpdate::getTargetObject() const
{
  if( m_targetID != INVALID_OBJECT_ID )
  {
    return TheGameLogic->findObjectByID( m_targetID );
  }
  return 0;
}

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// Unverified donor definition banked in reverse/attempt_support/link-seat-20261021/HijackerUpdate-unmatched.cpp.txt

// The unverified Zero Hour xfer attempt is banked in
// reverse/attempt_support/hijackerupdate-xfer-cleanup-20261103.md.
// Retail 0x004A3FAA remains rowed in Rva004A3F8BXfer.cpp.

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
void HijackerUpdate::loadPostProcess( void )
{

	// extend base class
	UpdateModule::loadPostProcess();

	// set the target object, this will also tie up teh m_ejectPilotDMI pointer
	Object *obj = TheGameLogic->findObjectByID( m_targetID );
	setTargetObject( obj );

}

  // end loadPostProcess

// tu-skeleton: 0x004A3F8B 25B ??1Rva004A3F8B@@UAE@XZ -- matched in Code/GameEngine/Source/Common/Rva0024A797Derived.cpp (not merged yet)

// ---- from Code/GameEngine/Source/Common/ModuleNameGetters3.cpp

// Module literal name getters (cold slice): six-byte const members with one
// shape:
//
//     mov eax,<offset string literal> / ret
//
// Each body returns a pointer to a NUL-terminated class-name string in
// .rdata. Contributor-local unit split from ModuleNameGetters2.cpp to keep
// concurrent landings conflict-free; the BFME_LITERAL_NAME_GETTER macro is
// verbatim, only the class names follow this tree's address-derived
// convention (identity unrecoverable from 6 bytes, string carried in source
// where verify_string_refs re-reads it).
// No // cl: line (defaults match the frameless 6-byte shape, same as the
// ModuleNameGetters.cpp precedent).

// tu-skeleton: 0x004A3FAA 102B ?xfer@Rva004A3F8B@@MAEXPAVXfer@@@Z -- matched in Code/GameEngine/Source/Common/Rva004A3F8BXfer.cpp (not merged yet)

// tu-skeleton: 0x004A4010 69B ?rva0004A4010@HijackerUpdate@@SA?AW4NameKeyType@@XZ -- matched in Code/GameEngine/Source/GameLogic/Object/Update/HijackerUpdatePoolKey.cpp (not merged yet)

// tu-skeleton: 0x004A4055 74B ??0HijackerUpdate@@QAE@PAVThing@@PBVModuleData@@@Z -- matched in Code/GameEngine/Source/GameLogic/Object/Update/HijackerUpdateCtor.cpp (not merged yet)

// tu-skeleton: 0x004A409F 28B ??_GRva004A3F8B@@UAEPAXI@Z -- matched in Code/GameEngine/Source/Common/Rva0024A797Derived.cpp (not merged yet)

// tu-skeleton: 0x004A40DB 313B ?update@HijackerUpdate@@UAE?AW4UpdateSleepTime@@XZ -- matched in Code/GameEngine/Source/GameLogic/Object/Update/HijackerUpdateUpdate.cpp (not merged yet)

// tu-skeleton: 0x0078DD56 13B $L306 -- matched in Code/GameEngine/Source/GameLogic/Object/Update/HijackerUpdatePoolKey.cpp (not merged yet)

// tu-skeleton: 0x0078DD63 10B __ehhandler$?rva0004A4010@HijackerUpdate@@SA?AW4NameKeyType@@XZ -- matched in Code/GameEngine/Source/GameLogic/Object/Update/HijackerUpdatePoolKey.cpp (not merged yet)
