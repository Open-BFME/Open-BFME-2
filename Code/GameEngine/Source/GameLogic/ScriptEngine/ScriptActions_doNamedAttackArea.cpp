// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
//
// ScriptActions::doNamedAttackArea, retail 0x003C8351, 92 bytes.
// Target identity: initActionTemplates index 0x2F (47) is NAMED_ATTACK_AREA;
// executeAction case 0x2F calls VA 0x007C8351. Target body resolves the named
// unit via pinned getUnitNamed at 0x3588E7 and the qualified trigger via pinned
// getQualifiedTriggerAreaByName at 0x35768D, reads the AI update pointer at
// Object+0x258, calls pinned Object::leaveGroup at 0x28C01F, then calls pinned
// AICommandInterface::aiAttackArea at 0x36F136 through the subobject at +0x20.
// Donor facts: BFME1 ScriptActions.cpp names this handler doNamedAttackArea and
// performs the same unit/area validation, leaveGroup, and attack-area command.
// Target-specific difference: BFME1 also calls chooseLocomotorSet(NORMAL), but
// the complete BFME2 body has no such call; this recovery follows target bytes.

// The donor AsciiString stores one StringBase<char> pointer. The inline copy
// constructor is carried locally so this handler uses the matched retail
// StringBase copy routine without depending on broader headers.
#include "ascii_string.h"


class PolygonTrigger;
class Object;
enum CommandSourceType { CMD_FROM_SCRIPT = 1 };

class ScriptEngine
{
public:
    Object *getUnitNamed(const AsciiString &);
    PolygonTrigger *getQualifiedTriggerAreaByName(AsciiString);
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
    AIUpdateInterface *getAIUpdateInterface();
    void leaveGroup();
};

class ScriptActions
{
protected:
    void doNamedAttackArea(const AsciiString &, const AsciiString &);
};

void ScriptActions::doNamedAttackArea(const AsciiString &unitName, const AsciiString &areaName)
{
    Object *theSrcUnit = TheScriptEngine->getUnitNamed(unitName);
    if (!theSrcUnit) {
        return;
    }
    PolygonTrigger *trigger = TheScriptEngine->getQualifiedTriggerAreaByName(areaName);
    if (!trigger) {
        return;
    }
    AIUpdateInterface *aiUpdate = *(AIUpdateInterface **)((char *)theSrcUnit + 0x258);
    if (!aiUpdate) {
        return;
    }
    theSrcUnit->leaveGroup();
    aiUpdate->m_commandInterface.aiAttackArea(trigger, CMD_FROM_SCRIPT);
}
