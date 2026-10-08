// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /EHsc
// The Lua print/debug callers declare this logger as bfmeLogMsg574. Retail
// gates on the byte at TheWritableGlobalData + 0x9C1 (0xDFE758), accumulates
// text in a function-local AsciiString, and forwards completed lines to
// TheScriptEngine (0xDFE16C).
#include "ascii_string.h"

class ScriptEngine
{
public:
    void AppendDebugMessage(const AsciiString &message, bool forcePause);
};

class GlobalData;
extern GlobalData *TheWritableGlobalData;
extern ScriptEngine *TheScriptEngine;

void __cdecl bfmeLogMsg574(const char *message)
{
    char *state = (char *)TheWritableGlobalData;
    if (!state[0x9C1])
        return;

// Retail calls the AsciiString constructor from the guarded static initializer.
#pragma inline_depth(0)
    static AsciiString output;
#pragma inline_depth(8)
    ((StringBase<char> *)&output)->concat(message);
    if (output.getLength() <= 80 && !((const StringBase<char> *)&output)->reverseFind('\n'))
        return;

    if (((const StringBase<char> *)&output)->reverseFind('\n'))
        output.removeLastChar();
    TheScriptEngine->AppendDebugMessage(output, false);
    ((StringBase<char> *)&output)->clear();
}
