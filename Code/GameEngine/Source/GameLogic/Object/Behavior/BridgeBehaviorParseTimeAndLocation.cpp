// Copyright notice and GPL terms retained from the reference BridgeBehavior.cpp.
/*
**  Command & Conquer Generals Zero Hour(tm)
**  Copyright 2025 Electronic Arts Inc.
**
**  This program is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
// Donor semantics: BridgeBehaviorParseFX.cpp::parseTimeAndLocationInfo.
// Target evidence: BridgeDieFX registered callback 0x4580A9 calls 0x45679B;
// target Delay/Bone diagnostics identify this parser. Target extent 194B.
// Target-local view: INI separator pointer is at +0x420 (donor +0x41C).
// Force_ParseTimeAndLocation below is an isolated emission aid, not a target
// function claim; it keeps this otherwise-static helper out of line.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/asciistring_outofline /Ireference/shims/iniexception /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /O1

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
};

struct TimeAndLocationInfo
{
    UnsignedInt delay;
    AsciiString boneName;
};

struct BoneNameSlot
{
    AsciiString *destination;

    __forceinline BoneNameSlot( AsciiString *value ) : destination( value ) {}

    __forceinline void operator=( const AsciiString &value )
    {
        destination->operator=( value );
    }
};

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
// ?Force_ParseTimeAndLocation@@YAXPAVINI@@PAXPAUTimeAndLocationInfo@@@Z absent-from-retail
void Force_ParseTimeAndLocation( INI *ini, void *instance, TimeAndLocationInfo *info )
{
    parseTimeAndLocationInfo( ini, instance, info );
}
