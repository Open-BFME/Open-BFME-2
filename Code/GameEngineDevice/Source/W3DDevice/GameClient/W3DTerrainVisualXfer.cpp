// cl: /Ireference/shims/moduledata /O1 /G7 /DNDEBUG /MD /EHsc
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


// W3DTerrainVisual::xfer, ported from Zero Hour's GameEngineDevice/Source/
// W3DDevice/GameClient/W3DTerrainVisual.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference). It is slot 3 of the vftable whose
// name getter returns "W3DTerrainVisual".
//
// BFME 2 order: the TerrainVisual base first. That base is ZH's version-only
// xfer, the 12-byte body 0x00306A9B (rowed as Rva00306A9BDoXfer). Then come
// the light-CRC gate and Version1, with no further version checks. ZH's
// water-grid flag check is kept. BFME 2 checks the presence of the logic
// height map the same way; both mismatches share one XferException tag 5.
// The height data is 16 bits per cell (x * y * 2 bytes). On load, the
// terrain render object's slot 137 (+0x224, ZH's staticLightingChanged) is
// called with 1. The terrain render object is xferred through its Snapshot
// base at +0xC8, null-checked as a pointer conversion.

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
typedef unsigned char UnsignedByte;

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException(void);

	char *text;
	int tagValue;
};

class WorldHeightMap
{
public:
	Int getXExtent( void ) { return m_width; }
	Int getYExtent( void ) { return m_height; }
	UnsignedByte *getDataPtr( void ) { return m_data; }
private:
	char m_unrecovered00[ 0x08 ];
	Int m_width;																															///< 0x08
	Int m_height;																															///< 0x0C
	char m_unrecovered10[ 0x24 - 0x10 ];
	UnsignedByte *m_data;																											///< 0x24
};

// The render-object half of BaseHeightMapRenderObjClass (0xC8 bytes).
class BaseHeightMapRenderObjBase
{
public:
	virtual void v000();
	virtual void v001();
	virtual void v002();
	virtual void v003();
	virtual void v004();
	virtual void v005();
	virtual void v006();
	virtual void v007();
	virtual void v008();
	virtual void v009();
	virtual void v010();
	virtual void v011();
	virtual void v012();
	virtual void v013();
	virtual void v014();
	virtual void v015();
	virtual void v016();
	virtual void v017();
	virtual void v018();
	virtual void v019();
	virtual void v020();
	virtual void v021();
	virtual void v022();
	virtual void v023();
	virtual void v024();
	virtual void v025();
	virtual void v026();
	virtual void v027();
	virtual void v028();
	virtual void v029();
	virtual void v030();
	virtual void v031();
	virtual void v032();
	virtual void v033();
	virtual void v034();
	virtual void v035();
	virtual void v036();
	virtual void v037();
	virtual void v038();
	virtual void v039();
	virtual void v040();
	virtual void v041();
	virtual void v042();
	virtual void v043();
	virtual void v044();
	virtual void v045();
	virtual void v046();
	virtual void v047();
	virtual void v048();
	virtual void v049();
	virtual void v050();
	virtual void v051();
	virtual void v052();
	virtual void v053();
	virtual void v054();
	virtual void v055();
	virtual void v056();
	virtual void v057();
	virtual void v058();
	virtual void v059();
	virtual void v060();
	virtual void v061();
	virtual void v062();
	virtual void v063();
	virtual void v064();
	virtual void v065();
	virtual void v066();
	virtual void v067();
	virtual void v068();
	virtual void v069();
	virtual void v070();
	virtual void v071();
	virtual void v072();
	virtual void v073();
	virtual void v074();
	virtual void v075();
	virtual void v076();
	virtual void v077();
	virtual void v078();
	virtual void v079();
	virtual void v080();
	virtual void v081();
	virtual void v082();
	virtual void v083();
	virtual void v084();
	virtual void v085();
	virtual void v086();
	virtual void v087();
	virtual void v088();
	virtual void v089();
	virtual void v090();
	virtual void v091();
	virtual void v092();
	virtual void v093();
	virtual void v094();
	virtual void v095();
	virtual void v096();
	virtual void v097();
	virtual void v098();
	virtual void v099();
	virtual void v100();
	virtual void v101();
	virtual void v102();
	virtual void v103();
	virtual void v104();
	virtual void v105();
	virtual void v106();
	virtual void v107();
	virtual void v108();
	virtual void v109();
	virtual void v110();
	virtual void v111();
	virtual void v112();
	virtual void v113();
	virtual void v114();
	virtual void v115();
	virtual void v116();
	virtual void v117();
	virtual void v118();
	virtual void v119();
	virtual void v120();
	virtual void v121();
	virtual void v122();
	virtual void v123();
	virtual void v124();
	virtual void v125();
	virtual void v126();
	virtual void v127();
	virtual void v128();
	virtual void v129();
	virtual void v130();
	virtual void v131();
	virtual void v132();
	virtual void v133();
	virtual void v134();
	virtual void v135();
	virtual void v136();
	virtual void staticLightingChanged( Bool flag );													///< slot 137
private:
	char m_unrecovered04[ 0xC8 - 0x04 ];
};

