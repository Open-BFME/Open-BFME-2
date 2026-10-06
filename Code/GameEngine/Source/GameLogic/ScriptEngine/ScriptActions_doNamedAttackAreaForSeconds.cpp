// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ScriptActions::doNamedAttackAreaForSeconds, retail 0x003C83AD, 114 bytes.
// Target identity: initActionTemplates index 0x30 (48) is
// NAMED_ATTACK_AREA_FOR_SECONDS; executeAction case 0x30 passes three
// parameters and calls VA 0x007C83AD. The full target body resolves the named
// unit and trigger area, reads AIUpdateInterface at Object+0x258, leaves the
// old group, calls aiAttackArea through the +0x20 command subobject, then calls
// pinned ScriptEngine::setSequentialTimer at 0x203FCF. The target factor at
// VA 0xDBA4E4 is 5, independently read from the BFME2 data image.
// Donor facts: Zero Hour ScriptActionsNamedUnitAttack.cpp and BFME1
// ScriptActions.cpp identify this action and the sequence of area attack then
// sequential timer; the target global factor is established from retail data.

extern int g_Va00DBA4E4;

#include "ascii_string.h"


class Object;
class PolygonTrigger;
enum CommandSourceType { CMD_FROM_SCRIPT = 1 };

class ScriptEngine
{
public:
    Object *getUnitNamed(const AsciiString &);
    PolygonTrigger *getQualifiedTriggerAreaByName(AsciiString);
    void setSequentialTimer(Object *, int);
};
extern ScriptEngine *TheScriptEngine;

class AICommandInterface
{
public:
    void aiAttackArea(const PolygonTrigger *, CommandSourceType);
};

class AIUpdateInterface
{
public:
    char m_pad00[0x20];
    AICommandInterface m_commandInterface;
};

class Object
{
public:
    AIUpdateInterface *getAIUpdateInterface()
    {
        return *(AIUpdateInterface **)((char *)this + 0x258);
    }
    void leaveGroup();
};

class ScriptActions
{
protected:
    void doNamedAttackAreaForSeconds(const AsciiString &, const AsciiString &, int);
};

void ScriptActions::doNamedAttackAreaForSeconds(const AsciiString &unitName,
                                                 const AsciiString &areaName,
                                                 int seconds)
{
    Object *theSrcUnit = TheScriptEngine->getUnitNamed(unitName);
    if (!theSrcUnit) {
        return;
    }
    PolygonTrigger *trigger = TheScriptEngine->getQualifiedTriggerAreaByName(areaName);
    if (!trigger) {
        return;
    }
    AIUpdateInterface *aiUpdate = theSrcUnit->getAIUpdateInterface();
    if (!aiUpdate) {
        return;
    }
    theSrcUnit->leaveGroup();
    aiUpdate->m_commandInterface.aiAttackArea(trigger, CMD_FROM_SCRIPT);
    int framesPerSecond = g_Va00DBA4E4;
    TheScriptEngine->setSequentialTimer(theSrcUnit, seconds * framesPerSecond);
}
