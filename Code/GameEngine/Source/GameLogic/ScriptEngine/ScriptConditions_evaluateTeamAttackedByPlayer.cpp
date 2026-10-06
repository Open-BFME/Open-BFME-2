// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?evaluateTeamAttackedByPlayer@ScriptConditions@@IAE_NPAVParameter@@0@Z
// @0x003E6784 127B. BFME1 donor ScriptConditionsTeamMembers.cpp
// evaluateTeamAttackedByPlayer: player mask from the ScriptEngine helper
// 0x00357B82 (pinned by this call site), then each member's body (+0x254)
// last DamageInfo (vslot +0x3C) source mask (+0x0C) is compared to it.
#include "ascii_string.h"
class Parameter
{
public:
    const AsciiString &getString() const { return m_string; }
    unsigned char m_beforeInt[8]; int m_int; float m_real; AsciiString m_string;
    unsigned char m_afterString[8];
};
struct DamageInfo
{
    unsigned char m_pad[0xC];
    int m_sourcePlayerMask; // +0x0C
};
class BodyModuleInterface
{
public:
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14();
    virtual const DamageInfo *getLastDamageInfo() const; // slot +0x3C
};
class Object
{
public:
    BodyModuleInterface *getBodyModule() const { return m_body; }
private:
    unsigned char m_pad[0x254];
    BodyModuleInterface *m_body; // +0x254
};
template<class OBJCLASS>
class DLINK_ITERATOR
{
private:
    OBJCLASS *m_cur;
    unsigned char m_targetAbiState[20];
public:
    void advance();
    bool done() const { return m_cur == 0; }
    OBJCLASS *cur() const { return m_cur; }
};
class Team
{
public:
    DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
};
class ScriptEngine
{
public:
    Team *getTeamNamed(AsciiString, bool);
    int rva00357B82(Parameter *playerParm);
};
extern ScriptEngine *TheScriptEngine;
class ScriptConditions
{
protected:
    bool evaluateTeamAttackedByPlayer(Parameter *, Parameter *);
};
bool ScriptConditions::evaluateTeamAttackedByPlayer(Parameter *teamParm, Parameter *playerParm)
{
    Team *team = TheScriptEngine->getTeamNamed(teamParm->getString(), false);
    if (!team)
        return false;
    int mask = TheScriptEngine->rva00357B82(playerParm);
    for (DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList(); !iter.done(); iter.advance())
    {
        Object *cur = iter.cur();
        if (!cur)
            continue;
        BodyModuleInterface *body = cur->getBodyModule();
        if (!body)
            continue;
        const DamageInfo *lastDamageInfo = body->getLastDamageInfo();
        if (!lastDamageInfo)
            continue;
        if (lastDamageInfo->m_sourcePlayerMask == mask)
            return true;
    }
    return false;
}
