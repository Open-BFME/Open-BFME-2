// ?newBridge@TerrainRoadCollection@@QAEPAVTerrainRoadType@@VAsciiString@@@Z
// partial score=0.89 date=2026-10-08
// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /MD /EHsc
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

// FILE: TerrainRoads.cpp /////////////////////////////////////////////////////////////////////////
// Author: Colin Day, December 2001
// Desc:   Terrain road descriptions
//
// Ported from Zero Hour's GameEngine/Source/GameClient/Terrain/TerrainRoads.cpp
// (GeneralsMD tree vendored under reference/open-bfme-1/inputs/reference).
// BFME 2 keeps the bridge transition tables but moves the friend_set*String
// accessors out of line, and the INI parsers throw an INIException carrying
// Zero Hour's DEBUG_CRASH text instead of INI_INVALID_DATA.
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
#define TRUE true
#define FALSE false

enum BodyDamageType
{
	BODY_PRISTINE,
	BODY_DAMAGED,
	BODY_REALLYDAMAGED,
	BODY_RUBBLE,

	BODYDAMAGETYPE_COUNT
};

// "PRISTINE", "DAMAGED", "REALLYDAMAGED", "RUBBLE", NULL (retail 0x00DBCF30)
extern const char *TheBodyDamageTypeNames[];

enum { MAX_BRIDGE_BODY_FX = 3 };

class INI
{
public:
	const char *getNextSubToken(const char *expected);
	Int scanIndexList(const char *token, const char *const *nameList);
	Int scanInt(const char *token);
};

class INIException
{
public:
	char *mFailureMessage;
	int m_argCount;
	INIException(int argCount, const char *errorMessage, ...);
	INIException(const INIException &that);
	~INIException();
};

// Trial ABI: native sound slots are 4-byte reference records, not donor strings.
struct OpaqueRefElement4 {
    struct OpaqueRefCounted *referent;
    ~OpaqueRefElement4();
    OpaqueRefElement4 &operator=(const OpaqueRefElement4 &);
};

// BFME 2 layout: the road allocation/INI paths establish name +4, bridge +8,
// ID +0xC, next +0x10, widths +0x14/+0x18 and texture +0x38. Other prefix
// fields remain opaque. Existing transition-table accessor offsets are retained.
class TerrainRoadType
{
public:
	TerrainRoadType();
	virtual ~TerrainRoadType();
	void friend_setName(AsciiString name);
	void friend_setTexture(AsciiString texture);
    AsciiString getBridgeModel();
    AsciiString getBridgeModelNameDamaged();
    AsciiString getBridgeModelNameReallyDamaged();
    AsciiString getBridgeModelNameBroken();
    AsciiString getTextureDamaged();
    AsciiString getTextureReallyDamaged();
    AsciiString getTextureBroken();
    void friend_setBridgeModelName(AsciiString);
    void friend_setBridgeModelNameDamaged(AsciiString);
    void friend_setBridgeModelNameReallyDamaged(AsciiString);
    void friend_setBridgeModelNameBroken(AsciiString);
    void friend_setTextureDamaged(AsciiString);
    void friend_setTextureReallyDamaged(AsciiString);
    void friend_setTextureBroken(AsciiString);
    float getBridgeScale() const { return m_bridgeScale; }
    void friend_setBridgeScale(float scale) { m_bridgeScale = scale; }
    float getTransitionEffectsHeight() const { return m_transitionEffectsHeight; }
    Int getNumFXPerType() const { return m_numFXPerType; }
    void friend_setTransitionEffectsHeight(float height) { m_transitionEffectsHeight = height; }
    void friend_setNumFXPerType(Int n) { m_numFXPerType = n; }
    const OpaqueRefElement4 &getDamageToSoundString(BodyDamageType state) const { return m_damageToSoundString[state]; }
    const OpaqueRefElement4 &getRepairedToSoundString(BodyDamageType state) const { return m_repairedToSoundString[state]; }
    void friend_setDamageToSoundString(BodyDamageType, const OpaqueRefElement4 &);
    void friend_setRepairedToSoundString(BodyDamageType, const OpaqueRefElement4 &);
    void friend_setID(unsigned int id) { m_id = id; }
    void friend_setBridge(Bool bridge) { m_isBridge = bridge; }
    void friend_setNext(TerrainRoadType *next) { m_next = next; }
    void friend_setRoadWidth(float width) { m_roadWidth = width; }
    void friend_setRoadWidthInTexture(float width) { m_roadWidthInTexture = width; }
    const AsciiString &getTexture() const { return m_texture; }
    float getRoadWidth() const { return m_roadWidth; }
    float getRoadWidthInTexture() const { return m_roadWidthInTexture; }
	static void parseTransitionToOCL( INI *ini, void *instance, void *store, const void *userData );
	static void parseTransitionToFX( INI *ini, void *instance, void *store, const void *userData );

