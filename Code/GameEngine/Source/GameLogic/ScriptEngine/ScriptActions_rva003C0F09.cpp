// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Retail RVA 0x003C0F09, 59 bytes.
// ?rva003C0F09@ScriptActions@@IAEXABVAsciiString@@H@Z
// Honest address name: ScriptActions team method dispatched from FUN_007ca4be
// (caller at 0x003CD35E). No donor found (BFME1 doTeamSetRepulsor iterates
// members instead). Target evidence: getTeamNamed pin 0x003584E9 with the
// by-value AsciiString temp pattern, then two flag bytes on Team at +0x110
// (set to 1) and +0x111 (set to (param != 0)).
// Prev doTeamExitAll / next doTeamSpinForFramecount share flags and patterns.
#include "ascii_string.h"
typedef bool Bool;

class Team
{
public:
    char m_pad[0x110];
    bool m_unk110;
    bool m_unk111;
};

class ScriptEngine
{
public:
    Team *getTeamNamed(AsciiString, Bool);
};
extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
protected:
    void rva003C0F09(const AsciiString &, int);
};

void ScriptActions::rva003C0F09(const AsciiString &teamName, int value)
{
    Team *team = TheScriptEngine->getTeamNamed((AsciiString &)teamName, false);
    if (!team)
        return;
    team->m_unk110 = true;
    team->m_unk111 = (value != 0);
}
