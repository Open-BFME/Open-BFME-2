// cl: /I. /Ireference/shims/bfme2_ascii /O1 /G7 /DNDEBUG /MD /EHsc /arch:SSE
// ?Rva003C2A9FDo@@YGXABVAsciiString@@H@Z @0x003C2A9F 289B: team attacks the nearest
// object of a KindOf bit among all players (Zero Hour ScriptActions team "attack
// nearest object type"). The team (rowed ScriptEngine 0x003584E9) gives its centre
// (pinned Team::rva0039E5B9), each player of the 0xFFFFF mask returns its closest
// object of the KindOf bit (Player::findClosestToPosByKindOf 0x002AB1DE, set mask
// built through the BitSet ctor 0x00045411, clear mask the KINDOFMASK_NONE copy
// 0x0004543D); the nearest one becomes the target of a fresh AI group built from the
// team (AI::createGroup 0x002FEC4B, Team::getTeamAsAIGroup 0x003A0F62, AIGroup 0x00370410
// with source 1 = from script). Target evidence: retail body and callee REL32s read byte
// for byte; the 99999.0f initial distance is the literal at 0x00BC93FC. Method roles
// beyond the pinned names are address-derived.
#include "ascii_string.h"

typedef bool Bool;
class Object;
class Player;
class PlayerList;
class AIGroup;
#include "Code/Libraries/Include/Lib/Coord3D.h"

extern "C" void *memset(void *dst, int val, unsigned size);
template<int N> class BitFlags
{
public:
	unsigned int m_bits[7];
	BitFlags(int unused, int bit);
	BitFlags(const BitFlags &other) throw();
	~BitFlags() {}
};
template<int N> __declspec(noinline) BitFlags<N>::BitFlags(int /*unused*/, int bit)
{
	memset(this, 0, 0x1C);
	m_bits[(unsigned)bit >> 5] |= 1u << (bit & 31);
}
extern BitFlags<116> KINDOFMASK_NONE;

class Team
{
public:
	void rva0039E5B9(Coord3D *center);
	void getTeamAsAIGroup(AIGroup *group);
};

class Parameter;

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString team, Bool exact);
	int rva00357B82(Parameter *playerParm);	// 0x00357B82: the parameter's player mask
	Object *getUnitNamed(Parameter *name);	// 0x003588E7
};

enum CommandSourceType { CMD_FROM_SCRIPT = 1 };

class AICommandInterface
{
public:
	void rva0036F4DF(Object *target, int value, CommandSourceType cmdSource);	// 0x0036F4DF
};
class AIUpdateInterface
{
public:
	unsigned char m_pad[0x20];
	AICommandInterface m_cmd;	// +0x20
};
extern ScriptEngine *TheScriptEngine;

class PlayerList
{
public:
	Player *getEachPlayerFromMask(int &mask);
};
extern PlayerList *ThePlayerList;

class Player
{
public:
	Object *findClosestToPosByKindOf(const Coord3D *pos, BitFlags<116> setMask, BitFlags<116> clearMask);
};

class Object
{
public:
	const Coord3D *getPosition() const { return (const Coord3D *)((const char *)this + 0x38); }
	AIUpdateInterface *getAI() const { return *(AIUpdateInterface **)((const char *)this + 0x258); }
};


// The argument block 0x00372571 takes (built inline by its callers).
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
	void rva00370410(Object *target, int value, CommandSourceType cmdSource);
	void rva00372571(Rva00372571Params *params, int source);	// 0x00372571
};

class AI
{
public:
	AIGroup *createGroup();
};
extern AI *TheAI;

void __stdcall Rva003C2A9FDo(const AsciiString &teamName, int kindBit)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (team == 0)
		return;
	Coord3D center;
	team->rva0039E5B9(&center);
	Object *best = 0;
	float bestDist = 99999.0f;
	int mask = 0xFFFFF;
	do {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		Object *cand = player->findClosestToPosByKindOf(&center, BitFlags<116>(0, kindBit), KINDOFMASK_NONE);
		if (cand) {
			const Coord3D *candPos = cand->getPosition();
			Coord3D delta;
			delta.x = candPos->x;
			delta.y = candPos->y;
			delta.z = candPos->z;
			delta.x -= center.x;
			delta.y -= center.y;
			delta.z -= center.z;
			float d = delta.length();
			if (!best || d < bestDist) {
				best = cand;
				bestDist = d;
			}
		}
	} while (mask != 0);
	if (!best)
		return;
	AIGroup *group = TheAI->createGroup();
	if (!group)
		return;
	team->getTeamAsAIGroup(group);
	group->rva00370410(best, 0, CMD_FROM_SCRIPT);
}

