// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?doTeamFollowSkirmishApproachPath@ScriptActions@@IAEXABVAsciiString@@0_N@Z @0x003BF045 442B.
// Script team centroid to formatted waypoint via getTeamNamed createGroup
// getTeamAsAIGroup iterate Rva-advance, average with g_Va00BBB8D8, enemy
// index plus one formatted as prefix with "%s%d", TerrainLogic slot 0x90,
// current player slot 0x14 with first object, waypoint command by bool.
// Evidence: rowed getTeamNamed createGroup getTeamAsAIGroup iterate
// Rva-advance getSkirmishEnemyPlayer format getCurrentPlayer rva0036FAF8
// rva0036F9FE, externs g_Va009FE16C g_Va009FF0F8 g_Va00BBB8D8 TheTerrainLogic
// g_Rva0107301CEmptyString, "%s%d", caller 0x003CA855 ret 0xc.
#include "ascii_string.h"
typedef bool Bool;
enum CommandSourceType { CMD_FROM_PLAYER = 0, CMD_FROM_SCRIPT = 1 };
#include "../../../../Libraries/Include/Lib/Coord3D.h"
class Waypoint;
class Object;
class Team;
class AIGroup;
class Rva0036FAF8;
class Player;
template<class OBJCLASS>
class DLINK_ITERATOR
{
private:
	OBJCLASS *m_cur;
	unsigned char m_targetAbiState[20];
public:
	void advance();
	Bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};
#include "../Object/object.h"
#include "../../../Include/Common/TeamBFME2.h"
#include "../../../Include/GameLogic/ScriptEngine.h"
#include "../../../Include/GameLogic/AI.h"
#include "../../../Include/GameLogic/AIGroup.h"
class Rva0036FAF8
{
public:
	void rva0036FAF8(const Waypoint *wp, CommandSourceType src, int x);
};
#include "../../../Include/Common/Player.h"
#include "../../../Include/GameLogic/TerrainLogic.h"
extern class ScriptEngine *TheScriptEngine;
extern class AI *TheAI;
extern TerrainLogic *TheTerrainLogic;
extern float g_Va00BBB8D8;

class ScriptActions
{
protected:
	void doTeamFollowSkirmishApproachPath(const AsciiString &teamName, const AsciiString &prefix, bool which);
};

void ScriptActions::doTeamFollowSkirmishApproachPath(const AsciiString &teamName, const AsciiString &prefix, bool which)
{
	Team *team = TheScriptEngine->getTeamNamed((AsciiString &)teamName, false);
	if (team == 0)
		return;
	AIGroup *group = TheAI->createGroup();
	if (group == 0)
		return;
	team->getTeamAsAIGroup(group);
	int memberCount = 0;
	Coord3D sum;
	sum.z = 0.0f;
	sum.y = 0.0f;
	sum.x = 0.0f;
	Object *first = 0;
	DLINK_ITERATOR<Object> it = team->iterate_TeamMemberList();
	while (!it.done()) {
		Object *object = it.cur();
		float x = object->m_cachedPos.x;
		float y = object->m_cachedPos.y;
		float z = object->m_cachedPos.z;
		sum.x += x;
		sum.y += y;
		sum.z += z;
		++memberCount;
		if (first == 0)
			first = object;
		it.advance();
	}
	if (memberCount == 0)
		return;
	float inv = g_Va00BBB8D8 / (float)memberCount;
	sum.x *= inv;
	sum.y *= inv;
	sum.z *= inv;
	Player *enemy = TheScriptEngine->getSkirmishEnemyPlayer();
	if (enemy == 0)
		return;
	int base = enemy->m_mpStartIndex;
	int num = base + 1;
	AsciiString waypointName;
	const void *prefixHeader = *(const void * const *)&prefix;
	const char *s = prefixHeader ? (const char *)prefixHeader + 8 : "";
	waypointName.format("%s%d", s, num);
	Waypoint *wp = TheTerrainLogic->getClosestWaypointOnPath(&sum, waypointName);
	if (wp == 0)
		return;
	Player *cur = TheScriptEngine->getCurrentPlayer();
	if (cur != 0 && first != 0)
		cur->checkBridges(first, wp);
	if (which)
		((Rva0036FAF8 *)group)->rva0036FAF8(wp, CMD_FROM_SCRIPT, 0);
	else
		group->rva0036F9FE(wp, CMD_FROM_SCRIPT, 0);
}
