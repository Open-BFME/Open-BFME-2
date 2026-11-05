// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -D_STLP_USE_STATIC_LIB -D_STLP_NO_EXCEPTIONS -Ireference/open-bfme-1/inputs/reference/shims/ini -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/game/GameEngine/Source/Common/INI
// stlport
// Open-BFME7: INI block parser at 0x0014C090 (174 B): reads the block name
// into an AsciiString then allocates the 16-byte Gen0014AE40 definition (its
// constructor takes the name by value: the copy is built straight into the
// argument slot) fills it through INI::initFromINI with the field table at
// VA 0x0109596C and hands it to the owning store (the instance argument)
// through the add routine at 0x0014BE10.  Names are address-derived.

#include "PreRTS.h"
#include "Common/INI.h"

class Gen0014AE40
{
public:
	Gen0014AE40( AsciiString name );
	virtual ~Gen0014AE40();

private:
	char m_unreconstructed[ 12 ];
};

// The field table (retail .rdata 0x008073A0, 32 bytes): Zero Hour AI.cpp's
// parseBuildList table, one Structure field through the rowed
// BuildListInfo::parseStructure (0x0032A942), then the terminator.
class BuildListInfo
{
public:
	static void parseStructure( INI *ini, void *instance, void *store, const void *userData );
};

extern const FieldParse Rva0014C090FieldParseTable[] =
{
	{ "Structure", BuildListInfo::parseStructure, NULL, 0 },
	{ NULL, NULL, NULL, 0 }
};

// The instance's add (call target 0x002FE8CC) is the rowed
// TAiData::addFactionBuildList (AIConstructor.cpp).
class TAiData
{
public:
	void addFactionBuildList( Gen0014AE40 *definition );
};

class Rva0014C090
{
public:
	static void parseDefinition(INI *ini, void *instance, void *store, const void *userData);
};

// ?parseDefinition@Rva0014C090@@SAXPAVINI@@PAX1PBX@Z
void Rva0014C090::parseDefinition( INI *ini, void *instance, void *, const void * )
{
	AsciiString name = ini->getNextToken();
	Gen0014AE40 *definition = new Gen0014AE40( name );
	ini->initFromINI( definition, Rva0014C090FieldParseTable );
	((TAiData *)instance)->addFactionBuildList( definition );
}
