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
class PolygonTrigger;
class ScriptEngine {
public:
    Team *getTeamNamed(AsciiString name,bool create);
    PolygonTrigger *getQualifiedTriggerAreaByName(AsciiString name);
    char unknown00[0x1A15C];
    unsigned int expiry;
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

// Native3E63CD..3E64A6 RET16. Source guide: ZH ScriptConditions' area
// lookup and six comparisons. Target adds cached tri-state44/expiry48,
// TerrainLogic stamp1910 and ScriptEngine expiry1A15C. Qualified-area and
// measured TerrainLogic-receiver metric27F171 callees are independently rowed.
// The metric's BfmeThingCME spelling is its existing borrowed view; this
// cast describes the native receiver and does not identify TerrainLogic as it.
// Cache owner, original condition name and metric meaning remain unknown.
class BfmeThingCME {public: int rva0027F171(PolygonTrigger *area);};
class TerrainLogic {public: char unknown00[0x1910]; unsigned int stamp;};
extern TerrainLogic *TheTerrainLogic;
struct Rva003E63CDState {char unknown00[0x44];int cached;unsigned int until;};
bool __stdcall Rva003E63CDGet(Rva003E63CDState *state,Parameter *comparison,Parameter *threshold,Parameter *areaName)
{
    PolygonTrigger *area=TheScriptEngine->getQualifiedTriggerAreaByName(areaName->text);
    if (!area) return false;
    if (TheTerrainLogic->stamp<=state->until) {
        if (state->cached==-1) return false;
        if (state->cached==1) return true;
    }
    int value=((BfmeThingCME *)TheTerrainLogic)->rva0027F171(area);
    bool match=false;
    switch(comparison->mode) {
    case 0: match=value<threshold->mode; break;
    case 1: match=value<=threshold->mode; break;
    case 2: match=value==threshold->mode; break;
    case 3: match=value>=threshold->mode; break;
    case 4: match=value>threshold->mode; break;
    case 5: match=value!=threshold->mode; break;
    }
    state->until=TheScriptEngine->expiry;
    if(match) {state->cached=1; return true;}
    state->cached=-1;
    return false;
}