	AsciiString getDamageToOCLString( BodyDamageType state, Int index );

	void friend_setDamageToOCLString( BodyDamageType state, Int index, AsciiString str );
	void friend_setDamageToFXString( BodyDamageType state, Int index, AsciiString str );
	void friend_setRepairedToOCLString( BodyDamageType state, Int index, AsciiString str );
	void friend_setRepairedToFXString( BodyDamageType state, Int index, AsciiString str );

protected:
	AsciiString m_name;                         ///< 0x04
	Bool m_isBridge;                            ///< 0x08
	unsigned int m_id;                          ///< 0x0C
	TerrainRoadType *m_next;                     ///< 0x10
	float m_roadWidth;                           ///< 0x14
	float m_roadWidthInTexture;                  ///< 0x18
	float m_bridgeScale;
    AsciiString m_scaffoldObjectName;
    AsciiString m_scaffoldSupportObjectName;
    float m_radarColor[3];
    AsciiString m_bridgeModelName;
	AsciiString m_texture;                      ///< 0x38
	AsciiString m_bridgeModelNameDamaged;
    AsciiString m_textureDamaged;
    AsciiString m_bridgeModelNameReallyDamaged;
    AsciiString m_textureReallyDamaged;
    AsciiString m_bridgeModelNameBroken;
    AsciiString m_textureBroken;
    AsciiString m_towerObjectName[4];
	OpaqueRefElement4 m_damageToSoundString[ BODYDAMAGETYPE_COUNT ];								///< 0x64
	AsciiString m_damageToOCLString[ BODYDAMAGETYPE_COUNT ][ MAX_BRIDGE_BODY_FX ];		///< 0x74
	AsciiString m_damageToFXString[ BODYDAMAGETYPE_COUNT ][ MAX_BRIDGE_BODY_FX ];		///< 0xA4
	OpaqueRefElement4 m_repairedToSoundString[ BODYDAMAGETYPE_COUNT ];							///< 0xD4
	AsciiString m_repairedToOCLString[ BODYDAMAGETYPE_COUNT ][ MAX_BRIDGE_BODY_FX ];	///< 0xE4
	AsciiString m_repairedToFXString[ BODYDAMAGETYPE_COUNT ][ MAX_BRIDGE_BODY_FX ];	///< 0x114
	float m_transitionEffectsHeight;            ///< 0x144
	Int m_numFXPerType;                         ///< 0x148
};

// Native newRoad/newBridge calls prove this by-value name setter at 0x002DAD19.
// ZH calls the same operation friend_setName. The complete 52-byte body has
// its own EH graph, so it replaces the old gen-alias claim rather than folding.
void TerrainRoadType::friend_setName(AsciiString name)
{
    AsciiString &slot = m_name;
    slot = name;
}

// Native calls at 0x002DB60D and 0x002DB6E5 set the texture at +0x38.
// Keep the existing 52-byte body while reconciling its real owner and home unit.
void TerrainRoadType::friend_setTexture(AsciiString texture)
{
    AsciiString &slot = m_texture;
    slot = texture;
}

AsciiString TerrainRoadType::getDamageToOCLString( BodyDamageType state, Int index )
{
	return m_damageToOCLString[ state ][ index ];
}

void TerrainRoadType::friend_setDamageToOCLString( BodyDamageType state, Int index, AsciiString str )
{
	m_damageToOCLString[ state ][ index ] = str;
}

void TerrainRoadType::friend_setDamageToFXString( BodyDamageType state, Int index, AsciiString str )
{
	m_damageToFXString[ state ][ index ] = str;
}

void TerrainRoadType::friend_setRepairedToOCLString( BodyDamageType state, Int index, AsciiString str )
{
	m_repairedToOCLString[ state ][ index ] = str;
}

void TerrainRoadType::friend_setRepairedToFXString( BodyDamageType state, Int index, AsciiString str )
{
	m_repairedToFXString[ state ][ index ] = str;
}

// ------------------------------------------------------------------------------------------------
/** In the form of
	* Label = Transition:<Damage|Repair> ToState:<BODYTYPE> EffectNum:<INT> OCL:<OCL NAME> */
