// cl: /Ireference/shims/moduledata /DNDEBUG /MD /EHsc
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


// TeamInQueue::xfer, ported from Zero Hour's GameEngine/Source/GameLogic/AI/
// AIPlayer.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference). It is slot 3 of the vftable whose
// name getter returns "TeamInQueue".
//
// BFME 2 opens with the light-CRC gate and Version1, then follows ZH's body.
// Work orders are allocated with plain operator new and the WorkOrder
// constructor 0x004F10E6, which installs the vftable whose name getter returns
// WorkOrder and clears m_next at +0x0C. ZH's throw SC_INVALID_DATA becomes
// XferException tag 5. The team is saved by its id (Team+0x34) and reloaded
// through the team factory lookup 0x0039F761. The constructor is declared
// non-throwing: retail has no unwind frame around the allocation.

#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"

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

#include "../../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class Coord3DBase
{
public:
	float x;
	float y;
	float z;
};

typedef bool Bool;
typedef unsigned short UnsignedShort;

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID( Xfer *xfer, ObjectID *value );

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException(void);

	char *text;
	int tagValue;
};

#include "../../../Include/Common/TeamBFME2.h"

class TeamFactory
{
public:
	Team *findTeamByID(unsigned int id);
};

class TeamFactory;
extern TeamFactory *TheTeamFactory;

#include "WorkOrder.h"

#include "TeamInQueue.h"

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void TeamInQueue::xfer( Xfer *xfer )
{
	if( xfer->IsLightCRC() )
		return;

	// version
	xfer->Version1();

	// xfer work order count
	UnsignedShort workOrderCount = 0;
	WorkOrder *workOrder;
	for( workOrder = m_workOrders; workOrder; workOrder = workOrder->m_next )
		workOrderCount++;
	*xfer == workOrderCount;

	// xfer work orders
	if( xfer->IsStoring() )
	{

		// xfer each work order
		for( workOrder = m_workOrders; workOrder; workOrder = workOrder->m_next )
		{

			// xfer work order data
			*xfer == *workOrder;

		}  // end for

	}  // end if, save
	else
	{

		// sanity
		if( m_workOrders != 0 )
			throw XferException( 5, 0 );

		// load all work orders
		for( UnsignedShort i = 0; i < workOrderCount; ++i )
		{

			// allocate new work order
			workOrder = new WorkOrder;

			// attach to list at the end
			workOrder->m_next = 0;
			if( m_workOrders == 0 )
				m_workOrders = workOrder;
			else
			{
				WorkOrder *last = m_workOrders;

				while( last->m_next != 0 )
					last = last->m_next;

				last->m_next = workOrder;

			}  // end else

			// load work order data
			*xfer == *workOrder;

		}  // end for, i

	}  // end else, load

	// xfer the rest of the team in queue data
	*xfer == m_priorityBuild;
	UnsignedInt teamID = m_team ? m_team->getID() : 0;
	*xfer == teamID;
	if( xfer->IsLoading() )
		m_team = TheTeamFactory->findTeamByID( teamID );
	*xfer == m_frameStarted;
	*xfer == m_sentToStartLocation;
	*xfer == m_stopQueueing;
	*xfer == m_reinforcement;
	XferObjectID( xfer, &m_reinforcementID );

}  // end xfer
