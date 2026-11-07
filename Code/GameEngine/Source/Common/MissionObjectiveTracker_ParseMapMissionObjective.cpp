// cl: /MD /EHs-c-
// ?ParseMapMissionObjective@MissionObjectiveTracker@@SAXPAVINI@@@Z @0x00426D14 194B.
// Renamed from placeholder Rva00426D14Parse — the WorldBuilder twin names
// MissionObjectiveTracker::ParseMapMissionObjective in EA's own
// MissionObjectiveTracker.cpp (assert TheMissionObjectiveTracker, line 303).
// Static member spelling: ABI-identical to the proven cdecl free function.
// Original evidence: calls rowed ctor 0x426C4D plus initFromINI wrapper 0x42666E with new 0x10 plus holder TheMissionObjectiveTracker at +0x10 plus debug theDebug slots 0x60 0x6c 0x38 0x4c plus literal plus INIException filler 0x2F681 plus throw 0x629094
#include "../../Include/Common/INI/INI.h"

class Rva00426C4D
{
public:
	Rva00426C4D();
	virtual void *v0(int x);
private:
	char _pad[12];
};

class Rva0042666E
{
public:
	void rva0042666E(class INI *ini);
};

struct Holder00426D14
{
	char _00[0x10];
	Rva00426C4D *m_10;
};

// TheMissionObjectiveTracker is defined as Rva0039B95FHolder* in Rva0039B95FCount.cpp (same
// VA 0x00E031E8, same +0x10 holder slot); declare that exact name here and
// cast at use so the link resolves instead of adding a second global name.
struct Rva0039B95FHolder;
extern Rva0039B95FHolder *TheMissionObjectiveTracker;

#include <new>

void __cdecl _bfme_debugRecordCallsite(int kind);

#include "debug.h"


#include "../../Include/Common/INI/FieldParse.h"

class MissionObjectiveTracker
{
public:
	static void ParseMapMissionObjective(INI *ini);
};

void MissionObjectiveTracker::ParseMapMissionObjective(INI *ini)
{
	if (ini->m_loadType == 2)
	{
		if ((Holder00426D14 *)TheMissionObjectiveTracker == 0)
			return;
		Rva00426C4D *objectiveList = new Rva00426C4D;
		((Rva0042666E *)objectiveList)->rva0042666E(ini);
		if (((Holder00426D14 *)TheMissionObjectiveTracker)->m_10 == 0)
		{
			((Holder00426D14 *)TheMissionObjectiveTracker)->m_10 = objectiveList;
			return;
		}
		void *q = objectiveList ? objectiveList->v0(0) : (void *)0;
		::operator delete(q);
		return;
	}
	if (ini->m_loadType == 5)
		return;
	_bfme_debugRecordCallsite(1);
	theDebug->SkipNext();
	(theDebug->CrashBegin(0, 0, 0) << "A MissionObjectiveList may only appear in a map.ini file.").CrashDone(1);
	throw INIException(9, (const char *)0);
}

// INI block registration (LINK-236). Each unit links its own 12-byte BlockParse nodes onto
// theBlockParseList from a file-scope object whose inline constructor does the link; MSVC 7.1
// builds token and parse in .data, so the node's .text$yc initializer is only the 21-byte link
// (retail .CRT$XCU 0x007B0383, node 0x00DC85B8; the node is its unit's only .text$yc entry before the
// pool-init marker 0x007B0398 and follows the unit's header name lists in .data).
typedef void (*INIBlockParse)( INI *ini );
extern struct BlockParse *theBlockParseList;
struct BlockParse
{
	BlockParse *next;
	const char *token;
	INIBlockParse parse;

	BlockParse( const char *token, INIBlockParse parse ) : next(theBlockParseList), token(token), parse(parse)
	{
		theBlockParseList = this;
	}
};

BlockParse theMissionObjectiveListBlockParse( "MissionObjectiveList", MissionObjectiveTracker::ParseMapMissionObjective );
