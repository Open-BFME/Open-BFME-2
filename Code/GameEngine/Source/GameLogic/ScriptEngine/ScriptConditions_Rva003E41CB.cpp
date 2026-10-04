// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /arch:SSE2 /O1
// ?Rva003E41CBGet@@YG_NPAVParameter@@@Z
// retail 0x003E41CB 24B leaf free stdcall bool of 1x Parameter ret 4 from 0x003EB3ED. Evidence:
// Parameter string at +0x10 forwarded with true to rowed ScriptEngine::rva00357A97
// const AsciiString plus bool like donor layout; global g_Va009FE16C.
#include "ascii_string.h"

class Parameter
{
public:
    int m_paramType;
    char m_pad04[4];
    int m_int;
    float m_real;
    AsciiString m_string;
};

class ScriptEngine
{
public:
    bool rva00357A97(const AsciiString &s, bool b);
};
extern ScriptEngine *g_Va009FE16C;

bool __stdcall Rva003E41CBGet(Parameter *p)
{
    return g_Va009FE16C->rva00357A97(p->m_string, true);
}
