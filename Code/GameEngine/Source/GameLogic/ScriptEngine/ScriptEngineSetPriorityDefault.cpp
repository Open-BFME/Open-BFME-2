// cl: /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineSetPriorityDefault.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus
// /O1). Compiled that way each body below places uniquely on unclaimed
// game.dat .text by masked whole-.text search, and ./build.sh reproduces it
// byte for byte: ScriptEngine::setPriorityDefault 0x002061D7 (126B). Callee
// addresses are read off retail's call sites (reverse/symbols.csv). Only the
// placed bodies are carried; the donor's other definitions are omitted.

typedef bool Bool;
typedef int Int;

#include "ascii_string.h"

class Parameter
{
public:
    __declspec(dllimport) __forceinline Int getInt(void) const { return m_integer; }
    const AsciiString &getString(void) const { return m_string; }

private:
    char m_unknown[8];
    Int m_integer;
    float m_real;
    AsciiString m_string;
};

class ScriptAction
{
public:
    Parameter *getParameter(Int index)
    {
        if (index >= 0 && index < m_parameterCount)
            return m_parameters[index];
        return 0;
    }

private:
    char m_unknown[8];
    Int m_parameterCount;
    Parameter *m_parameters[12];
};

enum KindOfType { KINDOF_FIRST = 0 };

class ThingTemplate
{
public:
    Bool isKindOf(KindOfType kind) const;
    const ThingTemplate *friend_getNextTemplate() const { return m_nextTemplate; }
private:
    char m_unknown[0x484];
    const ThingTemplate *m_nextTemplate;
};

class ThingFactory
{
public:
    const ThingTemplate *firstTemplate() const { return m_firstTemplate; }
private:
    char m_unknown[0xC];
    const ThingTemplate *m_firstTemplate;
};
extern ThingFactory *TheThingFactory;

class AttackPriorityInfo
{
public:
    void setPriority(const ThingTemplate *thing, Int priority);
    void setDefaultPriority(Int priority) { m_defaultPriority = priority; }

private:
    char m_unknown[8];
    Int m_defaultPriority;
};

#include "../../../Include/GameLogic/ScriptEngine.h"

void ScriptEngine::setPriorityDefault(ScriptAction *action)
{
    AttackPriorityInfo *info = findAttackInfo(action->getParameter(0)->getString(), true);
    if (info == 0)
    {
        AsciiString message("***Error allocating attack priority set - fix or raise limit. ***");
        AppendDebugMessage(message, false);
        return;
    }
    info->setDefaultPriority(action->getParameter(1)->getInt());
}

// ZH ScriptEngine.cpp setPriorityKind and BFME 1 f98983a7d donor provide
// the allocation/template loop. Target accesses and calls establish the
// factory +C, template next +484, and the kind/setPriority helpers.
void ScriptEngine::setPriorityKind(ScriptAction *action)
{
    AttackPriorityInfo *info = findAttackInfo(action->getParameter(0)->getString(), true);
    if (info == 0)
    {
        AsciiString message("***Error allocating attack priority set - fix or raise limit. ***");
        AppendDebugMessage(message, false);
        return;
    }
    KindOfType kind = (KindOfType)action->getParameter(1)->getInt();
    Int priority = action->getParameter(2)->getInt();
    const ThingTemplate *thingTemplate;
    for (thingTemplate = TheThingFactory->firstTemplate(); thingTemplate;
         thingTemplate = thingTemplate->friend_getNextTemplate())
    {
        if (thingTemplate->isKindOf(kind))
            info->setPriority(thingTemplate, priority);
    }
}