// ------------------------------------------------------------------------------------------------
/*static*/ void TerrainRoadType::parseTransitionToOCL( INI *ini,
																											 void *instance,
																											 void *store,
																											 const void *userData )
{
	const char *token;
	TerrainRoadType *theInstance = (TerrainRoadType *)instance;

	// which transition is this
	Bool damageTransition;
	token = ini->getNextSubToken( "Transition" );
	if( _strcmpi( token, "Damage" ) == 0 )
		damageTransition = TRUE;
	else if( _strcmpi( token, "Repair" ) == 0 )
		damageTransition = FALSE;
	else
	{

		throw INIException( 3, "Expected Damage/Repair transition keyword\n" );

	}  // end else

	// get body damage state
	token = ini->getNextSubToken( "ToState" );
	BodyDamageType state = (BodyDamageType)ini->scanIndexList( token, TheBodyDamageTypeNames );

	// get effect num
	token = ini->getNextSubToken( "EffectNum" );
	Int effectNum = ini->scanInt( token );

	// make effect num zero based
	--effectNum;

	// sanity check effect num
	if( effectNum < 0 || effectNum >= MAX_BRIDGE_BODY_FX )
	{

		throw INIException( 3, "Effect number max on bridge transitions is '%d'\n", MAX_BRIDGE_BODY_FX );

	}  // end if

	// read the string
	token = ini->getNextSubToken( "OCL" );
	if( damageTransition )
		theInstance->friend_setDamageToOCLString( state, effectNum, token );
	else
		theInstance->friend_setRepairedToOCLString( state, effectNum, token );

}  // end parseTransitionToOCL

// ------------------------------------------------------------------------------------------------
/** In the form of
	* Label = Transition:<Damage|Repair> ToState:<BODYTYPE> EffectNum:<INT> FX:<FXLIST NAME> */
// ------------------------------------------------------------------------------------------------
/*static*/ void TerrainRoadType::parseTransitionToFX( INI *ini,
																											void *instance,
																											void *store,
																											const void *userData )
{
	const char *token;
	TerrainRoadType *theInstance = (TerrainRoadType *)instance;

	// which transition is this
	Bool damageTransition;
	token = ini->getNextSubToken( "Transition" );
	if( _strcmpi( token, "Damage" ) == 0 )
		damageTransition = TRUE;
	else if( _strcmpi( token, "Repair" ) == 0 )
		damageTransition = FALSE;
	else
	{

		throw INIException( 3, "Expected Damage/Repair transition keyword\n" );

	}  // end else

	// get body damage state
	token = ini->getNextSubToken( "ToState" );
	BodyDamageType state = (BodyDamageType)ini->scanIndexList( token, TheBodyDamageTypeNames );

	// get effect num
	token = ini->getNextSubToken( "EffectNum" );
	Int effectNum = ini->scanInt( token );

	// make effect num zero based
	--effectNum;

	// sanity check effect num
	if( effectNum < 0 || effectNum >= MAX_BRIDGE_BODY_FX )
	{

		throw INIException( 3, "Effect number max on bridge transitions is '%d'\n", MAX_BRIDGE_BODY_FX );

	}  // end if

	// read the string
	token = ini->getNextSubToken( "FX" );
	if( damageTransition )
		theInstance->friend_setDamageToFXString( state, effectNum, token );
	else
		theInstance->friend_setRepairedToFXString( state, effectNum, token );

}  // end parseTransitionToFX

// TerrainRoadCollection: only the lookups are declared. findRoad (0x002DB496)
// and findBridge (0x002DB4DA) are the ledger's rows reached through their
// symbols.csv pins. findRoadOrBridge is the Zero Hour body verbatim, placed
// by compiling the Open-BFME-1 donor at /O1. The calls and adjacency agree
// with the pinned callees.
// Native collection list slots are +0x0C/+0x10; the subsystem prefix remains opaque.
class TerrainRoadCollection
{
    char m_subsystemPrefix[0x0C];
    TerrainRoadType *m_roadList;
    TerrainRoadType *m_bridgeList;
    static unsigned int m_idCounter;
public:
    TerrainRoadType *newRoad(AsciiString name);
    TerrainRoadType *newBridge(AsciiString name);
	TerrainRoadType *findRoad( AsciiString name );
	TerrainRoadType *findBridge( AsciiString name );
	TerrainRoadType *findRoadOrBridge( AsciiString name );
};

// Native 0x009FF088 is a zero-initialized 4-byte counter. The collection
// constructor resets it to one; newRoad and newBridge increment the same slot.
unsigned int TerrainRoadCollection::m_idCounter;

