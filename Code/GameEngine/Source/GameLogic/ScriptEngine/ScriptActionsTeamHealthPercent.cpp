// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -DNDEBUG -MD -GX -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// BFME1 f98983a7d ScriptActions_doTeamSetHealth.cpp supplies health clamp,
// min/max reference templates and member traversal. Native 0x003C301D/188B
// independently proves direct ScriptEngine lookup, Object body+254 and body
// slots21/23 with float/bool1. Original free action spelling remains unknown.
// ?Rva003C301DDo@ScriptActions@@QAEXPAVParameter@@0@Z @0x003C301D 188B: team float-clamped body module via getTeamNamed iterate. Evidence: rowed getTeamNamed 0x3584E9 iterate 0x263864 advance 0x263526 StringBase copy 0x365F0; retail100.0 literal; caller 0x003CE3E8; ret 0x8 stdcall.
#include "ascii_string.h"


class Object;
class Team;

template<class OBJCLASS>
class DLINK_ITERATOR
{
private:
	OBJCLASS *m_cur;
	unsigned char m_targetAbiState[20];
public:
	void advance();
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

#include "../../../Include/GameLogic/Module/BodyModuleClass.h"

class Object
{
public:
	char m_pad00[0x254];
	BodyModuleInterface *m_body;
};

#include "../../../Include/Common/TeamBFME2.h"

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

inline const float &FloatMinRef(const float &a, const float &b) { return a < b ? a : b; }
inline const float &FloatMaxRef(const float &a, const float &b) { return a > b ? a : b; }

#include "../../../Include/GameLogic/ScriptParameter.h"

void ScriptActions::Rva003C301DDo(Parameter *teamParm, Parameter *floatParm)
{
	Team *team = TheScriptEngine->getTeamNamed((AsciiString &)teamParm->getString(), false);
	if (team == 0)
		return;
	float healthPercent = floatParm->m_real;
	healthPercent = FloatMinRef(healthPercent, 100.0f);
	healthPercent = FloatMaxRef(0.0f, healthPercent);
	for (DLINK_ITERATOR<Object> it = team->iterate_TeamMemberList(); !it.done(); it.advance()) {
		BodyModuleInterface *body = it.cur()->m_body;
		if (body == 0)
			continue;
		body->setInitialHealth(healthPercent, true);
		body->rva004BDB37();
	}
}
