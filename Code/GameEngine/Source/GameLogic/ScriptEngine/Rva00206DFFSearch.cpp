// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD
//
// ?Rva00206DFF... @0x00206DFF 100B: chain from ??1Rva003B39C7. Builds a local
// Rva003B39C7 via ctor 0x003B39C7, initFromINI with table g_00BE3908, then if
// g_Va009FE16C (ScriptEngine) is set calls Rva00205A2B::rva00205A2B with the
// local as Arg205A2B, then destroys the local via dtor 0x002045AB.
// Evidence: packet disassembly; StringSearch Arg layout matches Rva003B39C7
// strings at +4/+8/+0xC/+0x7C; callers none (leaf chain head).

#include "ascii_string.h"

struct FieldParse;
class INI
{
public:
    void initFromINI(void *what, const FieldParse *table);
};

struct Rva003B39C7
{
    int m00;
    AsciiString m04;
    AsciiString m08;
    AsciiString m0C;
    int m10;
    int m14;
    AsciiString m18[12];
    int m48;
    int m4C[12];
    AsciiString m7C;
    Rva003B39C7();
    ~Rva003B39C7();
};

extern const FieldParse g_00BE3908[];

struct Arg205A2B
{
    char _pad0[4];
    AsciiString m_4;
    AsciiString m_8;
    AsciiString m_C;
    char _pad10[0x7c - 0x10];
    AsciiString m_7c;
};

class Rva00205A2B
{
public:
    void rva00205A2B(Arg205A2B *arg);
};

class ScriptEngine;
extern class ScriptEngine *TheScriptEngine;

void __cdecl Rva00206DFFSearch(INI *ini)
{
    Rva003B39C7 tmp;
    ini->initFromINI(&tmp, g_00BE3908);
    if (TheScriptEngine)
        ((Rva00205A2B *)TheScriptEngine)->rva00205A2B((Arg205A2B *)&tmp);
}
