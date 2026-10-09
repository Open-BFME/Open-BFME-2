// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva003E7F3A@ScriptConditions@@IAE_NPAVParameter@@0@Z retail 0x003E7F3A 155 bytes.
// Evidence: leaf free stdcall ret 8 two Parameter args; caller 0x003EBEC7; prev/next same cl;
// calls rowed getUnitNamed 0x003588E7 via g_Va009FE16C plus StringBase copy 0x365F0 plus releaseBuffer 0x36410 plus IAT strcmpi; isEmpty plus str plus strcmpi==0 shape.
#include "ascii_string.h"

class Parameter
{
public:
    const AsciiString &getString() const { return m_string; }
    unsigned char m_beforeInt[8]; int m_int; float m_real; AsciiString m_string;
    unsigned char m_afterString[8];
};

class Object;
class ScriptEngine
{
public:
    Object *getUnitNamed(Parameter *parameter);
};
extern class ScriptEngine *TheScriptEngine;

class Object
{
public:
    unsigned char m_pad[0x264];
    void *m_ptr264;
};

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *, const char *);

class ScriptConditions
{
protected:
	bool rva003E7F3A(Parameter *p1, Parameter *p2);
};

bool ScriptConditions::rva003E7F3A(Parameter *p1, Parameter *p2)
{
    if (!p1 || !p2)
        return false;
    Object *obj = TheScriptEngine->getUnitNamed(p1);
    if (!obj)
        return false;
    AsciiString tmp = p2->getString();
    if (tmp.isEmpty())
        return false;
    void *holder = obj->m_ptr264;
    if (!holder)
        return false;
    const AsciiString *named = (const AsciiString *)((const char *)holder + 8);
    return _strcmpi(named->str(), tmp.str()) == 0;
}
