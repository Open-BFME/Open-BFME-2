// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ScriptActions::doNamedEnterNamed, retail 0x003C8669, 92 bytes.
// Target identity: initActionTemplates index 0x35 (53) is NAMED_ENTER_NAMED;
// executeAction case 0x35 calls VA 0x007C8669. Target resolves the source unit
// via pinned getUnitNamed at 0x3588E7, then calls an address-derived opaque
// ScriptEngine helper at 0x358752 with the destination name by value; its
// returned pointer is used as the transport. Target reads AIUpdateInterface
// at Object+0x258, leaves the source group, then calls the pinned command at
// 0x26C347 through the +0x20 subobject with the transport and value 1.
// Donor facts: BFME1 ScriptActions.cpp names doNamedEnterNamed and describes
// source/destination validation, leaveGroup and aiEnter. The target call at
// 0x26C347 has an address-derived name because its semantic API identity is
// not independently proven; target behavior establishes its use here.


#include "ascii_string.h"


class Object;

class ScriptEngine
{
public:
    Object *getUnitNamed(const AsciiString &);
};
extern ScriptEngine *TheScriptEngine;

class Rva00358752Opaque
{
public:
    Object *lookupUnitByValue(AsciiString);
};

class Rva0026C347Commands
{
public:
    void Rva0026C347Command(void *, int);
};

class AIUpdateInterface
{
public:
    char m_pad00[0x20];
    Rva0026C347Commands m_command;
};

class Object
{
public:
    __declspec(dllimport) __forceinline AIUpdateInterface *getAIUpdateInterface()
    {
        return *(AIUpdateInterface **)((char *)this + 0x258);
    }
    void leaveGroup();
};

class ScriptActions
{
protected:
    void doNamedEnterNamed(const AsciiString &, const AsciiString &);
};

void ScriptActions::doNamedEnterNamed(const AsciiString &unitSrcName,
                                      const AsciiString &unitDestName)
{
    Object *theSrcUnit = TheScriptEngine->getUnitNamed(unitSrcName);
    if (!theSrcUnit) {
        return;
    }
    Object *theTransport = ((Rva00358752Opaque *)*(ScriptEngine **)&TheScriptEngine)
        ->lookupUnitByValue(unitDestName);
    if (!theTransport) {
        return;
    }
    AIUpdateInterface *aiUpdate = theSrcUnit->getAIUpdateInterface();
    if (!aiUpdate) {
        return;
    }
    theSrcUnit->leaveGroup();
    aiUpdate->m_command.Rva0026C347Command(theTransport, 1);
}
