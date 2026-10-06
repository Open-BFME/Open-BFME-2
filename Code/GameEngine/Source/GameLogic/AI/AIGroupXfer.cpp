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


// AIGroup::xfer, ported from Zero Hour's GameEngine/Source/GameLogic/AI/
// AIGroup.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference). It is slot 3 of the vftable whose
// name getter returns "AIGroup".
//
// ZH's xfer is only a version. BFME 2 adds ZH's crc() body behind IsCRC
// (Xfer +0x0C): the member ids, then the member count, now counted from the
// list instead of ZH's m_memberListSize. ZH's unused leader id is dropped.
// Then come speed, dirty and id, plus two BFME 2 Coord3Ds (+0x18, +0x24).

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
typedef float Real;

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID( Xfer *xfer, ObjectID *value );

class Object
{
public:
	ObjectID getID( void ) const { return m_id; }
private:
	char m_unrecovered00[ 0x74 ];
	ObjectID m_id;																														///< 0x74
};

struct AIGroupMemberNode
{
	AIGroupMemberNode *m_next;
	AIGroupMemberNode *m_previous;
	Object *m_value;
};

class AIGroupMemberList
{
public:
	UnsignedInt size( void ) const
	{
		UnsignedInt n = 0;
		for( AIGroupMemberNode *p = m_node->m_next; p != m_node; p = p->m_next )
			++n;
		return n;
	}
	AIGroupMemberNode *m_node;
};

class AIGroup
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
private:
	AIGroupMemberList m_memberList;																						///< 0x04
	Real m_speed;																															///< 0x08
	Bool m_dirty;																															///< 0x0C
	UnsignedInt m_id;																													///< 0x10
	char m_unrecovered14[ 0x18 - 0x14 ];
	Coord3DBase m_bfmeCoord18;																								///< 0x18
	Coord3DBase m_bfmeCoord24;																								///< 0x24
};

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void AIGroup::xfer( Xfer *xfer )
{

	// version
	xfer->Version1();

	if( xfer->IsCRC() )
	{
		for( AIGroupMemberNode *it = m_memberList.m_node->m_next; it != m_memberList.m_node; it = it->m_next )
		{
			ObjectID id = INVALID_ID;
			if( it->m_value )
				id = it->m_value->getID();
			XferObjectID( xfer, &id );
		}

		UnsignedInt memberListSize = m_memberList.size();
		*xfer == memberListSize;
		*xfer == m_speed;
		*xfer == m_dirty;
		*xfer == m_id;
		*xfer == m_bfmeCoord18;
		*xfer == m_bfmeCoord24;
	}

}  // end xfer
