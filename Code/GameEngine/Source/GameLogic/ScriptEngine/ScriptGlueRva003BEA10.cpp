// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /DNDEBUG /MD /arch:SSE
//
// ?Rva003BEA10Do@@YGXPBVAsciiString@@PAX@Z @0x003BEA10 241B (dump range 18).
// Team-plus-position AI-group dispatch: copies the team name on the stack
// (rowed StringBase copy 0x00365F0, leaked like the landed 0x003C4570 call
// site), resolves the team through rowed getTeamNamed 0x003584E9, creates a
// group through rowed AI::createGroup 0x002FEC4B, fills it through rowed
// Team::getTeamAsAIGroup 0x003A0F62, counts members through rowed
// Team::rva0039DC9E 0x0039DC9E with two flag copies off the 0x00DFEFA4
// global, reads a position block through the TerrainLogic slot-0x88 idiom
// (result +0xC is the Coord3D, same as landed 0x003BD116), then either fires
// the pinned AIGroup 0x00372C22 member with (coord, 1, 0, 1) when the count
// exceeds 1 or builds the rowed Rva00372571Params block (m_14 = -1 first,
// same order as ScriptActions_closestOfObjectTypes) for the rowed AIGroup
// 0x00372571 member with source 1. The shared leading push-1 serves both
// calls. Flag/global identities unproven beyond their byte roles.
#include "ascii_string.h"

struct Coord3D
{
	float x;
	float y;
	float z;
};

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
	void rva00372571(Rva00372571Params *params, int source);
	void rva00372C22(Coord3D *pos, int a, int b, int c);
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

extern BitFlags<116> g_00DFEFA4;

void __stdcall Rva003BEA10Do(const AsciiString *teamName, void *posSrc)
{
	Team *team = TheScriptEngine->getTeamNamed(*teamName, false);
	if (team == 0)
		return;
	AIGroup *group = TheAI->createGroup();
	if (group == 0)
		return;
	team->getTeamAsAIGroup(group);
	BitFlags<116> *flagSets = &g_00DFEFA4;
	int count = team->rva0039DC9E(*flagSets, *flagSets);
	void *base = TheTerrainLogic->s34(posSrc);
	if (base == 0)
		return;
	Coord3D pos;
	pos.x = ((const Coord3D *)((const char *)base + 0xC))->x;
	pos.y = ((const Coord3D *)((const char *)base + 0xC))->y;
	pos.z = ((const Coord3D *)((const char *)base + 0xC))->z;
	if (count > 1) {
		group->rva00372C22(&pos, 1, 0, 1);
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
		group->rva00372571(&params, 1);
	}
}
