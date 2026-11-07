// cl: /Oy- /DNDEBUG /MD /GX-
// Six TeamDefeatCondition-style ParseINI helpers recovered from the
// ?Rva004FD77CParse@@YAXPAVINI@@PAVRva004FD3E2@@@Z recipe at 0x004FD77C.
// Same operand-masked shape: null-check the INI and holder, new a record,
// INI::initFromINI it against a per-type FieldParse table, then append it to
// the holder, else throw INIException(3) with that type's literal. Only the
// record size, its constructor, the FieldParse table, the holder method and
// the literal differ. Evidence: each member's retail literal names its type
// (Tutorial/PlayerDefeatCondition/TeamDefeatCondition/SpawnGenericBuilding/
// SpawnGenericArmy/OwnershipSet), and the ctor and holder call displacements
// are read from the retail bodies.
typedef void (*FieldParseProc)(class INI *, void *, void *, const void *);
#include "../../Include/Common/INI/FieldParse.h"

#include "../../Include/Common/INI/INI.h"

class ModuleData;



// 0x003F9258 Tutorial::ParseINI, record size 0x24.
class Rva003F9258Data
{
public:
	Rva003F9258Data();
	virtual ~Rva003F9258Data();
private:
	char m_pad[0x20];
};

class Rva003F7BE9
{
public:
	void rva003F7BE9(const ModuleData *p);
};

extern "C" {
void __identifier("?Rva003F91A4Parse@@YAXPAVINI@@PAURva003F9048@@@Z")();
}
// The retail table at 0x00837560: 1 entries and the null terminator; every parser is a rowed code owner.
extern const FieldParse g_00C37560[2] = {
	{ "Turn", (FieldParseProc)&__identifier("?Rva003F91A4Parse@@YAXPAVINI@@PAURva003F9048@@@Z"), 0, 0x0 },
	{ 0, 0, 0, 0 }
};

void Rva003F9258Parse(INI *ini, Rva003F7BE9 *holder)
{
	if (!ini || !holder) {
		throw INIException(3, "Invalid data in Tutorial::ParseINI");
	}
	Rva003F9258Data *tutorial = new Rva003F9258Data;
	ini->initFromINI(tutorial, g_00C37560);
	holder->rva003F7BE9((const ModuleData *)tutorial);
}

// 0x004FD719 PlayerDefeatCondition::ParseINI, record size 0x18.
class Rva004FD719Data
{
public:
	Rva004FD719Data();
	virtual ~Rva004FD719Data();
private:
	char m_pad[0x14];
};

class Rva004FD37F
{
public:
	void rva004FD37F(const ModuleData *p);
};

