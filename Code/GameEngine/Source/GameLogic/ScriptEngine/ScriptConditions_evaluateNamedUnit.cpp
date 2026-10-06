// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ZH donor: GeneralsMD ScriptConditions.cpp evaluateNamedUnitDestroyed,
// evaluateNamedUnitExists, evaluateNamedCreated, evaluateNamedUnitDying and
// evaluateNamedUnitTotallyDead. Target evidence: the evaluateCondition jump
// table (0x007EC5C0) sends cases 15, 16, 24, 56 and 57 to 0x003E3DF7,
// 0x003E3E2F, 0x003E3F41, 0x003E3E54 and 0x003E3E89, which
// initConditionTemplates names NAMED_DESTROYED, NAMED_NOT_DESTROYED,
// NAMED_CREATED, NAMED_DYING and NAMED_TOTALLY_DEAD. BFME2 differences: the
// unit lookup takes the Parameter itself (rowed getUnitNamed 0x003588E7), and
// isEffectivelyDead reads bit 0 of the Object byte at +0x438.
#include "ascii_string.h"
class Parameter
{
public:
    const AsciiString &getString() const { return m_string; }
    unsigned char m_beforeInt[8]; int m_int; float m_real; AsciiString m_string;
    unsigned char m_afterString[8];
};
enum NameKeyType
{
};
class Module
{
public:
    virtual void moduleSlot();
};
class Object
{
public:
    bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }
protected:
    Module *findModule(NameKeyType key) const;
public:
    unsigned char m_pad000[0x438];
    unsigned char m_privateStatus;
};
class ObjectWithPub : public Object
{
public:
    using Object::findModule;
};
class GateOpenAndCloseBehaviorView
{
public:
    virtual void gate00();
    virtual void gate01();
    virtual void gate02();
    virtual void gate03();
    virtual void gate04();
    virtual void gate05();
    virtual bool stateIsOne();
};
class NameKeyGenerator
{
public:
    NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;
class ScriptEngine
{
public:
    Object *getUnitNamed(Parameter *);
    bool didUnitExist(const AsciiString &);
};
extern ScriptEngine *TheScriptEngine;
class ScriptConditions
{
protected:
    bool evaluateNamedUnitDestroyed(Parameter *);
    bool evaluateNamedUnitExists(Parameter *);
    bool evaluateNamedCreated(Parameter *);
    bool evaluateNamedUnitDying(Parameter *);
    bool evaluateNamedUnitTotallyDead(Parameter *);
    bool rva003E3EC3(Parameter *);
};
bool ScriptConditions::evaluateNamedUnitDestroyed(Parameter *pUnitParm)
{
    Object *theUnit = TheScriptEngine->getUnitNamed(pUnitParm);
    if (theUnit)
    {
        return theUnit->isEffectivelyDead();
    }

    if (TheScriptEngine->didUnitExist(pUnitParm->getString())) {
        return true;
    }
    return false;
}
bool ScriptConditions::evaluateNamedUnitExists(Parameter *pUnitParm)
{
    Object *theUnit = TheScriptEngine->getUnitNamed(pUnitParm);
    if (theUnit)
    {
        return !theUnit->isEffectivelyDead();
    }

    return false;
}
bool ScriptConditions::evaluateNamedCreated(Parameter *pUnitParm)
{
    return (TheScriptEngine->getUnitNamed(pUnitParm) != 0);
}
bool ScriptConditions::evaluateNamedUnitDying(Parameter *pUnitParm)
{
    Object *theUnit = TheScriptEngine->getUnitNamed(pUnitParm);
    if (theUnit)
    {
        return theUnit->isEffectivelyDead();
    }

    if (TheScriptEngine->didUnitExist(pUnitParm->getString()))
    {
        return false;
    }
    return false;
}
bool ScriptConditions::evaluateNamedUnitTotallyDead(Parameter *pUnitParm)
{
    Object *theUnit = TheScriptEngine->getUnitNamed(pUnitParm);
    if (theUnit) {
        return false;
    }

    if (TheScriptEngine->didUnitExist(pUnitParm->getString())) {
        return true;
    }
    return false;
}

bool ScriptConditions::rva003E3EC3(Parameter *pUnitParm)
{
    Object *theUnit = TheScriptEngine->getUnitNamed(pUnitParm);
    if (theUnit == 0) {
        return false;
    }

    static NameKeyType gateKey = TheNameKeyGenerator->nameToKey("GateOpenAndCloseBehavior");
    Module *module = ((ObjectWithPub *)theUnit)->findModule(gateKey);
    GateOpenAndCloseBehaviorView *gate = module ? reinterpret_cast<GateOpenAndCloseBehaviorView *>(reinterpret_cast<unsigned char *>(module) - 4) : 0;
    if (gate == 0) {
        return false;
    }

    return gate->stateIsOne();
}
