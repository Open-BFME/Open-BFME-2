// cl: /O1 /G7 /GX- /DNDEBUG /MD
// ?parsePlayerPosition@@YAXPAVINI@@PAX1PBX@Z, retail 0x00535087 (51B): PlayerPosition
// FieldParse proc (0x00C68C58). 1-based atoi slot selects the 0x14-byte record at
// instance + 0xB0, filled through initFromINI with the table at 0x00C68D78.
#include <stdlib.h>
struct FieldParse;
class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	void initFromINI(void *what, const FieldParse *parseTable);
};

// The five side-flag parsers retail's PlayerPosition table reaches, all
// already-rowed bodies in Code/GameEngine/Source/Common/SideFlagsParseCallbacks.cpp
// and ParseAllowedFactions.cpp. Declared with the real INI* first argument so
// the table binds to those rowed symbols rather than a second spelling of them.
void parseHuman(INI *ini, void *instance, void *store, const void *userData);
void parseComputer(INI *ini, void *instance, void *store, const void *userData);
void parseLoadAIScripts(INI *ini, void *instance, void *store, const void *userData);
void parseForcePlayerTeam(INI *ini, void *instance, void *store, const void *userData);
void parseAllowedFactions(INI *ini, void *instance, void *store, const void *userData);

struct FieldParse
{
	const char *token;
	void (__cdecl *parse)(INI *ini, void *instance, void *store, const void *userData);
	const void *userData;
	int offset;
};

// Retail VA 0x00C68D78 (.rdata, file offset 0x00868778): the five side flags of a
// starting position, every record with a null user-data column and offset 0 - the
// parsers themselves select their slot - then the zero sentinel. The 96-byte
// extent is the ledger's own bound and ends where retail's next object begins.
// Symbol ?g_00C68D78@@3QBUFieldParse@@B, transcribed below.
extern const FieldParse g_00C68D78[] =
{
	{ "Human",           &parseHuman,           0, 0x0 },
	{ "Computer",        &parseComputer,        0, 0x0 },
	{ "LoadAIScripts",   &parseLoadAIScripts,   0, 0x0 },
	{ "ForcePlayerTeam", &parseForcePlayerTeam, 0, 0x0 },
	{ "AllowedFactions", &parseAllowedFactions, 0, 0x0 },
	{ 0, 0, 0, 0 }
};
struct Rva00535087Position { unsigned char m_unreconstructed_00[0x14]; };
struct Rva00535087Owner { unsigned char m_unreconstructed_00[0xB0]; Rva00535087Position m_positions[1]; };
void parsePlayerPosition(INI *ini, void *instance, void *, const void *)
{
	Rva00535087Owner *owner = (Rva00535087Owner *)instance;
	int slot = atoi(ini->getNextToken());
	--slot;
	ini->initFromINI(&owner->m_positions[slot], g_00C68D78);
}
