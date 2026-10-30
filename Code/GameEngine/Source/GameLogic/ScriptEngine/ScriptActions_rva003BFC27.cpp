// stlport
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD
#include "GameLogic/ScriptActionsBFME2.h"
// ?Rva003BFC27Do@ScriptActions@@QAEXABVAsciiString@@@Z @0x003BFC27 152B
// Script team priority decrease via getTeamNamed pin 0x003584E9 with false,
// Team+0x30 TeamPrototype rowed decreaseAIPriorityForFailure 0x0039D73A, AsciiString format
// row 0x00038150 Team priority decreased, rowed AppendDebugMessage 0x00205263
// with false, rowed releaseBuffer 0x00036410.
// ?Rva003BFAF4Do@ScriptActions@@QAEXABVAsciiString@@@Z @0x003BFAF4 152B is the success twin
// (caller 0x003CB963): TeamPrototype increaseAIPriorityForSuccess 0x0039D72D, then "Team '%s'
// priority increased to %d for success." at 0x0081FEA0.
// Evidence: TheScriptEngine 0x009FE16C; caller 0x003CB99F; string at
// 0x0081FEF4 Team priority decreased; precedent ScriptEngineAppendDebugMessage
// StringBase layout with str plus format plus release.
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
	void increaseAIPriorityForSuccess();
	void decreaseAIPriorityForFailure();
private:
	char m_pad00[0x21C];
public:
	int m_priority21C;
private:
	char m_pad220[0x224 - 0x220];
	int m_delta224;
};
#include "../../../Include/Common/TeamBFME2.h"
#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

void ScriptActions::Rva003BFC27Do(const AsciiString &teamName)
{
	Team *team = TheScriptEngine->getTeamNamed((AsciiString &)teamName, false);
	if (team == 0)
		return;
	TeamPrototype *proto = team->m_proto;
	if (proto == 0)
		return;
	proto->decreaseAIPriorityForFailure();
	AsciiString msg;
	msg.format("Team '%s' priority decreased to %d for failure.", teamName.str(), proto->m_priority21C);
	TheScriptEngine->AppendDebugMessage(msg, false);
}

void ScriptActions::Rva003BFAF4Do(const AsciiString &teamName)
{
	Team *team = TheScriptEngine->getTeamNamed((AsciiString &)teamName, false);
	if (team == 0)
		return;
	TeamPrototype *proto = team->m_proto;
	if (proto == 0)
		return;
	proto->increaseAIPriorityForSuccess();
	AsciiString msg;
	msg.format("Team '%s' priority increased to %d for success.", teamName.str(), proto->m_priority21C);
	TheScriptEngine->AppendDebugMessage(msg, false);
}

// Member ABI proved at each native executeAction3CA4BE call site: ECX=this.
// Canonical ScriptActions owner; address-derived verbs remain uncertain.
