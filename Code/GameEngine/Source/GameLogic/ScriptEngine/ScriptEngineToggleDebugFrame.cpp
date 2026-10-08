// cl: /O1 /MD /EHsc /Ireference/shims/bfme2_ascii
// Semantic donor: BFME 1 ScriptEngineDebugFrame.cpp at ba7ddda7e8,
// address-named Rva0033E880. Target 0x002064D0..0x00206559 toggles the byte
// at +0x1A4D9 and logs the two identical frame-stepping literals through
// the already rowed ScriptEngine::AppendDebugMessage at 0x00205263.
// Its original method name remains unknown.
#include "ascii_string.h"

// Existing address-derived receiver view for the frame-freeze predicate.
class Rva00203B08
{
public:
    bool rva0020424FF();
};

class ScriptEngine
{
public:
    void rva002064D0();
    void AppendDebugMessage(const AsciiString &message, bool forcePause);

private:
    char m_prefix[0x1A4D9];
    bool m_useLogicDebugFrame;
};

void ScriptEngine::rva002064D0()
{
    bool forcePause = ((Rva00203B08 *)this)->rva0020424FF();
    m_useLogicDebugFrame = !m_useLogicDebugFrame;
    if (m_useLogicDebugFrame)
        AppendDebugMessage(AsciiString("Stepping logic frames."), forcePause);
    else
        AppendDebugMessage(AsciiString("Stepping client frames."), forcePause);
}
