// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native 0x003E7E54..0x003E7F3A, RET16; ECX is unused on entry.
// Four Parameter pointers have native modes at +8, float values at +C,
// and strings at +10, consistent with the adjacent rowed condition helpers.
// A named team is resolved through verified getTeamNamed(AsciiString,false),
// then the independently rowed Team::rva003A3736 float result is compared
// against the threshold using the six native modes. The Team metric and
// this condition's original spelling remain unknown.
// Source guide: ZH ScriptConditions.cpp's six Parameter comparison cases;
// the target's full branches, parameter order and callees establish this body.
#include "ascii_string.h"
class Parameter {
public:
    char unknown00[8];
    int mode;
    float value;
    AsciiString text;
};
class Team {public: float rva003A3736(float value);};
class ScriptEngine {
public:
    Team *getTeamNamed(AsciiString name,bool create);
};
extern ScriptEngine *TheScriptEngine;
bool __stdcall Rva003E7E54Get(Parameter *teamName,Parameter *comparison,Parameter *threshold,Parameter *input)
{
    if (!teamName || !input || !comparison || !threshold)
        return false;
    Team *team=TheScriptEngine->getTeamNamed(teamName->text,false);
    if (!team) return false;
    float value=team->rva003A3736(input->value);
    switch(comparison->mode) {
    case 0: return value<threshold->value;
    case 1: return value<=threshold->value;
    case 2: return value==threshold->value;
    case 3: return value>=threshold->value;
    case 4: return value>threshold->value;
    case 5: return value!=threshold->value;
    }
    return false;
}
