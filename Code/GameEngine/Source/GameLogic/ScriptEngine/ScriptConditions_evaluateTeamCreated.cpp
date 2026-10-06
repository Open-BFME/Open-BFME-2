// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ScriptConditions::evaluateTeamCreated @0x003E6803 50B. returns the team's isCreated byte (+0x5E), ZH donor shape;
// retail returns an unsigned char (mangled E).
// Same style as the matched ScriptConditions siblings (/O1, TheScriptEngine).
#include "ascii_string.h"
class Parameter
{
public:
    const AsciiString &getString() const { return m_string; }
    int getInt() const { return m_int; }
    unsigned char m_beforeInt[8]; int m_int; float m_real; AsciiString m_string;
    unsigned char m_afterString[8];
};
class Team
{
public:
    bool hasAnyObjects(bool ignoreBuildings);
    int countKind(int kind, bool flagA, bool flagB);
    bool isCreated() const { return m_created; }
    unsigned char m_pad00[0x5E];
    bool m_created;               // +0x5E
    unsigned char m_pad5F[0x128 - 0x5F];
    bool m_flag128;               // +0x128
};
class ScriptEngine
{
public:
    Team *getTeamNamed(AsciiString, bool);
};
extern ScriptEngine *TheScriptEngine;
class ScriptConditions
{
protected:
    unsigned char evaluateTeamCreated(Parameter *);
};
unsigned char ScriptConditions::evaluateTeamCreated(Parameter *teamParm)
{
    Team *team = TheScriptEngine->getTeamNamed(teamParm->getString(), false);
    if (team)
        return team->isCreated();
    return false;
}
