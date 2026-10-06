// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?evaluateTeamCountCompare@ScriptConditions@@IAE_NPAVParameter@@00@Z, retail 0x003e5e2f, 78 bytes. Banked partial (score 0.82) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// Target adaptation of the BFME1 ScriptConditions::evaluateTeamCountCompare.
// Target boundary 0x003E5E2F (78 bytes): getTeamNamed, then Team's three-arg
// count helper, then a signed comparison of countParm against that result.

typedef bool Bool;

#include "ascii_string.h"

class Parameter
{
public:
    const AsciiString &getString() const { return m_string; }
    int getInt() const { return m_int; }
    unsigned char m_beforeInt[8];
    int m_int;
    float m_real;
    AsciiString m_string;
};

class Team
{
public:
    int countKind(int kind, Bool includeContained, Bool includeDead);
};

class ScriptEngine
{
public:
    Team *getTeamNamed(AsciiString name, Bool exact);
};

class ScriptConditions
{
protected:
    Bool evaluateTeamCountCompare(Parameter *, Parameter *, Parameter *);
};

extern ScriptEngine *TheScriptEngine;

Bool ScriptConditions::evaluateTeamCountCompare(
    Parameter *teamParm, Parameter *countParm, Parameter *kindParm)
{
    Team *team = TheScriptEngine->getTeamNamed(
        teamParm->getString(), false);
    if (team) {
        int kind = kindParm->getInt();
        if (countParm->getInt() < team->countKind(kind, false, true)) {
            return true;
        }
        return false;
    }
    return false;
}
