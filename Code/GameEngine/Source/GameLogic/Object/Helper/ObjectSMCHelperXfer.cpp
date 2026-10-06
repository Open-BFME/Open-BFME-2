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


// ObjectSMCHelper::xfer, ported from Zero Hour's GameEngine/Source/GameLogic/
// Object/Helper/ObjectSMCHelper.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference), with the timer list that BFME 1
// added (reference/open-bfme-1/game/GameEngine/Source/GameLogic/Object/
// Helper/ObjectSMCHelperXfer.cpp, retail BFME 1 0x00257390). It is slot 3 of
// the vftable whose name getter (0x0029288E) returns "ObjectSMCHelper".
//
// BFME 2 order: the helper base xfer (Rva004DF81B, ZH's ObjectHelper) first,
// then the light-CRC gate and Version1, then the timer count and the
// (model condition, frame) pairs. Loading appends each pair through the list's
// out-of-line push_back (0x004DE74D). The list sits at +0x20, as the matched
// destructor 0x004DE767 shows.

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


typedef int Int;
typedef unsigned int UnsignedInt;

void XferModelConditionFlagType( Xfer *xfer, Int *value );

struct ObjectSMCHelperTimerValue
{
	Int m_condition;
	UnsignedInt m_frame;
};

struct ObjectSMCHelperTimerNode
{
	ObjectSMCHelperTimerNode *m_next;
	ObjectSMCHelperTimerNode *m_previous;
	ObjectSMCHelperTimerValue m_value;
};

class ObjectSMCHelperTimerList
{
public:
	Int size( void ) const
	{
		Int n = 0;
		for( ObjectSMCHelperTimerNode *p = m_node->m_next; p != m_node; p = p->m_next )
			++n;
		return n;
	}
	ObjectSMCHelperTimerNode *m_node;
};

// Rowed 8-byte list element at 0x004DE74D (SpecialPowerTimerList.cpp). Same
// layout as ObjectSMCHelperTimerValue (condition + frame); the retail xfer
// calls it directly, so this TU calls the row name via cast. Declaration
// only: the definition lives in the row owner.
struct BfmeSpecialPowerTimer8 { unsigned int m_templateID; unsigned int m_readyFrame; };

namespace _STL
{
	template <class T> class allocator;
	template <class T, class Alloc> class list
	{
	public:
		void push_back(const T &value);
	};
}

class Rva004DF81B
{
public:
	virtual ~Rva004DF81B();
	void xfer( Xfer *xfer );
private:
	char m_unrecovered04[ 0x20 - 0x04 ];
};

class ObjectSMCHelper : public Rva004DF81B
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	ObjectSMCHelperTimerList m_timers;																				///< 0x20
};

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void ObjectSMCHelper::xfer( Xfer *xfer )
{

	// object helper base class
	Rva004DF81B::xfer( xfer );

	if( xfer->IsLightCRC() )
		return;

	xfer->Version1();

	ObjectSMCHelperTimerValue timer;
	Int count = m_timers.size();
	*xfer == count;

	if( xfer->IsStoring() )
	{
		for( ObjectSMCHelperTimerNode *it = m_timers.m_node->m_next; it != m_timers.m_node; )
		{
			timer = it->m_value;
			it = it->m_next;
			XferModelConditionFlagType( xfer, &timer.m_condition );
			*xfer == timer.m_frame;
		}
	}
	else
	{
		for( Int i = 0; i < count; ++i )
		{
			XferModelConditionFlagType( xfer, &timer.m_condition );
			*xfer == timer.m_frame;
			(( _STL::list<BfmeSpecialPowerTimer8, _STL::allocator<BfmeSpecialPowerTimer8> > *)&m_timers)->push_back(*(const BfmeSpecialPowerTimer8 *)&timer);
		}
	}

}  // end xfer
