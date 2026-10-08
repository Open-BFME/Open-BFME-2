// cl: /Ireference/shims/bfme2_ascii /EHsc
//
// ?getConditionTeamName@Script@@QBE?AVAsciiString@@XZ @0x002041E1 27B: AsciiString getter at +0x44.
// Evidence: same copy-through-pin shape as ParticleSystemTemplate getters 0x00002600 and 0x0000261E;
// callee StringBase copy pin 0x000365F0; callers 0x000DE648 and 0x00209E15 and 0x002DB64E take AsciiString by value.
// Name: ScriptEngine::executeScript (0x00209E15) calls it twice on its Script
// where Zero Hour's executeScript calls Script::getConditionTeamName (a
// by-value AsciiString getter). The setter 0x002041FC beside it keeps its
// address name: a dup_ alias row binds that symbol.

#include "ascii_string.h"


class Script
{
public:
    AsciiString getConditionTeamName() const;

private:
    char pad[0x44];
    AsciiString m_conditionTeamName;   // +0x44
};

AsciiString Script::getConditionTeamName() const
{
    return m_conditionTeamName;
}

struct Rva002041E1
{
    char pad[0x44];
    AsciiString m_name;
    void rva002041FC(AsciiString s);
};

void Rva002041E1::rva002041FC(AsciiString s)
{
    AsciiString &slot = m_name;
    slot = s;
}
