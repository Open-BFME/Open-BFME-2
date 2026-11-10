// cl: /DNDEBUG /MD
// cl: /O1 /DNDEBUG /MD /GX
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


// BattlePlanUpdate::xfer, ported from Zero Hour's GameEngine/Source/GameLogic/
// Object/Update/BattlePlanUpdate.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference). It is slot 3 of the vftable whose
// name getter returns "BattlePlanUpdate".
//
// BFME 2 order: the UpdateModule base (0x0044DF9F) first, then the light-CRC
// gate and Version1, then ZH's fields. The two kind-of masks go through the
// 7-dword BitFlags<218> xfer 0x002AC06A. KindOfMaskType is the donor's
// typedef, with the target's 218-bit extent proven by the provider. After
// ZH's vision object id, BFME 2 hands Xfer and the +0x84 member to TheAudio's
// slot 88 (+0x160).

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;

#include "../../../../Include/Common/BfmeXfer.h"

#include "../../../../Include/Common/XferVersion.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

#include "../../../../../Libraries/Include/Lib/Coord3DBase.h"

typedef bool Bool;
typedef float Real;

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID( Xfer *xfer, ObjectID *value );

enum BattlePlanStatus
{
	PLANSTATUS_NONE
};

enum TransitionStatus
{
	TRANSITIONSTATUS_IDLE
};

#include "../../../../Include/Common/BitFlagsTemplate.h"
typedef BitFlags<218> KindOfMaskType;

struct BattlePlanBonuses
{
	Real m_armorScalar;																												///< 0x00
	Int m_bombardment;																												///< 0x04
	Int m_searchAndDestroy;																										///< 0x08
	Int m_holdTheLine;																												///< 0x0C
	Real m_sightRangeScalar;																									///< 0x10
	KindOfMaskType m_validKindOf;																							///< 0x14
	KindOfMaskType m_invalidKindOf;																						///< 0x30
};

#include "../../../../Include/Common/GameAudio.h"

extern AudioManager *TheAudio;

#include "../../../../Include/GameLogic/Module/UpdateModule.h"

class BattlePlanUpdate : public UpdateModule
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	char m_unrecovered20[0x24 - 0x20]; // +0x20, unrecovered bytes before this class's fields
	BattlePlanStatus m_currentPlan;																						///< 0x24
	BattlePlanStatus m_desiredPlan;																						///< 0x28
	BattlePlanStatus m_planAffectingArmy;																			///< 0x2C
	TransitionStatus m_status;																								///< 0x30
	UnsignedInt m_nextReadyFrame;																							///< 0x34
	void *m_specialPowerModule;																								///< 0x38
	Bool m_invalidSettings;																										///< 0x3C
	Bool m_centeringTurret;																										///< 0x3D
	BattlePlanBonuses *m_bonuses;																							///< 0x40
	char m_unrecovered44[ 0x84 - 0x44 ];
	unsigned int m_bfmeAudio84;																				///< 0x84
	ObjectID m_visionObjectID;																								///< 0x88
};

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void BattlePlanUpdate::xfer( Xfer *xfer )
{

	// extend base class
	UpdateModule::xfer( xfer );

	if( xfer->IsLightCRC() )
		return;

	// version
	xfer->Version1();

	// current plan
	xfer->XferRawBytes( &m_currentPlan, sizeof( BattlePlanStatus ) );

	// desired plan
	xfer->XferRawBytes( &m_desiredPlan, sizeof( BattlePlanStatus ) );

	// plan affecting army
	xfer->XferRawBytes( &m_planAffectingArmy, sizeof( BattlePlanStatus ) );

	// status
	xfer->XferRawBytes( &m_status, sizeof( TransitionStatus ) );

	// next ready frame
	*xfer == m_nextReadyFrame;

	// invalid settings
	*xfer == m_invalidSettings;

	// centering turret
	*xfer == m_centeringTurret;

	// bonuses
	*xfer == m_bonuses->m_armorScalar;
	*xfer == m_bonuses->m_bombardment;
	*xfer == m_bonuses->m_searchAndDestroy;
	*xfer == m_bonuses->m_holdTheLine;
	*xfer == m_bonuses->m_sightRangeScalar;
	m_bonuses->m_validKindOf.xfer( xfer );
	m_bonuses->m_invalidKindOf.xfer( xfer );

	// vision object data
	XferObjectID( xfer, &m_visionObjectID );

	TheAudio->xferAudioHandle( xfer, &m_bfmeAudio84 );

}  // end xfer
