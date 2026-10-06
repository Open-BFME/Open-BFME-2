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

class Xfer
{
public:
	class Version;

	Xfer();
	virtual ~Xfer();

	void Version1();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);

	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

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

class Team
{
public:
	UnsignedInt getID( void ) const { return m_id; }
private:
	char m_unrecovered00[ 0x34 ];
	UnsignedInt m_id;																													///< 0x34
};

class Rva0039F761Owner
{
public:
	Team *findInstance( void *prototypeKey );
};

class TeamFactory;
extern TeamFactory *TheTeamFactory;

class WorkOrder : public Snapshot
{
public:
	WorkOrder( void ) throw();
protected:
	virtual void crc( Xfer *xfer );
	virtual void xfer( Xfer *xfer );
	virtual void loadPostProcess( void );
public:
	char m_unrecovered04[ 0x0C - 0x04 ];
	WorkOrder *m_next;																												///< 0x0C
	char m_unrecovered10[ 0x30 - 0x10 ];
};

class TeamInQueue
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
private:
	char m_unrecovered04[ 0x14 - 0x04 ];
	WorkOrder *m_workOrders;																									///< 0x14
	Bool m_priorityBuild;																											///< 0x18
	Team *m_team;																															///< 0x1C
	char m_unrecovered20[ 0x24 - 0x20 ];
	Int m_frameStarted;																												///< 0x24
	Bool m_sentToStartLocation;																								///< 0x28
	Bool m_stopQueueing;																											///< 0x29
	Bool m_reinforcement;																											///< 0x2A
	ObjectID m_reinforcementID;																								///< 0x2C
};

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
		m_team = ((Rva0039F761Owner *)TheTeamFactory)->findInstance( (void *)teamID );
	*xfer == m_frameStarted;
	*xfer == m_sentToStartLocation;
	*xfer == m_stopQueueing;
	*xfer == m_reinforcement;
	XferObjectID( xfer, &m_reinforcementID );

}  // end xfer