//-------------------------------------------------------------------------------------------------
/** Search the roads first, then the bridges */
//-------------------------------------------------------------------------------------------------
TerrainRoadType *TerrainRoadCollection::findRoadOrBridge( AsciiString name )
{
	TerrainRoadType *road = findRoad( name );

	if( road )
		return road;
	else
		return findBridge( name );

}  // end findRoadOrBridge

// ZH newRoad at BFME1 ba7ddda7e8. Target differences: ordinary global new
// allocates 0x14C (not the donor's pool macro); texture access returns a
// reference. Native code proves all fields copied and the complete list update.
typedef char TerrainRoadTypeSizeCheck[sizeof(TerrainRoadType) == 0x14C ? 1 : -1];
TerrainRoadType *TerrainRoadCollection::newRoad(AsciiString name)
{
    TerrainRoadType *road = new TerrainRoadType;
    road->friend_setName(name);
    road->friend_setID(m_idCounter++);
    road->friend_setBridge(FALSE);
    TerrainRoadType *defaultRoad = findRoad(AsciiString("DefaultRoad"));
    if (defaultRoad) {
        road->friend_setTexture(defaultRoad->getTexture());
        road->friend_setRoadWidth(defaultRoad->getRoadWidth());
        road->friend_setRoadWidthInTexture(defaultRoad->getRoadWidthInTexture());
    }
    road->friend_setNext(m_roadList);
    m_roadList = road;
    return road;
}

// Target-adapted source trial; donor helper names with new argument types
// are leads until their getter/setter providers are independently reconciled.
TerrainRoadType *TerrainRoadCollection::newBridge( AsciiString name )
{
	TerrainRoadType *bridge = new TerrainRoadType;

	// assign the name
	bridge->friend_setName( name );

	// assign unique id
	bridge->friend_setID( m_idCounter++ );

	// is a bridge
	bridge->friend_setBridge( TRUE );

	// set defaults from the default bridge
	TerrainRoadType *defaultBridge = findBridge( AsciiString( "DefaultBridge" ) );
	if( defaultBridge )
	{
		
		bridge->friend_setTexture( defaultBridge->getTexture() );
		bridge->friend_setBridgeScale( defaultBridge->getBridgeScale() );
		bridge->friend_setBridgeModelName( defaultBridge->getBridgeModel() );
		bridge->friend_setBridgeModelNameDamaged( defaultBridge->getBridgeModelNameDamaged() );
		bridge->friend_setBridgeModelNameReallyDamaged( defaultBridge->getBridgeModelNameReallyDamaged() );
		bridge->friend_setBridgeModelNameBroken( defaultBridge->getBridgeModelNameBroken() );
		bridge->friend_setTextureDamaged( defaultBridge->getTextureDamaged() );
		bridge->friend_setTextureReallyDamaged( defaultBridge->getTextureReallyDamaged() );
		bridge->friend_setTextureBroken( defaultBridge->getTextureBroken() );

		bridge->friend_setTransitionEffectsHeight( defaultBridge->getTransitionEffectsHeight() );
		bridge->friend_setNumFXPerType( defaultBridge->getNumFXPerType() );
		for( Int state = BODY_PRISTINE; state < BODYDAMAGETYPE_COUNT; state++ )
		{

			bridge->friend_setDamageToSoundString( (BodyDamageType)state, defaultBridge->getDamageToSoundString( (BodyDamageType)state ) );
			bridge->friend_setRepairedToSoundString( (BodyDamageType)state, defaultBridge->getRepairedToSoundString( (BodyDamageType)state ) );

			for( Int i = 0; i < MAX_BRIDGE_BODY_FX; i++ )
			{

				bridge->friend_setDamageToOCLString( (BodyDamageType)state, i, defaultBridge->getDamageToOCLString( (BodyDamageType)state, i ) );
				bridge->friend_setDamageToFXString( (BodyDamageType)state, i, defaultBridge->getDamageToOCLString( (BodyDamageType)state, i ) );
				bridge->friend_setRepairedToOCLString( (BodyDamageType)state, i, defaultBridge->getDamageToOCLString( (BodyDamageType)state, i ) );
				bridge->friend_setRepairedToFXString( (BodyDamageType)state, i, defaultBridge->getDamageToOCLString( (BodyDamageType)state, i ) );

			}  // end for i

		}  // end for

	}  // end if

	// link to list
	bridge->friend_setNext( m_bridgeList );
	m_bridgeList = bridge;

	// return the new bridge
	return bridge;

}  // end newBridge
