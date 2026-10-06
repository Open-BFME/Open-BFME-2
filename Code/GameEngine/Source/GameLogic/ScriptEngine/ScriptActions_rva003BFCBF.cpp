// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?Rva003BFCBFDo@@YGXABVAsciiString@@H@Z @0x003BFCBF 155B
// Script team priority decrease with delta via getTeamNamed pin 0x003584E9,
// Team+0x30 TeamPrototype rowed rva0039D754 0x0039D754 with delta, format row
// 0x00038150 Team priority decreased, rowed AppendDebugMessage 0x00205263.
// Evidence: TheScriptEngine 0x009FE16C; caller 0x003CB9C3; string at
// 0x0081FF24 Team priority decreased; precedent Rva003BFB8CDo 155B increase.
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

void __stdcall Rva003BFCBFDo(const AsciiString &teamName, int delta)
{
	Team *team = TheScriptEngine->getTeamNamed((AsciiString &)teamName, false);
	if (team == 0)
		return;
	TeamPrototype *proto = team->m_proto30;
	if (proto == 0)
		return;
	proto->rva0039D754(delta);
	AsciiString msg;
	msg.format("Team '%s' priority decreased to %d.", teamName.str(), proto->m_priority21C);
	TheScriptEngine->AppendDebugMessage(msg, false);
}
