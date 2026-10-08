// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?rva003C062D@ScriptActions@@IAEXABVAsciiString@@M@Z, retail 0x003C062D, 110 bytes.
// Target evidence: dispatched from FUN_007ca4be (caller at 0x003CC3F4) like sibling
// ScriptActions team methods; takes team name plus float, uses pinned
// ScriptEngine::getTeamNamed with by-value AsciiString temp, iterates team members
// via rowed iterate_TeamMemberList and rowed advance, null-checks +0x258/+0x1f0
// chain and conditionally stores float at +0x3c gated by global float.
// Donor facts: none; layout from target bytes only.

typedef bool Bool;

#include "ascii_string.h"

class Object;
class MidTarget
{
public:
    char m_pad[0x3c];
    float m_val;
};

class Mid
{
public:
    char m_pad[0x1f0];
    MidTarget *m_target;
};

class Object
{
public:
    char m_pad[0x258];
    Mid *m_mid;
};

template <class OBJCLASS>
class DLINK_ITERATOR
{
public:
    OBJCLASS *cur() const { return m_cur; }
    void advance();

private:
    OBJCLASS *m_cur;
    void *m_pad2[5];
};

class Team
{
public:
    DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
};

class ScriptEngine
{
public:
    Team *getTeamNamed(AsciiString team, Bool exact);
};
extern class ScriptEngine *TheScriptEngine;
extern float g_Va007C26F0;

class ScriptActions
{
protected:
    void rva003C062D(const AsciiString &, float);
};

void ScriptActions::rva003C062D(const AsciiString &teamName, float value)
{
    Team *team = TheScriptEngine->getTeamNamed(teamName, false);
    if (!team)
        return;
    for (DLINK_ITERATOR<Object> it = team->iterate_TeamMemberList(); it.cur() != 0; it.advance()) {
        Mid *mid = it.cur()->m_mid;
        if (mid == 0)
            break;
        MidTarget *target = mid->m_target;
        if (target == 0)
            break;
        if (value >= g_Va007C26F0)
            target->m_val = value;
    }
}
