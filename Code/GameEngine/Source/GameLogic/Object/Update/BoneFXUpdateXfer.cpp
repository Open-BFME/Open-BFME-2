// cl: /G7 /MD /O1 /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /EHsc
// stlport
// cl: /O1 /DNDEBUG /MD /GX
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

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


// BoneFXUpdate::xfer, ported from Zero Hour's GameEngine/Source/GameLogic/
// Object/Update/BoneFXUpdate.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference). It is slot 3 of the vftable whose
// name getter returns "BoneFXUpdate".
//
// BFME 2 order: the UpdateModule base (0x0044DF9F) first, then the light-CRC
// gate and Version1, then ZH's body unchanged (four body-damage states by
// eight bones). Particle system ids go through XferParticleSystemID
// (0x0030600A, an Int helper, hence the cast) and the out-of-line, ICF-shared
// 4-byte vector push_back 0x002E01C6. ZH's throw SC_INVALID_DATA becomes
// XferException tag 5.

#include <vector>

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

enum ParticleSystemID
{
	INVALID_PARTICLE_SYSTEM_ID = 0
};

void XferParticleSystemID( Xfer *xfer, Int *value );

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException(void);

	char *text;
	int tagValue;
};

enum BodyDamageType
{
	BODY_PRISTINE,
	BODY_DAMAGED,
	BODY_REALLYDAMAGED,
	BODY_RUBBLE,

	BODYDAMAGETYPE_COUNT
};

enum { BONE_FX_MAX_BONES = 8 };

class UpdateModule
{
public:
	virtual ~UpdateModule();
	void xfer( Xfer *xfer );
private:
	char m_unrecovered04[ 0x20 - 0x04 ];
};

class BoneFXUpdate : public UpdateModule
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	_STL::vector<ParticleSystemID> m_particleSystemIDs;												///< 0x20
	Int m_nextFXFrame[ BODYDAMAGETYPE_COUNT ][ BONE_FX_MAX_BONES ];						///< 0x2C
	Int m_nextOCLFrame[ BODYDAMAGETYPE_COUNT ][ BONE_FX_MAX_BONES ];					///< 0xAC
	Int m_nextParticleSystemFrame[ BODYDAMAGETYPE_COUNT ][ BONE_FX_MAX_BONES ];	///< 0x12C
	Coord3DBase m_FXBonePositions[ BODYDAMAGETYPE_COUNT ][ BONE_FX_MAX_BONES ];	///< 0x1AC
	Coord3DBase m_OCLBonePositions[ BODYDAMAGETYPE_COUNT ][ BONE_FX_MAX_BONES ];	///< 0x32C
	Coord3DBase m_PSBonePositions[ BODYDAMAGETYPE_COUNT ][ BONE_FX_MAX_BONES ];	///< 0x4AC
	BodyDamageType m_curBodyState;																						///< 0x62C
	Bool m_bonesResolved[ BODYDAMAGETYPE_COUNT ];															///< 0x630
	Bool m_active;																														///< 0x634
};

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void BoneFXUpdate::xfer( Xfer *xfer )
{

	// extend base class
	UpdateModule::xfer( xfer );

	if( xfer->IsLightCRC() )
		return;

	// version
	xfer->Version1();

	// particle system vector count and data
	UnsignedShort particleSystemCount = m_particleSystemIDs.size();
	*xfer == particleSystemCount;
	ParticleSystemID systemID;
	if( xfer->IsStoring() )
	{
		_STL::vector<ParticleSystemID>::const_iterator it;

		for( it = m_particleSystemIDs.begin(); it != m_particleSystemIDs.end(); ++it )
		{

			systemID = *it;
			XferParticleSystemID( xfer, (Int *)&systemID );

		}  // end for

	}  // end if, save
	else
	{

		// the list should be emtpy right now
		if( m_particleSystemIDs.empty() == false )
			throw XferException( 5, 0 );

		// read all data
		for( UnsignedShort i = 0; i < particleSystemCount; ++i )
		{

			// read id
			XferParticleSystemID( xfer, (Int *)&systemID );

			// put at end of vector
			m_particleSystemIDs.push_back( systemID );

		}  // end for, i

	}  // end else

	// next fx frame
	xfer->XferRawBytes( m_nextFXFrame, sizeof( Int ) * BODYDAMAGETYPE_COUNT * BONE_FX_MAX_BONES );

	// next OCL farme
	xfer->XferRawBytes( m_nextOCLFrame, sizeof( Int ) * BODYDAMAGETYPE_COUNT * BONE_FX_MAX_BONES );

	// next particle system frame
	xfer->XferRawBytes( m_nextParticleSystemFrame, sizeof( Int ) * BODYDAMAGETYPE_COUNT * BONE_FX_MAX_BONES );

	// fx bone positions
	xfer->XferRawBytes( m_FXBonePositions, sizeof( Coord3DBase ) * BODYDAMAGETYPE_COUNT * BONE_FX_MAX_BONES );

	// ocl bone positions
	xfer->XferRawBytes( m_OCLBonePositions, sizeof( Coord3DBase ) * BODYDAMAGETYPE_COUNT * BONE_FX_MAX_BONES );

	// particle system bone positions
	xfer->XferRawBytes( m_PSBonePositions, sizeof( Coord3DBase ) * BODYDAMAGETYPE_COUNT * BONE_FX_MAX_BONES );

	// current body state
	xfer->XferRawBytes( &m_curBodyState, sizeof( BodyDamageType ) );

	// bones resolved
	xfer->XferRawBytes( m_bonesResolved, sizeof( Bool ) * BODYDAMAGETYPE_COUNT );

	// active
	*xfer == m_active;

}  // end xfer
