// cl: /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
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


// TunnelTracker::xfer, ported from Zero Hour's GameEngine/Source/Common/RTS/
// TunnelTracker.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference). It is slot 3 of the vftable whose
// name getter returns "TunnelTracker".
//
// BFME 2 opens with the light-CRC gate and Version1. ZH's xferSTLObjectIDList
// is the rowed helper 0x0036ABAF (over list<int>). The load loop appends
// through the out-of-line list push_back 0x0005548F. ZH's fields are at
// +0x08..+0x1C; BFME 2 adds an ObjectID (+0x20) and an UnsignedInt (+0x24).

#include <list>

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}

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

typedef unsigned short UnsignedShort;

// The native four-byte append is the rowed list<int> member at 0x0005548F,
// also used by TunnelTracker's other ID list. Keep it out of line here.
namespace _STL { template <> void list<int, allocator<int> >::push_back(const int &); }

#include "TunnelTrackerNemesisView.h"

void XferObjectID( Xfer *xfer, ObjectID *value );
Xfer *Rva0036ABAFXfer( Xfer *xfer, _STL::list<int> *values );

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void TunnelTracker::xfer( Xfer *xfer )
{
	if( xfer->IsLightCRC() )
		return;

	// version
	xfer->Version1();

	// tunnel object id list
	Rva0036ABAFXfer( xfer, &m_tunnelIDs );

	// contain list count
	*xfer == m_containListSize;

	// contain list data
	ObjectID objectID;
	if( xfer->IsStoring() )
	{
		ContainedItemsList::const_iterator it;

		for( it = m_containList.begin(); it != m_containList.end(); ++it )
		{

			objectID = (ObjectID)(*it)->getID();
			XferObjectID( xfer, &objectID );

		}  // end for, it

	}  // end if, save
	else
	{

		for( UnsignedShort i = 0; i < m_containListSize; ++i )
		{

			XferObjectID( xfer, &objectID );
			m_xferContainList.push_back( reinterpret_cast<const int &>(objectID) );

		}  // end for, i

	}  // end else, load

	// tunnel count
	*xfer == m_tunnelCount;

	XferObjectID( xfer, (ObjectID *)&m_curNemesisID );
	*xfer == m_nemesisTimestamp;

}  // end xfer
