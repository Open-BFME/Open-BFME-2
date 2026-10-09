// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// BFME 2 INI block parsers that are reached only through the block-parse
// registrations (Rva007ABBF6BlockParseInits.cpp lists each token with its
// parse address), so Ghidra never started a function at any of them and they
// sat as unclaimed bytes between rowed neighbours. Each is the small
// "initFromINI the subsystem singleton against its field table" shape of
// Zero Hour's INI::parse*Definition. The tokens are target facts read from the
// registrations; the original function names are not known, so the bodies keep
// address names, and the singletons and tables use the data ledger's names
// where it has one.
#include "ascii_string.h"

typedef int Int;
typedef bool Bool;

struct FieldParse;

class INI
{
public:
	void initFromINI(void *what, const FieldParse *parseTable);
};

// 0x00215C38 (16B): "PlayerAIType" (registration VA 0x00DB9B74). Forwards the
// INI to ThePlayerAITypeSet (0x00DFE31C) through its unrowed member 0x00215B14
// (thiscall, ret 4, builds a 0x24-byte entry on the stack).
class PlayerAITypeSet
{
public:
	void rva00215B14(INI *ini);
};

extern PlayerAITypeSet *ThePlayerAITypeSet;

void Rva00215C38Parse(INI *ini)
{
	ThePlayerAITypeSet->rva00215B14(ini);
}

// 0x00221012 (21B): "ArmySummaryDescription" (registration VA 0x00DBA184).
// No null check: initFromINI the object at 0x00DFE490 against VA 0x00BE6B2C.
extern void *g_00DFE490;
extern const FieldParse ArmySummaryDescriptionFields[];

void Rva00221012Parse(INI *ini)
{
	ini->initFromINI(g_00DFE490, ArmySummaryDescriptionFields);
}

// 0x0022232E (21B): "InGameNotificationBox" (registration VA 0x00DBA19C).
// No null check: initFromINI the object at 0x00DFE4C4 against VA 0x00BE6CE0.
extern void *g_00DFE4C4;
extern const FieldParse InGameNotificationBoxFields[];

void Rva0022232EParse(INI *ini)
{
	ini->initFromINI(g_00DFE4C4, InGameNotificationBoxFields);
}

// 0x002859A8 (25B): "FireLogicSystem" (registration VA 0x00DBB758). Skips
// when the singleton at 0x00DFEC68 is null, else initFromINI it against
// VA 0x00BFB620.
class Rva002872BA;
extern Rva002872BA *TheTriggerManager;
extern const FieldParse FireLogicSystemFields[];

void Rva002859A8Parse(INI *ini)
{
	if (TheTriggerManager)
		ini->initFromINI(TheTriggerManager, FireLogicSystemFields);
}

// 0x002A8A31 (24B): "SkirmishAIData" (registration VA 0x00DBBC28). No null
// check: initFromINI the +0x10 member of the singleton at 0x00DFEEF8 against
// VA 0x00BFDA50.
class Rva002A8F24
{
public:
	char m_unreconstructed_00[0x10];
	char m_skirmishAIData[0x10];
};

extern Rva002A8F24 *g_00DFEEF8;
extern const FieldParse SkirmishAIDataFields[];

void Rva002A8A31Parse(INI *ini)
{
	ini->initFromINI(g_00DFEEF8->m_skirmishAIData, SkirmishAIDataFields);
}

// 0x00210F64 (40B): "LivingWorldMapInfo" (registration VA 0x00DB9A2C). Skips
// without TheLivingWorldManager, else initFromINI its +0x14 member against
// VA 0x00BE4560 and sets the +0x1C4 flag.
class LivingWorldManager
{
public:
	char m_unreconstructed_00[0x14];
	char m_mapInfo[0x1B0];
	Bool m_mapInfoParsed;
};

extern LivingWorldManager *TheLivingWorldManager;
extern const FieldParse LivingWorldMapInfoFields[];

void Rva00210F64Parse(INI *ini)
{
	if (TheLivingWorldManager)
	{
		ini->initFromINI(TheLivingWorldManager->m_mapInfo, LivingWorldMapInfoFields);
		TheLivingWorldManager->m_mapInfoParsed = true;
	}
}

// 0x00417A94 (36B): "HouseColor" (registration VA 0x00DC822C). Skips without
// TheHouseColorSystem (0x00E030A0), else initFromINI it against VA 0x00C3A600
// and tail-calls its no-argument member 0x00417A6B.
// 0x00417A6B (41B), the HouseColor parser's tail callee: hands the C strings
// of the +0x10 and +0x0C AsciiStrings (empty string 0x00BBAC1C when unset)
// to the unrowed cdecl 0x00136B5E, which null-checks both arguments.
void Rva00136B5E(const char *first, const char *second);

class HouseColorSystem
{
public:
	void rva00417A6B();

private:
	char m_unreconstructed_00[0x0C];
	AsciiString m_0c;
	AsciiString m_10;
};

void HouseColorSystem::rva00417A6B()
{
	Rva00136B5E(m_10.str(), m_0c.str());
}

extern HouseColorSystem *TheHouseColorSystem;
extern const FieldParse HouseColorFields[];

void Rva00417A94Parse(INI *ini)
{
	if (TheHouseColorSystem)
	{
		ini->initFromINI(TheHouseColorSystem, HouseColorFields);
		TheHouseColorSystem->rva00417A6B();
	}
}