// 0x003C2260 (319B): the move form of 0x003C2A9F -- the team's new group is
// ordered to the nearest object's position through 0x00372571 (source 1)
// instead of attacking it.
void __stdcall Rva003C2260Do(const AsciiString &teamName, int kindBit)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (team == 0)
		return;
	Coord3D center;
	team->rva0039E5B9(&center);
	Object *best = 0;
	float bestDist = 99999.0f;
	int mask = 0xFFFFF;
	do {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		Object *cand = player->findClosestToPosByKindOf(&center, BitFlags<116>(0, kindBit), KINDOFMASK_NONE);
		if (cand) {
			const Coord3D *candPos = cand->getPosition();
			Coord3D delta;
			delta.x = candPos->x;
			delta.y = candPos->y;
			delta.z = candPos->z;
			delta.x -= center.x;
			delta.y -= center.y;
			delta.z -= center.z;
			float d = delta.length();
			if (!best || d < bestDist) {
				best = cand;
				bestDist = d;
			}
		}
	} while (mask != 0);
	if (!best)
		return;
	AIGroup *group = TheAI->createGroup();
	if (!group)
		return;
	team->getTeamAsAIGroup(group);
	Rva00372571Params params;
	params.m_14 = -1;
	params.m_pos = best->getPosition();
	params.m_04 = false;
	params.m_08 = 0;
	params.m_0C = 0;
	params.m_10 = 0;
	params.m_18 = 0;
	params.m_1C = false;
	group->rva00372571(&params, 1);
}

// 0x003C239F (337B): the player-parameter form of 0x003C2260 -- only the
// players of the parameter's mask are searched.
void __stdcall Rva003C239FDo(const AsciiString &teamName, int kindBit, Parameter *playerParm)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (team == 0)
		return;
	Coord3D center;
	team->rva0039E5B9(&center);
	Object *best = 0;
	float bestDist = 99999.0f;
	int mask = TheScriptEngine->rva00357B82(playerParm);
	if (mask == 0)
		return;
	do {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		Object *cand = player->findClosestToPosByKindOf(&center, BitFlags<116>(0, kindBit), KINDOFMASK_NONE);
		if (cand) {
			const Coord3D *candPos = cand->getPosition();
			Coord3D delta;
			delta.x = candPos->x;
			delta.y = candPos->y;
			delta.z = candPos->z;
			delta.x -= center.x;
			delta.y -= center.y;
			delta.z -= center.z;
			float d = delta.length();
			if (!best || d < bestDist) {
				best = cand;
				bestDist = d;
			}
		}
	} while (mask != 0);
	if (!best)
		return;
	AIGroup *group = TheAI->createGroup();
	if (!group)
		return;
	team->getTeamAsAIGroup(group);
	Rva00372571Params params;
	params.m_14 = -1;
	params.m_pos = best->getPosition();
	params.m_04 = false;
	params.m_08 = 0;
	params.m_0C = 0;
	params.m_10 = 0;
	params.m_18 = 0;
	params.m_1C = false;
	group->rva00372571(&params, 1);
}

// 0x003C9C0A (259B): the named unit attacks the nearest object of a KindOf
// bit over all players (the unit-based form of 0x003C2A9F).
void __stdcall Rva003C9C0AAttack(Parameter *unitParm, int kindBit)
{
	Object *unit = TheScriptEngine->getUnitNamed(unitParm);
	if (!unit)
		return;
	float bestDist = 99999.0f;
	Object *best = 0;
	int mask = 0xFFFFF;
	const Coord3D *unitPos = unit->getPosition();
	do {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		Object *cand = player->findClosestToPosByKindOf(unitPos, BitFlags<116>(0, kindBit), KINDOFMASK_NONE);
		if (cand) {
			const Coord3D *candPos = cand->getPosition();
			Coord3D delta;
			delta.x = candPos->x;
			delta.y = candPos->y;
			delta.z = candPos->z;
			delta.x -= unitPos->x;
			delta.y -= unitPos->y;
			delta.z -= unitPos->z;
			float d = delta.length();
			if (!best || d < bestDist) {
				best = cand;
				bestDist = d;
			}
		}
	} while (mask != 0);
	if (!best)
		return;
	AIUpdateInterface *ai = unit->getAI();
	if (!ai)
		return;
	ai->m_cmd.rva0036F4DF(best, 0, CMD_FROM_SCRIPT);
}
