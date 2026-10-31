// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -DNDEBUG -MD -EHsc -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
//
// ?Rva003C0DE1Do@ScriptActions@@QAEXABVAsciiString@@_N@Z @0x003C0DE1 81B.
// Script team helper over named team via getTeamNamed iterate Rva-advance,
// applying Rva002EFB20 helper to each member with bool flag. Neighbours
// ScriptActions_rva003C0A2E / rva003C0F09 share flags. Evidence: rowed
// getTeamNamed iterate Rva-advance helper, extern g_Va009FE16C, caller
// 0x003CCFD1 ret 8.
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
#include "../../../Include/Common/TeamBFME2.h"
#include "../../../Include/GameLogic/ScriptEngine.h"
extern class ScriptEngine *TheScriptEngine;
namespace Rva002EFB20
{
void __cdecl helper(void *obj, bool flag);
}

void ScriptActions::Rva003C0DE1Do(const AsciiString &teamName, bool flag)
{
	Team *team = TheScriptEngine->getTeamNamed((AsciiString &)teamName, false);
	if (team == 0)
		return;
	for (DLINK_ITERATOR<Object> it = team->iterate_TeamMemberList(); !it.done(); it.advance()) {
		Rva002EFB20::helper(it.cur(), flag);
	}
}
