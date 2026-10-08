// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /DNDEBUG /MD /arch:SSE
//
// ?Rva003BEB01Do@@YGXPBVAsciiString@@PAX@Z @0x003BEB01 213B (dump range 18).
// Team-plus-position AI-group dispatch, sibling of landed 0x003BEA10:
// same head (team-name copy, getTeamNamed, AI createGroup, getTeamAsAIGroup,
// two flag copies off 0x00DFEFA4, member count, TerrainLogic slot-0x88
// position) but the group stays in EBX, scratch saves reuse [ebp+8], the
// coord path fires the rowed BfmeC986 0x00372C74 member with
// (coordaddr, 1, group, 1), and the else path calls the same group's
// AIGroup::groupAttackMoveToPosition (0x00372B09, WB name, pinned) with
// (pos, 0x7FFFFFFF, CMD_FROM_SCRIPT). Retail loads ecx = group once before
// the branch for both member calls; spelling the else call as a free
// stdcall function was the bank's only difference.
// Checks use test-style (!team, !group).
#include "ascii_string.h"

#include "../../../../Libraries/Include/Lib/Coord3D.h"

template <int N>
class BitFlags
{
public:
	BitFlags(const BitFlags &other);
private:
	unsigned m_words[7];
};

class AIGroup;
class Object;

class Team
{
public:
	void getTeamAsAIGroup(AIGroup *group);
	int rva0039DC9E(BitFlags<116> mustBeSet, BitFlags<116> mustBeClear) const;
};

class BfmeC986
{
public:
	void rva00372C74(int a, int b, int c, int d);
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

class AIGroup
{
public:
	void groupAttackMoveToPosition(const Coord3D *pos, int maxShotsToFire, CommandSourceType cmdSource);
};

class AI
{
public:
	AIGroup *createGroup();
};
extern AI *TheAI;

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString name, bool exact);
};
extern ScriptEngine *TheScriptEngine;

class TerrainLogic
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04();
	virtual void s05(); virtual void s06(); virtual void s07(); virtual void s08(); virtual void s09();
	virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
	virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
	virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
	virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33();
	virtual void *s34(void *p);
};
extern TerrainLogic *TheTerrainLogic;

extern BitFlags<116> KINDOFMASK_NONE;

void __stdcall Rva003BEB01Do(const AsciiString *teamName, void *posSrc)
{
	Team *team = TheScriptEngine->getTeamNamed(*teamName, false);
	if (!team)
		return;
	AIGroup *group = TheAI->createGroup();
	if (!group)
		return;
	team->getTeamAsAIGroup(group);
	BitFlags<116> *flagSets = &KINDOFMASK_NONE;
	int count = team->rva0039DC9E(*flagSets, *flagSets);
	void *base = TheTerrainLogic->s34(posSrc);
	if (base == 0)
		return;
	Coord3D pos;
	pos.x = ((const Coord3D *)((const char *)base + 0xC))->x;
	pos.y = ((const Coord3D *)((const char *)base + 0xC))->y;
	pos.z = ((const Coord3D *)((const char *)base + 0xC))->z;
	if (count > 1) {
		((BfmeC986 *)group)->rva00372C74((int)&pos, 1, 0, 1);
	} else {
		group->groupAttackMoveToPosition(&pos, 0x7FFFFFFF, CMD_FROM_SCRIPT);
	}
}
