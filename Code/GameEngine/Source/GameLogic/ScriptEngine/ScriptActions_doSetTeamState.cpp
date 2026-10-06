// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ScriptActions::doSetTeamState, retail 0x003BEC9B, 50 bytes.
// Target evidence: executeAction action index 0x25 is named TEAM_SET_STATE by
// the landed action-template table and directly calls VA 0x007BEC9B. Ghidra's
// boundary is 0x003BEC9B/50. Retail copies the first AsciiString through the
// pinned StringBase copy constructor, calls the team lookup through the
// ScriptEngine pointer at VA 0x00DFE16C, then assigns into Team+0x44 through
// the pinned AsciiString assignment body at RVA 0x000366F0.
// Donor facts: BFME1 ScriptActions.cpp maps TEAM_SET_STATE to doSetTeamState;
// it looks up the named team, then sets the team's state string. The target
// offset and callees above are established independently from retail bytes.

typedef bool Bool;

#include "ascii_string.h"


class Team
{
public:
    char m_pad[0x44];
    AsciiString m_state;
};

class ScriptEngine
{
public:
    Team *getTeamNamed(AsciiString team, Bool exact);
};
extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
protected:
    void doSetTeamState(const AsciiString &, const AsciiString &);
};

void ScriptActions::doSetTeamState(const AsciiString &team, const AsciiString &state)
{
    Team *theTeam = TheScriptEngine->getTeamNamed(team, false);
    if (theTeam != 0) {
        theTeam->m_state = state;
    }
}
