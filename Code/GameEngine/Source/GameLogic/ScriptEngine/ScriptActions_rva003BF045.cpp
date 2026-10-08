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
struct Coord3D { float x; float y; float z; };
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
class Object
{
public:
	char m_pad00[0x38];
	Coord3D m_position;
};
class Team
{
public:
	void getTeamAsAIGroup(AIGroup *group);
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
};
class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString, Bool);
	Player *getSkirmishEnemyPlayer();
	Player *getCurrentPlayer();
};
class AI
{
public:
	AIGroup *createGroup();
};
class AIGroup
{
public:
	void rva0036F9FE(const Waypoint *wp, CommandSourceType src, int x);
};
class Rva0036FAF8
{
public:
	void rva0036FAF8(const Waypoint *wp, CommandSourceType src, int x);
};
class Player
{
public:
	virtual void d00(); virtual void d01(); virtual void d02(); virtual void d03();
	virtual void d04();
	virtual void v05(Object *o, Waypoint *wp);
	char m_pad04[0x2E0 - 4];
	int m_2E0;
};
class TerrainLogic
{
public:
	virtual void d00(); virtual void d01(); virtual void d02(); virtual void d03();
	virtual void d04(); virtual void d05(); virtual void d06(); virtual void d07();
	virtual void d08(); virtual void d09(); virtual void d10(); virtual void d11();
	virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
	virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
	virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
	virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27();
	virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31();
	virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35();
	virtual Waypoint *v36(const Coord3D *pos, const AsciiString *name);
};
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
	int n = 0;
	Coord3D sum;
	sum.z = 0.0f;
	sum.y = 0.0f;
	sum.x = 0.0f;
	Object *first = 0;
	DLINK_ITERATOR<Object> it = team->iterate_TeamMemberList();
	while (!it.done()) {
		Object *o = it.cur();
		float x = o->m_position.x;
		float y = o->m_position.y;
		float z = o->m_position.z;
		sum.x += x;
		sum.y += y;
		sum.z += z;
		++n;
		if (first == 0)
			first = o;
		it.advance();
	}
	if (n == 0)
		return;
	float inv = g_Va00BBB8D8 / (float)n;
	sum.x *= inv;
	sum.y *= inv;
	sum.z *= inv;
	Player *enemy = TheScriptEngine->getSkirmishEnemyPlayer();
	if (enemy == 0)
		return;
	int base = enemy->m_2E0;
	int num = base + 1;
	AsciiString waypointName;
	const void *q = *(const void * const *)&prefix;
	const char *s = q ? (const char *)q + 8 : "";
	waypointName.format("%s%d", s, num);
	Waypoint *wp = TheTerrainLogic->v36(&sum, &waypointName);
	if (wp == 0)
		return;
	Player *cur = TheScriptEngine->getCurrentPlayer();
	if (cur != 0 && first != 0)
		cur->v05(first, wp);
	if (which)
		((Rva0036FAF8 *)group)->rva0036FAF8(wp, CMD_FROM_SCRIPT, 0);
	else
		group->rva0036F9FE(wp, CMD_FROM_SCRIPT, 0);
}
