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


// BattlePlanUpdate::xfer, ported from Zero Hour's GameEngine/Source/GameLogic/
// Object/Update/BattlePlanUpdate.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference). It is slot 3 of the vftable whose
// name getter returns "BattlePlanUpdate".
//
// BFME 2 order: the UpdateModule base (0x0044DF9F) first, then the light-CRC
// gate and Version1, then ZH's fields. The two kind-of masks go through the
// 7-dword BitFlags<218> xfer 0x002AC06A. KindOfMaskType is the donor's
// typedef, with the target's 218-bit extent proven by the provider. After
// ZH's vision object id, BFME 2 hands Xfer and the +0x84 member to TheAudio's
// slot 88 (+0x160).

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

enum BattlePlanStatus
{
	PLANSTATUS_NONE
};

enum TransitionStatus
{
	TRANSITIONSTATUS_IDLE
};

template <int NUMBITS>
class BitFlags
{
public:
	void xfer( Xfer *xfer );
private:
	UnsignedInt m_bits[ (NUMBITS + 31) / 32 ];
};
typedef BitFlags<218> KindOfMaskType;

struct BattlePlanBonuses
{
	Real m_armorScalar;																												///< 0x00
	Int m_bombardment;																												///< 0x04
	Int m_searchAndDestroy;																										///< 0x08
	Int m_holdTheLine;																												///< 0x0C
	Real m_sightRangeScalar;																									///< 0x10
	KindOfMaskType m_validKindOf;																							///< 0x14
	KindOfMaskType m_invalidKindOf;																						///< 0x30
};

class AudioManager
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
	virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
	virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
	virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55();
	virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
	virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63();
	virtual void v64(); virtual void v65(); virtual void v66(); virtual void v67();
	virtual void v68(); virtual void v69(); virtual void v70(); virtual void v71();
	virtual void v72(); virtual void v73(); virtual void v74(); virtual void v75();
	virtual void v76(); virtual void v77(); virtual void v78(); virtual void v79();
	virtual void v80(); virtual void v81(); virtual void v82(); virtual void v83();
	virtual void v84(); virtual void v85(); virtual void v86(); virtual void v87();
	virtual void slot88( Xfer *xfer, void *value );														///< +0x160
};
extern AudioManager *TheAudio;

class UpdateModule
{
public:
	virtual ~UpdateModule();
	void xfer( Xfer *xfer );
private:
	char m_unrecovered04[ 0x24 - 0x04 ];
};

class BattlePlanUpdate : public UpdateModule
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	BattlePlanStatus m_currentPlan;																						///< 0x24
	BattlePlanStatus m_desiredPlan;																						///< 0x28
	BattlePlanStatus m_planAffectingArmy;																			///< 0x2C
	TransitionStatus m_status;																								///< 0x30
	UnsignedInt m_nextReadyFrame;																							///< 0x34
	void *m_specialPowerModule;																								///< 0x38
	Bool m_invalidSettings;																										///< 0x3C
	Bool m_centeringTurret;																										///< 0x3D
	BattlePlanBonuses *m_bonuses;																							///< 0x40
	char m_unrecovered44[ 0x84 - 0x44 ];
	char m_bfmeAudio84[ 0x88 - 0x84 ];																				///< 0x84
	ObjectID m_visionObjectID;																								///< 0x88
};

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void BattlePlanUpdate::xfer( Xfer *xfer )
{

	// extend base class
	UpdateModule::xfer( xfer );

	if( xfer->IsLightCRC() )
		return;

	// version
	xfer->Version1();

	// current plan
	xfer->XferRawBytes( &m_currentPlan, sizeof( BattlePlanStatus ) );

	// desired plan
	xfer->XferRawBytes( &m_desiredPlan, sizeof( BattlePlanStatus ) );

	// plan affecting army
	xfer->XferRawBytes( &m_planAffectingArmy, sizeof( BattlePlanStatus ) );

	// status
	xfer->XferRawBytes( &m_status, sizeof( TransitionStatus ) );

	// next ready frame
	*xfer == m_nextReadyFrame;

	// invalid settings
	*xfer == m_invalidSettings;

	// centering turret
	*xfer == m_centeringTurret;

	// bonuses
	*xfer == m_bonuses->m_armorScalar;
	*xfer == m_bonuses->m_bombardment;
	*xfer == m_bonuses->m_searchAndDestroy;
	*xfer == m_bonuses->m_holdTheLine;
	*xfer == m_bonuses->m_sightRangeScalar;
	m_bonuses->m_validKindOf.xfer( xfer );
	m_bonuses->m_invalidKindOf.xfer( xfer );

	// vision object data
	XferObjectID( xfer, &m_visionObjectID );

	TheAudio->slot88( xfer, m_bfmeAudio84 );

}  // end xfer
