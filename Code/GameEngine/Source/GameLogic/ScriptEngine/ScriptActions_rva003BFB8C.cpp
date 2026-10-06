// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?Rva003BFB8CDo@@YGXABVAsciiString@@H@Z @0x003BFB8C 155B
// Script team priority increase via getTeamNamed pin 0x003584E9 with false,
// Team+0x30 TeamPrototype rowed rva0039D747 0x0039D747 with delta, AsciiString
// format row 0x00038150 Team priority increased, rowed AppendDebugMessage
// 0x00205263 with false, rowed releaseBuffer 0x00036410.
// Evidence: TheScriptEngine 0x009FE16C; caller 0x003CB987; string at
// 0x0081FED0 Team priority increased; precedent Rva003BFC27Do 152B decrease.
typedef bool Bool;
template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};
#include "ascii_string.h"
class TeamPrototype
{
public:
	void rva0039D73A();
	void rva0039D747(int delta);
	void rva0039D754(int delta);
private:
	char m_pad00[0x21C];
public:
	int m_priority21C;
private:
	char m_pad220[0x224 - 0x220];
	int m_delta224;
};
class Team
{
public:
	char m_pad00[0x30];
	TeamPrototype *m_proto30;
};
class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString, Bool);
	void AppendDebugMessage(const AsciiString &, Bool);
};
extern ScriptEngine *TheScriptEngine;

void __stdcall Rva003BFB8CDo(const AsciiString &teamName, int delta)
{
	Team *team = TheScriptEngine->getTeamNamed((AsciiString &)teamName, false);
	if (team == 0)
		return;
	TeamPrototype *proto = team->m_proto30;
	if (proto == 0)
		return;
	proto->rva0039D747(delta);
	AsciiString msg;
	msg.format("Team '%s' priority increased to %d.", teamName.str(), proto->m_priority21C);
	TheScriptEngine->AppendDebugMessage(msg, false);
}
