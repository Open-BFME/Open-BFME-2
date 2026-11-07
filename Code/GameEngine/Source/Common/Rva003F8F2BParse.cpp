// cl: /Oy- /DNDEBUG /MD /GX- /G7 /arch:SSE /O1
// ?ParseINI@SessionTask@LivingWorldTutorial@@SAXPAVINI@@PAURva003F7C0C@@@Z (0x003F8F2B, 104B)
// ?ParseINI@LogicTurn@LivingWorldTutorial@@SAXPAVINI@@PAURva003F9004@@@Z (0x003F907B, 104B): the
// LogicTurn twin, same shape with the 0x1c Rva003F7EC7 (0x003F7E9D), table
// 0x00C37468 and the rowed holder Rva003F9004::rva003F9004 (0x003F9004).
// Seat Z1 (w5-z1) near-exact bank for 0x003F8F2B (104B), twin of the rowed
// Rva003F2576Parse body in the same unit. Verified difference: retail parks the
// receiver in ESI and the {null, new-result} pair in EDI, pushing BOTH saved
// registers in the prologue; every source spelling tried (member holder local,
// holder in the guard, reference view, char* cast, ==0 guard, two locals in all
// orders) makes MSVC park the {null, new-result} pair in ESI instead, with the
// receiver in a lazily-saved EDI. Nothing else differs: all four callee targets,
// the 0x20 allocation, the push [esi+4] ctor argument, the FieldParse table VA
// 0x00C373D8 and the "Invalid data in SessionTask::ParseINI" literal match.
// Source kept in the attempt file for the next seat.
// Callee placeholders already admitted by address: ??0Rva003F8ED6@@QAE@H@Z
// (0x003F8EA2), ?rva003F7C0C@Rva003F7C0C@@QAEXPAX@Z (0x003F7C0C).
typedef void (*FieldParseProc)(class INI *, void *, void *, const void *);
#include "../../Include/Common/INI/FieldParse.h"

#include "../../Include/Common/INI/INI.h"

class ModuleData;

class Rva003F8ED6
{
public:
	Rva003F8ED6(int field);
private:
	char m_pad[0x20];
};

class Rva003F7EC7
{
public:
	Rva003F7EC7(int field);
private:
	char m_pad[0x1c];
};

struct Rva003F9004
{
	char m_pad[4];
	int m_04;
	void rva003F9004(const ModuleData *p);
};

struct Rva003F7C0C
{
	char m_pad[4];
	int m_04;
	void rva003F7C0C(void *p);
};



// Both parsers name themselves in their INIException text, and WB names them
// LivingWorldTutorial::SessionTask::ParseINI and LivingWorldTutorial::
// LogicTurn::ParseINI: static (cdecl, two arguments, plain ret), referenced
// only from the FieldParse tables at 0x00C3749C and 0x00C374F0.
namespace LivingWorldTutorial
{
	class SessionTask { public: static void ParseINI(INI *ini, Rva003F7C0C *outer); };
	class LogicTurn { public: static void ParseINI(INI *ini, Rva003F9004 *outer); };
}

extern "C" {
void __identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?ParseINI@SessionTask@LivingWorldTutorial@@SAXPAVINI@@PAURva003F7C0C@@@Z")();
void __identifier("?parseIndexList@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseAsciiStringVector@INI@@SAXPAV1@PAX1PBX@Z")();
}
// The task names the "Task" field indexes (retail .rdata 0x00C37174): 14
// pointers, the last "INVALID", with no null after them (the strings follow).
extern const char *const LivingWorldTutorialTaskNames[14] = {
	"EndPhase",
	"ZoomScroll",
	"BuildBarracks",
	"TrainUnit",
	"MergeGarrison",
	"MoveHeroArmyToRegion",
	"OpenDetailsPanel",
	"SelectBattle",
	"EnableAutoResolveButtonAndWaitForCompletion",
	"RetreatArmies",
	"ScriptedArmyMove",
	"ScriptedDelay",
	"EndTutorial",
	"INVALID",
};
// SessionTask's table at 0x00C373D8: 3 entries and the null terminator.
extern const FieldParse g_00C373D8[4] = {
	{ "Task", (FieldParseProc)&__identifier("?parseIndexList@INI@@SAXPAV1@PAX1PBX@Z"), LivingWorldTutorialTaskNames, 0x8 },
	{ "Params", (FieldParseProc)&__identifier("?parseAsciiStringVector@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xC },
	{ "Text", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x18 },
	{ 0, 0, 0, 0 }
};
// The retail table at 0x00837468: 4 entries and the null terminator; every parser is a rowed code owner.
extern const FieldParse g_logicTurnFieldParse[5] = {
	{ "Audio", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x8 },
	{ "Text", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x10 },
	{ "ClearPreviousText", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x19 },
	{ "TaskAfterAudio", (FieldParseProc)&__identifier("?ParseINI@SessionTask@LivingWorldTutorial@@SAXPAVINI@@PAURva003F7C0C@@@Z"), 0, 0x0 },
	{ 0, 0, 0, 0 }
};

void LivingWorldTutorial::SessionTask::ParseINI(INI *ini, Rva003F7C0C *outer)
{
	if (!ini || !outer)
	{
		throw INIException(3, "Invalid data in SessionTask::ParseINI");
	}
	Rva003F8ED6 *task = new Rva003F8ED6((outer->m_04?outer->m_04:outer->m_04));
	ini->initFromINI(task, g_00C373D8);
	outer->rva003F7C0C(task);
}

void LivingWorldTutorial::LogicTurn::ParseINI(INI *ini, Rva003F9004 *outer)
{
	if (!ini || !outer)
	{
		throw INIException(3, "Invalid data in LogicTurn::ParseINI");
	}
	Rva003F7EC7 *logicTurn = new Rva003F7EC7((outer->m_04?outer->m_04:outer->m_04));
	ini->initFromINI(logicTurn, g_logicTurnFieldParse);
	outer->rva003F9004((const ModuleData *)logicTurn);
}
