// cl: /Ireference/shims/bfme2_ascii /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /EHsc
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


// AttackPriorityInfo::xfer, ported from Zero Hour's GameEngine/Source/
// GameLogic/ScriptEngine/ScriptEngine.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference). It is slot 3 of the vftable whose
// name getter returns "AttackPriorityInfo" (the ledger's Rva0034C5E0).
//
// BFME 2 opens with the light-CRC gate and Version1. It takes the map count
// from size(), the variant ZH keeps commented out, and drops the save-side
// recount. Otherwise ZH's body is unchanged: STLport map iteration (the
// out-of-line _Rb_global<bool>::_M_increment), template lookup through the
// thing factory (0x002D06CA), XferException tag 5 on a missing template, and
// setPriority (0x00358333).

#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#include "ascii_string.h"

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

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException(void);

	char *text;
	int tagValue;
};

class ThingTemplate
{
public:
	const AsciiString &getName( void ) const { return m_nameString; }
private:
	char m_unrecovered00[ 0x64 ];
	AsciiString m_nameString;																									///< 0x64
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate( const AsciiString &name );
};
extern ThingFactory *TheThingFactory;

typedef _STL::map< const ThingTemplate *, Int, _STL::less< const ThingTemplate * > > AttackPriorityMap;

class AttackPriorityInfo
{
public:
	void setPriority( const ThingTemplate *tThing, Int priority );
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
private:
	AsciiString m_name;																												///< 0x04
	Int m_defaultPriority;																										///< 0x08
	AttackPriorityMap *m_priorityMap;																					///< 0x0C
};

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void AttackPriorityInfo::xfer( Xfer *xfer )
{
	if( xfer->IsLightCRC() )
		return;

	// version
	xfer->Version1();

	// name
	*xfer == m_name;

	*xfer == m_defaultPriority;

	// priority map count
	UnsignedShort priorityMapCount = m_priorityMap ? m_priorityMap->size() : 0;
	*xfer == priorityMapCount;

	// priority map
	AsciiString thingTemplateName;
	const ThingTemplate *thingTemplate;
	Int priority;
	if( xfer->IsStoring() )
	{

		if( m_priorityMap )
		{

			// iterate all the entries
			AttackPriorityMap::const_iterator it;
			for( it = m_priorityMap->begin(); it != m_priorityMap->end(); ++it )
			{

				// write thing template name
				thingTemplate = (*it).first;
				thingTemplateName = thingTemplate->getName();
				*xfer == thingTemplateName;

				// write priority
				priority = (*it).second;
				*xfer == priority;

			}  // end for i

		}  // end if

	}  // end if, save
	else
	{

		// read all entries
		for( UnsignedShort i = 0; i < priorityMapCount; ++i )
		{

			// read thing template name, and get template
			*xfer == thingTemplateName;
			thingTemplate = TheThingFactory->findTemplate( thingTemplateName );
			if( thingTemplate == 0 )
				throw XferException( 5, 0 );

			// read priority
			*xfer == priority;

			// set priority (this will allocate the map on the first call as well)
			setPriority( thingTemplate, priority );

		}  // end for

	}  // end else, load

}  // end xfer
