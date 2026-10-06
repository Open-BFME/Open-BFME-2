// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?evaluateTeamHasObjectStatus@ScriptConditions@@IAE_NPAVParameter@@0_N@Z
// @0x003E712A 114B. BFME1 donor ScriptConditionsTeamMembers.cpp
// evaluateTeamHasObjectStatus, member walk through the pinned
// iterate_TeamMemberList 0x00263864 and DLINK advance 0x00263526; BFME2 asks
// the rowed Object::testStatus 0x0004E536 instead of reading the bit array.
#include "ascii_string.h"
enum ObjectStatusTypes { OBJECT_STATUS_NONE = 0 };
class Parameter
{
public:
    const AsciiString &getString() const { return m_string; }
    int getInt() const { return m_int; }
    unsigned char m_beforeInt[8]; int m_int; float m_real; AsciiString m_string;
    unsigned char m_afterString[8];
};
class Object
{
public:
    bool testStatus(ObjectStatusTypes status) const;
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
};
extern ScriptEngine *TheScriptEngine;
class ScriptConditions
{
protected:
    bool evaluateTeamHasObjectStatus(Parameter *, Parameter *, bool);
};
bool ScriptConditions::evaluateTeamHasObjectStatus(Parameter *teamParm, Parameter *statusParm, bool entireTeam)
{
    Team *team = TheScriptEngine->getTeamNamed(teamParm->getString(), false);
    if (!team)
        return false;
    for (DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList(); !iter.done(); iter.advance())
    {
        Object *obj = iter.cur();
        if (!obj)
            return false;
        bool has = obj->testStatus((ObjectStatusTypes)statusParm->getInt());
        if (entireTeam && !has)
            return false;
        else if (!entireTeam && has)
            return true;
    }
    if (entireTeam)
        return true;
    return false;
}
