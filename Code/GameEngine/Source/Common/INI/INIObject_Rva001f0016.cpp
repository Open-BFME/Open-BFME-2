// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -Ireference/open-bfme-1/inputs/reference/shims/ini -Ireference/open-bfme-1/inputs/reference/shims/iniexception -Ireference/open-bfme-1/inputs/reference/shims/ini_noinline -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common/INI
// stlport
//
// The Object block. It is one line: read the name and hand off to the shared
// four-argument body at 0x00139D00, which the ObjectReskin and ChildObject
// blocks also use -- they pass the original's name where this one passes empty
// strings, which is why that function carries both "ObjectReskin must come after
// the original Object (%s, %s)." and "ChildObject must come after the original
// Object (%s, %s)."
//
// That body is ThingFactory::parseObjectDefinition, as in Zero Hour, whose
// shared body takes two names; BFME's takes three.
#include "PreRTS.h"
#include "Common/INI.h"

class ThingFactory
{
public:
	static void parseObjectDefinition( INI *ini, const AsciiString &name,
									   const AsciiString &reskinFrom,
									   const AsciiString &childOf );	// 0x00139D00
};

void INI::parseObjectReskinDefinition( INI* ini )
{
	AsciiString name( ini->getNextToken() );
	AsciiString reskinFrom( ini->getNextToken() );
	ThingFactory::parseObjectDefinition( ini, name, reskinFrom, AsciiString::TheEmptyString );
}
