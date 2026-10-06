// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ScriptConditions::evaluateIsDestroyed @0x003E5DE9 70B. BFME2 also requires the team byte at +0x128 before testing
// !hasAnyObjects(false) (rowed 0x0039E042); ZH donor tests the team only.
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
    bool evaluateIsDestroyed(Parameter *);
};
bool ScriptConditions::evaluateIsDestroyed(Parameter *teamParm)
{
    Team *team = TheScriptEngine->getTeamNamed(teamParm->getString(), false);
    if (team && team->m_flag128)
        return !team->hasAnyObjects(false);
    return false;
}
