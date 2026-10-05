// cl: /O1 /DNDEBUG /MD
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


// BridgeBehavior::xfer, ported from Zero Hour's GameEngine/Source/GameLogic/
// Object/Behavior/BridgeBehavior.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference). It is slot 3 of the vftable whose
// name getter returns "BridgeBehavior".
//
// BFME 2 order: the UpdateModule base (0x0044DF9F) first, then the light-CRC
// gate and Version1, then ZH's body. The object is read once and serves both
// load-time bridge fix-ups (TerrainLogic slot 0xA4, findBridgeAt). Bridge
// keeps the bridge object id at +0x60 and the tower ids at +0x64. The scaffold
// load loop counts unsigned, and BFME 2 adds a trailing flag at +0xFC.
// The scaffold id list's push_back is the out-of-line ICF-shared 4-byte list
// insert 0x002A1B6F.

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
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID( Xfer *xfer, ObjectID *value );

enum BridgeTowerType
{
	BRIDGE_MAX_TOWERS = 4
};

class Object
{
public:
	const Coord3DBase *getPosition( void ) const { return &m_pos; }
	ObjectID getID( void ) const { return m_id; }
private:
	char m_unrecovered00[ 0x38 ];
	Coord3DBase m_pos;																												///< 0x38
	char m_unrecovered44[ 0x74 - 0x44 ];
	ObjectID m_id;																														///< 0x74
};

class Bridge
{
public:
	void setBridgeObjectID( ObjectID id ) { m_bridgeObjectID = id; }
	void setTowerObjectID( ObjectID id, BridgeTowerType which ) { m_towerObjectID[ which ] = id; }
private:
	char m_unrecovered00[ 0x60 ];
	ObjectID m_bridgeObjectID;																								///< 0x60
	ObjectID m_towerObjectID[ BRIDGE_MAX_TOWERS ];														///< 0x64
};

class TerrainLogic
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
	virtual void v40();
	virtual Bridge *findBridgeAt( const Coord3DBase *loc ) const;							///< slot 41
};
extern TerrainLogic *TheTerrainLogic;

struct BridgeBehaviorObjectIDNode
{
	BridgeBehaviorObjectIDNode *m_next;
	BridgeBehaviorObjectIDNode *m_previous;
	ObjectID m_value;
};

class BridgeBehaviorObjectIDList
{
public:
	UnsignedInt size( void ) const
	{
		UnsignedInt n = 0;
		for( BridgeBehaviorObjectIDNode *p = m_node->m_next; p != m_node; p = p->m_next )
			++n;
		return n;
	}
	void push_back( const ObjectID &value );
	BridgeBehaviorObjectIDNode *m_node;
};

class UpdateModule
{
public:
	virtual ~UpdateModule();
	void xfer( Xfer *xfer );
protected:
	Object *getObject( void ) const { return m_object; }
private:
	void *m_moduleData;																												///< 0x04
	Object *m_object;																													///< 0x08
	char m_unrecovered0C[ 0x24 - 0x0C ];
};

class BridgeBehaviorInterface
{
public:
	virtual void v00();
};

class BridgeBehavior : public UpdateModule, public BridgeBehaviorInterface
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	char m_unrecovered28[ 0x2C - 0x28 ];
	ObjectID m_towerID[ BRIDGE_MAX_TOWERS ];																	///< 0x2C
	char m_unrecovered3C[ 0xFC - 0x3C ];
	Bool m_bfmeFlagFC;																												///< 0xFC
	Bool m_scaffoldPresent;																										///< 0xFD
	BridgeBehaviorObjectIDList m_scaffoldObjectIDList;												///< 0x100
	UnsignedInt m_deathFrame;																									///< 0x104
};

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void BridgeBehavior::xfer( Xfer *xfer )
{

	// extend base class
	UpdateModule::xfer( xfer );

	if( xfer->IsLightCRC() )
		return;

	Object *us = getObject();

	// version
	xfer->Version1();

	// set us as the bridge object in the bridge info
	if( xfer->IsLoading() )
	{
		Bridge *bridge = TheTerrainLogic->findBridgeAt( us->getPosition() );

		// set new object ID in bridge info to us
		bridge->setBridgeObjectID( us->getID() );

	}  // end if

	// xfer the tower object ids
	for( Int i = 0; i < BRIDGE_MAX_TOWERS; ++i )
		XferObjectID( xfer, &m_towerID[ i ] );

	// set the tower object ids in the bridge info
	if( xfer->IsLoading() )
	{
		Bridge *bridge = TheTerrainLogic->findBridgeAt( us->getPosition() );

		for( Int i = 0; i < BRIDGE_MAX_TOWERS; ++i )
			bridge->setTowerObjectID( m_towerID[ i ], (BridgeTowerType)i );

	}  // end if

	// scaffold present flag
	*xfer == m_scaffoldPresent;

	// scaffold object id list
	UnsignedShort scaffoldObjectCount = 0;
	scaffoldObjectCount = m_scaffoldObjectIDList.size();
	*xfer == scaffoldObjectCount;
	ObjectID scaffoldObjectID;
	if( xfer->IsStoring() )
	{

		// write out all object IDs
		for( BridgeBehaviorObjectIDNode *it = m_scaffoldObjectIDList.m_node->m_next; it != m_scaffoldObjectIDList.m_node; it = it->m_next )
		{
			scaffoldObjectID = it->m_value;
			XferObjectID( xfer, &scaffoldObjectID );
		}  // end for

	}  // end if, save
	else
	{

		// read all object IDs
		for( UnsignedInt i = 0; i < scaffoldObjectCount; ++i )
		{
			XferObjectID( xfer, &scaffoldObjectID );
			m_scaffoldObjectIDList.push_back( scaffoldObjectID );
		}  // end for i

	}  // end load

	// death frame
	*xfer == m_deathFrame;

	*xfer == m_bfmeFlagFC;

}  // end xfer
