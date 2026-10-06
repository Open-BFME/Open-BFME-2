// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ScriptActions::doTeamAvailableForRecruitment, retail 0x003C01AB, 55 bytes.
// Target evidence: action template 0x5E is TEAM_AVAILABLE_FOR_RECRUITMENT and
// executeAction calls VA 0x007C01AB; Ghidra boundary is 0x003C01AB/55. Retail
// copies the team name through the pinned StringBase copy constructor and uses
// the pinned ScriptEngine::getTeamNamed body. On success it writes byte +0x110
// to 1 and byte +0x111 to the requested availability value.
// Donor facts: BFME1 ScriptActions.cpp maps this action to
// doTeamAvailableForRecruitment and calls Team::setRecruitable. Target-backed
// writes establish only the two byte offsets and values.

typedef bool Bool;

#include "ascii_string.h"


class Team
{
public:
    void setRecruitable(Bool availability)
    {
        m_recruitable = 1;
        m_available = availability;
    }

private:
    char m_pad[0x110];
    unsigned char m_recruitable;
    unsigned char m_available;
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
    void doTeamAvailableForRecruitment(const AsciiString &, Bool);
};

void ScriptActions::doTeamAvailableForRecruitment(const AsciiString &teamName, Bool availability)
{
    Team *theTeam = TheScriptEngine->getTeamNamed(teamName, false);
    if (!theTeam) {
        return;
    }
    theTeam->setRecruitable(availability);
}
