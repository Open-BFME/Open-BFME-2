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

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
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

typedef unsigned short UnsignedShort;

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID( Xfer *xfer, ObjectID *value );
Xfer *Rva0036ABAFXfer( Xfer *xfer, _STL::list<int> *values );

class Object
{
public:
	ObjectID getID( void ) const { return m_id; }
private:
	char m_unrecovered00[ 0x74 ];
	ObjectID m_id;																														///< 0x74
};

typedef _STL::list<Object *> ContainedItemsList;

class TunnelTracker
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
private:
	char m_unrecovered04[ 0x08 - 0x04 ];
	_STL::list<int> m_tunnelIDs;																							///< 0x08
	char m_unrecovered0C[ 0x10 - 0x0C ];
	ContainedItemsList m_containList;																					///< 0x10
	_STL::list<ObjectID> m_xferContainList;																		///< 0x14
	Int m_containListSize;																										///< 0x18
	UnsignedInt m_tunnelCount;																								///< 0x1C
	ObjectID m_bfmeObject20;																									///< 0x20
	UnsignedInt m_bfmeUnsigned24;																							///< 0x24
};

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

			objectID = (*it)->getID();
			XferObjectID( xfer, &objectID );

		}  // end for, it

	}  // end if, save
	else
	{

		for( UnsignedShort i = 0; i < m_containListSize; ++i )
		{

			XferObjectID( xfer, &objectID );
			m_xferContainList.push_back( objectID );

		}  // end for, i

	}  // end else, load

	// tunnel count
	*xfer == m_tunnelCount;

	XferObjectID( xfer, &m_bfmeObject20 );
	*xfer == m_bfmeUnsigned24;

}  // end xfer