extern "C" {
void __identifier("?Rva004FCB23Parse@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z")();
}
// The retail table at 0x008635D0: 3 entries and the null terminator; every parser is a rowed code owner.
extern const FieldParse g_00C635D0[4] = {
	{ "Teams", (FieldParseProc)&__identifier("?Rva004FCB23Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x4 },
	{ "LoseIfCapitalLost", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x14 },
	{ "NumControlledRegionsLessOrEqualTo", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x10 },
	{ 0, 0, 0, 0 }
};

void Rva004FD719Parse(INI *ini, Rva004FD37F *holder)
{
	if (!ini || !holder) {
		throw INIException(3, "Invalid data in PlayerDefeatCondition::ParseINI");
	}
	Rva004FD719Data *playerDefeatCondition = new Rva004FD719Data;
	ini->initFromINI(playerDefeatCondition, g_00C635D0);
	holder->rva004FD37F((const ModuleData *)playerDefeatCondition);
}

// 0x004FD7FB TeamDefeatCondition::ParseINI, record size 0x24.
class Rva004FD7FBData
{
public:
	Rva004FD7FBData();
	virtual ~Rva004FD7FBData();
private:
	char m_pad[0x20];
};

// Preserve the parser's existing address-derived holder ABI spelling.
class Rva004FD448;
#include "../../Include/Common/LivingWorldScenario.h"
class LivingWorldScenario::Scenario
{
public:
    void addTeamVictoryCondition(const TeamVictoryCondition *condition);
};

extern "C" {
void __identifier("?Rva004FCB23Parse@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseAsciiStringVector@INI@@SAXPAV1@PAX1PBX@Z")();
}
// The retail table at 0x008636D0: 4 entries and the null terminator; every parser is a rowed code owner.
extern const FieldParse g_00C636D0[5] = {
	{ "Teams", (FieldParseProc)&__identifier("?Rva004FCB23Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 0x4 },
	{ "NumControlledRegionsGreaterOrEqualTo", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x10 },
	{ "ControlledRegions", (FieldParseProc)&__identifier("?parseAsciiStringVector@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x14 },
	{ "ControlledRegionsHeldForTurns", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x20 },
	{ 0, 0, 0, 0 }
};

void Rva004FD7FBParse(INI *ini, Rva004FD448 *holder)
{
	if (!ini || !holder) {
		throw INIException(3, "Invalid data in TeamDefeatCondition::ParseINI");
	}
	Rva004FD7FBData *teamDefeatCondition = new Rva004FD7FBData;
	ini->initFromINI(teamDefeatCondition, g_00C636D0);
	reinterpret_cast<LivingWorldScenario::Scenario *>(holder)->addTeamVictoryCondition(reinterpret_cast<const LivingWorldScenario::TeamVictoryCondition *>(teamDefeatCondition));
}

// 0x0059E436 SpawnGenericBuilding::ParseINI, record size 0x14.
class Rva0059E436Data
{
public:
	Rva0059E436Data();
	virtual ~Rva0059E436Data();
private:
	char m_pad[0x10];
};

class Rva0059E390
{
public:
	void rva0059E390(const ModuleData *p);
};

extern "C" {
void __identifier("?parseAsciiStringVector@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z")();
}
// The retail table at 0x00870FFC: 2 entries and the null terminator; every parser is a rowed code owner.
extern const FieldParse g_00C70FFC[3] = {
	{ "Buildings", (FieldParseProc)&__identifier("?parseAsciiStringVector@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x4 },
	{ "Region", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x10 },
	{ 0, 0, 0, 0 }
};

void Rva0059E436Parse(INI *ini, Rva0059E390 *holder)
{
	if (!ini || !holder) {
		throw INIException(3, "Invalid data in SpawnGenericBuilding::ParseINI");
	}
	Rva0059E436Data *spawnGenericBuilding = new Rva0059E436Data;
	ini->initFromINI(spawnGenericBuilding, g_00C70FFC);
	holder->rva0059E390((const ModuleData *)spawnGenericBuilding);
}

// 0x0059E511 SpawnGenericArmy::ParseINI, record size 0x14.
class Rva0059E511Data
{
public:
	Rva0059E511Data();
	virtual ~Rva0059E511Data();
private:
	char m_pad[0x10];
};

class Rva0059E3A7
{
public:
	void rva0059E3A7(const ModuleData *p);
};

extern "C" {
void __identifier("?parseAsciiStringVector@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z")();
}
// The retail table at 0x00871064: 2 entries and the null terminator; every parser is a rowed code owner.
extern const FieldParse g_00C71064[3] = {
	{ "Armies", (FieldParseProc)&__identifier("?parseAsciiStringVector@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x4 },
	{ "Region", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x10 },
	{ 0, 0, 0, 0 }
};

void Rva0059E511Parse(INI *ini, Rva0059E3A7 *holder)
{
	if (!ini || !holder) {
		throw INIException(3, "Invalid data in SpawnGenericArmy::ParseINI");
	}
	Rva0059E511Data *spawnGenericArmy = new Rva0059E511Data;
	ini->initFromINI(spawnGenericArmy, g_00C71064);
	holder->rva0059E3A7((const ModuleData *)spawnGenericArmy);
}

// 0x0059E6D3 OwnershipSet::ParseINI, record size 0x2c.
class Rva0059E6D3Data
{
public:
	Rva0059E6D3Data();
	virtual ~Rva0059E6D3Data();
private:
	char m_pad[0x28];
};

class Rva004FD4AE
{
public:
	void rva004FD4AE(const ModuleData *p);
};

extern "C" {
void __identifier("?parseAsciiStringVector@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?Rva0059E436Parse@@YAXPAVINI@@PAVRva0059E390@@@Z")();
void __identifier("?Rva0059E511Parse@@YAXPAVINI@@PAVRva0059E3A7@@@Z")();
void __identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z")();
}
// The retail table at 0x008710E8: 4 entries and the null terminator; every parser is a rowed code owner.
extern const FieldParse g_00C710E8[5] = {
	{ "Regions", (FieldParseProc)&__identifier("?parseAsciiStringVector@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x1C },
	{ "SpawnBuildings", (FieldParseProc)&__identifier("?Rva0059E436Parse@@YAXPAVINI@@PAVRva0059E390@@@Z"), 0, 0x0 },
	{ "SpawnArmies", (FieldParseProc)&__identifier("?Rva0059E511Parse@@YAXPAVINI@@PAVRva0059E3A7@@@Z"), 0, 0x0 },
	{ "StartRegion", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x28 },
	{ 0, 0, 0, 0 }
};

void Rva0059E6D3Parse(INI *ini, Rva004FD4AE *holder)
{
	if (!ini || !holder) {
		throw INIException(3, "Invalid data in OwnershipSet::ParseINI");
	}
	Rva0059E6D3Data *ownershipSet = new Rva0059E6D3Data;
	ini->initFromINI(ownershipSet, g_00C710E8);
	holder->rva004FD4AE((const ModuleData *)ownershipSet);
}
