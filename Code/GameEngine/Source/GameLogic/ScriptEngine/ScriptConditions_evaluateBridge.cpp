// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ZH donor: GeneralsMD ScriptConditions.cpp evaluateBridgeBroken and
// evaluateBridgeRepaired. Target evidence: the evaluateCondition jump table
// (0x007EC5C0) sends cases 55 and 54 to 0x003E3D95 and 0x003E3DC6, which
// initConditionTemplates names BRIDGE_BROKEN and BRIDGE_REPAIRED. Both test
// the TheTerrainLogic (0x00DFEC50) byte at +0x44 (anyBridgesDamageStatesChanged)
// before looking the bridge up through the rowed getUnitNamed 0x003588E7,
// which takes the Parameter in BFME2, then ask TerrainLogic::isBridgeBroken
// 0x0027D447 or isBridgeRepaired 0x0027D40B.
#include "ascii_string.h"
class Parameter
{
public:
    const AsciiString &getString() const { return m_string; }
    unsigned char m_beforeInt[8]; int m_int; float m_real; AsciiString m_string;
    unsigned char m_afterString[8];
};
class Object;
class TerrainLogic
{
public:
    bool anyBridgesDamageStatesChanged() { return m_bridgeDamageStatesChanged; }
    bool isBridgeRepaired(const Object *bridge);
    bool isBridgeBroken(const Object *bridge);
    unsigned char m_pad00[0x44];
    bool m_bridgeDamageStatesChanged;
};
extern TerrainLogic *TheTerrainLogic;
class ScriptEngine
{
public:
    Object *getUnitNamed(Parameter *);
};
extern ScriptEngine *TheScriptEngine;
class ScriptConditions
{
protected:
    bool evaluateBridgeBroken(Parameter *);
    bool evaluateBridgeRepaired(Parameter *);
};
bool ScriptConditions::evaluateBridgeBroken(Parameter *pBridgeParm)
{
    if (!TheTerrainLogic->anyBridgesDamageStatesChanged()) {
        return false;
    }
    Object *theBridge = TheScriptEngine->getUnitNamed(pBridgeParm);
    if (theBridge) {
        return (TheTerrainLogic->isBridgeBroken(theBridge));
    }
    return false;
}
bool ScriptConditions::evaluateBridgeRepaired(Parameter *pBridgeParm)
{
    if (!TheTerrainLogic->anyBridgesDamageStatesChanged()) {
        return false;
    }
    Object *theBridge = TheScriptEngine->getUnitNamed(pBridgeParm);
    if (theBridge) {
        return (TheTerrainLogic->isBridgeRepaired(theBridge));
    }
    return false;
}
