// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?evaluateSkirmishNamedAreaExists@ScriptConditions@@IAE_NPAVParameter@@0@Z
// @0x003E77FF 46B. BFME1 donor ScriptConditions.cpp (byte-exact in BFME1):
// the qualified trigger lookup on the second parameter is non-null.
#include "ascii_string.h"
class Parameter
{
public:
    const AsciiString &getString() const { return m_string; }
    unsigned char m_beforeInt[8]; int m_int; float m_real; AsciiString m_string;
    unsigned char m_afterString[8];
};
class PolygonTrigger;
class ScriptEngine
{
public:
    PolygonTrigger *getQualifiedTriggerAreaByName(AsciiString name);
};
extern ScriptEngine *TheScriptEngine;
class ScriptConditions
{
protected:
    bool evaluateSkirmishNamedAreaExists(Parameter *, Parameter *);
};
bool ScriptConditions::evaluateSkirmishNamedAreaExists(Parameter *, Parameter *triggerParm)
{
    PolygonTrigger *trigger = TheScriptEngine->getQualifiedTriggerAreaByName(triggerParm->getString());
    return (trigger != 0);
}
