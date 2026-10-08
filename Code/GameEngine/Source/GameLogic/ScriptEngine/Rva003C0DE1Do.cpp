// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?Rva003C0DE1Do@@YGXABVAsciiString@@_N@Z @0x003C0DE1 81B.
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
class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
};
class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString, bool);
};
extern class ScriptEngine *TheScriptEngine;
namespace Rva002EFB20
{
void __cdecl helper(void *obj, bool flag);
}

void __stdcall Rva003C0DE1Do(const AsciiString &teamName, bool flag)
{
	Team *team = TheScriptEngine->getTeamNamed((AsciiString &)teamName, false);
	if (team == 0)
		return;
	for (DLINK_ITERATOR<Object> it = team->iterate_TeamMemberList(); !it.done(); it.advance()) {
		Rva002EFB20::helper(it.cur(), flag);
	}
}
