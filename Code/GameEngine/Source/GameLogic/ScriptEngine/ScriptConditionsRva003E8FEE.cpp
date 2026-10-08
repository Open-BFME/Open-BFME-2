// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /O1
// Dump range 18 ScriptConditions trigger-area checks (0x003E8FEE 59B,
// 0x003E9029 57B, adjacent). Sibling of the matched evaluateTeamEnteredArea
// family: Parameter string at +0x10 via getString, ScriptEngine
// getQualifiedTriggerAreaByName, then a manager/lookup gate returning bool.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#include "ascii_string.h"

class Parameter
{
public:
    const AsciiString &getString() const { return m_string; }
    unsigned char m_before[16];
    AsciiString m_string;
};

class PolygonTrigger;

class ScriptEngine
{
public:
    PolygonTrigger *getQualifiedTriggerAreaByName(AsciiString name);
    void *rva00208DB8(AsciiString name);
};
extern ScriptEngine *TheScriptEngine;

class Rva00286772Manager
{
public:
    bool rva00286772(PolygonTrigger *trig, int v);
};
extern Rva00286772Manager *g_00DFEC68;

class Rva002104B6
{
public:
    void *rva002104B6(void *p);
};
struct LivingWorldRva
{
    char m_pad[0xB0];
    Rva002104B6 *m_B0;
};

bool __stdcall Rva003E8FEE(Parameter *parm)
{
    PolygonTrigger *trig = TheScriptEngine->getQualifiedTriggerAreaByName(parm->getString());
    if (!trig)
        return false;
    return g_00DFEC68->rva00286772(trig, 1);
}

bool __stdcall Rva003E9029(const AsciiString *name)
{
    void *p1 = TheScriptEngine->rva00208DB8(*name);
    Rva002104B6 *mgr = (*(LivingWorldRva **)&TheLivingWorldLogic)->m_B0;
    void *p2 = mgr->rva002104B6(p1);
    return p2 != 0;
}
