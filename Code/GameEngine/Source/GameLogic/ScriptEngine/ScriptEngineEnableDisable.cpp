// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /EHsc
// Donor semantic guide: ZH ScriptEngine.cpp enableScript/disableScript;
// BFME1 donor revision f98983a7d. Target independently proves incoming
// ScriptAction* (count+8 and first Parameter*+C), Parameter string+10,
// group active+C, script active+40 and current Team+1A110. BFME2 adds
// enableGenericScript(name, resolveName(name), enabled) to the ZH workflow.
// Existing dispatcher pins name these methods at 204FBB/20507F. Lookup
// receiver names BfmeOwnZC and Rva002046C0Owner remain inherited placeholders.
#include "ascii_string.h"

class Parameter
{
public:
    const AsciiString &getString() const { return m_string; }
private:
    unsigned char m_pad00[0x10];
    AsciiString m_string;
};
class ScriptAction
{
public:
    Parameter *getParameter(int index) const
    {
        return index < m_count ? m_parameters[index] : 0;
    }
private:
    unsigned char m_pad00[8];
    int m_count;
    Parameter *m_parameters[1];
};
class BfmeRoomZC
{
public:
    AsciiString m_name;
};
class Rva002046C0Owner
{
public:
    AsciiString resolveName(const AsciiString &name);
};
class BfmeOwnZC
{
public:
    void *rva00204EBB(BfmeRoomZC name, void *extra);
    void *bfmeRunZC(BfmeRoomZC name, void *extra);
};
struct Rva00204FBBGroup
{
    unsigned char pad00[0xC];
    bool active;
};
struct Rva00204FBBScript
{
    unsigned char pad00[0x40];
    bool active;
};
class Team
{
public:
    bool enableGenericScript(const AsciiString &name, const AsciiString &group, bool enabled);
};
class ScriptEngine
{
protected:
    void enableScript(ScriptAction *action);
    void disableScript(ScriptAction *action);
private:
    unsigned char m_pad00[0x1A110];
    Team *m_currentTeam;
};

void ScriptEngine::enableScript(ScriptAction *action)
{
    AsciiString name = action->getParameter(0)->getString();
    // The by-value lookup argument's one AsciiString is built directly,
    // with no independently live owning-room temporary in retail.
    Rva00204FBBGroup *group = reinterpret_cast<Rva00204FBBGroup *>(
        reinterpret_cast<BfmeOwnZC *>(this)->rva00204EBB(*(BfmeRoomZC *)&name, 0));
    if (group)
        group->active = true;
    Rva00204FBBScript *script = reinterpret_cast<Rva00204FBBScript *>(
        reinterpret_cast<BfmeOwnZC *>(this)->bfmeRunZC(*(BfmeRoomZC *)&name, 0));
    if (script)
        script->active = true;
    if (m_currentTeam)
    {
        AsciiString resolved = reinterpret_cast<Rva002046C0Owner *>(this)->resolveName(name);
        m_currentTeam->enableGenericScript(name, resolved, true);
    }
}

void ScriptEngine::disableScript(ScriptAction *action)
{
    AsciiString name = action->getParameter(0)->getString();
    Rva00204FBBScript *script = reinterpret_cast<Rva00204FBBScript *>(
        reinterpret_cast<BfmeOwnZC *>(this)->bfmeRunZC(*(BfmeRoomZC *)&name, 0));
    if (script)
        script->active = false;
    Rva00204FBBGroup *group = reinterpret_cast<Rva00204FBBGroup *>(
        reinterpret_cast<BfmeOwnZC *>(this)->rva00204EBB(*(BfmeRoomZC *)&name, 0));
    if (group)
        group->active = false;
    if (m_currentTeam)
    {
        AsciiString resolved = reinterpret_cast<Rva002046C0Owner *>(this)->resolveName(name);
        m_currentTeam->enableGenericScript(name, resolved, false);
    }
}
