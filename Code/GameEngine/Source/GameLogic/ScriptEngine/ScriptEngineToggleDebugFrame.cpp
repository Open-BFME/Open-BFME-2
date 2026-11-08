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
	bool rva00203B08();
	bool rva00203AE5();
	bool rva0020424FF();
	char m_pad00[0x1A4D9];
private:
	bool m_flag; // +0x1A4D9
};

#include "../../../Include/GameLogic/ScriptEngine.h"

void ScriptEngine::rva002064D0()
{
    bool forcePause = ((Rva00203B08 *)this)->rva0020424FF();
    m_1A4D9 = !m_1A4D9;
    if (m_1A4D9)
        AppendDebugMessage(AsciiString("Stepping logic frames."), forcePause);
    else
        AppendDebugMessage(AsciiString("Stepping client frames."), forcePause);
}
