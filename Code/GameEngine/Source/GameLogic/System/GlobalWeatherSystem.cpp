// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/iniexception /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
//
// ?parseWeatherData@GlobalWeatherSystem@@SAXPAVINI@@@Z, retail 0x0031842A (142 bytes).
//
// Identity (target family): worldbuilder.exe's assert names its partner
// GlobalWeatherSystem::parseWeatherData in
// Code\GameEngine\Source\GameLogic\System\GlobalWeatherSystem.cpp (the only
// function in each image referencing the "Cannot define WeatherData in
// map.ini" and "Unknown weather type %s" literals). The parameter list is inferred from
// the body (one stack argument used as the INI) and from the donor.
//
// Body (donor): Open-BFME-1's WeatherData.cpp, where the same code is matched
// as the free function ?parseWeatherData@@YAXPAVINI@@@Z; worldbuilder places
// it in GlobalWeatherSystem as a static member, which compiles identically.
// BFME2 repairs read from retail: the five 8-byte weather entries start at
// +0x30 of the system (BFME1: +0x28), and the unit is /O1 -- the ebp frame
// and the single shared _CxxThrowException tail (142B) against the donor's
// /O2 frameless body with two throw sites (167B).
#include "PreRTS.h"
#include "Common/INI.h"
#include "Common/INIException.h"

static INILoadType retailLoadType( const INI *ini )
{
	struct RetailINI { char m_pad[ 0x08 ]; INILoadType m_loadType; };
	return reinterpret_cast<const RetailINI *>( ini )->m_loadType;
}

struct WeatherData
{
	Int m_weatherSound;			// 0x00
	Bool m_hasLightning;		// 0x04

	static const FieldParse m_fieldParseTable[];
};

class GlobalWeatherSystem
{
public:
	static void parseWeatherData( INI *ini );

private:
	char m_unknown00[ 0x30 ];
	WeatherData m_weather[ 5 ];		// 0x30
};

extern GlobalWeatherSystem *TheGlobalWeatherSystem;

static const char *TheWeatherNames[] =
{
	"NONE", "CLOUDY", "RAINY", "CLOUDYRAINY", "SUNNY"
};

void GlobalWeatherSystem::parseWeatherData( INI *ini )
{
	if( retailLoadType( ini ) != INI_LOAD_OVERWRITE )
		throw INIException( 3, "Cannot define WeatherData in map.ini" );

	const char *token = ini->getNextToken();

	Int which;
	for( which = 0; which < 5; which++ )
		if( _strcmpi( TheWeatherNames[ which ], token ) == 0 )
			break;

	if( which == 5 )
		throw INIException( 3, "Unknown weather type %s", token );

	ini->initFromINI( &TheGlobalWeatherSystem->m_weather[ which ],
										WeatherData::m_fieldParseTable );
}
