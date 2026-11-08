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

#include "../../../Include/Common/INI/INI.h"

// 0x00215C38 (16B): "PlayerAIType" (registration VA 0x00DB9B74). Forwards the
// INI to ThePlayerAITypeSet (0x00DFE31C) through its unrowed member 0x00215B14
// (thiscall, ret 4, builds a 0x24-byte entry on the stack).
class PlayerAITypeSet
{
public:
	void rva00215B14(INI *ini);
};

extern PlayerAITypeSet *ThePlayerAITypeSet;


// 0x00221012 (21B): "ArmySummaryDescription" (registration VA 0x00DBA184).
// No null check: initFromINI the object at 0x00DFE490 against VA 0x00BE6B2C.
extern void *g_00DFE490;
extern const FieldParse ArmySummaryDescriptionFields[];


// 0x0022232E (21B): "InGameNotificationBox" (registration VA 0x00DBA19C).
// No null check: initFromINI the object at 0x00DFE4C4 against VA 0x00BE6CE0.
extern void *g_00DFE4C4;
extern const FieldParse InGameNotificationBoxFields[];


// 0x002859A8 (25B): "FireLogicSystem" (registration VA 0x00DBB758). Skips
// when the singleton at 0x00DFEC68 is null, else initFromINI it against
// VA 0x00BFB620.
class Rva002872BA;
extern Rva002872BA *TheTriggerManager;
extern const FieldParse FireLogicSystemFields[];


// 0x002A8A31 (24B): "SkirmishAIData" (registration VA 0x00DBBC28). No null
// check: initFromINI the +0x10 member of the singleton at 0x00DFEEF8 against
// VA 0x00BFDA50.
#include "../../../Include/GameLogic/Rva002A8F24.h"

extern Rva002A8F24 *TheSkirmishAIManager;
extern const FieldParse SkirmishAIDataFields[];


// 0x00210F64 (40B): "LivingWorldMapInfo" (registration VA 0x00DB9A2C). Skips
// without TheLivingWorldManager, else initFromINI its +0x14 member against
// VA 0x00BE4560 and sets the +0x1C4 flag.
#include "../../../Include/GameLogic/LivingWorldManager.h"

extern LivingWorldManager *TheLivingWorldManager;
extern const FieldParse LivingWorldMapInfoFields[];


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


// 0x00289265 (136B): "ExperienceScalarTable" (registration VA 0x00DBB898).
// Skips without TheExperienceLevelSystem (0x00DFECC4), else reads the table
// name with getNextToken(0), news a 0x10-byte table through its rowed
// constructor 0x00288BBA, initFromINI's it against VA 0x00BFB820 and hands
// it to the system through the rowed forwarder 0x00289218 (the same
// forwarder LivingWorldCampaign's parser uses).
class ModuleData;

class ExperienceLevelSystem;
extern ExperienceLevelSystem *TheExperienceLevelSystem;
extern const FieldParse ExperienceScalarTableFields[];


// 0x00200FE3 (129B): "AerialPathfindNoFlyZone" (registration VA 0x00DB9558).
// Reads "TriggerArea" and looks the area up through TheTerrainLogic's
// virtual at +0x9C (by const reference), reads "Height" with scanReal, and
// when the area exists hands it and the height to TheAerialPathfinder through
// the rowed 0x00375BFF (unsigned int, float).
class PolygonTrigger;

#include "../../../Include/GameLogic/TerrainLogic.h"

class Rva00375BFF
{
public:
	void rva00375BFF(unsigned int key, float value);
};

class AerialPathfinder;
extern TerrainLogic *TheTerrainLogic;
extern AerialPathfinder *TheAerialPathfinder;

void parseAerialPathfindNoFlyZoneDefinition(INI *ini)
{
	AsciiString name(ini->getNextSubToken("TriggerArea"));
	PolygonTrigger *trigger = TheTerrainLogic->getTriggerAreaByName(name);
	float height = ini->scanReal(ini->getNextSubToken("Height"));
	if (trigger)
		((Rva00375BFF *)TheAerialPathfinder)->rva00375BFF((unsigned int)trigger, height);
}

// 0x0040C32B (25B): "AwardSystem" (registration VA 0x00DC1D9C). Skips when
// the object at 0x00E02F74 is null, else initFromINI it against VA 0x00C39410.
class Rva0040AAD5;
extern Rva0040AAD5 *TheAwardSystemManager;
extern const FieldParse AwardSystemFields[];


// 0x0040F0F0 (31B): "LivingWorldPlayerArmy" (registration VA 0x00DC1F68).
// Skips without TheCampaignManager (0x00E02D6C), else initFromINI the entry
// its rowed member 0x003B93BC returns against VA 0x00C39538.
struct BfmePod104;

class Rva00E02D6C;
extern Rva00E02D6C *TheCampaignManager;
extern const FieldParse LivingWorldPlayerArmyFields[];

