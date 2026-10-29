// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -ICode/GameEngine/Include -DNDEBUG -MD -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
//
// ?Rva003BEBD6Do@ScriptActions@@QAEXPBVAsciiString@@@Z @0x003BEBD6 197B (dump range 18).
// Team-plus-position AI-group dispatch, sibling of landed 0x003BEA10:
// same head (team-name copy, getTeamNamed, AI createGroup, getTeamAsAIGroup,
// two flag copies off 0x00DFEFA4, member count) but the position comes from
// the rowed Team 0x0039E9A1 out-member (its returned pointer unused)
// instead of the TerrainLogic slot, then the same count>1 branch (rowed
// 0x00372C22 member, called as BfmeC986 like the sibling, vs rowed
// Rva00372571Params block with source 1). Single string param, ret 4.
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
	int countObjects(BitFlags<116> mustBeSet, BitFlags<116> mustBeClear) const;
	Coord3D *rva0039E9A1(Coord3D *pos) const;
};

struct Rva00372571Params
{
	const Coord3D *m_pos;
	bool m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	bool m_1C;
};

class AIGroup
{
public:
	void groupMoveToPosition(Rva00372571Params *params, int source);
};
class BfmeC986
{
public:
	void groupGatherAndMoveInFormationToPosition(int pos, int a, int b, int c);
};

class AI
{
public:
	AIGroup *createGroup();
};
extern AI *TheAI;

#include "../../../Include/GameLogic/ScriptEngine.h"
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
#define g_00DFEFA4 KINDOFMASK_NONE
// ^ g_00DFEFA4 is only an alias of the owned global KINDOFMASK_NONE (ledger names column).

void ScriptActions::Rva003BEBD6Do(const AsciiString *teamName)
{
	Team *team = TheScriptEngine->getTeamNamed(*teamName, false);
	if (team == 0)
		return;
	AIGroup *group = TheAI->createGroup();
	if (group == 0)
		return;
	team->getTeamAsAIGroup(group);
	BitFlags<116> *flagSets = &g_00DFEFA4;
	int count = team->countObjects(*flagSets, *flagSets);
	Coord3D pos;
	team->rva0039E9A1(&pos);
	if (count > 1) {
		((BfmeC986 *)group)->groupGatherAndMoveInFormationToPosition((int)&pos, 1, 0, 1);
	} else {
		Rva00372571Params params;
		params.m_14 = -1;
		params.m_pos = &pos;
		params.m_04 = false;
		params.m_08 = 0;
		params.m_0C = 0;
		params.m_10 = 0;
		params.m_18 = 0;
		params.m_1C = false;
		group->groupMoveToPosition(&params, 1);
	}
}
