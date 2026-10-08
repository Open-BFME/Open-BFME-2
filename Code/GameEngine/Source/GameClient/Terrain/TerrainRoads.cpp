// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
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
	char m_unrecovered1C[0x1C];
	AsciiString m_texture;                      ///< 0x38
	char m_unrecovered3C[0x28];
	AsciiString m_damageToSoundString[ BODYDAMAGETYPE_COUNT ];								///< 0x64
	AsciiString m_damageToOCLString[ BODYDAMAGETYPE_COUNT ][ MAX_BRIDGE_BODY_FX ];		///< 0x74
	AsciiString m_damageToFXString[ BODYDAMAGETYPE_COUNT ][ MAX_BRIDGE_BODY_FX ];		///< 0xA4
	AsciiString m_repairedToSoundString[ BODYDAMAGETYPE_COUNT ];							///< 0xD4
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
class TerrainRoadCollection
{
public:
	TerrainRoadType *findRoad( AsciiString name );
	TerrainRoadType *findBridge( AsciiString name );
	TerrainRoadType *findRoadOrBridge( AsciiString name );
};

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
