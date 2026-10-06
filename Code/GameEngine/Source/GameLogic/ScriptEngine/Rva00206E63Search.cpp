// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD
//
// ?Rva00206E63Search@@YAXPAVINI@@@Z @0x00206E63 100B: chain sibling of 0x00206DFF.
// Builds local Rva003B39C7 via ctor 0x003B39C7, initFromINI with table
// g_00BE3908, then if g_Va009FE16C is set calls Rva00205A8D::rva00205A8D with
// the local as Arg205A8D, then dtor 0x002045AB. Evidence: packet disassembly
// identical to 0x00206DFF except callee 0x00205A8D; Arg layout same strings.

#include "ascii_string.h"

class INI;
typedef void (*INIFieldParseProc)(INI *, void *, void *, const void *);
struct FieldParse
{
	const char *token;
	INIFieldParseProc parse;
	const void *userData;
	int offset;
};

class INI
{
public:
    void initFromINI(void *what, const FieldParse *table);
    static void parseAsciiString(INI *ini, void *instance, void *store, const void *userData);
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

// Matched DIR32 references in the two ScriptEngine search rows place this
// FieldParse table at VA 0x00BE3908 (.rdata). Four 16-byte entries plus the
// zero sentinel occupy 0x50 bytes, ending at VA 0x00BE3958 where the HelpText
// token begins. The local literals reproduce the target token text; their
// pointer identity is not asserted. parseAsciiString is rowed at VA 0x0042F11E.
// Target offsets agree with Rva003B39C7's recovered layout.
extern const FieldParse g_00BE3908[] = {
    { "InternalName", &INI::parseAsciiString, 0, 0x0C },
    { "UIName", &INI::parseAsciiString, 0, 0x04 },
    { "UIName2", &INI::parseAsciiString, 0, 0x08 },
    { "HelpText", &INI::parseAsciiString, 0, 0x7C },
    { 0, 0, 0, 0 }
};

struct Arg205A8D
{
    char _pad0[4];
    AsciiString m_4;
    AsciiString m_8;
    AsciiString m_C;
    char _pad10[0x7c - 0x10];
    AsciiString m_7c;
};

class Rva00205A8D
{
public:
    void rva00205A8D(Arg205A8D *arg);
};

class ScriptEngine;
extern class ScriptEngine *TheScriptEngine;

void __cdecl Rva00206E63Search(INI *ini)
{
    Rva003B39C7 tmp;
    ini->initFromINI(&tmp, g_00BE3908);
    if (TheScriptEngine)
        ((Rva00205A8D *)TheScriptEngine)->rva00205A8D((Arg205A8D *)&tmp);
}
