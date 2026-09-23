// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/asciistring_outofline /Ireference/shims/iniexception /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /O1

// BFME2 target evidence: registeredFieldParse row RVA 0x840B50 bytes
// d4 0a c4 00 53 81 85 00 00 00 00 00 14 00 00 00 (BridgeDieOCL name,
// callback VA 0x858153 / RVA 0x458153, field offset 0x14). Target callback
// extent is 170B through ret 0x4581FC; call 0x4581CF reaches shared parser
// 0x45679B and call 0x4581DE reaches the shared 26B list helper 0x457FD7.
// Both callbacks pass a 12B pointer/delay/AsciiString value.
// BFME1 donor provenance: BridgeBehavior.cpp::parseOCL semantics; compiler and
// helper view follow `reference/open-bfme-1/Code/GameEngine/Source/GameLogic/Object/Behavior/BridgeBehaviorParseFX.cpp`.
// Donor parser RVA/ILT addresses belong to BFME1 only.
// Donor EA/GPL notice follows.
/*
** Command & Conquer Generals Zero Hour(tm)
** Copyright 2025 Electronic Arts Inc.
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

// stlport
#include "Common/AsciiString.h"
#include "Common/INIException.h"

extern "C" __declspec( dllimport ) int __cdecl _strcmpi( const char *, const char * );

typedef unsigned int UnsignedInt;

class INI
{
    char unknown[0x420];
    const char *sepsColon;
public:
	const char *getNextToken( const char *seps );
	const char *getNextTokenOrNull( const char *seps );
	__forceinline const char *getSepsColon() const
	{
		return sepsColon;
	}
	AsciiString getNextAsciiString();
	static void parseDurationUnsignedInt( INI *, void *, void *, const void * );
	static void parseObjectCreationList( INI *, void *, void *, const void * );
};

class ObjectCreationList;

struct TimeAndLocationInfo
{
	UnsignedInt delay;
	AsciiString boneName;
};

class BridgeBehaviorModuleData
{
public:
	static void parseOCL( INI *, void *, void *, const void * );
};

struct BridgeOCLInfo
{
    const ObjectCreationList *ocl;
    TimeAndLocationInfo timeAndLocationInfo;
};

#include <list>

namespace _STL
{
// BFME1 donor detail only: BridgeBehaviorParseFX.cpp records an out-of-line
// _Construct call through donor ILT 0x00007C84 and donor body RVA 0x001F32A0.
// BFME2 copy semantics are independently traced through 0x4570DD -> 0x456E70
// -> 0x000CF475 -> 0x000365F0; do not interpret the donor addresses as target RVAs.
template <> void _Construct<BridgeOCLInfo, BridgeOCLInfo>(BridgeOCLInfo *, const BridgeOCLInfo &);
}

struct BoneNameSlot
{
    AsciiString *destination;
    __forceinline BoneNameSlot( AsciiString *value ) : destination( value ) {}
    __forceinline void operator=( const AsciiString &value )
    {
        destination->operator=( value );
    }
};

// The body duplicates the separately matched 0x45679B parser because keeping
// it in this TU is required for the callback's retail inline/call scheduling.
static void parseTimeAndLocationInfo( INI *ini, void *instance, TimeAndLocationInfo *info )
{
    const char *token = ini->getNextToken( ini->getSepsColon() );
    if( _strcmpi( token, "Delay" ) != 0 )
        throw INIException( 3, "Expected 'Delay' token, found '%s'\n", token );
    ini->parseDurationUnsignedInt( ini, instance, &info->delay, 0 );
    token = ini->getNextTokenOrNull( ini->getSepsColon() );
    if( token != 0 )
    {
        if( _strcmpi( token, "Bone" ) != 0 )
            throw INIException( 3, "Expected 'Bone' token, found '%s'\n", token );
        BoneNameSlot( &info->boneName ) = ini->getNextAsciiString();
    }
}

void BridgeBehaviorModuleData::parseOCL( INI *ini, void *instance, void *store, const void * )
{
	BridgeOCLInfo item;
	const char *token;
	item.ocl = 0;
	_STL::list<BridgeOCLInfo, _STL::allocator<BridgeOCLInfo> > *bridgeOCLList =
		(_STL::list<BridgeOCLInfo, _STL::allocator<BridgeOCLInfo> > *)store;

	const char *sepsColon = *(const char **)((const char *)ini + 0x420);
	token = ini->getNextToken( sepsColon );
	if( _strcmpi( token, "OCL" ) != 0 )
		throw INIException( 3, "Expected 'OCL' token, found '%s'\n", token );

	ObjectCreationList *ocl;
	INI::parseObjectCreationList( ini, instance, &ocl, 0 );
	item.ocl = ocl;
	parseTimeAndLocationInfo( ini, instance, &item.timeAndLocationInfo );
	bridgeOCLList->push_back( item );
}
