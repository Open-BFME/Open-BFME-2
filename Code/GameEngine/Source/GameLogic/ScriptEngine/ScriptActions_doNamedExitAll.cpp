// cl: /DNDEBUG /MD /EHsc
//
// ScriptActions::doNamedExitAll, retail 0x003C86C5, 53 bytes.
// Target identity: initActionTemplates index 0x37 (55) is NAMED_EXIT_ALL;
// executeAction case 0x37 calls VA 0x007C86C5. Target resolves the named unit,
// reads AIUpdateInterface at Object+0x258, leaves its current group, and invokes
// pinned aiEvacuate through the command subobject at +0x20 with arguments
// false and command source 1.
// Donor facts: BFME1 ScriptActions.cpp maps this action to doNamedExitAll and
// performs lookup, AI-update validation, leaveGroup, and aiEvacuate(false,
// CMD_FROM_SCRIPT); target call ABI independently supports the helper identities.

class AsciiString;
class Object;
enum CommandSourceType { CMD_FROM_SCRIPT = 1 };

class ScriptEngine
{
public:
    Object *getUnitNamed(const AsciiString &);
};
extern ScriptEngine *TheScriptEngine;

class AICommandInterface
{
public:
    void aiEvacuate(bool, CommandSourceType);
};

class AIUpdateInterface
{
public:
    char m_pad00[0x20];
    AICommandInterface m_command;
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
    void doNamedExitAll(const AsciiString &);
};

void ScriptActions::doNamedExitAll(const AsciiString &unitName)
{
    Object *theTransport = TheScriptEngine->getUnitNamed(unitName);
    if (!theTransport) {
        return;
    }
    AIUpdateInterface *aiUpdate = *(AIUpdateInterface **)((char *)theTransport + 0x258);
    if (!aiUpdate) {
        return;
    }
    theTransport->leaveGroup();
    aiUpdate->m_command.aiEvacuate(false, CMD_FROM_SCRIPT);
}
