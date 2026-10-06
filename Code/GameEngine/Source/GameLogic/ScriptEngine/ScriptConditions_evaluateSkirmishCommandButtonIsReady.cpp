// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?evaluateSkirmishCommandButtonIsReady@ScriptConditions@@MAE_NPAVParameter@@00_N@Z
// @0x003E73E7 183B. BFME1 donor ScriptConditionsTeamMembers.cpp; BFME2
// compares the command type with 0x17 (BFME1 0x16). Callees pinned from this
// call site: ControlBar::findCommandButton 0x0031BE3C on TheControlBar,
// CommandButton::isReady 0x0035B069, Object::hasSpecialPower 0x0028D8EB.
// Retail rereads iter.cur() at each use.
#include "ascii_string.h"
class Parameter
{
public:
    const AsciiString &getString() const { return m_string; }
    unsigned char m_beforeInt[8]; int m_int; float m_real; AsciiString m_string;
    unsigned char m_afterString[8];
};
enum SpecialPowerType { SPECIAL_INVALID = 0 };
class Overridable
{
public:
    const Overridable *friend_getFinalOverride() const;
};
class SpecialPowerTemplate : public Overridable
{
public:
    SpecialPowerType getSpecialPowerType() const { return m_type; }
private:
    unsigned char m_pad[0x1C];
    SpecialPowerType m_type; // +0x1C
};
class Object;
class CommandButton
{
public:
    const SpecialPowerTemplate *getSpecialPowerTemplate() const { return m_specialPower; }
    const void *getUpgradeTemplate() const { return m_upgrade; }
    int getCommandType() const { return m_commandType; }
    bool isReady(const Object *obj) const;
private:
    unsigned char m_pad00[0x14];
    int m_commandType;                         // +0x14
    unsigned char m_pad18[0x24 - 0x18];
    const void *m_upgrade;                     // +0x24
    unsigned char m_pad28[0x44 - 0x28];
    const SpecialPowerTemplate *m_specialPower; // +0x44
};
class ControlBar
{
public:
    const CommandButton *findCommandButton(const AsciiString &name);
};
extern ControlBar *TheControlBar;
class Object
{
public:
    bool hasSpecialPower(SpecialPowerType type) const;
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
    virtual bool evaluateSkirmishCommandButtonIsReady(Parameter *, Parameter *, Parameter *, bool);
};
bool ScriptConditions::evaluateSkirmishCommandButtonIsReady(Parameter *, Parameter *teamParm, Parameter *commandButtonParm, bool allReady)
{
    Team *team = TheScriptEngine->getTeamNamed(teamParm->getString(), false);
    if (!team)
        return false;
    const CommandButton *commandButton = TheControlBar->findCommandButton(commandButtonParm->getString());
    if (!commandButton)
        return false;
    for (DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList(); !iter.done(); iter.advance())
    {
        if (commandButton->getSpecialPowerTemplate())
        {
            const SpecialPowerTemplate *sp = commandButton->getSpecialPowerTemplate();
            const Overridable *finalOverride = sp->friend_getFinalOverride();
            if (!iter.cur()->hasSpecialPower(((const SpecialPowerTemplate *)finalOverride)->getSpecialPowerType()))
                continue;
        }
        else if (!commandButton->getUpgradeTemplate())
        {
            if (commandButton->getCommandType() != 0x17)
                continue;
        }
        if (commandButton->isReady(iter.cur()))
        {
            if (!allReady)
                return true;
        }
        else
        {
            if (allReady)
                return false;
        }
    }
    return allReady;
}
