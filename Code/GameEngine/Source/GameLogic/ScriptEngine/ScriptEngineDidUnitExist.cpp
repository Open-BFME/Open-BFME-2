// cl: /Ireference/shims/bfme2_ascii
//
// ?didUnitExist@ScriptEngine@@QAE_NABVAsciiString@@@Z, retail 0x0035743F, 54 bytes.
// Donor: BFME1 ScriptEngine::didUnitExist (reference/open-bfme-1/Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngine_didUnitExist.cpp).
// Target evidence: ScriptEngine named-object vector at +0x1A120/+0x1A124 (8-byte AsciiString+Object* entries, Rva0032C0CADestroyPairs);
// callers at 0x003C502A 0x003CA0EA 0x003E3E21 0x0049ED87 0x0049EE6E test al then bind via 0x00357960 or add via 0x0020A5FF (BFME1 doCreateObject pattern).

#include "ascii_string.h"


class Object;

struct ScriptNamedEntry
{
    AsciiString m_name;
    Object *m_object;
};

class ScriptEngine
{
public:
    bool didUnitExist(const AsciiString &name);
private:
    char m_pad[0x1A120];
    ScriptNamedEntry *m_namedBegin;
    ScriptNamedEntry *m_namedEnd;
    ScriptNamedEntry *m_namedEndAlloc;
};

bool ScriptEngine::didUnitExist(const AsciiString &name)
{
    for (ScriptNamedEntry *it = m_namedBegin; it != m_namedEnd; ++it) {
        if (name.compare(it->m_name) == 0)
            return it->m_object == 0;
    }
    return false;
}
