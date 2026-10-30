// cl: /DNDEBUG /MD /GX
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

// SupplyTruckAIUpdate::xfer, ported from Zero Hour's GameEngine/Source/
// GameLogic/Object/Update/AIUpdate/SupplyTruckAIUpdate.cpp (GeneralsMD tree
// vendored under reference/open-bfme-1/inputs/reference). It is slot 3 of the
// SupplyTruckAIUpdate table in BFME 2's Xfer spelling: AIUpdateInterface::xfer
// (slot 3 of AIUpdateInterface's vftable 0x00BFA480, 0x00267EDD), the
// light-CRC early-out, Version1, then the state-machine snapshot (+0x3E8)
// and preferred dock (+0x3EC) as in ZH. BFME 2 inserts a Coord3D (+0x3F0)
// and a Bool (+0x3FC) before ZH's box count (+0x400) and force-pending flag
// (+0x404), and adds a final Bool (+0x405). The inserted fields have no ZH
// counterpart and keep offset names.

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

#include "../../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../../Include/Common/BfmeXfer.h"

typedef bool Bool;
typedef int Int;

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID( Xfer *xfer, ObjectID *id );

class Coord3DBase
{
public:
	float x;
	float y;
	float z;
};

class Object;
class SupplyTruckAIInterface;

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

enum NameKeyType
{
	NK_UNKNOWN = 0
};

enum UpdateSleepTime
{
	USLEEP_MIN = 0
};

class AICommandInterface
{
public:
	void aiDock(Object *obj, CommandSourceType cmdSource);
	void aiHarvest(const Coord3D *pos, CommandSourceType cmdSource);
};

class AIUpdateInterface
{
public:
	virtual UpdateSleepTime update(); virtual void v001(); virtual void v002(); virtual void xfer(Xfer *xfer);
	virtual void v004(); virtual void v005(); virtual void v006(); virtual void v007();
	virtual void v008(); virtual void v009(); virtual void v010(); virtual void v011();
	virtual void v012(); virtual void v013(); virtual void v014(); virtual void v015();
	virtual void v016(); virtual void v017(); virtual void v018(); virtual void v019();
	virtual void v020(); virtual void v021(); virtual void v022(); virtual void v023();
	virtual void v024(); virtual void v025(); virtual void v026(); virtual void v027();
	virtual void v028(); virtual void v029(); virtual void v030(); virtual void v031();
	virtual void v032(); virtual void v033(); virtual void v034(); virtual void v035();
	virtual void v036(); virtual void v037(); virtual void v038(); virtual void v039();
	virtual void v040(); virtual void v041(); virtual void v042(); virtual void v043();
	virtual void v044(); virtual void v045(); virtual void v046(); virtual void v047();
	virtual void v048(); virtual void v049(); virtual void v050(); virtual void v051();
	virtual void v052(); virtual void v053(); virtual void v054(); virtual void v055();
	virtual void v056(); virtual void v057(); virtual void v058(); virtual void v059();
	virtual void v060(); virtual void v061(); virtual void v062(); virtual void v063();
	virtual void v064(); virtual void v065(); virtual void v066(); virtual void v067();
	virtual void v068(); virtual void v069(); virtual void v070(); virtual void v071();
	virtual void v072(); virtual void v073(); virtual void v074(); virtual void v075();
	virtual void v076(); virtual void v077(); virtual void v078(); virtual void v079();
	virtual void v080(); virtual void v081(); virtual void v082(); virtual void v083();
	virtual void v084(); virtual void v085(); virtual void v086(); virtual void v087();
	virtual void v088(); virtual void v089(); virtual void v090(); virtual void v091();
	virtual void v092(); virtual void v093(); virtual void v094();
	virtual SupplyTruckAIInterface *getSupplyTruckAIInterface(); // slot 95 (+0x17C)
	virtual void v096(); virtual void v097(); virtual void v098(); virtual void v099();
	virtual void v100(); virtual void v101(); virtual void v102(); virtual void v103();
	virtual void v104(); virtual void v105(); virtual void v106(); virtual void v107();
	virtual void v108(); virtual void v109();
	virtual Bool isIdle(); // slot 110 (+0x1B8)
	Int getCurrentStateID() const; // rowed 0x00262FC3

	char m_pad04[0x20 - 0x04];
	AICommandInterface m_commands; // +0x20
	char m_pad21[0x3E8 - 0x21];
};

class SupplyTruckAIUpdate : public AIUpdateInterface
{
public:
	virtual NameKeyType getModuleNameKey() const;
protected:
	virtual void xfer( Xfer *xfer );
private:
	Snapshot *m_supplyTruckStateMachine;																			///< 0x3E8
	ObjectID m_preferredDock;																									///< 0x3EC
	Coord3DBase m_bfmeCoord3F0;																								///< 0x3F0
	Bool m_bfmeFlag3FC;																												///< 0x3FC
	Int m_numberBoxes;																												///< 0x400
	Bool m_forcePending;																											///< 0x404
	Bool m_forcedBusyPending;																												///< 0x405
};

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void SupplyTruckAIUpdate::xfer( Xfer *xfer )
{

	// extend base class
	AIUpdateInterface::xfer(xfer);

	if( xfer->IsLightCRC() )
		return;

	// version
	xfer->Version1();

	*xfer == *m_supplyTruckStateMachine;
	XferObjectID( xfer, &m_preferredDock );
	*xfer == m_bfmeCoord3F0;
	*xfer == m_bfmeFlag3FC;
	*xfer == m_numberBoxes;
	*xfer == m_forcePending;
	*xfer == m_forcedBusyPending;

}  // end xfer
