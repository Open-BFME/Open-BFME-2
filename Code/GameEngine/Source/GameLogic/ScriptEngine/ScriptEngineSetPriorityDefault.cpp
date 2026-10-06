// cl: /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineSetPriorityDefault.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus
// /O1). Compiled that way each body below places uniquely on unclaimed
// game.dat .text by masked whole-.text search, and ./build.sh reproduces it
// byte for byte: ScriptEngine::setPriorityDefault 0x002061D7 (126B). Callee
// addresses are read off retail's call sites (reverse/symbols.csv). Only the
// placed bodies are carried; the donor's other definitions are omitted.

typedef bool Bool;
typedef int Int;

#include "ascii_string.h"

class BfmeStringLiteralBase
{
    friend class BFMERetailAsciiString;

private:
    BfmeStringLiteralBase(const char *string);
};

class BFMERetailAsciiString
{
public:
    // Declared only: the donor's inline ctor/dtor were emitted here as
    // private COMDATs that are not retail's bodies for these names.
    BFMERetailAsciiString(const char *string);
    ~BFMERetailAsciiString();

private:
    void releaseBuffer();
    char *m_data;
};

class Parameter
{
public:
    Int getInt(void) const { return m_integer; }
    const AsciiString &getString(void) const { return m_string; }

private:
    char m_unknown[8];
    Int m_integer;
    float m_real;
    AsciiString m_string;
};

class ScriptAction
{
public:
    Parameter *getParameter(Int index)
    {
        if (index >= 0 && index < m_parameterCount)
            return m_parameters[index];
        return 0;
    }

private:
    char m_unknown[8];
    Int m_parameterCount;
    Parameter *m_parameters[12];
};

class AttackPriorityInfo
{
public:
    void setDefaultPriority(Int priority) { m_defaultPriority = priority; }

private:
    char m_unknown[8];
    Int m_defaultPriority;
};

class ScriptEngine
{
public:
    AttackPriorityInfo *findAttackInfo(const AsciiString &name, Bool addIfNotFound);
    void AppendDebugMessage(const AsciiString &message, Bool forcePause);
    void setPriorityDefault(ScriptAction *action);
};

void ScriptEngine::setPriorityDefault(ScriptAction *action)
{
    AttackPriorityInfo *info = findAttackInfo(action->getParameter(0)->getString(), true);
    if (info == 0)
    {
        BFMERetailAsciiString message("***Error allocating attack priority set - fix or raise limit. ***");
        AppendDebugMessage(*(const AsciiString *)&message, false);
        return;
    }
    info->setDefaultPriority(action->getParameter(1)->getInt());
}
