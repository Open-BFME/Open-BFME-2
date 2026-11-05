// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?doSetCaveIndex@ScriptActions@@IAEXABVAsciiString@@H@Z, retail 0x003C0E32 85 bytes.
// Target evidence: ScriptActions dispatch caller at 0x003CD166, AsciiString temp via
// pinned StringBase copy 0x000365F0, ScriptEngine global 0x009FE16C, pinned
// lookupUnitByValue 0x00358752, Object module list at +0x244 with +0x0C iface slot
// 0x40 then slot 0 with int arg, ret 8. Prev/next ScriptActions share flags.
// Donor facts: BFME1 ScriptActions team/unit patterns plus Object +0x244 module
// array precedent; honest address name, second arg int per neighbour shape.
#include "ascii_string.h"

class ScriptEngine;
extern ScriptEngine *TheScriptEngine;

class Rva00358752Opaque
{
public:
    class Object *lookupUnitByValue(AsciiString);
};

class ActionTarget
{
public:
    virtual void apply(int value);
};

#include "../../../Include/GameLogic/Module/BehaviorModule.h"

class Object
{
public:
    char m_pad[0x244];
    BehaviorModule **m_modules;
    __forceinline ActionTarget *getActionTarget() const
    {
        for (BehaviorModule **module = m_modules; *module; ++module)
        {
            ActionTarget *target = static_cast<ActionTarget *>((*module)->slot16());
            if (target)
                return target;
        }
        return 0;
    }
};

class ScriptActions
{
protected:
    void doSetCaveIndex(const AsciiString &, int);
};

// Native3C0E32..3C0E87 proves complete caller and module query;
// target slot16 returns an interface whose slot0 consumes the second arg.
// As in BF1/Object module-interface getters the inline scan returns null.
void ScriptActions::doSetCaveIndex(const AsciiString &name, int value)
{
    Object *obj = ((Rva00358752Opaque *)TheScriptEngine)->lookupUnitByValue(name);
    if (obj)
    {
        ActionTarget *target = obj->getActionTarget();
        if (target)
            target->apply(value);
    }
}
