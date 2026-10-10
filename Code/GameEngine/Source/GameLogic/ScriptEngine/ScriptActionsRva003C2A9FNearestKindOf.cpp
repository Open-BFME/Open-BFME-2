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

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString team, Bool exact);
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
};

enum CommandSourceType { CMD_FROM_SCRIPT = 1 };

class AIGroup
{
public:
	void rva00370410(Object *target, int value, CommandSourceType cmdSource);
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