class BaseHeightMapRenderObjClass : public BaseHeightMapRenderObjBase, public Snapshot
{
protected:
	virtual void crc( Xfer *xfer );
	virtual void xfer( Xfer *xfer );
	virtual void loadPostProcess( void );
};

class TerrainVisual
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
private:
	char m_unrecovered04[ 0x14 - 0x04 ];
};

class W3DTerrainVisual : public TerrainVisual
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	BaseHeightMapRenderObjClass *m_terrainRenderObject;												///< 0x14
	Snapshot *m_waterRenderObject;																						///< 0x18
	WorldHeightMap *m_logicHeightMap;																					///< 0x1C
	Bool m_isWaterGridRenderingEnabled;																				///< 0x20
};

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void W3DTerrainVisual::xfer( Xfer *xfer )
{

	// extend base class
	TerrainVisual::xfer( xfer );

	if( xfer->IsLightCRC() )
		return;

	// version
	xfer->Version1();

	// flag for whether or not the water grid is enabled
	Bool gridEnabled = m_isWaterGridRenderingEnabled;
	*xfer == gridEnabled;
	if( gridEnabled != m_isWaterGridRenderingEnabled )
		throw XferException( 5, 0 );

	// xfer grid data if enabled
	if( gridEnabled )
		*xfer == *m_waterRenderObject;

	// Write out the terrain height data.
	Bool hasHeightMap = m_logicHeightMap != 0;
	*xfer == hasHeightMap;
	if( hasHeightMap != ( m_logicHeightMap != 0 ) )
		throw XferException( 5, 0 );

	if( hasHeightMap )
	{
		UnsignedByte *data = m_logicHeightMap->getDataPtr();
		Int len = m_logicHeightMap->getXExtent()*m_logicHeightMap->getYExtent()*2;
		Int xferLen = len;
		*xfer == xferLen;
		if (len>xferLen) {
			len = xferLen;
		}
		xfer->XferRawBytes( data, len );
		if( xfer->IsLoading() )
		{
			// Update the display height map.
			m_terrainRenderObject->staticLightingChanged( true );
		}
	}

	Snapshot *terrainSnapshot = m_terrainRenderObject;
	*xfer == *terrainSnapshot;

}  // end xfer

// Retail 0x00072988..0x000729CC, RET8; called by 0x00073FFB.
// The two-byte grid cell supplies its low four bits, scaled by the retail
// 17.0f literal at 0x00BC653C. Only observed fields are modeled; the original
// class and method names remain unresolved. This terrain unit already uses
// the verified x87 /O1 /G7 configuration required by the native conversion.
struct Rva00072988Cell
{
	unsigned short level : 4;
	unsigned short rest : 12;
};

class Rva00072988
{
public:
	unsigned char rva00072988(int x, int y);
private:
	int width;
	int height;
	unsigned char pad[16];
	Rva00072988Cell *data;
};

unsigned char Rva00072988::rva00072988(int x, int y)
{
	if (!data)
		return 0;
	if (x >= width || y >= height)
		return 0;
	int value = y * width + x;
	value = data[value].level;
	float scaled = (float)value;
	scaled *= 17.0f;
	return (unsigned char)(int)scaled;
}
