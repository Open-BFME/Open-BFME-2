// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /arch:SSE
//
// ?Rva003BF5FEDo@@YGXABVAsciiString@@H_N@Z @0x003BF5FE 288B.
// Script team waypoint average via getTeamNamed, member centroid, terrain
// slot 0x90, waypoint command chosen by bool.
// Evidence: rowed getTeamNamed createGroup getTeamAsAIGroup iterate
// advance rva0036FBC5 rva0036FA56, externs g_Va009FE16C g_Va009FF0F8
// TheTerrainLogic g_Va00BBB8D8, caller 0x003CA7E7 ret 0xc.
#include "ascii_string.h"
typedef bool Bool;
enum CommandSourceType { CMD_FROM_PLAYER = 0, CMD_FROM_SCRIPT = 1 };
#include "../../../../Libraries/Include/Lib/Coord3D.h"
class Waypoint;
class Object;
class Team;
class AIGroup;
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
};
class AI
{
public:
	AIGroup *createGroup();
};
class AIGroup
{
public:
	void rva0036FBC5(const Waypoint *wp, CommandSourceType src);
	void rva0036FA56(const Waypoint *wp, CommandSourceType src);
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
	virtual Waypoint *v36(const Coord3D *pos, int way);
};
extern ScriptEngine *g_Va009FE16C;
extern AI *g_Va009FF0F8;
extern TerrainLogic *TheTerrainLogic;
extern float g_Va00BBB8D8;

void __stdcall Rva003BF5FEDo(const AsciiString &teamName, int way, bool which)
{
	Team *team = g_Va009FE16C->getTeamNamed((AsciiString &)teamName, false);
	if (team == 0)
		return;
	AIGroup *group = g_Va009FF0F8->createGroup();
	if (group == 0)
		return;
	team->getTeamAsAIGroup(group);
	Coord3D sum;
	sum.z = 0.0f;
	sum.y = 0.0f;
	sum.x = 0.0f;
	int n = 0;
	DLINK_ITERATOR<Object> it = team->iterate_TeamMemberList();
	while (!it.done()) {
		Object *o = it.cur();
		float x = *(const volatile float *)&o->m_position.x;
		float y = *(const volatile float *)&o->m_position.y;
		float z = *(const volatile float *)&o->m_position.z;
		sum.x += x;
		sum.y += y;
		sum.z += z;
		++n;
		it.advance();
	}
	if (n == 0)
		return;
	float inv = g_Va00BBB8D8 / (float)n;
	sum.x *= inv;
	sum.y *= inv;
	sum.z *= inv;
	Waypoint *wp = TheTerrainLogic->v36(&sum, way);
	if (wp == 0)
		return;
	if (which)
		group->rva0036FBC5(wp, CMD_FROM_SCRIPT);
	else
		group->rva0036FA56(wp, CMD_FROM_SCRIPT);
}
