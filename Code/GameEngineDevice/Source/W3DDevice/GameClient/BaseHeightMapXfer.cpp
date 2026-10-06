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


// BaseHeightMapRenderObjClass::xfer, ported from Zero Hour's
// GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMap.cpp (GeneralsMD
// tree vendored under reference/open-bfme-1/inputs/reference). It is slot 3
// of the vftable whose name getter returns "BaseHeightMapRenderObjClass".
//
// BFME 2 puts the light-CRC gate first and versions (1, 4). Versions before 3
// are refused by throwing XferException's unnamed-enum value 2, the same tag
// Xfer::operator==(Version&) uses for "older than supported". ZH's two buffer
// snapshots become three (+0x3788, +0x378C, +0x3790). Version 2 adds a fourth
// (+0x3798). Version 4 adds a counted array of 0x1C-byte snapshot records
// from +0x18 (count at +0x36C8) and an Int at +0x36D0. ZH's
// m_treeBuffer/m_propBuffer names on the first two follow ZH's order and are
// an inference.

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

class XferException
{
public:
	enum { VERSION_TOO_OLD = 2 };
};

// A 0x1C-byte snapshot record kept in an array at +0x18.
class BaseHeightMapSnapshotRecord : public Snapshot
{
protected:
	virtual void crc( Xfer *xfer );
	virtual void xfer( Xfer *xfer );
	virtual void loadPostProcess( void );
private:
	char m_unrecovered04[ 0x1C - 0x04 ];
};

class BaseHeightMapRenderObjClass
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
private:
	char m_unrecovered04[ 0x18 - 0x04 ];
	BaseHeightMapSnapshotRecord m_bfmeRecords[ ( 0x36C8 - 0x18 ) / 0x1C ];		///< 0x18
	Int m_bfmeRecordCount;																										///< 0x36C8
	char m_unrecovered36CC[ 0x36D0 - 0x36CC ];
	Int m_bfmeInt36D0;																												///< 0x36D0
	char m_unrecovered36D4[ 0x3788 - 0x36D4 ];
	Snapshot *m_treeBuffer;																										///< 0x3788
	Snapshot *m_propBuffer;																										///< 0x378C
	Snapshot *m_bfmeBuffer3790;																								///< 0x3790
	char m_unrecovered3794[ 0x3798 - 0x3794 ];
	Snapshot *m_bfmeBuffer3798;																								///< 0x3798
};

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version
	* 2: fourth buffer snapshot
	* 3: oldest version still accepted
	* 4: snapshot records and +0x36D0 */
// ------------------------------------------------------------------------------------------------
void BaseHeightMapRenderObjClass::xfer( Xfer *xfer )
{
	if( xfer->IsLightCRC() )
		return;

	// version
	Xfer::Version version( 1, 4 );
	*xfer == version;
	if( version.m_minimum < 3 )
		throw XferException::VERSION_TOO_OLD;

	*xfer == *m_treeBuffer;
	*xfer == *m_propBuffer;
	*xfer == *m_bfmeBuffer3790;

	if( version.m_minimum >= 2 )
		*xfer == *m_bfmeBuffer3798;

	if( version.m_minimum >= 4 )
	{
		*xfer == m_bfmeRecordCount;
		for( Int i = 0; i < m_bfmeRecordCount; ++i )
			*xfer == m_bfmeRecords[ i ];
		*xfer == m_bfmeInt36D0;
	}

}  // end xfer
